#pragma once

#define LANE_WIDTH 25

class Car;
class TrafficLight;

class Lane {
private:
    Car* firstCar = 0;
    Car* lastCar = 0;
    TrafficLight* light = 0;
    int length = 0;
    void addCar();
    void cleanup();
public:
    Lane(TrafficLight* trafficLight);
    void setLength(int length);
    int getLightState();
    Car* getFirstCar();
    Car* getLastCar();
    void tick();
    void attemptSpawn(int chance);
};