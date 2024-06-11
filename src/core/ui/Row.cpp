#include "core/ui/Row.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

void Tracer::ui::Row::render(const int rowIndex, const CursorPos& cursorPos, const bool rowSelected, const unsigned int toggledCellRow, const unsigned int toggledCellCol) {
    // Get the draw list for custom drawing
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // Get the current cursor position for the start of the row
    ImVec2 row_start_pos = ImGui::GetCursorScreenPos();

    // Move to the next row
    ImGui::TableNextRow();

    // Get the end position for the row (after moving to the next row)
    ImVec2 row_end_pos = ImGui::GetCursorScreenPos();
    row_end_pos.y += ImGui::GetTextLineHeightWithSpacing();  // Adjust height as needed

    // Highlight the row if needed
    if (rowSelected) {
        draw_list->AddRectFilled(row_start_pos, row_end_pos, ImColor(1.0f, 1.0f, 1.0f, 0.8f));  // Adjust color and alpha as needed
    }

    // Start the group for the cells
    ImGui::BeginGroup();

    for (int i = 0; i < m_cols; ++i) {
        ImGui::TableNextColumn();
        const bool isSelected = cursorPos.col == static_cast<int>(i);
        m_cells[i].render(isSelected, rowSelected, cursorPos, toggledCellRow == rowIndex && toggledCellCol == static_cast<unsigned int>(i));
    }
    ImGui::EndGroup();
}
