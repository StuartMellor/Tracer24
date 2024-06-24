#include "core/ui/Grid.h"

#include <iostream>

void Tracer::ui::Grid::render(const CellBlockPos& cursorPos, GridState& gridState) {
    if (m_rowUI.empty()) {
        return;
    }

    for (int i = 0; i < m_rowUI.size(); ++i) {
        m_rowUI[i].render(i, cursorPos, cursorPos.row == i, gridState.selectedRow, gridState.selectedCol);
    }
}

void Tracer::ui::Grid::toggleCell(GridState& gridState, int row, int col) {
    if (gridState.selectedRow == row && gridState.selectedCol == col) {
        gridState.selectedCol = -1;
        gridState.selectedRow = -1;
    } else {
        gridState.selectedCol = col;
        gridState.selectedRow = row;
    }
}

bool Tracer::ui::Grid::cellToggled(const GridState& gridState) const {
    return gridState.selectedRow != -1 && gridState.selectedCol != -1;
}
