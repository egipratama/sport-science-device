#include <WiFi.h>
#include <HTTPClient.h>

int timeOut = 10000; // 10 detik
unsigned long previousMillis = 0;
unsigned long start = 0, finish = 0;

boolean whileLoop = true;

int jumlahPukulan = 0;
int randomSen = 0;
int dataRandom = 0;

//int arrWaktuPukulan[100];
int waktuTotal = 0;
int waktuSebelumnya = 0;
//int waktuKalibrasi = 0;

int pinsLed[] = {2, 18, 22, 19, 23, 4, 5};
int pinsSensor[] = {14, 33, 32, 34, 25, 27, 26};

const char* ssid = "Ini";
const char* password = "353058100";

void setup() {
  Serial.begin(112500);

  Serial.println("Mulai loop");
  for (int i = 0; i < 7; i++) {
    pinMode(pinsSensor[i], INPUT_PULLUP);
  }

  //led setup
  for (int i = 0; i < 7; i++) {
    pinMode(pinsLed[i], OUTPUT);
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  for (int i = 0; i < 7; i++) {
    digitalWrite(pinsLed[i], LOW);
    delay(1000);
    digitalWrite(pinsLed[i], HIGH);
  }
  digitalWrite(pinsLed[6], LOW);
}

void loop() {
  char ss = Serial.read();
  unsigned long currentMillis = millis();

  if (digitalRead(pinsSensor[6]) == 0) {
    start = currentMillis;
    //    Serial.println("Mulai hitung");
    digitalWrite(pinsLed[dataRandom], LOW);
    mulai();
  }
}

void mulai() {
  while (whileLoop) {
    finish = millis();
    hitungPukulan();
    if (finish - start >= timeOut) {
      kirim();
      Serial.println(jumlahPukulan);
    }
  }
}

void hitungPukulan() {
  char p = Serial.read();

  if (digitalRead(pinsSensor[dataRandom]) == 0) {
    int waktuSekarang = millis();

    if (dataRandom == 0) {
      waktuTotal +=  waktuSekarang - start;
      waktuSebelumnya = waktuSekarang;
    } else {
      waktuTotal += waktuSekarang - waktuSebelumnya;
      waktuSebelumnya = waktuSekarang;
    }

    jumlahPukulan++;

    dataRandom = random(0, 7);
    if (dataRandom != randomSen) {
      //      Serial.println(dataRandom);
      digitalWrite(pinsLed[dataRandom], LOW);
    } else {
      dataRandom++;
      //      Serial.println(dataRandom);
      digitalWrite(pinsLed[dataRandom], LOW);
    }
    randomSen = dataRandom;
  }

  for (int i = 0; i < 7; i++) {
    if (i != dataRandom) {
      digitalWrite(pinsLed[i], HIGH);
    }
  }
}

void kirim() {
  //  String d = "[";
  //  for (int i = 0; i < 100; i++) {
  //    d += arrWaktuPukulan[i];
  //    d += ",";
  //  }
  //  d += "]";
  Serial.print("waktu : ");
  Serial.println(waktuTotal);
  Serial.print("Jumlah Pukulan : ");
  Serial.println(jumlahPukulan);
  for (int i = 0; i < 7; i++) {
    digitalWrite(pinsLed[i], HIGH);
  }
  delay(1000);
  HTTPClient http;
  String url = "http://us-central1-unikom-sport-science.cloudfunctions.net/punch?id=001";
  url += "&punch=";
  url += jumlahPukulan;
  url += "&time=";
  url += (waktuTotal / jumlahPukulan);
  delay(1000);
  http.begin(url);
  http.GET();
  http.end();

  while (1) {

  }
  whileLoop = false;
}
