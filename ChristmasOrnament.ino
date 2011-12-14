/*
This sketch uses DHCP to obtain an IP address automatically and requires Arduino 1.0.
   
 Network Requirements:
   * Ethernet port on Router    
   * DHCP enabled on Router
   * Unique MAC Address for Arduino

 Getting a Globally Unique MAC Address from ThingSpeak:
   * Sign Up for New User Account - https://www.thingspeak.com/users/new
   * Register your Arduino by selecting Devices, Add New Device
   * Once the Arduino is registered, click Generate Unique MAC Address
   * Enter the new MAC Address in this sketch under "Local Network Settings"
 Created: Novemeber 29, 2011 by Hans Scharler - http://www.iamshadowlord.com
 Additional Credits:
 http://www.digitalmisery.com
 http://www.deepdarc.com
*/

#include <SPI.h>
#include <Ethernet.h>

//---bof---RGBL-Analog Preamble
//RGB LED pins
int ledAnalogOne[] = {3, 5, 6}; 
//the three pins of the first analog LED 3 = redPin, 5 = greenPin, 6 = bluePin                                
//These pins must be PWM

//Defined Colors (different RGB (red, green, blue) values for colors
const byte RED[] = {0, 255, 255}; 
const byte ORANGE[] = {172, 251, 255}; 
const byte YELLOW[] = {0, 200, 255}; 
const byte GREEN[] = {255, 0, 255}; 
const byte BLUE[] = {255, 255, 0}; 
const byte INDIGO[] = {200, 255, 220}; //? 
const byte VIOLET[] = {232, 255, 233}; //?
const byte CYAN[] = {255, 0, 0}; 
const byte MAGENTA[] = {0, 255, 200}; 
const byte WHITE[] = {0, 50, 150}; 
const byte WARMWHITE[] = {0, 70, 220};
const byte BLACK[] = {255, 255, 255}; //?
const byte PURPLE[] = {100, 255, 160}; 
//---eof---RGBL-Analog Preamble

static uint16_t c;

// Local Network Settings
byte mac[] = { 0xD4, 0x28, 0xB2, 0xFF, 0xDB, 0x54 }; // Must be unique on local network

// ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";
String thingSpeakChannel = "1417";                // Channel number of the CheerLights Channel
String thingSpeakField = "1";                     // Field number of the CheerLights commands 
const int thingSpeakInterval = 16 * 1000;      // Time interval in milliseconds to get data from ThingSpeak (number of seconds * 1000 = interval)

// Variable Setup
long lastConnectionTime = 0; 
String lastCommandString = "";
byte lastCommand[] = {255, 255, 255};
boolean lastConnected = false;
int failedCounter = 0;

// Initialize Arduino Ethernet Client
EthernetClient client;

void setup() {
  //delay(100);
  for(int i = 0; i < 3; i++) {   
    pinMode(ledAnalogOne[i], OUTPUT);   //Set the three LED pins as outputs   
  }  
  setColor(ledAnalogOne, BLACK);       //Turn off led 1  

  // Setup Serial
  Serial.begin(9600);
  delay(100);
  
  Serial.flush();
  delay(100);
  
  // Start Ethernet on Arduino
  startEthernet();
}

