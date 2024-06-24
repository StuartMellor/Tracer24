#include "core/ui/CellBlock.h"

#include <utils/types.h>

#include <chrono>
#include <cmath>

#include "core/render/elements/Box.h"

void Tracer::ui::CellBlock::render(bool isFocused, bool isBeingEdited, bool isRowActive) {
    // if (isBeingEdited) {
    //     auto now = std::chrono::steady_clock::now();
    //     auto time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    //     float alpha = static_cast<float>(sin(time * 0.01) * 0.1 + 0.7);
    // } else if (isFocused && !isRowActive) {
    //     auto now = std::chrono::steady_clock::now();
    //     auto time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    //     float alpha = static_cast<float>(sin(time * 0.007) * 0.1 + 0.6);
    // } else {
    // }
    m_box.render();
}
