#ifndef PARKING_LOGIC_H
#define PARKING_LOGIC_H

#include <Arduino.h>
#include "config.h"
#include "servo_control.h"
#include "led_buzzer.h"

class ParkingLogic {
public:
    void init();
    void update(uint8_t mode, bool coXeVao, bool coXeRa,
                bool coXeO1, bool coXeO2, bool coXeO3,
                unsigned long uidVao, unsigned long uidRa,
                String bienSoVao, String bienSoRa,
                uint8_t &soXe, uint8_t &vr, uint8_t &dcRa, bool &cp);
    bool coSuKienMoi();
    uint16_t getLoaiSuKien();
    
private:
    bool _coSuKien = false;
    uint16_t _loaiSuKien = 0;
};

extern ParkingLogic parking;
#endif