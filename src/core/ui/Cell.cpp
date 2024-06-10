#include "core/ui/Cell.h"

#include "core/ui/CellBlock.h"
#include "utils/types.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

void Tracer::ui::Cell::render(const bool colSelected, const bool rowSelected, const CursorPos& cursorPos, const bool cellRowSelected, const int cellCol) {
    ImGui::BeginGroup();
    for (int i = 0; i < Tracer::ui::Cell::m_cellBlocks.size(); ++i) {
        m_cellBlocks[i].render(colSelected && rowSelected, );
    }
    ImGui::EndGroup();
};