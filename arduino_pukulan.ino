#include <WiFi.h>
#include <HTTPClient.h>

int sensorPin = 32;
int sensorValue = 0;
int kalibrasiValue = 0;

int R = 5, G = 18, B = 19;

const char* ssid = "Ini";
const char* password = "353058100";

int dat = 0;
String id = "001";
String track = "1";
String gate = "D";

void setup() {
  Serial.begin(112500);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  kalibrasiValue = analogRead(sensorPin);
  if (kalibrasiValue < 3000) {
    indikator("R");
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
}

void loop() {
  //  kalibrasiValue = analogRead(sensorPin);
  sensorValue = analogRead(sensorPin);

  if (sensorValue > 3000) {
    indikator("G");
  }
  if (sensorValue < 2000) {
    dat++;
    indikator("B");
    delay(500);
    indikator("C");

    Serial.print("data: ");
    Serial.println(dat);

    delay(1000);
    HTTPClient http;
    String url = "http://192.168.43.74:5000/data?";
    url += "id=";
    url += id;
    url += "&track=";
    url += track;
    url += "&data=";
    url += String(dat);
    url += "&gate=";
    url += gate;

    http.begin(url);
    http.GET();
    http.end();

    delay(5000);
  }

  Serial.println(sensorValue);
}

String indikator(String dat) {
  String d = "";
  if (dat == "R") {
    d = "red";
    digitalWrite(R, HIGH);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
  }
  if (dat == "G") {
    d = "green";
    digitalWrite(R, LOW);
    digitalWrite(G, HIGH);
    digitalWrite(B, LOW);
  }
  if (dat == "B") {
    d = "blue";
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(B, HIGH);
  }

  if (dat == "C") {
    d = "clear";
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
  }
  return d;
}
