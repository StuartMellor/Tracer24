#include "core/ui/CellBlock.h"

#include <chrono>

#include "imgui.h"

void Tracer::ui::CellBlock::render(bool isFocused, bool isBeingEdited, bool isRowActive) {
    const ImVec2 boxSize = ImVec2(25, 20);

    if (isBeingEdited) {
        auto now = std::chrono::steady_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        float alpha = 10 * sin(time * 0.01);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.0f, 1.0f, alpha));
        ImGui::Button("++", boxSize);
        ImGui::PopStyleColor();
    } else if (isFocused) {
        auto now = std::chrono::steady_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        float alpha = 10.0f * sin(time * 0.005) - 4.0f;
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, alpha));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
        ImGui::Button("--", boxSize);
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(2);
    } else {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImGui::Button("--", boxSize);
        ImGui::PopStyleColor();
    }

    ImGui::SameLine();
}
