
// Pin for Light control MOSFET.
#define LightPin 13
// Threshold of when light should come on
// Out of 1024.
#define Thresh 150

// Pin for PIR motion sensor
#define MotionPin 2
// Minimum number of movements.
#define minmoves 5

// Pin for light sensor
#define LDRpin A0

// Variable for the interupt
// This holdes the number of movements.
volatile byte MotionCount = 0;

// This will trigger whenever pin 2 rises from 0V to 5V.
void PIR_interrupt()
{
  MotionCount++;
  if ( analogRead( LDRpin ) < Thresh )
    digitalWrite ( LightPin, HIGH );
}

void setup()
{
  // Sets pin for the light control to an output and off.
  pinMode ( LightPin, OUTPUT );
  digitalWrite ( LightPin, LOW );

  // This creates a interupt to trigger the above whenever the motion sensor is triggered.
  pinMode ( MotionPin, INPUT );
  attachInterrupt(digitalPinToInterrupt(MotionPin), PIR_interrupt, RISING);
}

void loop()
{
  // Resets number of motion pulses from the PIR sensor.
  MotionCount = 0;
  // Waits 60 seconds
  delay ( 60000 );
  // If there is more than 5 counts per minute, turns on light.
  if ( MotionCount < minmoves )
    digitalWrite ( LightPin, LOW );
}

