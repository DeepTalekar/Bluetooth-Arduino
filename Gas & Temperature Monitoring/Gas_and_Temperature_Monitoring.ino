// The Version of "Blynk" Library used - 0.6.1

/* Comment this out to disable prints and save space */
#define BLYNK_USE_DIRECT_CONNECT

#include <DHT.h>

// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(0, 1); // RX, TX
// Connect RX pin of Bluetooth to TX (i.e. Digital 1) in Arduino
// Connect TX pin of Bluetooth to RX (i.e. Digital 0) in Arduino

#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleSerialBLE.h>

// You should get Auth Token from your Email.
char auth[] = "Your_Authentication_Token";

#define DHTPIN 2          // What digital pin we have connected DHT11 to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);

#define LPG_SENSOR A0     // What analog pin we have connected MQ6 to
int LPG_detected = 0;

BlynkTimer timer;

void sendSensor()
{
  // Code For MQ6 Start
  LPG_detected = analogRead(LPG_SENSOR);
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3, LPG_detected);

  // If the value of sensor is greater then 700ppm it will send a notification to the device.
  if(LPG_detected > 700){
    Blynk.notify("⚠ LPG/Propane Gas Leak Detected!");
  }
  // Code For MQ6 End

  // Code For DHT11 Start
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
  // Code For DHT11 End
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
  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
