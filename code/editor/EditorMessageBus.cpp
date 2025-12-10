#include "EditorMessageBus.h"

namespace SbEditor {
    void EditorMessageBus::SubscribeWindow(EditorMessageType type, EditorWindow* win) {
        subscribers[type].push_back(win);
    }

    void EditorMessageBus::DispatchWindowMessage(const EditorMessage& msg) const {
        auto it = subscribers.find(msg._type);
        if(it != subscribers.end()) {
            for (EditorWindow* win : it->second) {
                win->OnMessage(msg);
            }
        }
    }
}