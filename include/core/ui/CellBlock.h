#ifndef TRACER_CELL_BLOCK_H
#define TRACER_CELL_BLOCK_H

namespace Tracer {
namespace ui {

class CellBlock {
   public:
    CellBlock() = default;
    void render(bool isFocused, bool isBeingEdited, bool isRowActive);

   private:
    bool m_isBeingEdited = false;
};

}  // namespace ui
}  // namespace Tracer

#endif  // TRACER_CELL_BLOCK_H
