#ifndef TRACER_APP_H
#define TRACER_APP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "core/config/settings.h"
#include "core/ui/Grid.h"
#include "utils/input.h"
#include "utils/types.h"

class App {
   public:
    App(Tracer::TracerStatusCode* status) : m_status(status), m_grid(Tracer::ui::Grid(16, 4)){};
    ~App();
    int run();
    Tracer::config::Settings m_settings;

   private:
    Tracer::TracerStatusCode* m_status;
    void render();
    void init();
    void moveCursor(int dir, int modifier);
    void HandleUtilKeyPress(int key, int action);
    Tracer::ui::Grid m_grid;
    Tracer::CursorPos m_cursorPos = {0, 0};
    Tracer::utils::Input m_input;
};

#endif  // !TRACER_APP_H