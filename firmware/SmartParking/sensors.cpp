// ============================================================
// sensors.cpp - Cài đặt module cảm biến
// ============================================================
#include "sensors.h"

Sensors sensors;

void Sensors::init() {
    pinMode(CBV, INPUT_PULLUP);
    pinMode(CBR, INPUT_PULLUP);
    pinMode(CB1, INPUT_PULLUP);
    pinMode(CB2, INPUT_PULLUP);
    pinMode(CB3, INPUT_PULLUP);
    
    pinMode(LED_VAO, OUTPUT);
    pinMode(LED_RA, OUTPUT);
    pinMode(LED_O1, OUTPUT);
    pinMode(LED_O2, OUTPUT);
    pinMode(LED_O3, OUTPUT);
}

bool Sensors::coXeVao() {
    return digitalRead(CBV) == LOW;
}

bool Sensors::coXeRa() {
    return digitalRead(CBR) == LOW;
}

bool Sensors::coXeTaiViTri(uint8_t viTri) {
    switch (viTri) {
        case 1: return digitalRead(CB1) == LOW;
        case 2: return digitalRead(CB2) == LOW;
        case 3: return digitalRead(CB3) == LOW;
        default: return false;
    }
}

void Sensors::capNhatDenBao() {
    digitalWrite(LED_O1, coXeTaiViTri(1) ? HIGH : LOW);
    digitalWrite(LED_O2, coXeTaiViTri(2) ? HIGH : LOW);
    digitalWrite(LED_O3, coXeTaiViTri(3) ? HIGH : LOW);
}