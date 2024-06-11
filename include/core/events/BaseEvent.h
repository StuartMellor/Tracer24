#ifndef TRACER_BASEEVENT_H
#define TRACER_BASEEVENT_H

namespace Tracer {
namespace events {

class BaseEvent {
   public:
    BaseEvent();           // Declare constructor
    virtual ~BaseEvent();  // Declare destructor
    virtual void handleEvent() = 0;
};

}  // namespace events
}  // namespace Tracer

#endif  // TRACER_BASEEVENT_H
