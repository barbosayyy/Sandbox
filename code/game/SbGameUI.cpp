#include "SbGameUI.h"

bool SbGameUI::_uiVisibility = true;

void SbGameUI::ShowUI(Sb::ImGuiSbContext& imGuiSbContext){
    if(_uiVisibility){
        imGuiSbContext.RenderMain(1, 200, "Game Window", 0, 3);
    }
}

void SbGameUI::SetUIVisibility(bool isVisible){
    _uiVisibility = isVisible;
}