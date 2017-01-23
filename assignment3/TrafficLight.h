#pragma once

#define STATE_STOP 0
#define STATE_PREPARE 1
#define STATE_GO 2
#define STATE_SLOW 3

class TrafficLight {
private:
    int state = 0;
public:
    TrafficLight(int state);
    void setState(int newState);
    void advanceState();
    int getState();
};