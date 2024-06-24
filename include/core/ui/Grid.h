#ifndef TRACER_UI_GRID_H
#define TRACER_UI_GRID_H

#include <iostream>
#include <vector>

#include "core/ui/Row.h"
#include "utils/types.h"

namespace Tracer {
namespace ui {

class Grid {
   public:
    Grid() = default;
    Grid(const Tracer::TracerData& TracerData, int windowWidth, int windowHeight, Tracer::Text& textRenderer)
        : m_tracerData(const_cast<Tracer::TracerData*>(&TracerData)) {
        GLfloat cellWidth = static_cast<GLfloat>(windowWidth) / m_tracerData->cols;
        for (int i = 0; i < m_tracerData->rows; ++i) {
            m_rowUI.emplace_back(m_tracerData->cols, i, m_tracerData->subCols, cellWidth, windowWidth, windowHeight, textRenderer);
        }
    }

    void render(const CellBlockPos& cursorPos, GridState& gridState);
    void toggleCell(GridState& gridState, int row, int col);
    bool cellToggled(const GridState& gridState) const;

    int getRows() const { return m_tracerData->rows; }
    int getCols() const { return m_tracerData->cols; }
    int getSubCols() const { return m_tracerData->subCols; }

   private:
    std::vector<Row> m_rowUI;
    Tracer::TracerData* m_tracerData;
};

}  // namespace ui
}  // namespace Tracer

#endif  // TRACER_UI_GRID_H
