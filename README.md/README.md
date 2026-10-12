# 🚗 Hệ thống bãi đỗ xe thông minh sử dụng nhận diện biển số
# Smart Parking System using License Plate Recognition


## 📖 Giới thiệu

Cùng với sự phát triển của khoa học kỹ thuật và nhu cầu đi lại ngày càng tăng, số lượng phương tiện giao thông trên đường ngày càng nhiều. Điều này dẫn đến nhiều vấn đề trong việc kiểm soát và quản lý phương tiện, đặc biệt là tại các bãi đỗ xe.

**Đồ án này xây dựng một mô hình bãi đỗ xe tự động** sử dụng công nghệ **xử lý ảnh nhận diện biển số xe** kết hợp với **vi điều khiển Arduino Nano** để điều khiển barie ra/vào tự động.

### 🎯 Mục đích

- Hạn chế những vấn đề bất cập của bãi giữ xe hiện nay (tốn nhân công, mất vé, mất xe...)
- Xây dựng mô hình hệ thống quản lý bãi giữ xe tự động
- Ứng dụng công nghệ xử lý ảnh và nhận dạng biển số xe

---

## 🎬 Demo

![Mô hình hoàn thiện](docs/images/mo_hinh_hoan_thien.jpg)

![Giao diện điều khiển](docs/images/giao_dien.jpg)

---

## ✨ Tính năng chính

### 🔄 Hai chế độ hoạt động
- **Tự động (Auto):** Nhận diện biển số + quét thẻ RFID
- **Bằng tay (Manual):** Điều khiển barie qua nút bấm trên giao diện

### 🚗 Chức năng tự động
- ✅ Nhận diện biển số xe vào/ra bằng **2 camera**
- ✅ Quét thẻ từ **RFID** để xác thực
- ✅ Lưu trữ biển số tương ứng với thẻ RFID
- ✅ **Kiểm tra trùng khớp** giữa biển số và thẻ khi xe ra
- ✅ **Đếm số lượng xe** ra/vào (tối đa 3 xe)
- ✅ **Tính thời gian đỗ xe** và phí gửi xe (5k/10k/15k VND)
- ✅ **Đèn báo** trạng thái đầy/trống tại ô đỗ
- ✅ **Loa thông báo**: Mời vào, tạm biệt, sai biển số, hết chỗ
- ✅ **Không đóng barie** khi xe còn tại vị trí (an toàn)

### 🖼️ Chức năng xử lý ảnh
- ✅ Tách biển số từ ảnh chụp webcam
- ✅ Phân đoạn ký tự trong biển số
- ✅ Nhận dạng ký tự bằng **Tesseract OCR**
- ✅ Hiển thị kết quả lên giao diện PyQt5

---

## 🛠️ Công nghệ sử dụng

| Thành phần | Công nghệ |
|---|---|
| **Vi điều khiển** | Arduino Nano (ATmega328P) |
| **Ngôn ngữ firmware** | C/C++ (Arduino IDE) |
| **Ngôn ngữ phần mềm** | Python 3.8+ |
| **Xử lý ảnh** | OpenCV, Tesseract OCR |
| **Giao diện** | PyQt5 |
| **Giao tiếp** | Serial (UART, 9600 baud) |
| **Phần cứng** | Servo SG90, RFID RC522, IR Sensor, Relay 12V, LCD |
| **Thiết kế mạch** | Proteus 8.13 |
| **Quản lý mã nguồn** | Git, GitHub |

---

## 🏗️ Sơ đồ khối hệ thống

![Sơ đồ khối](docs/sơ đồ khối.png)

**Chức năng từng khối:**
- **Laptop:** Bộ xử lý ảnh trung tâm, chạy giao diện GUI
- **Camera 1 & 2:** Thu thập hình ảnh biển số xe vào/ra
- **Arduino Nano:** Điều khiển thiết bị ngoại vi
- **Cảm biến tiệm cận:** Phát hiện xe tại vị trí barie
- **Module RFID:** Đọc thẻ từ
- **Servo:** Điều khiển barie đóng/mở
- **Đèn báo:** Hiển thị trạng thái bãi đỗ

---

## 🔌 Phần cứng (Hardware)

### Sơ đồ nguyên lý
![Schematic](hardware/schematic_diagram.png)

### Sơ đồ kết nối
![Wiring](hardware/wiring_diagram.png)

### Mạch PCB
![PCB](hardware/pcb_layout.png)

### Lưu đồ thuật toán
![Flowchart](hardware/luu_do_thuat_toan.png)

