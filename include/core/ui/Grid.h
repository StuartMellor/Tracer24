#ifndef TRACER_UI_GRID_H
#define TRACER_UI_GRID_H

#include <vector>

#include "Row.h"
namespace Tracer {
namespace ui {
class Grid {
   public:
    Grid(const int& rows, const int& cols) : m_rows(rows), m_cols(cols) {
        // initialise m_colData with Col which declares Col(rows, index)
        for (int i = 0; i < m_rows; i++) {
            m_rowData.push_back(Row(m_cols, i));
        }
    };
    void render(const CursorPos& cursorPos);
    int getRows() const { return m_rows; }
    int getCols() const { return m_cols; }
    void toggleCell(const int& row, const int& col) {
        if (m_selectedCol == row && m_selectedRow == col) {
            m_selectedCol = -1;
            m_selectedRow = -1;
            return;
        }
        m_selectedCol = col;
        m_selectedRow = row;
    }

   private:
    int m_rows = 16;
    int m_cols = 4;
    std::vector<Row> m_rowData;
    int m_selectedRow = -1;
    int m_selectedCol = -1;
};
}  // namespace ui
}  // namespace Tracer

#endif  // !TRACER_UI_GRID_H