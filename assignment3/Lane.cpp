#include "Lane.h"

#include <stdlib.h>
#include "Car.h"
#include "TrafficLight.h"

void Lane::addCar() {
    // TODO Introduce variable car length (car types?)
    Car* newCar = new Car(15 + (rand() % 40), -(this->length / 2) - 10, this->lastCar, this);
    this->lastCar = newCar;
    if (this->firstCar == 0) {
        this->firstCar = newCar;
    }
}

void Lane::cleanup() {
    // Remove all cars that have "left" the lane (gone outside the screen)
    while (this->firstCar != 0 && this->firstCar->lanePosition - this->firstCar->length > (this->length / 2)) {
        Car* secondCar = this->firstCar->carBehind;
        delete this->firstCar;
        this->firstCar = secondCar;
        if (secondCar != 0) {
            secondCar->carInFront = 0;
        }
    }
}

Lane::Lane(TrafficLight* trafficLight) {
    this->light = trafficLight;
}

void Lane::setLength(int length) {
    this->length = length;
}

int Lane::getLightState() {
    return this->light->getState();
}

Car* Lane::getFirstCar() {
    return this->firstCar;
}

Car* Lane::getLastCar() {
    return this->lastCar;
}

void Lane::tick() {
    // Trigger the tick method for all the cars
    for (Car* c = this->firstCar; c != 0; c = c->getCarBehind()) {
        c->tick();
    }

    // TODO This is testing code
    if (this->count <= 0) {
        this->addCar();
        this->count = 100;
    }
    --this->count;

    // Perform cleanup
    this->cleanup();
}

int Lane::countCars() {
    if (firstCar == 0) return 0;
    int count = 0;
    for (Car* c = firstCar; c != 0; c = c->carBehind) {
        ++count;
    }
    return count;
}