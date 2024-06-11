#include "core/ui/CellBlock.h"

#include <chrono>
#include <iostream>

#include "imgui.h"

void Tracer::ui::CellBlock::render(bool cursorOver, bool beingEdited) {
    const ImVec2 boxSize = ImVec2(25, 20);

    // Calculate flashing alpha based on time
    auto now = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    float alpha = 0.5f + 0.5f * sin(time * 0.005f);  // Modulate alpha with a sine wave for smooth flashing

    if (beingEdited) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));   // Set button color to transparent
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, alpha));  // Set border color to white with animated alpha
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
        ImGui::Button("++", boxSize);
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(2);
    } else if (cursorOver) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));   // Set button color to transparent
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, alpha));  // Set border color to white with animated alpha
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
        ImGui::Button("--", boxSize);
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(2);
    } else {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));  // Set button color to transparent
        // ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, alpha));  // Set border color to white with animated alpha
        // ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
        ImGui::Button("--", boxSize);
        // ImGui::PopStyleVar();
        ImGui::PopStyleColor();
    }
    ImGui::SameLine();
}
