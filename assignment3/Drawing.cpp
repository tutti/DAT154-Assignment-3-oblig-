#include "Drawing.h"

RECT Drawing::rc;

void Drawing::setScreenSize(RECT rc) {
    Drawing::rc = rc;
}

void Drawing::drawBackground(HDC hdc) {
    // Draws the grass and roads
    static HPEN nullPen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
    static HBRUSH grassBrush = CreateSolidBrush(RGB(0, 255, 0));
    static HBRUSH roadBrush = CreateSolidBrush(RGB(200, 200, 200));

    HGDIOBJ origPen = SelectObject(hdc, nullPen);
    HGDIOBJ origBrush = SelectObject(hdc, grassBrush);

    Rectangle(hdc, 0, 0, Drawing::rc.right, Drawing::rc.bottom);
    SelectObject(hdc, roadBrush);
    Rectangle(hdc, 0, (Drawing::rc.bottom / 2) - (ROAD_WIDTH / 2), Drawing::rc.right, (Drawing::rc.bottom / 2) + (ROAD_WIDTH / 2));
    Rectangle(hdc, (Drawing::rc.right / 2) - (ROAD_WIDTH / 2), 0, (Drawing::rc.right / 2) + (ROAD_WIDTH / 2), Drawing::rc.bottom);

    SelectObject(hdc, origBrush);
    SelectObject(hdc, origPen);
}

void Drawing::drawTrafficLight(HDC hdc, TrafficLight* tl, int x, int y) {
    static HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
    static HBRUSH greyBrush = CreateSolidBrush(RGB(200, 200, 200));
    static HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
    static HBRUSH yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
    static HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));

    int xPos = (Drawing::rc.right - LIGHT_WIDTH) / 2 + x;
    int yPos = (Drawing::rc.bottom - LIGHT_HEIGHT) / 2 + y;

    HGDIOBJ orig = SelectObject(hdc, blackBrush);
    RoundRect(hdc, xPos, yPos, xPos + LIGHT_WIDTH, yPos + LIGHT_HEIGHT, ROUNDING, ROUNDING);

    if (tl->getState() < 2) {
        SelectObject(hdc, redBrush);
    } else {
        SelectObject(hdc, greyBrush);
    }
    Ellipse(hdc, xPos + MARGIN, yPos + MARGIN, xPos + MARGIN + CIRCLE_SIZE, yPos + MARGIN + CIRCLE_SIZE);

    if (tl->getState() % 2 == 1) {
        SelectObject(hdc, yellowBrush);        
    } else {
        SelectObject(hdc, greyBrush);
    }
    Ellipse(hdc, xPos + MARGIN, yPos + 2*MARGIN + CIRCLE_SIZE, xPos + MARGIN + CIRCLE_SIZE, yPos + 2*MARGIN + 2*CIRCLE_SIZE);

    if (tl->getState() == 2) {
        SelectObject(hdc, greenBrush);
    } else {
        SelectObject(hdc, greyBrush);
    }
    Ellipse(hdc, xPos + MARGIN, yPos + 3*MARGIN + 2*CIRCLE_SIZE, xPos + MARGIN + CIRCLE_SIZE, yPos + 3*MARGIN + 3*CIRCLE_SIZE);

    SelectObject(hdc, orig);
}

void Drawing::drawCar(HDC hdc, Car* car, int direction) {
    static HBRUSH carBrush = CreateSolidBrush(RGB(0, 0, 255));

    int width;
    int height;
    if (direction == DIRECTION_LEFT || direction == DIRECTION_RIGHT) {
        width = car->getLength();
        height = CAR_WIDTH;
    } else {
        width = CAR_WIDTH;
        height = car->getLength();
    }

    int xPos;
    int yPos;
    switch (direction) {
        case DIRECTION_RIGHT:
            xPos = Drawing::rc.right / 2 + car->getLanePosition() - car->getLength();
            yPos = (Drawing::rc.bottom + ROAD_WIDTH / 2 - CAR_WIDTH) / 2;
            break;
        case DIRECTION_UP:
            xPos = (Drawing::rc.right + ROAD_WIDTH / 2 - CAR_WIDTH) / 2;
            yPos = Drawing::rc.bottom / 2 - car->getLanePosition();
            break;
        case DIRECTION_LEFT:
            xPos = Drawing::rc.right / 2 - car->getLanePosition();
            yPos = (Drawing::rc.bottom - ROAD_WIDTH / 2 - CAR_WIDTH) / 2;
            break;
        case DIRECTION_DOWN:
            xPos = (Drawing::rc.right - ROAD_WIDTH / 2 - CAR_WIDTH) / 2;
            yPos = Drawing::rc.bottom / 2 + car->getLanePosition() - car->getLength();
            break;
    }

    HGDIOBJ orig = SelectObject(hdc, carBrush);
    Rectangle(hdc, xPos, yPos, xPos + width, yPos + height);
    SelectObject(hdc, orig);
}

void Drawing::drawLane(HDC hdc, Lane* lane, int direction) {
    for (Car* c = lane->getFirstCar(); c != 0; c = c->getCarBehind()) {
        Drawing::drawCar(hdc, c, direction);
    }
}