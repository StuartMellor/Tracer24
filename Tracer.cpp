#include "App.h"

int main(void) {
    Tracer::TracerStatusCode appStatus;
    return App(&appStatus).run();
};
