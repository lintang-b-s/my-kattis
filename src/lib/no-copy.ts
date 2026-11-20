import { EditorState, type Extension } from "@codemirror/state";
import { EditorView } from "@codemirror/view";

const BLOCKED_MODIFIER_KEYS = new Set([
  "c",
  "x",
  "a",
  "s",
  "p",
  "u",
  "insert",
]);

export interface ShortcutKeyEvent {
  ctrlKey: boolean;
  metaKey: boolean;
  shiftKey?: boolean;
  key: string;
}

/**
 * Returns true if the keyboard event is a copy, cut, select-all, save, print,
 * or view-source shortcut (Ctrl/Cmd + C/X/A/S/P/U/Insert, or Shift+Delete).
 */
export function isBlockedCopyShortcut(event: ShortcutKeyEvent): boolean {
  const lowerKey = event.key.toLowerCase();
  if ((event.ctrlKey || event.metaKey) && BLOCKED_MODIFIER_KEYS.has(lowerKey)) {
    return true;
  }
  if (event.shiftKey && lowerKey === "delete") {
    return true;
  }
  return false;
}

function clearBrowserSelection(): void {
  if (typeof window !== "undefined") {
    window.getSelection()?.removeAllRanges();
  }
}

export const NO_COPY_DOM_EVENT_HANDLERS = {
  copy(event: ClipboardEvent) {
    event.preventDefault();
    clearBrowserSelection();
    return true;
  },
  cut(event: ClipboardEvent) {
    event.preventDefault();
    clearBrowserSelection();
    return true;
  },
  contextmenu(event: MouseEvent) {
    event.preventDefault();
    return true;
  },
  selectstart(event: Event) {
    event.preventDefault();
    clearBrowserSelection();
    return true;
  },
  dragstart(event: DragEvent) {
    event.preventDefault();
    return true;
  },
  keydown(event: KeyboardEvent) {
    if (isBlockedCopyShortcut(event)) {
      event.preventDefault();
      clearBrowserSelection();
      return true;
    }
    return false;
  },
};

/**
 * Builds CodeMirror 6 extensions that render code read-only and block user
 * text selection, copying, cutting, dragging, context menu, and copy shortcuts.
 */
export function createNoCopyExtensions(): Extension[] {
  return [
    EditorState.readOnly.of(true),
    EditorView.editable.of(false),
    EditorView.contentAttributes.of({
      "aria-readonly": "true",
      unselectable: "on",
    }),
    EditorView.domEventHandlers(NO_COPY_DOM_EVENT_HANDLERS),
    EditorView.theme({
      "&": {
        height: "100%",
        fontSize: "13px",
        backgroundColor: "#ffffff",
        color: "#171717",
        userSelect: "none",
        WebkitUserSelect: "none",
        MozUserSelect: "none",
        WebkitTouchCallout: "none",
      },
      "&.cm-focused": {
        outline: "none",
      },
      ".cm-scroller": {
        overflow: "auto",
        fontFamily:
          "var(--font-mono), ui-monospace, SFMono-Regular, Menlo, monospace",
        lineHeight: "1.6",
        userSelect: "none",
        WebkitUserSelect: "none",
        MozUserSelect: "none",
      },
      ".cm-content": {
        padding: "12px 0",
        caretColor: "transparent",
        cursor: "default",
        userSelect: "none",
        WebkitUserSelect: "none",
        MozUserSelect: "none",
      },
      ".cm-line": {
        padding: "0 16px",
        userSelect: "none",
        WebkitUserSelect: "none",
        MozUserSelect: "none",
      },
      ".cm-gutters": {
        backgroundColor: "#fafafa",
        color: "#a3a3a3",
        borderRight: "1px solid #e5e5e5",
        userSelect: "none",
        WebkitUserSelect: "none",
        MozUserSelect: "none",
      },
      ".cm-lineNumbers .cm-gutterElement": {
        padding: "0 12px 0 16px",
        minWidth: "40px",
      },
      ".cm-selectionBackground, ::selection": {
        backgroundColor: "transparent !important",
      },
    }),
  ];
}
