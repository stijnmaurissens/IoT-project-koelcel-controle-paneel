#define BLYNK_TEMPLATE_ID "user4"
#define BLYNK_TEMPLATE_NAME "user4@server.wyns.it"// de server waarmee ik geconecteer ben
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ezBuzzer.h>

//DHT11 configuratie
#define DHTPIN 17
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define LIGHT_SENSOR_PIN 35 //LDR pin


WidgetLED led1(V2); //koeling LED op Blynk
WidgetLED led2(V3); //deur open? LED op blynk

int licht; //ldr waarde
int gewenst; // slider op blynk
float t; //temperatuur
float h; // vochtigheid
int ledpin = 16;
const int BUZZER_PIN = 26;
ezBuzzer buzzer(BUZZER_PIN);

// Mijn WiFi credentials.
char auth[] = ""; //voeg hier u code van blynk in
char ssid[] = ""; //wifi naam
char pass[] = ""; // wifi wachtwoord

LiquidCrystal_I2C lcd(0x27,16,2);
BlynkTimer timer;

BLYNK_WRITE(V1) { // V1 is de geconecteerd aan de slider in blynk
  gewenst = param.asInt();  // 
  Serial.print("de gewenste temperatuur is: ");
  Serial.println(gewenst);
}

void sendSensor()
{
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, h); // stuurt de vochtigheid naar virtuele pin 5 (V5)
  Blynk.virtualWrite(V6, t); // stuurt de temperatuur naar virtuele pin 6 (V6)
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ledpin, OUTPUT);
  lcd.init();
  lcd.backlight();
  Blynk.begin(auth, ssid, pass, "server.wyns.it", 8081); //conecteert met de server. verander "server.wyns.it" naar u eigen server.
  dht.begin();
  pinMode(BUZZER_PIN, OUTPUT);

}

void loop() {
 t = dht.readTemperature();
 h = dht.readHumidity();
 
 buzzer.loop();
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("temp: ");
 lcd.print(t,1);
 lcd.setCursor(0, 1);
 lcd.print("gewenst: ");
 lcd.print(gewenst,1);

 Serial.print("temp:");
 Serial.println(t);

delay(1000);
  sendSensor();
  Blynk.run();
  timer.run();
  test_temp();
  check_licht();
}



void test_temp() { //kijkt of de temperatuur niet te hoog is
  if (t > gewenst){
    led_staat(true);
    if (t > (gewenst+5)) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(200);
      digitalWrite(BUZZER_PIN, LOW);
       if (t > (gewenst+10)) {
          Blynk.logEvent("Hey, Koelcel word veel te warm"); // werkt helaas niet met de onze oudere maar gratis versie van de app
          //Blynk.email("koelcel1 is te warm", "Koelcel1 is meer dan 10 graden boven de ingestelde temperatuur. controleer dit zo snel mogelijk."); // deze werk helaas ook niet meer
      }
    }
  }
  else{
    led_staat(false);
  }
}
void led_staat(bool state) { //zet zowel de fyzieke LED aan en uit, als die op Blynk
if (state ==  true) {
  led1.on();
  digitalWrite(ledpin,HIGH);
}
if (state == false) {
  led1.off();
  digitalWrite(ledpin, LOW);
}
}

void check_licht() { // kijkt of de deur open staat of niet. (indien gesloten is het compleet donker en word er 0 uitgelzen)
 licht = analogRead(LIGHT_SENSOR_PIN);
  if (licht > 1 ){
  Serial.print("deur is open");
  led2.on();
  }
  else {
    led2.off();
  }
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
