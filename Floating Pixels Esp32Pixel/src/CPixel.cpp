//-----------------------------------------------
// Program: Swimming Pixel Slave (ESP32)
// File: CPixel.cpp
// Karlsruhe University of Applied Science
// Authors: Patrick Rodinger, Lukas Reimold
// Current Status: Release (22.04.2020)
//------------------------------------------------

#include "CPixel.h"

CPixel::CPixel(float x, float y)
{
    mPosition.mX = x;
    mPosition.mY = y;
}

void CPixel::setPosition(CPoint pPoint){
    mPosition = pPoint;
    updateColor();
}
        
void CPixel::setPosition(String jsonPoint){
    CPoint temp;
    StaticJsonDocument <100> json;
    deserializeJson(json, jsonPoint);
    setPosition(CPoint(json[0], json[1]));
}

int * CPixel::getColor()
{
    return mColor;
}

String CPixel::getPositionString()
{
    return "X: " + String(mPosition.mX) + " Y: " + String(mPosition.mY);
}
String CPixel::getColorString()
{
    return "R: " + String(mColor[0]) + " G: " + String(mColor[1]) + " B: " + String(mColor[2]);
}
void CPixel::setPicture(String & pPicture)
{
    deserializeJson(mPicture, pPicture); //converting input to a json 
}

void CPixel::updateColor()
{
    float widthStep = 1.0 / (float) mPicture["format"]["width"];
    float heigthStep = 1.0 / (float) mPicture["format"]["height"];
    CPoint tempUpperLeft;
    if(mPicture["rgbCoords"].size() == 0) // In case of missing picture data.
    {
        Serial.println("No picture found.");
        return;
    }
    for(int i = 0; i < mPicture["rgbCoords"].size(); i++) // Searching for corresponding color for current position,
    {  
        tempUpperLeft.set((float) mPicture["rgbCoords"][i]["upperLeftCoord"][0], (float) mPicture["rgbCoords"][i]["upperLeftCoord"][1]);
        if(mPosition.mX - tempUpperLeft.mX <= widthStep && tempUpperLeft.mY - mPosition.mY <= heigthStep) // Is my current position inside of this image-pixel?
            {
                setColor(mPicture["rgbCoords"][i]["rgbValue"][0], mPicture["rgbCoords"][i]["rgbValue"][1], mPicture["rgbCoords"][i]["rgbValue"][2]);
                Serial.print("Selected UpperLeft: "); Serial.print(tempUpperLeft.mX);Serial.print(" | "); Serial.println(tempUpperLeft.mY);
                return;
            }
    }
    Serial.print("No matching image-pixel found for this position: "); Serial.print(mPosition.mX);Serial.print(" | "); Serial.println(mPosition.mY);;;
}
void CPixel::updateColor(String & pPicture)
{
    setPicture(pPicture);
    updateColor();
}