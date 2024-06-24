#ifndef TRACER_UI_CELL_H
#define TRACER_UI_CELL_H

#include <vector>

#include "CellBlock.h"
#include "utils/types.h"

namespace Tracer {
namespace ui {

struct CellState {
    bool isFocused = false;
    bool isBeingEdited = false;
};

class Cell {
   public:
    Cell(const CellPos& cellPos, int numCellBlocks, int cellIndex, GLfloat width, GLfloat displayWidth, GLfloat displayHeight, Tracer::Text& textRenderer)
        : m_cellIndex(cellIndex) {
        for (int i = 0; i < numCellBlocks; ++i) {
            m_cellBlocks.emplace_back(CellBlock({cellPos.row, cellPos.col, i}, width, displayWidth, displayHeight, textRenderer));
        }
    }

    void render(const CellPos& cellLoc, const CellState& cellState, const CellBlockPos& cursorPos);

   private:
    int m_cellIndex;
    std::vector<CellBlock> m_cellBlocks;
};

}  // namespace ui
}  // namespace Tracer

#endif  // TRACER_UI_CELL_H
