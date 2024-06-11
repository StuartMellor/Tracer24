#include "core/ui/Cell.h"

#include "core/ui/CellBlock.h"
#include "utils/types.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

void Tracer::ui::Cell::render(const CellState& cellState, const CursorPos& cursorPos) {
    ImGui::BeginGroup();
    for (size_t i = 0; i < m_cellBlocks.size(); ++i) {
        bool isBlockActive = static_cast<size_t>(cursorPos.sub) == i && cellState.isBeingEdited;
        m_cellBlocks[i].render(cellState.isFocused, isBlockActive, cellState.isBeingEdited);
    }
    ImGui::EndGroup();
}