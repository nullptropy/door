#include <SPI.h>
#include <MFRC522.h>

#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "config.ipp"

MFRC522 rfids[2];

void setup() {
    Serial.begin(9600);

    WiFi.begin(SSID, PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    };

    Serial.println("WiFi connected");
    Serial.println(WiFi.localIP());

    SPI.begin();
    rfids[0].PCD_Init(SS_PIN1, RST_PIN);
    rfids[1].PCD_Init(SS_PIN2, RST_PIN);
}

void loop() {
    for (int i = 0; i < 2; ++i) {
        if (rfids[i].PICC_IsNewCardPresent() && rfids[i].PICC_ReadCardSerial()) {
            if (rfids[i].uid.size != 4)
                continue;

            uint32_t uid = \
                rfids[i].uid.uidByte[0] << 0x18 |
                rfids[i].uid.uidByte[1] << 0x10 |
                rfids[i].uid.uidByte[2] << 0x08 |
                rfids[i].uid.uidByte[3] << 0x00;

            rfids[i].PICC_HaltA();
            rfids[i].PCD_StopCrypto1();

            if (WiFi.status() == WL_CONNECTED) {
                char request_body[20];
                WiFiClient client;
                HTTPClient http;

                http.begin(client, i == 0 ? LOGIN_REMOTE_ADDR : EXIT_REMOTE_ADDR);
                http.addHeader("Content-Type", "application/json");

                snprintf(request_body, sizeof(request_body), "{\"uid\": %zu}", uid);
                Serial.print("reader: "); Serial.print(i);
                Serial.print(" request_body: "); Serial.print(request_body);
                int http_code = http.POST(request_body);
            }
        }
    }
}
