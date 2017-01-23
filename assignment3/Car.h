#pragma once

#define CAR_DISTANCE 10

class Lane;

class Car {
friend Lane;
private:
    Car* carInFront = 0;
    Car* carBehind = 0;
    Lane* lane = 0;
    int lanePosition = 0;
    int length = 0;
    void attemptMove();
public:
    Car(int length, int lanePosition, Car* inFront, Lane* lane);
    Car* getCarInFront();
    Car* getCarBehind();
    int getLanePosition();
    int getLength();
    void tick();
};