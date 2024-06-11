#include "core/events/BaseEvent.h"

#include <iostream>

Tracer::events::BaseEvent::BaseEvent() {
    std::cout << "BaseEvent constructor" << std::endl;
};

Tracer::events::BaseEvent::~BaseEvent() {
    std::cout << "BaseEvent destructor" << std::endl;
};

void Tracer::events::BaseEvent::handleEvent() {
    std::cout << "BaseEvent handleEvent" << std::endl;
};