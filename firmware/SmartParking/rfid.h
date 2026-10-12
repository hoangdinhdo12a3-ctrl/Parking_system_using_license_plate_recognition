#ifndef RFID_H
#define RFID_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include "config.h"

class RFIDManager {
public:
    void init();
    bool docTheVao(unsigned long &uid);
    bool docTheRa(unsigned long &uid);
private:
    MFRC522 rfidVao;
    MFRC522 rfidRa;
};

extern RFIDManager rfidManager;
#endif