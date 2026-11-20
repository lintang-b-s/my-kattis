"use client";

import { EditorState } from "@codemirror/state";
import { EditorView, lineNumbers } from "@codemirror/view";
import { useEffect, useRef, useState } from "react";

import {
  createNoCopyExtensions,
  isBlockedCopyShortcut,
} from "@/lib/no-copy";

export interface CodeViewerProblem {
  id: string;
  name: string;
  link: string;
}

interface SolutionCodeApiResponse {
  problemId: string;
  language: string;
  filename: string;
  relativePath: string;
  code: string;
}

interface CodeViewerModalProps {
  problem: CodeViewerProblem | null;
  language: string | null;
  onClose: () => void;
}

export function CodeViewerModal({
  problem,
  language,
  onClose,
}: CodeViewerModalProps) {
  const [code, setCode] = useState<string | null>(null);
  const [filename, setFilename] = useState<string | null>(null);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);

  const editorHostRef = useRef<HTMLDivElement | null>(null);
  const isOpen = problem !== null && language !== null;

  useEffect(() => {
    if (!problem || !language) {
      setCode(null);
      setFilename(null);
      setError(null);
      setLoading(false);
      return;
    }

    const controller = new AbortController();
    setLoading(true);
    setError(null);
    setCode(null);
    setFilename(null);

    const url = `/api/solutions/${encodeURIComponent(problem.id)}/code?lang=${encodeURIComponent(language)}`;

    fetch(url, { signal: controller.signal })
      .then(async (res) => {
        if (!res.ok) {
          let message = `Failed to load code (${res.status}).`;
          try {
            const payload = (await res.json()) as { error?: string };
            if (payload.error) {
              message = payload.error;
            }
          } catch {
            // Fall back to default status message if response is not JSON.
          }
          throw new Error(message);
        }
        const payload = (await res.json()) as SolutionCodeApiResponse;
        if (controller.signal.aborted) {
          return;
        }
        setFilename(payload.filename ?? null);
        setCode(payload.code);
        setLoading(false);
      })
      .catch((err: unknown) => {
        if (err instanceof DOMException && err.name === "AbortError") {
          return;
        }
        setError(
          err instanceof Error ? err.message : "Failed to load solution code.",
        );
        setLoading(false);
      });

    return () => {
      controller.abort();
    };
  }, [problem, language]);

  useEffect(() => {
    if (!isOpen || loading || code === null || !editorHostRef.current) {
      return;
    }

    const state = EditorState.create({
      doc: code,
      extensions: [lineNumbers(), ...createNoCopyExtensions()],
    });

    const view = new EditorView({
      state,
      parent: editorHostRef.current,
    });

    return () => {
      view.destroy();
    };
  }, [isOpen, loading, code]);

  useEffect(() => {
    if (!isOpen) {
      return;
    }

    const prevOverflow = document.body.style.overflow;
    document.body.style.overflow = "hidden";
    window.getSelection()?.removeAllRanges();

    function handleKeyDown(event: KeyboardEvent) {
      if (event.key === "Escape") {
        event.preventDefault();
        onClose();
        return;
      }
      if (isBlockedCopyShortcut(event)) {
        event.preventDefault();
        event.stopPropagation();
        window.getSelection()?.removeAllRanges();
      }
    }

    function blockClipboard(event: ClipboardEvent) {
      event.preventDefault();
      event.stopPropagation();
      window.getSelection()?.removeAllRanges();
    }

    function blockSelectStart(event: Event) {
      event.preventDefault();
      window.getSelection()?.removeAllRanges();
    }

    function clearSelection() {
      const selection = window.getSelection();
      if (selection && !selection.isCollapsed) {
        selection.removeAllRanges();
      }
    }

    window.addEventListener("keydown", handleKeyDown, { capture: true });
    window.addEventListener("copy", blockClipboard, { capture: true });
    window.addEventListener("cut", blockClipboard, { capture: true });
    document.addEventListener("selectstart", blockSelectStart, {
      capture: true,
    });
    document.addEventListener("selectionchange", clearSelection);

    return () => {
      document.body.style.overflow = prevOverflow;
      window.removeEventListener("keydown", handleKeyDown, { capture: true });
      window.removeEventListener("copy", blockClipboard, { capture: true });
      window.removeEventListener("cut", blockClipboard, { capture: true });
      document.removeEventListener("selectstart", blockSelectStart, {
        capture: true,
      });
      document.removeEventListener("selectionchange", clearSelection);
    };
  }, [isOpen, onClose]);

  if (!isOpen) {
    return null;
  }

  return (
    <div
      role="dialog"
      aria-modal="true"
      aria-labelledby="code-viewer-title"
      className="fixed inset-0 z-50 flex items-center justify-center bg-neutral-950/50 p-4 backdrop-blur-[1px] select-none print:hidden"
      onClick={(e) => {
        if (e.target === e.currentTarget) {
          onClose();
        }
      }}
      onCopy={(e) => e.preventDefault()}
      onCut={(e) => e.preventDefault()}
      onContextMenu={(e) => e.preventDefault()}
      onDragStart={(e) => e.preventDefault()}
    >
      <div className="flex h-[82vh] w-full max-w-4xl flex-col overflow-hidden rounded-lg border border-neutral-200 bg-white shadow-xl">
        <div className="flex items-start justify-between gap-4 border-b border-neutral-200 bg-neutral-50 px-5 py-3.5">
          <div className="min-w-0">
            <div className="flex flex-wrap items-center gap-2">
              <h2
                id="code-viewer-title"
                className="truncate text-base font-semibold text-neutral-900"
              >
                {problem.name}
              </h2>
              <span className="inline-block rounded bg-blue-50 px-2 py-0.5 text-xs font-medium text-blue-700 ring-1 ring-inset ring-blue-200">
                {language}
              </span>
            </div>
            <p className="mt-0.5 flex flex-wrap items-center gap-x-2 text-xs text-neutral-500">
              <span className="font-mono">{filename ?? problem.id}</span>
              <span aria-hidden="true">·</span>
              <span>Read-only · Copy disabled</span>
            </p>
          </div>
          <button
            type="button"
            onClick={onClose}
            aria-label="Close code viewer"
            className="rounded-md px-2.5 py-1 text-sm font-medium text-neutral-500 transition-colors hover:bg-neutral-200/70 hover:text-neutral-900"
          >
            Close
          </button>
        </div>

        <div className="relative min-h-0 flex-1 bg-white">
          {loading ? (
            <div className="flex h-full items-center justify-center text-sm text-neutral-500">
              Loading solution code...
            </div>
          ) : error ? (
            <div className="flex h-full items-center justify-center px-6 text-center text-sm text-red-600">
              {error}
            </div>
          ) : (
            <div
              ref={editorHostRef}
              data-testid="codemirror-container"
              className="h-full w-full overflow-hidden"
            />
          )}
        </div>
      </div>
    </div>
  );
}
