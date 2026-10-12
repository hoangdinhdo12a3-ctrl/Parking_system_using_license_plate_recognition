#include "led_buzzer.h"

LedBuzzer ledBuzzer;

void LedBuzzer::init() {
    pinMode(BUZZER, OUTPUT);
    digitalWrite(BUZZER, LOW);
}

void LedBuzzer::beep(uint16_t duration) {
    digitalWrite(BUZZER, HIGH);
    delay(duration);
    digitalWrite(BUZZER, LOW);
}

void LedBuzzer::thongBaoWelcome() { beep(200); delay(100); beep(200); }
void LedBuzzer::thongBaoBye()     { beep(300); }
void LedBuzzer::thongBaoError()   { beep(100); delay(50); beep(100); delay(50); beep(100); }
void LedBuzzer::thongBaoFull()    { beep(500); }