#include <ESP8266WiFi.h> // important libraries for wifi
#include <ESP8266HTTPClient.h> //important libraries for wifi

#include <DallasTemperature.h> // sensor libraries
#include <OneWire.h> // sensor libraries
#define ONE_WIRE_BUS 4                          //D2 pin of nodemcu

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);  // Pass the oneWire reference to Dallas Temperature.

char* ssid = "__________"; // your wifi connection 
char* password = "___________";
char* host = "dormmate.000webhostapp.com";
int floatSensor = 5;
int buttonState;

void setup()
{
    Serial.begin(115200);
    sensors.begin();
    pinMode(floatSensor, INPUT_PULLUP);
    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    Serial.println("Starting Wifi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(WiFi.status());
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}



void loop()
{
  sensors.requestTemperatures();                // Send the command to get temperatures  
  Serial.println("Temperature is: ");
  Serial.println(sensors.getTempCByIndex(0));   // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  delay(500);
  float temperature = sensors.getTempCByIndex(0);
  char* water;
  Serial.println(temperature);

  buttonState = digitalRead(floatSensor); 
  if(buttonState == HIGH){
    Serial.println("Water Level: Low");
    water = "LOW";
  }else{
    Serial.println("Water Level: High");
    water = "HIGH";
  }
  
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        //Serial.println(client.connect(host,httpPort));
        Serial.println("connection failed");
        return;
    } 
  Serial.println("Client Connected!");

    // This will send the request to the server
    client.print(String("GET /index.php?") + 
                          ("&temperature=") + temperature +
                          ("&water_level=") + water +
                          " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
                 
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 1000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    Serial.println();
    Serial.println("closing connection");
}
