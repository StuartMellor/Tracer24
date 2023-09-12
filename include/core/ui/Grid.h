#ifndef TRACER_UI_GRID_H
#define TRACER_UI_GRID_H

#include <vector>

#include "Col.h"
namespace Tracer {
namespace ui {

class Grid {
   public:
    Grid(const int& rows, const int& cols) : m_rows(rows), m_cols(cols){};
    void render();

   private:
    int m_rows = 16;
    int m_cols = 4;
    std::vector<Col> m_cols;
};
}  // namespace ui
}  // namespace Tracer

#endif  // !TRACER_UI_GRID_H