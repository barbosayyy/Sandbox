#pragma once

#include "EditorBase.h"
#include "Engine/IEngine.h"
#include "ImGui/ImGuiSbContext.h"

namespace SbEditor {
    class Editor {
    public:
		void Setup(Sb::IEngine* sbEngine);

		void Update();

		void Render();

		void Stop();
		
		// UI
		void UIRender();

		void UISetElementsVisible(Sb::u16 visibilityMask) { _uiVisibilityFlags |= visibilityMask; };
		void UISetElementsNonVisible(Sb::u16 visibilityMask) { _uiVisibilityFlags &= ~visibilityMask; };

		void UIShowMenu();
		void UIShowSceneTree();
		void UIShowAssetTree();
		void UIShowAssetExplorer();
		void UIShowInspector();
		
	private:
		int _editorWindowWidth;
		int _editorWindowHeight;
		Sb::IEngine* _sbEnginePtr;
		Sb::ImGuiSbContext* _sbImGuiContext;
		Sb::u16 _uiVisibilityFlags;
    };
}