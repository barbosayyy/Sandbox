#include "SbGameUI.h"

using namespace SbGame;

bool SbGameUI::_uiVisibility = true;

void SbGameUI::ShowUI(SbEngine::ImGuiSbContext& imGuiSbContext){
    if(_uiVisibility){
        imGuiSbContext.RenderMain(1, 200, "Game Window", 0, 3);
    }
}

void SbGameUI::SetUIVisibility(bool isVisible){
    _uiVisibility = isVisible;
}