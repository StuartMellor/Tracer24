#ifndef TRACER_CELL_BLOCK_H
#define TRACER_CELL_BLOCK_H
#include <iostream>

namespace Tracer {
namespace ui {
class CellBlock {
   public:
    CellBlock(){};
    void render(bool beingEdited);

   private:
    bool m_beingEdited = false;
};
}  // namespace ui
}  // namespace Tracer

#endif  // !TRACER_CELL_BLOCK_H