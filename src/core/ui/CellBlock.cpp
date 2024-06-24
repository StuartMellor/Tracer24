#include "core/ui/CellBlock.h"

#include <chrono>
#include <cmath>

void Tracer::ui::CellBlock::render(bool isFocused, bool isBeingEdited, bool isRowActive) {
    // Render the box
    m_box.render();

    // Save the current OpenGL state
    GLint lastProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &lastProgram);

    // Render the text
    glUseProgram(m_text_renderer.getShaderProgram());  // Activate text shader program
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_text_renderer.render("00", m_box.m_x + m_cellBlockLoc.sub * 3.0f, m_box.m_y, 0.3f, glm::vec3(1.0, 1.0f, 1.0f));
    glDisable(GL_BLEND);

    // Restore the previous OpenGL state
    glUseProgram(lastProgram);
}
