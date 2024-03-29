#include "TrafficLight.h"

TrafficLight::TrafficLight(int state, int ticks) {
    this->state = state;
    this->tickCounter = ticks;
}

TrafficLight::TrafficLight(int state) {
    this->state = state;
}

int TrafficLight::getState() {
    return this->state;
}

void TrafficLight::setState(int state) {
    if (state < 0 || state > 4) {
        return;
    }
    this->state = state;
    this->tickCounter = 0;
}

void TrafficLight::tick() {
    static int tickLimits[] = {
        1000, // Red
        100, // Red-yellow
        800, // Green
        100 // Yellow
    };

    if (++this->tickCounter >= tickLimits[this->state]) {
        this->state = (this->state + 1) % 4;
        this->tickCounter = 0;
    }
}