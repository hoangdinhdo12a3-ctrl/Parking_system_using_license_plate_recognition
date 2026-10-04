#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "config.h"

class Sensors {
public:
    void init();
    bool coXeVao();
    bool coXeRa();
    bool coXeTaiViTri(uint8_t viTri);
    void capNhatDenBao();
};

// Khai báo biến toàn cục để file khác dùng được
extern Sensors sensors;

#endif