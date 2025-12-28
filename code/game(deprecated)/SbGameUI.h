#pragma once
#include "ImGui/ImGuiSbContext.h"

class SbGameUI {
public:
    static void ShowUI(Sb::ImGuiSbContext& imGuiSbContext);
    static void SetUIVisibility(bool isVisible);
private:
    static bool _uiVisibility;
};