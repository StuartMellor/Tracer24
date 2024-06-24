#ifndef TRACER_UI_ROW_H
#define TRACER_UI_ROW_H

#include <vector>

#include "Cell.h"
#include "utils/types.h"

namespace Tracer {
namespace ui {

class Row {
   public:
    Row(int cols, int rowId, int subCols, GLfloat width, GLfloat displayWidth, GLfloat displayHeight, Tracer::Text& textRenderer)
        : m_cols(cols), m_rowId(rowId), m_subCols(subCols) {
        for (int i = 0; i < cols; ++i) {
            m_cells.emplace_back(Cell({rowId, i}, subCols, i, width, displayWidth, displayHeight, textRenderer));
        }
    }

    void render(int rowIndex, const CellBlockPos& cursorPos, bool rowSelected, unsigned int toggledCellRow, unsigned int toggledCellCol);

   private:
    int m_cols;
    int m_subCols;
    int m_rowId;
    std::vector<Cell> m_cells;
};

}  // namespace ui
}  // namespace Tracer

#endif  // TRACER_UI_ROW_H
