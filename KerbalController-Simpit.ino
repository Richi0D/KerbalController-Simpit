#include "KerbalSimpit.h"
#include <Button.h>
#include <Keyboard.h>
#include <Joystick.h>
#include <Nextion.h>

KerbalSimpit mySimpit(Serial);      //Establishing a connection to the Plugin

//analog pins
const byte pTHROTTLE = A0; //slide pot
const byte pTX = A5;       //translation x-axis
const byte pTY = A4;       //translation y-axis
const byte pTZ = A6;       //translation z-axis
const byte pRX = A2;       //rotation x-axis
const byte pRY = A1;       //rotation y-axis
const byte pRZ = A3;       //rotation z-axis

//digital pins
const byte dataPin = 2;      //DS - blue
const byte clockPin = 3;     //SH_CP - yellow
const byte latchPin = 4;     //ST_CP - pink
const byte motoron = 5;      //Motor on pin (L293D pin 1)
const byte motorup = 6;      //Motor up pin
const byte motordown = 7;   //Motor down pin 
const byte maxthrottle = 9;  //Max Throttle button
const byte minthrottle = 8;  //Min Throttle button
const byte pMODE = 51;       //mode switch (used for debug mode)
//Display 1 RX1  blue
//Display 1 TX1  yellow
//Display 2 RX2  blue
//Display 2 TX2  yellow
const byte pABORT = 47;      //Abort switch (safety switch, active high)
const byte pARM = 49;        //Arm switch (safety switch, active high)
const byte pSTAGE = 10;      //Stage button
const byte pSAS = 46;        //SAS switch
const byte pRCS = 48;        //RCS switch
const byte pprecision = 50;  //Precision Control Switch
const byte pLIGHTS = 45;     //Lights button
const byte pLIGHTSLED = 44;  //Lights button LED
const byte pBRAKES = 43;     //Brakes button
const byte pBRAKESLED = 42;  //Brakes button LED
const byte pGEARS = 41;      //Gears button
const byte pGEARSLED = 40;   //Gears button LED
const byte pSOLAR = 39;      //Solar button (action group 9)
const byte pSOLARLED = 38;   //Solar button LED
const byte pLADDER = 35;     //Ladder button (action group 7)
const byte pLADDERLED = 34;  //Ladder button LED
const byte pCHUTES = 37;     //Chutes button (action group 8)
const byte pCHUTESLED = 36;  //Chutes button LED
const byte pACTION6 = 33;    //Action Group 6 button
const byte pACTION6LED = 32; //Action Group 6 button LED
const byte pACTION5 = 31;    //Action Group 5 button
const byte pACTION5LED = 30; //Action Group 5 button LED
const byte pACTION4 = 29;    //Action Group 4 button
const byte pACTION4LED = 28; //Action Group 4 button LED
const byte pACTION3 = 27;    //Action Group 3 button  
const byte pACTION3LED = 26; //Action Group 3 button LED
const byte pACTION2 = 25;    //Action Group 2 button
const byte pACTION2LED = 24; //Action Group 2 button LED
const byte pACTION1 = 23;    //Action Group 1 button
const byte pACTION1LED = 22; //Action Group 1 button LED
const byte pmodeswitch = 52; //rocket mode or plane mode switch
const byte pswitch1 = 62;    //A8 Switch position 1, display mode orbit
const byte pswitch2 = 63;    //A9 Switch position 2, display mode surface
const byte pswitch3 = 64;    //A10 Switch position 3, display mode target/node
const byte pswitch4 = 65;    //A11 Switch position 4, display mode Body Info

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

/*Deactivate Joystick and use Simpit
// Create a joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  0, 0,                  // Button Count, Hat Switch Count
  true, true, true,      // X, Y, Z Axis
  true, true, true,      // Rx, Ry, Rz Axis
  false, true,           // rudder, throttle
  false, false, false);  // accelerator, brake, steering
*/

//debug variable
bool debug = false;
int chooseled = 0; 

//variables used in timing
const int IDLETIMER = 4000;        //if no message received from KSP for more than 5s, go idle (default 2000)
const int CONTROLREFRESH = 50;      //send control packet every 10 ms (default 25)
const int DISPLAYREFRESH = 100;      //refresh Display every 40 ms = 25fps
unsigned long deadtime, deadtimeOld, controlTime, controlTimeOld, displayTime, displayTimeOld = 0;
unsigned long debugtime, debugtimeOld =0, atmotime, atmotimeOld =0;
unsigned long now = 0;


//variables used for display status
byte PageDisplay1 = 0;              //Page display1
byte PageDisplay2 = 0;              //Page display2 

//variables used for motorfader
int throttletarget;
int theThreshold = 10;

//in-game states used to update button LEDs and other stuff
byte SASval;
byte SASvalOld;
bool refreshSASDisplay = true; //need bool to force update
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
bool inflight = false;
bool inAtmo = false;

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

