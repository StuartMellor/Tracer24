#include "core/ui/Grid.h"
#include "utils/types.h"

class App {
   public:
    App(Tracer::TracerStatusCode* status) : m_status(status){};
    ~App();
    int run();

   private:
    Tracer::TracerStatusCode* m_status;
    void render();
    void init();
    Tracer::ui::Grid m_grid;
};