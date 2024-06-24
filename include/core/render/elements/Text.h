#ifndef TEXT_H
#define TEXT_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <map>
#include <string>

namespace Tracer {

struct Character {
    GLuint TextureID;    // ID handle of the glyph texture
    glm::ivec2 Size;     // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;      // Offset to advance to next glyph
};

class Text {
   public:
    Text() = default;
    Text(const std::string& fontPath, GLuint windowWidth, GLuint windowHeight);
    void render(const std::string& text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    GLuint getShaderProgram() const;  // Add this method

   private:
    std::map<GLchar, Character> Characters;
    GLuint VAO, VBO;
    GLuint shaderProgram;
    glm::mat4 projection;
};

}  // namespace Tracer

#endif  // TEXT_H
