#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>

namespace Tracer {
class Box {
   public:
    Box() : m_width(0), m_height(0), m_x(0), m_y(0), m_color{0.0f, 0.0f, 0.0f} {}

    Box(GLfloat width, GLfloat height, GLfloat x, GLfloat y, const std::array<float, 3>& color)
        : m_width(width), m_height(height), m_x(x), m_y(y), m_color(color) {
    }

    void render();

    void updateProperties(float color[3], float borderColor[3], float opacity, bool filled, bool outlined, bool rounded,
                          float radius, float borderThickness, float borderOpacity) {
        for (int i = 0; i < 3; ++i) {
            m_color[i] = color[i];
            m_borderColor[i] = borderColor[i];
        }
        m_opacity = opacity;
        m_filled = filled;
        m_outlined = outlined;
        m_rounded = rounded;
        m_radius = radius;
        m_borderThickness = borderThickness;
        m_borderOpacity = borderOpacity;
    }

   private:
    GLfloat m_width;
    GLfloat m_height;
    GLfloat m_x;
    GLfloat m_y;
    std::array<float, 3> m_color;
    std::array<float, 3> m_borderColor;
    float m_opacity = 1.0f;
    bool m_filled = true;
    bool m_outlined = false;
    bool m_rounded = false;
    float m_radius = 0;
    float m_borderThickness = 1.0f;
    float m_borderOpacity = 1.0f;
};
}  // namespace Tracer