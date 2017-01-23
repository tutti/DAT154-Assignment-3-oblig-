#include "TrafficLight.h"

TrafficLight::TrafficLight(int state) {
    this->state = state;
}

void TrafficLight::setState(int state) {
    if (state < 0 || state > 4) {
        return;
    }
    this->state = state;
}

void TrafficLight::advanceState() {
    this->state = (state + 1) % 4;
}

int TrafficLight::getState() {
    return this->state;
}
