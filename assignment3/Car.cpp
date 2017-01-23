#include "Car.h"
#include "Lane.h"
#include "TrafficLight.h"

void Car::attemptMove() {
    // Check if the car in front is too close.
    // Skip this check if there is no car in front.
    if (this->carInFront != 0) {
        int distance = this->carInFront->lanePosition - this->carInFront->length - this->lanePosition;
        if (distance <= CAR_DISTANCE) {
            return;
        }
    }

    // If the car is at the traffic light, check that it is allowed to go
    if (this->lanePosition == -LANE_WIDTH) {
        if (this->lane->getLightState() != STATE_GO) {
            return;
        }
    }

    // Everything is OK, move one step
    ++this->lanePosition;
}

Car::Car(int length, int lanePosition, Car* inFront, Lane* lane) {
    this->carInFront = inFront;
    if (inFront != 0) {
        inFront->carBehind = this;
    }
    this->lane = lane;
    this->length = length;
    this->lanePosition = lanePosition;
}

Car* Car::getCarInFront() {
    return this->carInFront;
}

Car* Car::getCarBehind() {
    return this->carBehind;
}

int Car::getLanePosition() {
    return this->lanePosition;
}

int Car::getLength() {
    return this->length;
}

void Car::tick() {
    // Perform movement here
    this->attemptMove();
}
