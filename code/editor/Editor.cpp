#include "Editor.h"
#include "Engine/Engine.h"

namespace SbEditor {
    void Editor::Run() {
        Sb::Engine sbEngine;
        sbEngine.Start();

#ifdef SB_EDITOR
    sbEngine.GetRenderer().GetWindow()->SetWindowTitle("Sandbox Editor");
#endif

        this->SetSbEnginePtr(&sbEngine);

        while(sbEngine.Validate() && !this->ShouldStop()) {
            sbEngine.Update();
            sbEngine.BeginNewFrame();
            
            this->Update();
            this->Render();

            sbEngine.Render();
        }

        this->SetSbEnginePtr(nullptr);
        sbEngine.Stop();
    }

    void Editor::Update() {
        
    }

    void Editor::Render() {

    }
}
