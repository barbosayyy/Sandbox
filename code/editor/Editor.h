#pragma once

#include "EditorBase.h"
#include "EditorMessageBus.h"
#include "EditorWindow.h"
#include "Client/IClient.h"
#include "Engine/IEngine.h"
#include "ImGui/ImGuiSbContext.h"
#include <memory>

namespace SbEditor {
    class Editor : public IClient {
    public:
		Editor(Sb::IEngine* sbEngine);

		void Start() override;

		void Update() override;

		void Render() override;

		void Stop() override;

		void StartProjectManager();

		void StartEditor();
		
		// UI
		void AddEditorWindow(std::unique_ptr<EditorWindow> win);

		void UIRender();
		
		void UIShowMenu();

		void UISetElementsVisible(u16 visibilityMask) { _uiVisibilityFlags |= visibilityMask; };
		void UISetElementsNonVisible(u16 visibilityMask) { _uiVisibilityFlags &= ~visibilityMask; };

		const EditorMessageBus& GetMessageBus() const {return _messageBus;}
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