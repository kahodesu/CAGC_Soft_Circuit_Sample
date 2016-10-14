#include <CapPin.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//variables for Neopixels
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            12

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      3

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int R, B;

const int ledPin =  7;      // the number of the LED pin on FLORA

//variables for capcitive switch
CapPin cPin_9 = CapPin(9);    // read pin 10 (D10 on Flora)
CapPin capacitivePin = cPin_9;

//variables for button
const int buttonPin = 10;     // the number of the pushbutton pin
int buttonState = 0;
boolean currentPressed = false;
// Capactive touch threashhold, you might want to mess with this if you find its too
// sensitive or not sensitiva enough
#define THRESH 100


void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  pixels.begin(); // This initializes the NeoPixel library.
}


void loop()
{

  ///////////////////////Button Part ///////////////////////
  buttonState = digitalRead(buttonPin); //reading  buttonPin
  if (buttonState == LOW) {
    digitalWrite(ledPin, HIGH);
    R = 255;
    B = 0;
  }
  else {
    digitalWrite(ledPin, LOW);
    R = 0;
    B = 0;
  }

   ///////////////////////Capacitive Switch Part///////////////////////
  long total =  capacitivePin.readPin(2000);

  if ((total > THRESH) && (! currentPressed)) {
    currentPressed = true;
    digitalWrite(ledPin, HIGH);
    R = 0;
    B = 255;

  }
  else if ((total <= THRESH) && (currentPressed)) {
    // key was released (no touch, and it was pressed before)
    currentPressed = false;
    digitalWrite(ledPin, LOW);
    R = 0;
    B = 0;

  }

/////////////////NEOPIXELS PART/////////////////////////
   for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(R,0,B)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(100);
  }
}