void loop() {
   
  // Process CheerLights Commands
  if(client.available() > 0)
  {  
    delay(100); 
    
    String response;
    char charIn;

    do {
        charIn = client.read(); // read a char from the buffer
        response += charIn; // append that char to the string response
      } while (client.available() > 0); 
          
    // Light the tree
    if (response.indexOf("white") > 0)
    {  
       fadeToColor(ledAnalogOne, lastCommand, WHITE, 10);
       delay(3000);
       for(int i = 0; i < 3; i++) {   
          lastCommand[i] = WHITE[i];
       }
       lastCommandString = "white";  
    }
    else if (response.indexOf("black") > 0)
    {  
       fadeToColor(ledAnalogOne, lastCommand, BLACK, 10);  
       delay(3000);
       for(int i = 0; i < 3; i++) {   
          lastCommand[i] = BLACK[i];
       }  
       lastCommandString = "black";  
    }
    else if (response.indexOf("red") > 0)
    {  
       fadeToColor(ledAnalogOne, lastCommand, RED, 10);  
       delay(3000);
       for(int i = 0; i < 3; i++) {   
          lastCommand[i] = RED[i];
       }  
       lastCommandString = "red";  
    }
    else if (response.indexOf("green") > 0)
    {  
       fadeToColor(ledAnalogOne, lastCommand, GREEN, 10);  
       delay(3000);
       for(int i = 0; i < 3; i++) {   
          lastCommand[i] = GREEN[i];
       }  
       lastCommandString = "green";  
    }
    else if (response.indexOf("blue") > 0)
    {  
       fadeToColor(ledAnalogOne, lastCommand, BLUE, 10);  
       delay(3000);
       for(int i = 0; i < 3; i++) {   
          lastCommand[i] = BLUE[i];
       }  
       lastCommandString = "blue";  
    }
    else if (response.indexOf("cyan") > 0)
    {  
       fadeToColor(ledAnalogOne, lastCommand, CYAN, 10); 
       delay(3000);
       for(int i = 0; i < 3; i++) {   
          lastCommand[i] = CYAN[i];
       }  
       lastCommandString = "cyan";  
    }
    else if (response.indexOf("magenta") > 0)
    {  
       fadeToColor(ledAnalogOne, lastCommand, MAGENTA, 10);  
       delay(3000);
       for(int i = 0; i < 3; i++) {   
          lastCommand[i] = MAGENTA[i];
       }  
       lastCommandString = "magenta";  
    }
    else if (response.indexOf("yellow") > 0)
    {  
       fadeToColor(ledAnalogOne, lastCommand, YELLOW, 10);  
       delay(3000);
       for(int i = 0; i < 3; i++) {   
          lastCommand[i] = YELLOW[i];
       }  
       lastCommandString = "yellow";  
    }
    else if (response.indexOf("purple") > 0)
    {  
       fadeToColor(ledAnalogOne, lastCommand, PURPLE, 10);  
       delay(3000);
       for(int i = 0; i < 3; i++) {   
          lastCommand[i] = PURPLE[i];
       }  
       lastCommandString = "purple";  
    }
    else if (response.indexOf("orange") > 0)
    {  
       fadeToColor(ledAnalogOne, lastCommand, ORANGE, 10); 
       delay(3000);
       for(int i = 0; i < 3; i++) {   
          lastCommand[i] = ORANGE[i];
       }  
       lastCommandString = "orange";  
    }
    else if (response.indexOf("warmwhite") > 0)
    {  
       fadeToColor(ledAnalogOne, lastCommand, WARMWHITE, 10);
       delay(3000);
       for(int i = 0; i < 3; i++) {   
          lastCommand[i] = WARMWHITE[i];
       }  
       lastCommandString = "warmwhite";  
    }
    else if (response.indexOf("black") > 0)
    {  
      fadeToColor(ledAnalogOne, lastCommand, BLACK, 10);
      delay(3000);
      for(int i = 0; i < 3; i++) {   
          lastCommand[i] = BLACK[i];
      }  
      lastCommandString = "black";  
    }
    else
    {
      Serial.println("No match.");
      //lastCommand = "(no match)";  
    }
    
    // Echo command
    delay(200);
    Serial.println("CheerLight Command Received: "+lastCommandString);
    Serial.println();
    delay(200); 
    
  }
  
    // Disconnect from ThingSpeak
  if (!client.connected() && lastConnected)
  {
    Serial.println("...disconnected");
    Serial.println();
    
    client.stop();
  }
  
  // Subscribe to ThingSpeak Channel and Field
  if(!client.connected() && (millis() - lastConnectionTime > thingSpeakInterval))
  {
    subscribeToThingSpeak(thingSpeakChannel, thingSpeakField);
  }
  
  // Check if Arduino Ethernet needs to be restarted
  if (failedCounter > 3 ) {startEthernet();}
  
  lastConnected = client.connected();
  
} // End loop

