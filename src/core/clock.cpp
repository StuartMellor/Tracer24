#include "core/clock.h"

#include <chrono>

Clock::Clock() {
    m_tempo = 120.0f;
    m_steps = 16;
    m_currentStep = 0;
}