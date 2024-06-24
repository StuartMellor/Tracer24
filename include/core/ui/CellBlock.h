#ifndef TRACER_CELL_BLOCK_H
#define TRACER_CELL_BLOCK_H

#include "core/render/elements/Box.h"
#include "utils/types.h"

namespace Tracer {
namespace ui {

class CellBlock {
   public:
    CellBlock() : m_cellBlockLoc({0, 0, 0}) {}

    CellBlock(const CellBlockPos& cellBlockLoc, GLfloat width)
        : m_cellBlockLoc(cellBlockLoc),
          m_box(width * 0.18f, 15.0f,
                static_cast<GLfloat>(cellBlockLoc.col * width) + static_cast<GLfloat>(cellBlockLoc.sub * width / 4 + 5),  // Increase row spacing and offset
                static_cast<GLfloat>(cellBlockLoc.row * 20 + 10),                                                         // Increase column spacing and offset
                {1.0f, 1.0f, 1.0f}) {}

    void render(bool isFocused, bool isBeingEdited, bool isRowActive);

   private:
    bool m_isBeingEdited = false;
    Tracer::Box m_box;
    const CellBlockPos& m_cellBlockLoc;
};

}  // namespace ui
}  // namespace Tracer

#endif  // TRACER_CELL_BLOCK_H
