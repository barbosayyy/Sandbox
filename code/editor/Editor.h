#pragma once

#include "EditorBase.h"
#include "EditorMessageBus.h"
#include "EditorWindow.h"
#include "Engine/IEngine.h"
#include "ImGui/ImGuiSbContext.h"
#include <memory>

namespace SbEditor {
    class Editor {
    public:
		Editor(Sb::IEngine* sbEngine);

		void Start();

		void Update();

		void Render();

		void Stop();

		const EditorMessageBus& GetMessageBus() const {return _messageBus;}
		
		// UI
		void AddEditorWindow(std::unique_ptr<EditorWindow> win);

		void UIRender();
		
		void UIShowMenu();

		void UISetElementsVisible(u16 visibilityMask) { _uiVisibilityFlags |= visibilityMask; };
		void UISetElementsNonVisible(u16 visibilityMask) { _uiVisibilityFlags &= ~visibilityMask; };

	private:
		int _editorGlobalWindowWidth;
		int _editorGlobalWindowHeight;
		Sb::IEngine* _sbEnginePtr;
		Sb::ImGuiSbContext* _sbImGuiContext;
		u16 _uiVisibilityFlags;
		std::vector<std::unique_ptr<EditorWindow>> _windows;
		EditorMessageBus _messageBus;
    };
}