
#include "App.h"

#include <chrono>
#include <thread>

#include "core/clock.h"
#include "types.h"

App::App(const int& status) : m_status(status){};

App::~App(){};

int App::run() {
    Clock clockSystem(10, 4, 120.00);  // Assuming '4' as an arbitrary number of columns
    clockSystem.start();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    m_status = TracerStatusCode::EXIT;
    return 0;
}