#include <DHT.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <SPI.h>
  
#define DHTPIN 3
#define DHTTYPE DHT22 

byte mac[] = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 100);
IPAddress server(192, 168, 1, 93);

float humidity;
float temperature;

DHT dht(DHTPIN, DHTTYPE);
EthernetClient ethernetClient;
PubSubClient client(ethernetClient);

void setup() {
  Serial.begin(9600);
  client.setServer(server, 1883);

  if(Ethernet.begin(mac) == 0) {
    Ethernet.begin(mac, ip);
  }       
  Serial.print("Ethernet client is at ");
  Serial.println(Ethernet.localIP());
  
  delay(1500);

  dht.begin();
}

void loop() {

  readSensor();
  publishData();
  delay(10000);
}

void readSensor() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  Serial.print("Sensor reading: Humidity = ");
  Serial.print(humidity);
  Serial.print("% Temperature = ");
  Serial.print(temperature);
  Serial.print("C");
  Serial.println();
}

void publishData() {

  if(!client.connected()) {
    Serial.print("Attempting to connect to ");
    Serial.print(server);
    Serial.println("...");
    if(!client.connect("arduino")) {
      Serial.print("Failed with state: ");
      Serial.print(client.state());
      Serial.println();
    } else {
      Serial.println("Connected.");
    }
  }

  if(client.connected()) {
    String json = createPayload();
    char payload[100];
    json.toCharArray(payload, 100);
    Serial.println("Publishing data...");
    client.publish("sensor", payload);
  }

  String payload = createPayload();
 
}

String createPayload() {

  String payload = "";
  payload += "{ \"d\" : { \"temperature\" : "; 
  payload += (int)temperature; 
  payload += ", \"humidity\" : " ;
  payload += (int)humidity;
  payload += " } }";

  return payload;
}


