// ============================================================
// SmartParking.ino - File chính của hệ thống
// ============================================================
#include <Arduino.h>
#include "config.h"
#include "modules/sensors/sensors.h"
#include "modules/rfid/rfid.h"
#include "modules/servo/servo_control.h"
#include "modules/led_buzzer/led_buzzer.h"
#include "modules/serial_comm/serial_comm.h"
#include "modules/parking_logic/parking_logic.h"

// Biến toàn cục
uint8_t g_mode = 0;
uint8_t g_soXe = 0;
uint8_t g_vr = 0;
uint8_t g_dcRa = 0;
bool g_cp = false;
String g_bienSoVao = "";
String g_bienSoRa = "";
unsigned long g_uidVao = 0;
unsigned long g_uidRa = 0;

void setup() {
    Serial.begin(BAUD_RATE);
    Serial.println(F("[BOOT] Smart Parking System starting..."));
    
    sensors.init();
    ledBuzzer.init();
    rfidManager.init();
    barrierVao.init(SERVO_VAO);
    barrierRa.init(SERVO_RA);
    serialComm.init(BAUD_RATE);
    parking.init();
    
    ledBuzzer.beep(100);
    delay(100);
    ledBuzzer.beep(100);
    
    Serial.println(F("[BOOT] Ready!"));
}

void loop() {
    // 1. Đọc RFID
    unsigned long uid;
    if (rfidManager.docTheVao(uid)) {
        g_uidVao = uid;
        g_vr = 1;
        Serial.print(F("[RFID-VAO] UID = "));
        Serial.println(uid);
    }
    if (rfidManager.docTheRa(uid)) {
        g_uidRa = uid;
        g_vr = 2;
        Serial.print(F("[RFID-RA] UID = "));
        Serial.println(uid);
    }
    
    // 2. Đọc cảm biến
    bool coXeVao = sensors.coXeVao();
    bool coXeRa = sensors.coXeRa();
    bool coXeO1 = sensors.coXeTaiViTri(1);
    bool coXeO2 = sensors.coXeTaiViTri(2);
    bool coXeO3 = sensors.coXeTaiViTri(3);
    
    // 3. Đọc lệnh từ PC
    if (serialComm.coLenhMoi()) {
        serialComm.docLenh();
        g_mode = serialComm.getMode();
        g_bienSoVao = serialComm.getBienSoVao();
        g_bienSoRa = serialComm.getBienSoRa();
        if (g_mode == MODE_MANUAL) {
            barrierVao.setTrangThai(serialComm.getDkVao());
            barrierRa.setTrangThai(serialComm.getDkRa());
        }
    }
    
    // 4. Xử lý logic
    parking.update(g_mode, coXeVao, coXeRa, coXeO1, coXeO2, coXeO3,
                   g_uidVao, g_uidRa, g_bienSoVao, g_bienSoRa,
                   g_soXe, g_vr, g_dcRa, g_cp);
    
    // 5. Cập nhật output
    sensors.capNhatDenBao();
    if (parking.coSuKienMoi()) {
        ledBuzzer.beep(parking.getLoaiSuKien());
    }
    
    // 6. Gửi trạng thái về PC
    serialComm.guiTrangThai(g_mode, barrierVao.isMo(), barrierRa.isMo(),
                             g_cp, g_vr, g_dcRa, g_soXe);
    
    // 7. Reset cờ
    g_vr = 0;
    g_cp = false;
    g_dcRa = 0;
}