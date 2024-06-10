#ifndef TRACER_UI_ROW_H
#define TRACER_UI_R0W_H
#include <vector>

#include "core/ui/Cell.h"
#include "utils/types.h"
namespace Tracer {
namespace ui {
class Row {
   public:
    Row(const int& cols, const unsigned int& rowId) : m_cols(cols), m_rowId(rowId) {
        for (int i = 0; i < m_cols; i++) {
            m_cells.push_back(Cell(3, i));
        }
    };
    void render(const int rowIndex, const CursorPos& cursorPos, const bool rowSelected, const unsigned int toggledCellRow, const unsigned int toggledCellCol);

   private:
    int m_cols;
    int m_rowId = -1;
    bool isFocused = false;
    std::vector<Cell> m_cells;
};
}  // namespace ui
}  // namespace Tracer

#endif  // !