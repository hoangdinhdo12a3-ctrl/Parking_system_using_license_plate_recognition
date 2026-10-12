#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Arduino.h>
#include <Servo.h>
#include "config.h"

class Barrier {
public:
    void init(uint8_t chanServo);
    void moVao();
    void dongVao();
    void moRa();
    void dongRa();
    bool isMo();
    void setTrangThai(uint8_t tt);
private:
    Servo servo;
    bool trangThaiMo = false;
};

extern Barrier barrierVao;
extern Barrier barrierRa;
#endif