void subscribeToThingSpeak(String tsChannel, String tsField)
{
  if (client.connect(thingSpeakAddress, 80))
  {         
    Serial.println("Connecting to ThingSpeak...");
    Serial.println();
      
    failedCounter = 0;
    
    client.println("GET /channels/"+tsChannel+"/field/"+tsField+"/last.txt HTTP/1.0");
    client.println();
    
    lastConnectionTime = millis();
  }
  else
  {
    failedCounter++;
    
    Serial.println("Connection to ThingSpeak Failed ("+String(failedCounter, DEC)+")");   
    Serial.println();
    
    lastConnectionTime = millis(); 
  }
}

void startEthernet()
{
  
  client.stop();

  Serial.println("Connecting Arduino to network...");
  Serial.println();  

  delay(1000);
  
  // Connect to network amd obtain an IP address using DHCP
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("DHCP Failed, reset Arduino to try again");
    Serial.println();
  }
  else
  {
    Serial.println("Arduino connected to network using DHCP");
    Serial.println();
  }
  
  delay(1000);
}

/* Sets the color of the LED to any RGB Value   led - (int array of three values defining the LEDs pins (led[0] = redPin, led[1] = greenPin, led[2] = bluePin))   color - (byte array of three values defing an RGB color to display (color[0] = new Red value, color[1] = new Green value, color[2] = new Red value*/
void setColor(int* led, byte* color){ 
  for(int i = 0; i < 3; i++){             //iterate through each of the three pins (red green blue)   
    analogWrite(led[i], 255 - color[i]);  //set the analog output value of each pin to the input value (ie led[0] (red pin) to 255- color[0] (red input color)                                         
    //we use 255 - the value because our RGB LED is common anode, this means a color is full on when we output analogWrite(pin, 0)                                         
    //and off when we output analogWrite(pin, 255).  
  }
}

/* A version of setColor that takes a predefined color (neccesary to allow const int pre-defined colors */
void setColor(int* led, const byte* color) { 
  byte tempByte[] = {color[0], color[1], color[2]}; 
  setColor(led, tempByte);
}

/* Fades the LED from a start color to an end color at fadeSpeed   
led - (int array of three values defining the LEDs pins (led[0] = redPin, led[1] = greenPin, led[2] = bluePin))   
startCcolor - (byte array of three values defing the start RGB color (startColor[0] = start Red value, startColor[1] = start Green value, startColor[2] = start Red value   
endCcolor - (byte array of three values defing the finished RGB color (endColor[0] = end Red value, endColor[1] = end Green value, endColor[2] = end Red value   
fadeSpeed - this is the delay in milliseconds between steps, defines the speed of the fade*/ 
void fadeToNumColor(int* led, byte* startColor, byte* endColor, int fadeSpeed) {  
  int changeRed = endColor[0] - startColor[0];                             //the difference in the two colors for the red channel  
  int changeGreen = endColor[1] - startColor[1];                           //the difference in the two colors for the green channel   
  int changeBlue = endColor[2] - startColor[2];                            //the difference in the two colors for the blue channel  
  int steps = max(abs(changeRed),max(abs(changeGreen), abs(changeBlue)));  //make the number of change steps the maximum channel change    
  for(int i = 0 ; i < steps; i++) {                                        //iterate for the channel with the maximum change   
    byte newRed = startColor[0] + (i * changeRed / steps);                 //the newRed intensity dependant on the start intensity and the change determined above   
    byte newGreen = startColor[1] + (i * changeGreen / steps);             //the newGreen intensity   
    byte newBlue = startColor[2] + (i * changeBlue / steps);               //the newBlue intensity   
    byte newColor[] = {newRed, newGreen, newBlue};                         //Define an RGB color array for the new color   
    setColor(led, newColor);                                               //Set the LED to the calculated value   
    delay(fadeSpeed);                                                      //Delay fadeSpeed milliseconds before going on to the next color  
  }  
  setColor(led, endColor);                                                 //The LED should be at the endColor but set to endColor to avoid rounding errors
}

/* A version of fadeToColor that takes predefined colors (neccesary to allow const int pre-defined colors */
void fadeToColor(int* led, const byte* startColor, const byte* endColor, int fadeSpeed) {  
  byte tempByte1[] = {startColor[0], startColor[1], startColor[2]};   
  byte tempByte2[] = {endColor[0], endColor[1], endColor[2]};   
  fadeToNumColor(led, tempByte1, tempByte2, fadeSpeed);
}

