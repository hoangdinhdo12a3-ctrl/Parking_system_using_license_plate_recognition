// ============================================================
// config.h - Cấu hình chân và hằng số cho toàn bộ hệ thống
// ============================================================
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ---------- CẢM BIẾN HỒNG NGOẠI ----------
#define CBV     2       // Cảm biến cửa vào
#define CBR     3       // Cảm biến cửa ra
#define CB1     4       // Cảm biến vị trí ô đỗ 1
#define CB2     5       // Cảm biến vị trí ô đỗ 2
#define CB3     6       // Cảm biến vị trí ô đỗ 3

// ---------- LED BÁO ----------
#define LED_VAO     7   // LED báo cửa vào
#define LED_RA      8   // LED báo cửa ra
#define LED_O1      9   // LED ô đỗ 1
#define LED_O2      10  // LED ô đỗ 2
#define LED_O3      11  // LED ô đỗ 3

// ---------- BUZZER ----------
#define BUZZER      12

// ---------- SERVO ----------
#define SERVO_VAO   9
#define SERVO_RA    10

// ---------- RFID RC522 ----------
#define RFID_VAO_SS   10
#define RFID_VAO_RST  9
#define RFID_RA_SS    8
#define RFID_RA_RST   7

// ---------- HẰNG SỐ HỆ THỐNG ----------
#define MAX_XE      3       // Số xe tối đa trong bãi
#define BAUD_RATE   9600    // Tốc độ Serial

// ---------- TRẠNG THÁI ----------
#define MODE_AUTO       0
#define MODE_MANUAL     1

#define VR_KHONG        0   // Không có xe
#define VR_VAO          1   // Xe vào
#define VR_RA           2   // Xe ra

#define DC_BINH_THUONG  0
#define DC_HOP_LE       1
#define DC_SAI_BIEN     2

#endif