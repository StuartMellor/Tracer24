#ifndef TRACER_APP_H
#define TRACER_APP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "core/config/settings.h"
#include "core/events/EventDispatcher.h"
#include "core/ui/Grid.h"
#include "utils/input.h"
#include "utils/types.h"

class App {
   public:
    App(Tracer::TracerStatusCode* status) : dispatcher(), m_settings(), m_cursorPos() {}
    int run();
    Tracer::config::Settings m_settings;

    Tracer::events::EventDispatcher& getDispatcher() {
        return dispatcher;
    };

    void moveCursor(int colMove, int rowMove);

   public:
    Tracer::CellBlockPos m_cursorPos;
    Tracer::ui::Grid m_grid;
    Tracer::GridState gridState;
    bool shiftPressed = false;

   private:
    Tracer::TracerStatusCode* m_status;
    void render();
    void init(int windowWidth, int windowHeight);
    void HandleUtilKeyPress(int key, int scancode, int action, int mods);
    void HandleKeyInput(int key, int scancode, int action, int mods);

    Tracer::utils::Input m_input;

    Tracer::events::EventDispatcher dispatcher;
};

#endif  // !TRACER_APP_H
