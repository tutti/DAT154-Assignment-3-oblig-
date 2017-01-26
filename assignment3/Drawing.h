#pragma once

#include "TrafficLight.h"
#include "Car.h"
#include "Lane.h"

#define CIRCLE_SIZE 15
#define MARGIN 2
#define ROUNDING 5

#define LIGHT_WIDTH (CIRCLE_SIZE + 2*MARGIN)
#define LIGHT_HEIGHT (3*CIRCLE_SIZE + 4*MARGIN)

#define ROAD_WIDTH 50

#define CAR_WIDTH 15

#define DIRECTION_RIGHT 0
#define DIRECTION_UP 1
#define DIRECTION_LEFT 2
#define DIRECTION_DOWN 3

class Drawing {
private:
    static RECT rc;
public:
    static void setScreenSize(RECT rc);
    static void drawBackground(HDC hdc);
    static void drawTrafficLight(HDC hdc, TrafficLight* tl, int x, int y);
    static void drawCar(HDC hdc, Car* car, int direction);
    static void drawLane(HDC hdc, Lane* lane, int direction);
    static void write(HDC hdc, WCHAR* wc, int x, int y);
};