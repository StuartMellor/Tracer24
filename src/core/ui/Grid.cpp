#include "core/ui/Grid.h"

#include "imgui.h"

void Tracer::ui::Grid::render() {
    ImGui::BeginGroup();
    for (Col col : m_cols) {
        col.render();
    }
    ImGui::EndGroup();
};