// Declare objects that we are going to read from the Nextion display1.
// Format: <type of object> <object name> = <type of object>(<page id>, <object id>, "<object name>");
NexButton warpminus = NexButton(2, 2, "warpminus");
NexButton warpstop = NexButton(2, 3, "warpstop");
NexButton warpplus = NexButton(2, 4, "warpplus");
NexButton vesselprev = NexButton(2, 7, "vesselprev");
NexButton mapview = NexButton(2, 6, "mapview");
NexButton vesselnext = NexButton(2, 8, "vesselnext");
NexButton cameraiva = NexButton(2, 10, "cameraiva");
NexButton camerareset = NexButton(2, 11, "camerareset");
NexButton cameranext = NexButton(2, 12, "cameranext");
NexButton evaboard = NexButton(3, 2, "evaboard");
NexButton evause = NexButton(3, 3, "evause");
NexDSButton evarun = NexDSButton(3, 7, "evarun");
NexButton evarcs = NexButton(3, 4, "evarcs");
NexButton evahelmet = NexButton(3, 5, "evahelmet");
NexButton evachute = NexButton(3, 6, "evachute");
NexDSButton dsoff = NexDSButton(4, 2, "dsoff");
NexDSButton dsman = NexDSButton(4, 7, "dsman");
NexDSButton dspro = NexDSButton(4, 3, "dspro");
NexDSButton dsret = NexDSButton(4, 8, "dspro");
NexDSButton dsnorm = NexDSButton(4, 4, "dsnorm");
NexDSButton dsanti = NexDSButton(4, 9, "dsanti");
NexDSButton dsradout = NexDSButton(4, 5, "dsradout");
NexDSButton dsradin = NexDSButton(4, 10, "dsradin");
NexDSButton dstarg = NexDSButton(4, 6, "dstarg");
NexDSButton dsrettarg = NexDSButton(4, 11, "dsrettarg");
NexHotspot zoommin = NexHotspot(5, 11, "zoommin");
NexHotspot zoomplus = NexHotspot(5, 12, "zoomplus");

// Declare touch event objects to the touch event list: 
// Format: &<object name>,
NexTouch *nex_listen_list[] = 
{
  &warpminus,
  &warpstop,
  &warpplus,
  &vesselprev,
  &mapview,
  &vesselnext,      
  &cameraiva,
  &camerareset,
  &cameranext,
  &evaboard,
  &evause,
  &evarun,
  &evarcs,
  &evahelmet,
  &evachute,  
  &dsoff,
  &dsman,
  &dspro,
  &dsret,
  &dsnorm,
  &dsanti,
  &dsradout,
  &dsradin,
  &dstarg,
  &dsrettarg,
  &zoommin,
  &zoomplus,  
  NULL  // String terminated
};


void setup()  //Starting the Arduino
{
  Serial.begin(115200); // Open the serial connection.
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
  registernextionevent(); //register event callback function for nextion buttons  
  Keyboard.begin();       // initialize control over the keyboard:
  /* Use Joystick controls from simpit
  Joystick.begin(false);  // Initialize Joystick Library 
    // Set Range Values
    Joystick.setXAxisRange(0, 1023);
    Joystick.setYAxisRange(0, 1023);
    Joystick.setZAxisRange(0, 1023);
    Joystick.setRxAxisRange(0, 1023);
    Joystick.setRyAxisRange(0, 1023);
    Joystick.setRzAxisRange(0, 1023);
    Joystick.setThrottleRange(0, 1023);
    //Joystick.setAcceleratorRange(0, 1023);
  */

  //check if debug is on 
  while(!digitalRead(pMODE)){debugfunction();} 
   
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
      SASval = AP_STABILITYASSIST; //Set Standard SAS Mode on load
      
      mySimpit.printToKSP("Connected", PRINT_TO_SCREEN); // Display a message in KSP to indicate handshaking is complete.
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LOW);
  
  registerInputchannel();    //registering to input Data channels.
  mySimpit.inboundHandler(messageHandler); // Sets our callback function. The KerbalSimpit library will call this function every time a packet is received.   
}

void loop() {   //Looping
  //check if debug is on 
  while(!digitalRead(pMODE)){debugfunction();} 
   
  //KSP mode  
  mySimpit.update();          // Check for new serial messages
  //Joystick.sendState();     // send Joystick input, do not need if use simpit
  nexLoop(nex_listen_list);   // Check for any touch event    
  send_control_packet();
  get_vessel_data();          // update Displays  
  wave();                     // save Data and build wave
  
  //reset with buttons
  if (!digitalRead(pACTION1) && !digitalRead(pACTION2) && !digitalRead(pACTION3)){
    rstc_start_software_reset(RSTC);
  }
}
