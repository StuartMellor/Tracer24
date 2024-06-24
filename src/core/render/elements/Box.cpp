#include "core/render/elements/Box.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

void Tracer::Box::render() {
    // Disable shader program
    glUseProgram(0);

    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Render filled box
    glBegin(GL_QUADS);
    glColor4f(m_color[0], m_color[1], m_color[2], m_opacity);  // Set color for filled box
    glVertex2f(m_x, m_y);
    glVertex2f(m_x + m_width, m_y);
    glVertex2f(m_x + m_width, m_y + m_height);
    glVertex2f(m_x, m_y + m_height);
    glEnd();

    // Render outline if necessary
    if (m_outlined) {
        glLineWidth(m_borderThickness);
        glBegin(GL_LINE_LOOP);
        glColor4f(m_borderColor[0], m_borderColor[1], m_borderColor[2], m_borderOpacity);  // Set color for outline
        glVertex2f(m_x, m_y);
        glVertex2f(m_x + m_width, m_y);
        glVertex2f(m_x + m_width, m_y + m_height);
        glVertex2f(m_x, m_y + m_height);
        glEnd();
    }

    // Reset color to white after rendering
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    // Disable blending
    glDisable(GL_BLEND);

    // Check for any OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << error << std::endl;
    }
}
