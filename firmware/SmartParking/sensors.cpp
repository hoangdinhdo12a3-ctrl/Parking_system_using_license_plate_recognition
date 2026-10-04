#include "sensors.h"    // Include chính file .h của nó

Sensors sensors;        // Tạo instance toàn cục

void Sensors::init() {
    pinMode(CBV, INPUT_PULLUP);
    pinMode(CBR, INPUT_PULLUP);
    // ...
}

bool Sensors::coXeVao() {
    return digitalRead(CBV) == LOW;
}

bool Sensors::coXeRa() {
    return digitalRead(CBR) == LOW;
}
// ... các hàm khác