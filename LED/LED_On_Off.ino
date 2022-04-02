// The Version of "Blynk" Library used - 0.6.1
#define BLYNK_USE_DIRECT_CONNECT

// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>

SoftwareSerial DebugSerial(0, 1); // RX, TX
// Connect RX pin of Bluetooth to TX (i.e. Digital 1) in Arduino UNO
// Connect TX pin of Bluetooth to RX (i.e. Digital 0) in Arduino UNO

#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleSerialBLE.h>

// You should get Auth Token from your Email.
char auth[] = "Your_Authentication_Token";

void setup()
{
  // Debug console
  DebugSerial.begin(9600);
  DebugSerial.println("Waiting for connections...");

  // Blynk will work through Serial
  // 9600 is for HC-06. For HC-05 default speed is 38400
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  
  DebugSerial.println("Setting Up Things...");
  
  Blynk.begin(Serial, auth);
  
  // It Never gets here
  DebugSerial.println("Connected...");
}

void loop()
{
  Blynk.run();
}
