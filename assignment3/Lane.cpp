#include "Lane.h"

#include "Car.h"
#include "TrafficLight.h"

int count = 0;

void Lane::addCar() {
    // TODO Introduce variable car length (car types?)
    Car* newCar = new Car(25, -200, this->lastCar, this);
    this->lastCar = newCar;
    if (this->firstCar == 0) {
        this->firstCar = newCar;
    }
    ++this->cars;
}

void Lane::cleanup() {
    // Remove all cars that have "left" the lane (gone outside the screen)
    while (this->firstCar != 0 && this->firstCar->lanePosition + this->firstCar->length > (this->length / 2)) {
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
    if (count <= 0) {
        this->addCar();
        count = 100;
    }
    --count;

    // Perform cleanup
    //this->cleanup();
}

int Lane::countCars() {
    return this->cars;
}