// ============================================================
// SMART PARKING SYSTEM - FILE CHÍNH
// Vai trò: Điều phối các module, chứa setup() và loop()
// ============================================================

// ---------- 1. KHAI BÁO THƯ VIỆN HỆ THỐNG ----------
#include <Arduino.h>       // Thư viện lõi Arduino (tự động có)

// ---------- 2. KHAI BÁO CÁC MODULE TỰ VIẾT ----------
#include "config.h"           // Hằng số, chân kết nối
#include "sensors.h"          // Cảm biến hồng ngoại + đèn báo
#include "rfid.h"             // Module RFID RC522
#include "servo_control.h"    // Điều khiển Servo barie
#include "led_buzzer.h"       // Đèn + còi (nếu tách riêng)
#include "serial_comm.h"      // Giao tiếp Serial với PC
#include "parking_logic.h"    // Logic nghiệp vụ (auto/manual)

// ---------- 3. BIẾN TOÀN CỤC ----------
// Lưu trạng thái hiện tại của hệ thống
uint8_t  g_mode     = 0;      // 0 = Auto, 1 = Manual
uint8_t  g_soXe     = 0;      // Số xe hiện có trong bãi
uint8_t  g_vr       = 0;      // 0 = không có xe, 1 = xe vào, 2 = xe ra
uint8_t  g_dcRa     = 0;      // 0 = bình thường, 1 = hợp lệ, 2 = sai biển
bool     g_cp       = false;  // Cờ yêu cầu chụp ảnh (capture)
String   g_bienSoVao = "";    // Biển số xe vào (từ PC gửi)
String   g_bienSoRa  = "";    // Biển số xe ra (từ PC gửi)
unsigned long g_uidVao = 0;   // UID thẻ RFID vào
unsigned long g_uidRa  = 0;   // UID thẻ RFID ra

// ---------- 4. HÀM SETUP() - CHẠY 1 LẦN KHI KHỞI ĐỘNG ----------
void setup() {
    // 4.1. Khởi tạo Serial để debug và giao tiếp với PC
    Serial.begin(9600);
    Serial.println(F("[BOOT] Smart Parking System starting..."));
    
    // 4.2. Khởi tạo từng module theo thứ tự phụ thuộc
    sensors.init();          // Cấu hình chân INPUT_PULLUP cho cảm biến
    ledBuzzer.init();        // Cấu hình chân OUTPUT cho đèn + còi
    rfidManager.init();      // Khởi tạo SPI cho 2 module RC522
    barrierVao.init();       // Gắn servo vào chân, đưa về vị trí đóng
    barrierRa.init();        // Tương tự cho barie ra
    serialComm.init(9600);   // Cấu hình giao thức Serial
    parking.init();          // Reset các mảng lưu trữ
    
    // 4.3. Báo hiệu khởi động xong (nháy còi 2 lần)
    ledBuzzer.beep(100);
    delay(100);
    ledBuzzer.beep(100);
    
    Serial.println(F("[BOOT] Ready!"));
}

// ---------- 5. HÀM LOOP() - CHẠY LẶP LIÊN TỤC ----------
void loop() {
    // === BƯỚC 1: ĐỌC INPUT TỪ CÁC THIẾT BỊ NGOẠI VI ===
    
    // 1.1. Đọc RFID (không blocking - chỉ trả về true nếu có thẻ mới)
    unsigned long uid;
    if (rfidManager.docTheVao(uid)) {
        g_uidVao = uid;
        g_vr = 1;  // Đánh dấu có xe vào đang chờ xử lý
        Serial.print(F("[RFID-VAO] UID = "));
        Serial.println(uid);
    }
    if (rfidManager.docTheRa(uid)) {
        g_uidRa = uid;
        g_vr = 2;  // Đánh dấu có xe ra đang chờ xử lý
        Serial.print(F("[RFID-RA] UID = "));
        Serial.println(uid);
    }
    
    // 1.2. Đọc cảm biến hồng ngoại (CBV, CBR, CB1, CB2, CB3)
    bool coXeVao    = sensors.coXeVao();
    bool coXeRa     = sensors.coXeRa();
    bool coXeO1     = sensors.coXeTaiViTri(1);
    bool coXeO2     = sensors.coXeTaiViTri(2);
    bool coXeO3     = sensors.coXeTaiViTri(3);
    
    // 1.3. Đọc lệnh từ PC (Serial)
    if (serialComm.coLenhMoi()) {
        serialComm.docLenh();
        g_mode       = serialComm.getMode();
        g_bienSoVao  = serialComm.getBienSoVao();
        g_bienSoRa   = serialComm.getBienSoRa();
        // Các lệnh điều khiển barie thủ công
        if (g_mode == 1) {
            barrierVao.setTrangThai(serialComm.getDkVao());
            barrierRa.setTrangThai(serialComm.getDkRa());
        }
    }
    
    // === BƯỚC 2: XỬ LÝ LOGIC NGHIỆP VỤ ===
    // Giao toàn bộ xử lý cho module parking_logic
    parking.update(
        g_mode,
        coXeVao, coXeRa,
        coXeO1, coXeO2, coXeO3,
        g_uidVao, g_uidRa,
        g_bienSoVao, g_bienSoRa,
        g_soXe, g_vr, g_dcRa, g_cp
    );
    
    // === BƯỚC 3: ĐIỀU KHIỂN OUTPUT DỰA TRÊN LOGIC ===
    
    // 3.1. Điều khiển barie (module servo_control đã tự xử lý)
    // - parking.update() gọi barrierVao.moVao() / dongVao() / moRa() / dongRa()
    
    // 3.2. Cập nhật đèn báo vị trí đỗ
    sensors.capNhatDenBao();
    
    // 3.3. Bật/tắt còi tùy theo sự kiện
    if (parking.coSuKienMoi()) {
        ledBuzzer.beep(parking.getLoaiSuKien());  // WELCOME/BYE/ERROR/FULL
    }
    
    // === BƯỚC 4: GỬI DỮ LIỆU VỀ PC ===
    // Gửi trạng thái hiện tại mỗi 200ms (không gửi liên tục để tránh nghẽn Serial)
    serialComm.guiTrangThai(
        g_mode,
        barrierVao.isMo(),
        barrierRa.isMo(),
        g_cp,
        g_vr,
        g_dcRa,
        g_soXe
    );
    
    // === BƯỚC 5: RESET CÁC CỜ TẠM ===
    // Sau khi xử lý xong, reset các cờ để tránh xử lý lặp lại
    g_vr = 0;
    g_cp = false;
    g_dcRa = 0;
}