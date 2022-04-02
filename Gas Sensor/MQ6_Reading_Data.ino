// The Version of "Blynk" Library used - 0.6.1

/* Comment this out to disable prints and save space */
#define BLYNK_USE_DIRECT_CONNECT

// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(0, 1); // RX, TX
// Connect RX pin of Bluetooth to TX (i.e. Digital 1) in Arduino
// Connect TX pin of Bluetooth to RX (i.e. Digital 0) in Arduino

#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleSerialBLE.h>

// You should get Auth Token from your Email.
char auth[] = "Your_Authentication_Token";

#define LPG_SENSOR A0          // What analog pin we have connected MQ6 to
int LPG_detected = 0;

BlynkTimer timer;

void sendSensor()
{
  LPG_detected = analogRead(LPG_SENSOR);
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3, LPG_detected);

  if(LPG_detected > 700){
    Blynk.notify("⚠ LPG/Propane Gas Leak Detected!");
  }
}

void setup()
{
  // Debug console
  DebugSerial.begin(9600);

  pinMode(LPG_SENSOR, INPUT);
  
  Serial.begin(9600);
  
  DebugSerial.println("Setting Up Things...");
  
  Blynk.begin(Serial, auth);
  
  DebugSerial.println("Connected...");

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
