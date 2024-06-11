#include "App.h"
#include "utils/types.h"

int main() {
    Tracer::TracerStatusCode status;
    App app(&status);
    return app.run();
}