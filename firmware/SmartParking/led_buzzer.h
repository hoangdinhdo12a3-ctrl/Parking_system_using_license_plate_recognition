#ifndef LED_BUZZER_H
#define LED_BUZZER_H

#include <Arduino.h>
#include "config.h"

class LedBuzzer {
public:
    void init();
    void beep(uint16_t duration);
    void thongBaoWelcome();
    void thongBaoBye();
    void thongBaoError();
    void thongBaoFull();
};

extern LedBuzzer ledBuzzer;
#endif