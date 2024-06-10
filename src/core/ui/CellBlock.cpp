#include "core/ui/CellBlock.h"

#include <iostream>

#include "imgui.h"

void Tracer::ui::CellBlock::render(bool beingEdited) {
    const ImVec2 boxSize = ImVec2(20, 20);
    if (beingEdited) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.8f, 0.2f, 1.0f));  // Set button color to green
        ImGui::Button("--", boxSize);
        ImGui::PopStyleColor();
    } else {
        ImGui::Button("--", boxSize);
    }
    ImGui::SameLine();
}