#pragma once
#include "ImGui/ImGuiSbContext.h"

namespace SbGame{
    class SbGameUI{
    public:
        static void ShowUI(SbEngine::ImGuiSbContext& imGuiSbContext);
        static void SetUIVisibility(bool isVisible);
    private:
        static bool _uiVisibility;
    };
}