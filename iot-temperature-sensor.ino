#include <DHT.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <SPI.h>
  
#define DHTPIN 3
#define DHTTYPE DHT22 

byte mac[] = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(172, 16, 1, 100);
IPAddress server(172, 16, 1, 93);

float humidity;
float temperature;

DHT dht(DHTPIN, DHTTYPE);
EthernetClient ethernetClient;
PubSubClient client(ethernetClient);

void setup() {
  Serial.begin(9600);
  client.setServer(server, 1883);

  Ethernet.begin(mac, ip);    
  delay(1500);

  dht.begin();
}

void loop() {
  readSensor();
  publishData();
  delay(5000);
}

void readSensor() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
}

void publishData() {

  if(!client.connected()) {
    client.connect("arduino");
  }

  if(client.connected()) {
    String json = createPayload();
    char payload[100];
    json.toCharArray(payload, 100);
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


