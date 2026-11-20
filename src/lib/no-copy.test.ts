import { EditorState } from "@codemirror/state";
import { EditorView, lineNumbers } from "@codemirror/view";
import { describe, expect, it, vi } from "vitest";

import {
  createNoCopyExtensions,
  isBlockedCopyShortcut,
  NO_COPY_DOM_EVENT_HANDLERS,
} from "@/lib/no-copy";

describe("isBlockedCopyShortcut", () => {
  it("blocks Ctrl/Cmd + C, X, A, S, P, U, Insert regardless of letter case", () => {
    for (const key of [
      "c",
      "C",
      "x",
      "X",
      "a",
      "A",
      "s",
      "S",
      "p",
      "P",
      "u",
      "U",
      "Insert",
      "insert",
    ]) {
      expect(
        isBlockedCopyShortcut({ ctrlKey: true, metaKey: false, key }),
      ).toBe(true);
      expect(
        isBlockedCopyShortcut({ ctrlKey: false, metaKey: true, key }),
      ).toBe(true);
    }
  });

  it("blocks Shift+Delete cut shortcut", () => {
    expect(
      isBlockedCopyShortcut({
        ctrlKey: false,
        metaKey: false,
        shiftKey: true,
        key: "Delete",
      }),
    ).toBe(true);
  });

  it("allows unmodified keys and non-copy modifier shortcuts", () => {
    expect(
      isBlockedCopyShortcut({ ctrlKey: false, metaKey: false, key: "c" }),
    ).toBe(false);
    expect(
      isBlockedCopyShortcut({ ctrlKey: false, metaKey: false, key: "Escape" }),
    ).toBe(false);
    expect(
      isBlockedCopyShortcut({
        ctrlKey: false,
        metaKey: false,
        key: "ArrowDown",
      }),
    ).toBe(false);
    expect(
      isBlockedCopyShortcut({ ctrlKey: true, metaKey: false, key: "r" }),
    ).toBe(false);
    expect(
      isBlockedCopyShortcut({ ctrlKey: false, metaKey: true, key: "w" }),
    ).toBe(false);
    expect(
      isBlockedCopyShortcut({
        ctrlKey: false,
        metaKey: false,
        shiftKey: false,
        key: "Delete",
      }),
    ).toBe(false);
  });
});

describe("createNoCopyExtensions", () => {
  it("configures CodeMirror EditorState as read-only and non-editable", () => {
    const sampleCode = "#include <iostream>\nint main() { return 0; }\n";
    const state = EditorState.create({
      doc: sampleCode,
      extensions: [lineNumbers(), ...createNoCopyExtensions()],
    });

    expect(state.doc.toString()).toBe(sampleCode);
    expect(state.readOnly).toBe(true);
    expect(state.facet(EditorView.editable)).toBe(false);

    const contentAttrs = state.facet(EditorView.contentAttributes);
    const hasAriaReadOnly = contentAttrs.some(
      (attr) =>
        typeof attr === "object" &&
        attr !== null &&
        attr["aria-readonly"] === "true" &&
        attr.unselectable === "on",
    );
    expect(hasAriaReadOnly).toBe(true);
  });

  it("handles empty code documents cleanly", () => {
    const state = EditorState.create({
      doc: "",
      extensions: [lineNumbers(), ...createNoCopyExtensions()],
    });

    expect(state.doc.toString()).toBe("");
    expect(state.readOnly).toBe(true);
  });

  it("blocks copy, cut, contextmenu, selectstart, dragstart, and copy keydowns", () => {
    const preventCopy = vi.fn();
    expect(
      NO_COPY_DOM_EVENT_HANDLERS.copy({
        preventDefault: preventCopy,
      } as unknown as ClipboardEvent),
    ).toBe(true);
    expect(preventCopy).toHaveBeenCalledTimes(1);

    const preventCut = vi.fn();
    expect(
      NO_COPY_DOM_EVENT_HANDLERS.cut({
        preventDefault: preventCut,
      } as unknown as ClipboardEvent),
    ).toBe(true);
    expect(preventCut).toHaveBeenCalledTimes(1);

    const preventContext = vi.fn();
    expect(
      NO_COPY_DOM_EVENT_HANDLERS.contextmenu({
        preventDefault: preventContext,
      } as unknown as MouseEvent),
    ).toBe(true);
    expect(preventContext).toHaveBeenCalledTimes(1);

    const preventSelect = vi.fn();
    expect(
      NO_COPY_DOM_EVENT_HANDLERS.selectstart({
        preventDefault: preventSelect,
      } as unknown as Event),
    ).toBe(true);
    expect(preventSelect).toHaveBeenCalledTimes(1);

    const preventDrag = vi.fn();
    expect(
      NO_COPY_DOM_EVENT_HANDLERS.dragstart({
        preventDefault: preventDrag,
      } as unknown as DragEvent),
    ).toBe(true);
    expect(preventDrag).toHaveBeenCalledTimes(1);

    const blockedPrevent = vi.fn();
    expect(
      NO_COPY_DOM_EVENT_HANDLERS.keydown({
        ctrlKey: true,
        metaKey: false,
        key: "c",
        preventDefault: blockedPrevent,
      } as unknown as KeyboardEvent),
    ).toBe(true);
    expect(blockedPrevent).toHaveBeenCalledTimes(1);

    const insertPrevent = vi.fn();
    expect(
      NO_COPY_DOM_EVENT_HANDLERS.keydown({
        ctrlKey: true,
        metaKey: false,
        key: "Insert",
        preventDefault: insertPrevent,
      } as unknown as KeyboardEvent),
    ).toBe(true);
    expect(insertPrevent).toHaveBeenCalledTimes(1);

    const allowedPrevent = vi.fn();
    expect(
      NO_COPY_DOM_EVENT_HANDLERS.keydown({
        ctrlKey: false,
        metaKey: false,
        key: "ArrowDown",
        preventDefault: allowedPrevent,
      } as unknown as KeyboardEvent),
    ).toBe(false);
    expect(allowedPrevent).not.toHaveBeenCalled();
  });
});
