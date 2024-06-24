#include "core/ui/Row.h"

#include <print>

void Tracer::ui::Row::render(int rowIndex, const CellBlockPos& cursorPos, bool rowSelected, unsigned int toggledCellRow, unsigned int toggledCellCol) {
    for (size_t i = 0; i < m_cols; ++i) {
        CellPos cellPos{i, rowIndex};
        CellState cellState;
        cellState.isFocused = cursorPos.row == rowIndex && cursorPos.col == i;
        cellState.isBeingEdited = toggledCellRow == rowIndex && toggledCellCol == i;
        m_cells[i].render(cellPos, cellState, cursorPos);
    }
}
