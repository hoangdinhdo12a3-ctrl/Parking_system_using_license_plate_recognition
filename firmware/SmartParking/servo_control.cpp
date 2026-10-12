#include "servo_control.h"

Barrier barrierVao;
Barrier barrierRa;

void Barrier::init(uint8_t chanServo) {
    servo.attach(chanServo);
    servo.write(0);  // Vị trí đóng
    trangThaiMo = false;
}

void Barrier::moVao() {
    servo.write(90);  // Vị trí mở
    trangThaiMo = true;
}

void Barrier::dongVao() {
    servo.write(0);
    trangThaiMo = false;
}

void Barrier::moRa() { moVao(); }
void Barrier::dongRa() { dongVao(); }

bool Barrier::isMo() { return trangThaiMo; }

void Barrier::setTrangThai(uint8_t tt) {
    if (tt == 1) moVao();
    else dongVao();
}