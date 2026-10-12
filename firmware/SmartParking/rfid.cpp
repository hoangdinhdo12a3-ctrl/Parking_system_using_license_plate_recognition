#include "rfid.h"

RFIDManager rfidManager;

void RFIDManager::init() {
    SPI.begin();
    rfidVao.PCD_Init(RFID_VAO_SS, RFID_VAO_RST);
    rfidRa.PCD_Init(RFID_RA_SS, RFID_RA_RST);
}

bool RFIDManager::docTheVao(unsigned long &uid) {
    if (!rfidVao.PICC_IsNewCardPresent()) return false;
    if (!rfidVao.PICC_ReadCardSerial()) return false;
    
    uid = 0;
    for (byte i = 0; i < rfidVao.uid.size; i++) {
        uid = uid * 256 + rfidVao.uid.uidByte[i];
    }
    rfidVao.PICC_HaltA();
    return true;
}

bool RFIDManager::docTheRa(unsigned long &uid) {
    if (!rfidRa.PICC_IsNewCardPresent()) return false;
    if (!rfidRa.PICC_ReadCardSerial()) return false;
    
    uid = 0;
    for (byte i = 0; i < rfidRa.uid.size; i++) {
        uid = uid * 256 + rfidRa.uid.uidByte[i];
    }
    rfidRa.PICC_HaltA();
    return true;
}