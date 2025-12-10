#pragma once
#include "EditorMessage.h"
#include "EditorWindow.h"

#include <functional>
#include <unordered_map>

namespace SbEditor {
    class EditorMessageBus {
        std::unordered_map<EditorMessageType, std::vector<EditorWindow*>> subscribers;
    public:
        using Callback = std::function<void(const EditorMessage&)>;

        void SubscribeWindow(EditorMessageType type, EditorWindow* win);
        void DispatchWindowMessage(const EditorMessage& msg) const ;
    };
} 
