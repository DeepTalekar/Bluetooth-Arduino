// The Version of "Blynk" Library used - 0.6.1

/* Comment this out to disable prints and save space */
#define BLYNK_USE_DIRECT_CONNECT

// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(0, 1); // RX, TX
// Connect RX pin of Bluetooth to TX (i.e. Digital 1) in Arduino
// Connect TX pin of Bluetooth to RX (i.e. Digital 0) in Arduino

#define BLYNK_PRINT DebugSerial
#include <DHT.h>
#include <BlynkSimpleSerialBLE.h>

// You should get Auth Token from your Email.
char auth[] = "Your_Authentication_Token";

#define DHTPIN 2          // What digital pin we have connected DHT11 to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  DebugSerial.print("Temperature: ");
  DebugSerial.print(t);
  DebugSerial.print(" ℃");
  DebugSerial.print(" | Humidity: ");
  DebugSerial.print(h);
  DebugSerial.println("%");

  if (isnan(h) || isnan(t)) {
    DebugSerial.println("Failed to read from DHT sensor!");
    return;
  }

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, t);
}

void setup()
{
  // Debug console
  DebugSerial.begin(9600);
  
  Serial.begin(9600);
  DebugSerial.println("Setting Up Things...");
  Blynk.begin(Serial, auth);
  
  DebugSerial.println("Connected...");
  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
