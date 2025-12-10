#pragma once

#include "Core/Base.h"
namespace SbEditor {
    
    enum class EditorMessageType {
        SceneTreeSelect,
        AssetBrowserSelect
    };

    struct EditorMessage {
        EditorMessageType _type;
        explicit EditorMessage(EditorMessageType type) : _type(type) {}
        virtual ~EditorMessage() = default;
    };

    struct EditorSceneTreeSelectMessage : public EditorMessage {
        Sb::Entity _entityID;
        EditorSceneTreeSelectMessage(Sb::Entity entityID) : EditorMessage(EditorMessageType::SceneTreeSelect), _entityID(entityID) {}
    };
}