#include "core/ui/Row.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

void Tracer::ui::Row::render(const int /*rowIndex*/, const CursorPos& cursorPos, const bool rowSelected, const unsigned int toggledCellRow, const unsigned int toggledCellCol) {
    ImGui::TableNextRow();
    for (int i = 0; i < m_cols; ++i) {
        ImGui::TableNextColumn();
        const bool isSelected = cursorPos.col == i;
        m_cells[i].render(isSelected, rowSelected, cursorPos, toggledCellRow == m_rowId && toggledCellCol);
    }
}