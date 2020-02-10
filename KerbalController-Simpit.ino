#include "KerbalSimpit.h"
#include <Button.h>
KerbalSimpit mySimpit(Serial);      //Establishing a connection to the Plugin

//analog pins
const byte pTHROTTLE = A0; //slide pot
const byte pTX = A2;       //translation x-axis
const byte pTY = A1;       //translation y-axis
const byte pTZ = A3;       //translation z-axis
const byte pRX = A5;       //rotation x-axis
const byte pRY = A4;       //rotation y-axis
const byte pRZ = A6;       //rotation z-axis

//digital pins
const byte dataPin = 2;      //DS - blue
const byte clockPin = 4;     //SH_CP - yellow
const byte latchPin = 3;     //ST_CP - pink
const byte maxthrottle = 5;  //Max Throttle button
const byte minthrottle = 6;  //Min Throttle button
const byte motoron = 8;      //Motor on pin (L293D pin 1)
const byte motorup = 9;      //Motor up pin
const byte motordown = 10;   //Motor down pin 
const byte touchReceive = 11;//Receive pin for Capacitance Sensing Circuit 
const byte touchSend = 12;   //Send pin for Capacitance Sensing Circuit
const byte pMODE = 66;       //mode switch (used for debug mode)
//Display 1 RX1  blue
//Display 1 TX1  yellow
//Display 2 RX2  blue
//Display 2 TX2  yellow
const byte pABORT = 22;      //Abort switch (safety switch, active high)
const byte pARM = 23;        //Arm switch (safety switch, active high)
const byte pSTAGE = 24;      //Stage button
const byte pSAS = 25;        //SAS switch
const byte pRCS = 26;        //RCS switch
const byte pprecision = 27;  //Precision Control Switch
const byte pLIGHTS = 28;     //Lights button
const byte pLIGHTSLED = 29;  //Lights button LED
const byte pBRAKES = 30;     //Brakes button
const byte pBRAKESLED = 31;  //Brakes button LED
const byte pGEARS = 32;      //Gears button
const byte pGEARSLED = 33;   //Gears button LED
const byte pSOLAR = 34;      //Solar button (action group 9)
const byte pSOLARLED = 35;   //Solar button LED
const byte pLADDER = 38;     //Ladder button (action group 7)
const byte pLADDERLED = 39;  //Ladder button LED
const byte pCHUTES = 36;     //Chutes button (action group 8)
const byte pCHUTESLED = 37;  //Chutes button LED
const byte pACTION6 = 40;    //Action Group 6 button
const byte pACTION6LED = 41; //Action Group 6 button LED
const byte pACTION5 = 42;    //Action Group 5 button
const byte pACTION5LED = 43; //Action Group 5 button LED
const byte pACTION4 = 44;    //Action Group 4 button
const byte pACTION4LED = 45; //Action Group 4 button LED
const byte pACTION3 = 46;    //Action Group 3 button
const byte pACTION3LED = 47; //Action Group 3 button LED
const byte pACTION2 = 48;    //Action Group 2 button
const byte pACTION2LED = 49; //Action Group 2 button LED
const byte pACTION1 = 50;    //Action Group 1 button
const byte pACTION1LED = 51; //Action Group 1 button LED
const byte pmodeswitch = 52; //rocket mode or plane mode switch
const byte pswitch1 = 62;    //A8 Switch position 1, display mode orbit
const byte pswitch2 = 63;    //A9 Switch position 2, display mode surface
const byte pswitch3 = 64;    //A10 Switch position 3, display mode target/node
const byte pswitch4 = 65;    //A11 Switch position 4, display mode Body Info

//variables used in timing
const int IDLETIMER = 5000;        //if no message received from KSP for more than 5s, go idle (default 2000)
const int CONTROLREFRESH = 10;      //send control packet every 10 ms (default 25)
const int DISPLAYREFRESH = 50;      //refresh Display every 40 ms = 25fps
unsigned long deadtime, deadtimeOld, controlTime, controlTimeOld, displayTime, displayTimeOld = 0;
unsigned long debugtime, debugtimeOld =0, atmotime, atmotimeOld =0;
unsigned long now = 0;

