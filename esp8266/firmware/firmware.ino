#include <stdbool.h>
#include <inttypes.h>

#include <SPI.h>
#include <MFRC522.h>

#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define RST_PIN D1
#define  SS_PIN D4

#define SSID ""
#define PASS ""
#define REMOTE_ADDR ""

void led_success_sequence(void);
void led_failure_sequence(void);

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
    Serial.begin(9600); while (!Serial);
    SPI.begin(); rfid.PCD_Init();

    WiFi.begin(SSID, PASS);

    while (WiFi.status() != WL_CONNECTED) {
       delay(500);
       Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println(WiFi.localIP());

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    if (WiFi.status()== WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;

        http.begin(client, REMOTE_ADDR);
        http.GET();
    }
    digitalWrite(LED_BUILTIN, HIGH);

    if (!rfid.PICC_IsNewCardPresent()) return;
    if (!rfid.PICC_ReadCardSerial()) return;

    uint32_t uid = *(uint32_t *)rfid.uid.uidByte;
    Serial.println(uid);

    if (uid == 0xA2F28A90) {
        led_success_sequence();
    }
    else {
        led_failure_sequence();
    }
}

void led_success_sequence(void) {
    for (int i = 0; i < 3; i++) {
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
    }
}

void led_failure_sequence(void) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
}
