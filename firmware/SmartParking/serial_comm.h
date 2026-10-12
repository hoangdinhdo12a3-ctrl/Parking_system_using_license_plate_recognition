#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include <Arduino.h>
#include "config.h"

class SerialComm {
public:
    void init(uint32_t baud);
    bool coLenhMoi();
    void docLenh();
    
    // Getter
    uint8_t getMode();
    String getBienSoVao();
    String getBienSoRa();
    uint8_t getDkVao();
    uint8_t getDkRa();
    
    // Gửi trạng thái về PC
    void guiTrangThai(uint8_t mode, bool ttVao, bool ttRa, bool cp,
                      uint8_t vr, uint8_t dcRa, uint8_t soXe);
    
private:
    uint8_t _mode = 0;
    String _bienSoVao = "";
    String _bienSoRa = "";
    uint8_t _dkVao = 0;
    uint8_t _dkRa = 0;
    String _buffer = "";
};

extern SerialComm serialComm;
#endif