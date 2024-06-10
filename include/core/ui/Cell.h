#ifndef TRACER_CELL_H
#define TRACER_CELL_H

#include <vector>

#include "core/ui/CellBlock.h"
#include "utils/types.h"

namespace Tracer {
namespace ui {

class Cell {
   public:
    Cell(const int& NModTracks, const int& colId) : m_NModTracks(NModTracks), m_colId(colId) {
        for (int i = 0; i < m_NModTracks; i++) {
            m_cellBlocks.push_back(Tracer::ui::CellBlock());
        }
    }
    void render(const bool colSelected, const bool rowSelected, const CursorPos& cursorPos, const bool cellRowSelected, const int cellCol);
    void select();

   private:
    bool m_isFocused = false;
    bool m_disabled = false;
    bool m_isActive = false;
    int m_selectedCellBlock = -1;
    int m_NModTracks = 3;
    std::vector<Tracer::ui::CellBlock> m_cellBlocks;
    int m_colId = -1;
};
}  // namespace ui
}  // namespace Tracer

#endif  // !TRACER_CELL_H