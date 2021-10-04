#include <iostream>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "heltec.h"
#define DHTPIN 12
#define DHTTYPE DHT11

using namespace std;

#define INLINE inline __attribute__((always_inline))

using SenseType = float;   // user-defined types = ADT = abstract data type
using PortType  = uint8_t; // unsigned int 8-bits = fixed size int


class SensorTemp { // Class = user defined type definition (define-and-use)
private: // default private visibility
    SenseType t,h;
    SenseType moist;
    PortType  port=12;
    DHT *dht ;
public:
    void inicio() { 
       dht = new DHT(DHTPIN, DHTTYPE);
       dht->begin();
    }
    void leer() {
        // DHT11 read ports
        t=dht->readTemperature();
        h=dht->readHumidity(); 
        Heltec.display -> clear();
        Heltec.display -> drawString(0, 1, "Temperatura");
        Heltec.display -> drawString(2, 15, String(t));
        Heltec.display -> drawString(2, 15, "          °C");
        Heltec.display -> drawString(0, 30, "Humedad");
        Heltec.display -> drawString(3, 45, String(h));
        Heltec.display -> drawString(2, 45, "          %");
        Heltec.display -> display();
        if (isnan(h) || isnan(t)) {
          Serial.println("Falla al leer el sensor DHT11!");
          Heltec.display -> clear();
          Heltec.display -> drawString(0, 0, "FAllA de Sensor..........");
          Heltec.display -> display();
          return;
          } 
    }
    friend ostream& operator << (ostream &os,  SensorTemp &s) {
        os << "Temperatura =  " << s.t << "ºC" << "Humedad =  " << s.h << "%" << endl; // Add humidity value
        return os;
    }
};

SensorTemp th; // use = instance = objeto
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);
  th.inicio();
}

void loop() {
  // put your main code here, to run repeatedly:
    // DANGER! th.temp = 60;
    th.leer();
    cout << th; // attribute (dot-operator)
    delay(1000);

}
