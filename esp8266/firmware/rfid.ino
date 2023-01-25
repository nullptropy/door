#include <SPI.h>
#include <MFRC522.h>

// create an array of MFRC522 rfid card readers
MFRC522 rfids[2];

void rfid_init_readers() {
    // initialize the SPI bus
    SPI.begin();

    // initialize both of the readers
    rfids[0].PCD_Init(SS_PIN1, RST_PIN);
    rfids[1].PCD_Init(SS_PIN2, RST_PIN);
}

bool rfid_read_card(uint32_t *uid, uint8_t *reader) {
    for (int i = 0; i < 2; ++i) {
        if (rfids[i].PICC_IsNewCardPresent() && rfids[i].PICC_ReadCardSerial()) {
            if (rfids[i].uid.size != 4)
                continue;

            *uid = \
                rfids[i].uid.uidByte[0] << 0x18 |
                rfids[i].uid.uidByte[1] << 0x10 |
                rfids[i].uid.uidByte[2] << 0x08 |
                rfids[i].uid.uidByte[3] << 0x00;
            *reader = i;

            rfids[i].PICC_HaltA();
            rfids[i].PCD_StopCrypto1();

            return true;
        }
    }

    return false;
}
