#ifndef TRACER_UI_COL_H
#define TRACER_UI_COL_H
#include <vector>

#include "core/ui/Cell.h"
namespace Tracer {
namespace ui {
class Col {
   public:
    Col(const int& rows) : m_rows(rows){};
    void render();

   private:
    int m_rows;
    bool isFocused = false;
    std::vector<Cell> m_cells;
};
}  // namespace ui
}  // namespace Tracer

#endif  // !