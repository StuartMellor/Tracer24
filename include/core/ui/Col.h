#ifndef TRACER_UI_COL_H
#define TRACER_UI_COL_H

#include <vector>

#include "core/ui/Cell.h"

namespace Tracer {
namespace ui {
class Col {
   public:
    Col(const int& rows, const unsigned int& trackId) : m_rows(rows), m_trackId(trackId) {
        for (unsigned int i = 0; i < m_rows; i++) {
            m_cells.push_back(Cell(3, i));
        }
    };

    void render(int selectedCell);

   private:
    int m_rows;
    int m_trackId = -1;
    bool isFocused = false;
    std::vector<Cell> m_cells;
};
}  // namespace ui
}  // namespace Tracer

#endif  // !TRACER_UI_COL_H