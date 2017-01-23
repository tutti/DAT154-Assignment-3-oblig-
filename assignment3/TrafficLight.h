#pragma once

#define STATE_STOP 0
#define STATE_PREPARE 1
#define STATE_GO 2
#define STATE_SLOW 3

class TrafficLight {
private:
    int tickCounter = 0;
    int state = 0;
public:
    TrafficLight(int state, int ticks);
    TrafficLight(int state);
    int getState();
    void setState(int newState);
    void tick();
};