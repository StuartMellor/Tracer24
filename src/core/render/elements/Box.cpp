#include "core/render/elements/Box.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

void Tracer::Box::render() {
    glBegin(GL_QUADS);
    glColor4f(m_color[0], m_color[1], m_color[2], m_opacity);
    glVertex2f(m_x, m_y);
    glVertex2f(m_x + m_width, m_y);
    glVertex2f(m_x + m_width, m_y + m_height);
    glVertex2f(m_x, m_y + m_height);
    glEnd();

    if (m_outlined) {
        glLineWidth(m_borderThickness);
        glBegin(GL_LINE_LOOP);
        glColor4f(m_borderColor[0], m_borderColor[1], m_borderColor[2], m_borderOpacity);
        glVertex2f(m_x, m_y);
        glVertex2f(m_x + m_width, m_y);
        glVertex2f(m_x + m_width, m_y + m_height);
        glVertex2f(m_x, m_y + m_height);
        glEnd();
    }
};