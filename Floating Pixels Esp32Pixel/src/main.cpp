//-----------------------------------------------
// Program: Swimming Pixel Slave (ESP32)
// File: Main
// Karlsruhe University of Applied Science
// Authors: Patrick Rodinger, Lukas Reimold
// Current Status: Release (22.04.2020)
//------------------------------------------------

#include <WiFi.h>
#include <MQTT.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "CPixel.h"

//-------------------Creating pixel with position parameters----------------------
CPixel pixel(0.75,0.75);

//-----------------------Defines for OLED display---------------------------------
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET    false // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//------------------------Defines for Neo-Pixel ring ------------------------------
#define LED_PIN   18  // Which pin on the Arduino is connected to the NeoPixels? // On a Trinket or Gemma we suggest changing this to 1:
#define LED_COUNT 15 // How many NeoPixels are attached to the Arduino?
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

//---------------------------Defines Wifi Connection ------------------------------
const char ssid[] = "ObiWlanKenobi";  // Enter hotspot name
const char pass[] = "12344321";   // Enter hotspot password
const char MQTT_BROKER_ADDRESS[] = "192.168.137.1"; //Enter the IPv4-Adress of the MQTT Broker

WiFiClient net;
MQTTClient client(25000); //sets maximum message-size to ~25kB

//-------------------------------Defines MQTT topics------------------------------
const char TOPIC_PIXEL_RGB_COORDS[] = "pixel/rgbCoords";
const char TOPIC_PIXEL_POSITION[] = "pixel/position";

//-----------------------------Function Prototypes----------------------------------
///Function to set every LED of the NeoPixel to one color
void setEveryPixelColor(int * pColor);

//Function to establish connection to WiFi and MQTT
void connect();

//Function gets called on receiving a message via MQTT
void messageReceived(String &topic, String &input);

//-----------------------------Display-Helper-Functions----------------------------------
void clearDisplay()
{
  display.clearDisplay();
  display.setCursor(0,0);
}

void printlnAndDisplay(String msg)
{
  display.println(msg);
  display.display();

}

void printAndDisplay(String msg)
{
  display.print(msg);
  display.display();
}

void updateDisplay()
{
  clearDisplay();
  display.println("Connected to Broker."); display.println("");
  display.println("Current position: "); display.println(pixel.getPositionString()); display.println("");
  display.println("Current color: "); display.println(pixel.getColorString()); display.println("");
  display.display();
}

void log(String message)
{
  Serial.println(message.c_str());
}

//-----------------------gets called on startup--------------------
void setup() 
{
  Serial.begin(115200);

  //------------------------OLED-Display--------------------------

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  //------------------------Neo Pixel-------------------------------
  strip.begin();
  strip.show();
  
  //--------------------WIFI & MQTT Connection----------------------------
  
  client.begin(MQTT_BROKER_ADDRESS, net); //Set the IP address directly.
  client.onMessage(messageReceived); //Set wich function to call on receiving a MQTT message

  connect(); //connect to WiFi and MQTT
}


void loop() {
  client.loop(); // function to check for new message arrivals

  if (!client.connected()) { // in case of connection loss, the client reconnects
    connect();
    updateDisplay();
  }
    delay(500);
}

//Sets every LED of the Neo Pixel strip to one color
void setEveryPixelColor(int * pColor)
{
   for( int i=0; i<LED_COUNT; i++) 
    {
      strip.setPixelColor(i , pColor[0], pColor[1], pColor[2]); // (Led-number, Color)
    }
    strip.show();
}

void messageReceived(String &topic, String &input) {

//-----------------------if clauses between topics----------------------------------
 
  if (topic == TOPIC_PIXEL_RGB_COORDS)
    pixel.updateColor(input); //updates color inside pixel object
  else if(topic == TOPIC_PIXEL_POSITION)  // topic to test different position parameters (ireleveant in release version)
    pixel.setPosition(input);
  setEveryPixelColor(pixel.getColor()); // function to update neo pixel strip
  updateDisplay();
}

void connect() {
// Checking WiFi-Connection
  int i=0;
  log("Checking wifi");
  clearDisplay();
  printlnAndDisplay("Checking wifi");
  
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    printAndDisplay(".");
    i++;
          if ( i== 20)
      {
        clearDisplay();
        display.println("Checking wifi");
        i=0;
      }   
  }

  log("\nConnected!");
  display.println("");
  printlnAndDisplay("Connected!");
  delay(2000);
  //--------------------Connection to Broker---------------
  log("\nConnecting to Broker");
  clearDisplay();
  printlnAndDisplay("Connecting to Broker");
  
  while (!client.connect(WiFi.macAddress().c_str(), "try", "try")) {
    Serial.print(".");
    printAndDisplay(".");
    i++;
          if ( i== 20)
      {
        clearDisplay();
        display.println("Connecting to Broker");
        i=0;
      }   
  }

  log("\nConnected!");
  display.println("");
  printlnAndDisplay("Connected!");
  delay(2000);
  //---------------Subscribe to Topics--------------------
  client.subscribe(TOPIC_PIXEL_RGB_COORDS);
  client.subscribe(TOPIC_PIXEL_POSITION);

  updateDisplay();
}
