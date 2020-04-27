//-----------------------------------------------
// Program: Swimming Pixel Slave (ESP32)
// File: CGeometry.h
// Karlsruhe University of Applied Science
// Authors: Patrick Rodinger, Lukas Reimold
// Current Status: Release (22.04.2020)
//------------------------------------------------

class CPoint
{
    public:
        float mX,mY;
        CPoint(){}
        CPoint(float pX, float pY) {mX=pX;mY=pY;}
        void set(float pX, float pY) {mX=pX;mY=pY;}
        void set(CPoint pPoint) {mX = pPoint.mX; mY = pPoint.mY;}
};