### Danh sách linh kiện

| STT | Linh kiện | Số lượng | Chức năng |
|---|---|---|---|
| 1 | Arduino Nano | 1 | Vi điều khiển trung tâm |
| 2 | Module RFID RC522 | 2 | Đọc thẻ từ vào/ra |
| 3 | Servo SG90 | 2 | Điều khiển barie |
| 4 | Cảm biến hồng ngoại IR01 | 5 | Phát hiện xe |
| 5 | Module Relay 12V | 1 | Điều khiển thiết bị |
| 6 | LCD 16x2 | 1 | Hiển thị trạng thái |
| 7 | LED đỏ/xanh | 6 | Đèn báo |
| 8 | Buzzer | 1 | Còi thông báo |
| 9 | Webcam HD 720 | 2 | Thu thập hình ảnh |
| 10 | Adapter 9VDC | 1 | Cấp nguồn |
| 11 | Mica 5mm & 3mm | — | Khung mô hình |

---

## ⚙️ Nguyên lý hoạt động

### 🚗 Khi xe VÀO
1. Xe đến vị trí trước barie, chắn cảm biến vào (CBV)
2. Người vận hành quét thẻ từ RFID
3. Camera chụp và nhận diện biển số xe
4. Hệ thống **lưu biển số + mã thẻ + thời gian vào**
5. Nếu bãi còn chỗ → Barie mở, xe vào
6. Khi xe qua khỏi cảm biến → Barie đóng lại

### 🚙 Khi xe RA
1. Xe đến vị trí cảm biến ra (CBR), dừng lại
2. Quét thẻ từ RFID
3. Camera chụp và nhận diện biển số
4. Hệ thống **so sánh biển số với thẻ đã quét**
5. Nếu **trùng khớp**:
   - Tính thời gian gửi xe
   - Hiển thị phí: dưới 30s → 5.000 VND, 30-40s → 10.000 VND, trên 40s → 15.000 VND
   - Barie mở, loa thông báo "Tạm biệt"
6. Nếu **không trùng** → Loa thông báo "Thử lại"

---

## 💻 Phần mềm (Software)

### Cấu trúc thư mục dự án
Parking_system_using_license_plate_recognition/
├── README.md
├── LICENSE
├── .gitignore
│
├── firmware/ # Code Arduino
│ ├── SmartParking.ino
│ ├── config.h
│ ├── sensors.h / sensors.cpp
│ ├── rfid.h / rfid.cpp
│ ├── servo_control.h / .cpp
│ ├── led_buzzer.h / .cpp
│ ├── serial_comm.h / .cpp
│ └── parking_logic.h / .cpp
│
├── software/ # Code Python
│ ├── main.py
│ ├── GUID2.ui
│ └── requirements.txt
│
├── hardware/ # Sơ đồ mạch, PCB
│ ├── schematic_diagram.png
│ ├── wiring_diagram.png
│ ├── pcb_layout.png
│ ├── so_do_khoi.png
│ ├── luu_do_thuat_toan.png
│ └── SO_DO_KET_NOI.pdsprj
│
├── docs/ # Báo cáo, tài liệu
│ ├── BAO_CAO.docx
│ ├── file_cat_laser.docx
│ ├── pcb.docx
│ └── images/
│
├── test_images/ # Ảnh test biển số
│ ├── bien.jpg
│ ├── BIEN_SO_2.docx
│ └── BIEN_SO_3.docx
│
└── sound/ # File âm thanh
├── WELCOME.MP3
├── BYE.MP3
├── ERROR.MP3
└── FULL.MP3

text

### Các module chính trong Firmware

| Module | Chức năng |
|---|---|
| `sensors` | Đọc 5 cảm biến hồng ngoại (CBV, CBR, CB1-3) |
| `rfid` | Đọc thẻ RFID vào/ra (2 module RC522) |
| `servo_control` | Điều khiển 2 barie đóng/mở |
| `led_buzzer` | Đèn báo + còi thông báo |
| `serial_comm` | Giao tiếp Serial với PC |
| `parking_logic` | Logic nghiệp vụ (auto/manual) |

### Các hàm chính trong Software

| Hàm | Chức năng |
|---|---|
| `Time()` | Timer 50ms cập nhật giao diện + đọc Serial |
| `xulyanh()` | Nhận diện biển số bằng OpenCV + Tesseract |
| `auto()` / `manual()` | Chuyển chế độ tự động / thủ công |
| `vao()` / `ra()` | Điều khiển barie thủ công |