#ifndef TRACER_UI_CELL_H
#define TRACER_UI_CELL_H

#include <vector>

#include "CellBlock.h"
#include "imgui.h"
#include "utils/types.h"

namespace Tracer {
namespace ui {

struct CellState {
    bool isFocused = false;
    bool isBeingEdited = false;
};

class Cell {
   public:
    Cell(int numCellBlocks, int cellIndex)
        : m_cellIndex(cellIndex) {
        for (int i = 0; i < numCellBlocks; ++i) {
            m_cellBlocks.emplace_back();
        }
    }

    void render(const CellState& cellState, const CursorPos& cursorPos);

   private:
    int m_cellIndex;
    std::vector<CellBlock> m_cellBlocks;
};

}  // namespace ui
}  // namespace Tracer

#endif  // TRACER_UI_CELL_H