//variables used for display status
byte PageDisplay1 = 0;              //Page display1
byte PageDisplay2 = 0;              //Page display2 

//debug variable
bool debug = false;
int chooseled = 0; 

//variables used for detect bounce buttons
Button debouncerStage(pSTAGE);
Button debouncerLights(pLIGHTS);
Button debouncerBrakes(pBRAKES);
Button debouncerGears(pGEARS);
Button debouncerSolar(pSOLAR);
Button debouncerChutes(pCHUTES);
Button debouncerLadder(pLADDER);
Button debouncerA6(pACTION6);
Button debouncerA5(pACTION5);
Button debouncerA4(pACTION4);
Button debouncerA3(pACTION3);
Button debouncerA2(pACTION2);
Button debouncerA1(pACTION1);


//in-game state used to update button LEDs
bool SAS_on = false;
bool RCS_on = false;
bool Abort_on = false;
bool lights_on = false;
bool ladder_on = false;
bool solar_on = false;
bool gears_on = false;
bool brakes_on = false;
bool chutes_on = false;
bool stage_on = false;
bool action1_on = false;
bool action2_on = false;
bool action3_on = false;
bool action4_on = false;
bool action5_on = false;
bool action6_on = false;

//input value variables
int throttle_value;
int WheelThrottle_value;
int WheelSteer_value;
int tx_value;
int ty_value;
int tz_value;
int rx_value;
int ry_value;
int rz_value;
int flymode = 0;

//variables used for motorfader
int throttletarget;
int theThreshold = 30;

// Variables used for Echo state
bool receivedata = false;
bool scenechange = false;
bool receiveecho = true;
bool echostate = false;
unsigned long nowecho = 0;
unsigned long lastSentEcho = 0;         // A timestamp of the last time we sent an echo packet
unsigned int sendIntervalEcho = 1000;   // How often to send echo packets (in ms)

void setup()  //Starting the Arduino
{
  Serial.begin(230400); // Open the serial connection.
  Serial1.begin(115200);  //Display1 connection
  Serial2.begin(115200);  //Display2 connection
      PageDisplay1 = 0;
      PageDisplay2 = 0; 
      sendToDisplay1(String("page ") + String(PageDisplay1));
      sendToDisplay1(String("boot.txt=\"") + String("booting")+String("\""));
      sendToDisplay2(String("page ") + String(PageDisplay2));
      sendToDisplay2(String("boot.txt=\"") + String("booting")+String("\""));        
//Initialize
  controlsInit();           //set all pin modes
  testLEDS(50);             //blink every LED once to test (with a delay of xx ms)

  //check if debug is on 
  while(!digitalRead(pMODE)){debugfunction();} 
  
      PageDisplay1 = 0;
      PageDisplay2 = 0; 
      sendToDisplay1(String("page ") + String(PageDisplay1));
      sendToDisplay1(String("boot.txt=\"") + String("booting")+String("\""));
      sendToDisplay2(String("page ") + String(PageDisplay2));
      sendToDisplay2(String("boot.txt=\"") + String("booting")+String("\""));     
  
  while(!mySimpit.init())   //Stay in this loop as long as no connection established
  {
    delay(100);    
  }
      PageDisplay1 = 0;
      PageDisplay2 = 0; 
      sendToDisplay1(String("page ") + String(PageDisplay1));
      sendToDisplay1(String("boot.txt=\"") + String("booting complete")+String("\""));
      sendToDisplay2(String("page ") + String(PageDisplay2));
      sendToDisplay2(String("boot.txt=\"") + String("booting complete")+String("\""));
  
  registerInputchannel();    //registering to input Data channels.
  registerOutputchannel();   //registering to input Data channels.
  
  // Sets our callback function. The KerbalSimpit library will
  // call this function every time a packet is received.
  mySimpit.inboundHandler(messageHandler); 
}

void loop() {   //Looping
  //check if debug is on 
  while(!digitalRead(pMODE)){debugfunction();}  
   
  //KSP mode  
  mySimpit.update();       // Check for new serial messages     
  send_control_packet();
  //get_vessel_data();

  }
