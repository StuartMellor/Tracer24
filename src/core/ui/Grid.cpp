#include "core/ui/Grid.h"

#include "utils/types.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <iostream>

#include "imgui.h"
#include "imgui_internal.h"

void Tracer::ui::Grid::render(const CursorPos& cursorPos) {
    if (m_rowData.size() == 0) {
        ImGui::Text("No data to render");
        return;
    }

    if (ImGui::BeginTable("Tracer", m_cols + 1, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_ScrollY | ImGuiTableFlags_ScrollX | ImGuiTableFlags_SizingStretchSame)) {
        for (unsigned int i = 0; i < m_rowData.size(); ++i) {
            m_rowData[i].render(i, cursorPos, cursorPos.row == i, m_selectedRow, m_selectedCol);
        }
        ImGui::EndTable();
    }
};

void Tracer::ui::Grid::toggleCell(const int& row, const int& col) {
    {
        if (m_selectedRow == row && m_selectedCol == col) {
            m_selectedCol = -1;
            m_selectedRow = -1;
            std::cout << "Deselecting cell: " << row << "," << col << std::endl;
            return;
        }
        std::cout << "Selecting cell: " << row << ":" << m_selectedRow << "," << col << ":" << m_selectedCol << std::endl;
        m_selectedCol = col;
        m_selectedRow = row;
    }
}
