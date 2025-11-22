#include "EditorApplication.h"
#include "Editor.h"
#include "Engine/Engine.h"

namespace SbEditor {
    void EditorApplication::Run() {
        Sb::Engine sbEngine;
        sbEngine.Start();
        
#ifdef SB_EDITOR
        sbEngine.GetRenderer().GetWindow()->SetWindowTitle("Sandbox Editor");
#endif
        
        Editor sbEditor;
        
        sbEngine.SetUIRenderingEnabled(false);
        
        sbEditor.Setup(&sbEngine);

        while(sbEngine.Validate() && !this->ShouldStop()) {
            sbEngine.Update();
            sbEditor.Update();

            sbEngine.Render();

            sbEditor.Render();
            
            sbEngine.LateRender();
        }

        sbEngine.Stop();
    }
}