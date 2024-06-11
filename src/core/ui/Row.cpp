#include "core/ui/Row.h"

#include "imgui.h"

void Tracer::ui::Row::render(int rowIndex, const CursorPos& cursorPos, bool rowSelected, unsigned int toggledCellRow, unsigned int toggledCellCol) {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 row_start_pos = ImGui::GetCursorScreenPos();

    ImGui::TableNextRow();
    ImVec2 row_end_pos = ImGui::GetCursorScreenPos();
    row_end_pos.y += ImGui::GetTextLineHeightWithSpacing();

    if (rowSelected) {
        draw_list->AddRectFilled(row_start_pos, row_end_pos, ImColor(1.0f, 1.0f, 1.0f, 0.8f));
    }

    ImGui::BeginGroup();
    for (int i = 0; i < m_cols; ++i) {
        ImGui::TableNextColumn();
        CellState cellState;
        cellState.isFocused = cursorPos.row == rowIndex && cursorPos.col == i;
        cellState.isBeingEdited = toggledCellRow == rowIndex && toggledCellCol == i;
        m_cells[i].render(cellState, cursorPos);
    }
    ImGui::EndGroup();
}
