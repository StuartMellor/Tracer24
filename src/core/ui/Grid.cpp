#include "core/ui/Grid.h"

#include <iostream>

#include "imgui.h"
#include "imgui_internal.h"

void Tracer::ui::Grid::render(const CursorPos& cursorPos, GridState& gridState) {
    if (m_rowData.empty()) {
        ImGui::Text("No data to render");
        return;
    }

    if (ImGui::BeginTable("Tracer", m_cols + 1, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_ScrollY | ImGuiTableFlags_ScrollX | ImGuiTableFlags_SizingStretchSame)) {
        for (unsigned int i = 0; i < m_rowData.size(); ++i) {
            m_rowData[i].render(i, cursorPos, cursorPos.row == i, gridState.selectedRow, gridState.selectedCol);
        }
        ImGui::EndTable();
    }
}

void Tracer::ui::Grid::toggleCell(GridState& gridState, int row, int col) {
    if (gridState.selectedRow == row && gridState.selectedCol == col) {
        gridState.selectedCol = -1;
        gridState.selectedRow = -1;
        std::cout << "Deselecting cell: " << row << "," << col << std::endl;
    } else {
        std::cout << "Selecting cell: " << row << "," << col << std::endl;
        gridState.selectedCol = col;
        gridState.selectedRow = row;
    }
}

bool Tracer::ui::Grid::cellToggled(const GridState& gridState) const {
    return gridState.selectedRow != -1 && gridState.selectedCol != -1;
}
