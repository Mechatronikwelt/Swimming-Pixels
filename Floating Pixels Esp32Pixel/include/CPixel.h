//-----------------------------------------------
// Program: Swimming Pixel Slave (ESP32)
// File: CPixel.h
// Karlsruhe University of Applied Science
// Authors: Patrick Rodinger, Lukas Reimold
// Current Status: Release (22.04.2020)
//------------------------------------------------

#ifndef CPIXEL_H
#define CPIXEL_H

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include "CGeometry.h"

class CPixel
{
    private:
        CPoint mPosition;
        int mColor [3];
        StaticJsonDocument <25000> mPicture;
    public:
        CPixel(float x, float y);
        //Sets position of the pixel with CPoint(mX, mY)
        void setPosition(CPoint pPoint); 
        //Sets position of the pixel with a jsonPoint(['xPos', 'yPos'];)
        void setPosition(String jsonPoint);
        //Gets the curent color of the pixel as [R,G,B]-Array
        int * getColor();
        // Sets mPicture-JSON and updates displayed color
        void setPicture(String & pPicture);
        //Sets displayed color
        void setColor(int r, int g, int b) {mColor[0] = r; mColor[1] = g; mColor[2] = b;}
        //Sets displayed color
        void setColor(int rgb [3]) {setColor(rgb[0], rgb[1], rgb[2]);}
        //Gets current position as string
        String getPositionString();
        //Gets current color as string
        String getColorString();
        //Updates displayed color with mPicture and mPosition
        void updateColor();
        //Updates displayed color with a new picture and mPosition
        void updateColor(String & pPicture);
};
#endif