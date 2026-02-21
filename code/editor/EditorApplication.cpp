#include "EditorApplication.h"
#include "Editor.h"
#include "Engine/Engine.h"

namespace SbEditor {
    void EditorApplication::Run() {
        Sb::Engine sbEngine;
        
        Editor sbEditor(&sbEngine);

        sbEngine.SetUIRendering(false);

        sbEditor.StartProjectManager();

        // TODO -> context isnt being reset properly!

        sbEditor.StartEditor();

        sbEngine.Stop();
    }
}