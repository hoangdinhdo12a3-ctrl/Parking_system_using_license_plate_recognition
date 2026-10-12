#include "parking_logic.h"

ParkingLogic parking;

void ParkingLogic::init() {
    _coSuKien = false;
    _loaiSuKien = 0;
}

void ParkingLogic::update(uint8_t mode, bool coXeVao, bool coXeRa,
                           bool coXeO1, bool coXeO2, bool coXeO3,
                           unsigned long uidVao, unsigned long uidRa,
                           String bienSoVao, String bienSoRa,
                           uint8_t &soXe, uint8_t &vr, uint8_t &dcRa, bool &cp) {
    
    if (mode == MODE_MANUAL) return;  // Chế độ thủ công, bỏ qua
    
    // === XỬ LÝ XE VÀO ===
    if (coXeVao && soXe < MAX_XE) {
        cp = true;  // Yêu cầu chụp ảnh
        if (bienSoVao != "") {
            barrierVao.moVao();
            soXe++;
            _coSuKien = true;
            _loaiSuKien = 1;  // WELCOME
        }
    }
    
    // Đóng barie khi xe qua
    if (!coXeVao && barrierVao.isMo()) {
        barrierVao.dongVao();
    }
    
    // === XỬ LÝ XE RA ===
    if (coXeRa) {
        cp = true;
        if (bienSoRa != "") {
            // Kiểm tra trùng khớp (đơn giản hóa)
            if (soXe > 0) {
                barrierRa.moRa();
                soXe--;
                dcRa = DC_HOP_LE;
                _coSuKien = true;
                _loaiSuKien = 2;  // BYE
            } else {
                dcRa = DC_SAI_BIEN;
                _coSuKien = true;
                _loaiSuKien = 3;  // ERROR
            }
        }
    }
    
    if (!coXeRa && barrierRa.isMo()) {
        barrierRa.dongRa();
    }
    
    // === BÁO ĐẦY BÃI ===
    if (soXe >= MAX_XE) {
        _coSuKien = true;
        _loaiSuKien = 4;  // FULL
    }
}

bool ParkingLogic::coSuKienMoi() { return _coSuKien; }
uint16_t ParkingLogic::getLoaiSuKien() { return _loaiSuKien; }