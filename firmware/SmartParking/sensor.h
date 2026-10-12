// ============================================================
// sensors.h - Module đọc cảm biến hồng ngoại
// ============================================================
#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "config.h"

class Sensors {
public:
    void init();                          // Khởi tạo chân INPUT_PULLUP
    bool coXeVao();                       // Đọc cảm biến cửa vào
    bool coXeRa();                        // Đọc cảm biến cửa ra
    bool coXeTaiViTri(uint8_t viTri);     // Đọc cảm biến vị trí (1-3)
    void capNhatDenBao();                 // Cập nhật LED báo ô đỗ
};

extern Sensors sensors;
#endif