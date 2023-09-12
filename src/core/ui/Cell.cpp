#include "core/ui/Cell.h"

#include "imgui.h"

void Tracer::ui::Cell::render() {
    ImGui::BeginGroup();
    ImGui::Text("--");
    ImGui::Text("--");
    ImGui::Text("--");
    ImGui::EndGroup();
}