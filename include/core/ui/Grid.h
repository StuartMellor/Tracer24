#ifndef TRACER_UI_GRID_H
#define TRACER_UI_GRID_H

#include <vector>

#include "core/ui/Row.h"
#include "utils/types.h"

namespace Tracer {
namespace ui {

class Grid {
   public:
    Grid(int rows, int cols, int subCols)
        : m_rows(rows), m_cols(cols), m_subCols(subCols) {
        for (int i = 0; i < m_rows; ++i) {
            m_rowData.emplace_back(m_cols, i, m_subCols);
        }
    };

    void render(const CursorPos& cursorPos, GridState& gridState);
    void toggleCell(GridState& gridState, int row, int col);
    bool cellToggled(const GridState& gridState) const;

    int getRows() const { return m_rows; }
    int getCols() const { return m_cols; }
    int getSubCols() const { return m_subCols; }

   private:
    int m_rows;
    int m_cols;
    int m_subCols;
    std::vector<Row> m_rowData;
};

}  // namespace ui
}  // namespace Tracer

#endif  // TRACER_UI_GRID_H
