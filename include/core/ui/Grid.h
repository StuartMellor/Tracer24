#ifndef TRACER_UI_GRID_H
#define TRACER_UI_GRID_H

#include <vector>

#include "core/ui/Row.h"
#include "utils/types.h"

namespace Tracer {
namespace ui {

class Grid {
   public:
    Grid(const Tracer::TracerData& TracerData)
        : m_tracerData(const_cast<Tracer::TracerData*>(&TracerData)) {
        for (int i = 0; i < m_tracerData->rows; ++i) {
            m_rowUI.emplace_back(m_tracerData->cols, i, m_tracerData->subCols);
        }
    };

    void render(const CursorPos& cursorPos, GridState& gridState);
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
