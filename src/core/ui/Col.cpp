#include "core/ui/Col.h"

#include "imgui.h"

void Tracer::ui::Col::render() {
    ImGui::BeginGroup();
    for (Cell cell : m_cells) {
        cell.render();
    }
    ImGui::EndGroup();
}