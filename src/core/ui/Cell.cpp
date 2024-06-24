#include "core/ui/Cell.h"

#include "core/ui/CellBlock.h"

void Tracer::ui::Cell::render(const CellPos& cellLoc, const CellState& cellState, const CellBlockPos& cursorPos) {
    for (size_t i = 0; i < m_cellBlocks.size(); ++i) {
        bool isBlockActive = static_cast<size_t>(cursorPos.sub) == i && cellState.isBeingEdited;
        m_cellBlocks[i].render(cellState.isFocused, isBlockActive, cellState.isBeingEdited);
    }
}