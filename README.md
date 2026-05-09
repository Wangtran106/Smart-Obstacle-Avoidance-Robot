# 🤖 Smart Obstacle Avoidance & Wall-Follower Robot

Dự án này là hệ thống điều khiển Robot tự hành thông minh dựa trên nền tảng **Arduino**. Robot được trang bị 3 cảm biến siêu âm để quét môi trường xung quanh, giúp nó có khả năng tự động tránh vật cản và thực hiện thuật toán bám tường (Wall Following) để di chuyển trong mê cung hoặc các hành lang hẹp.

---

## 📋 Mục lục
1. [Giới thiệu](#giới-thiệu)
2. [Linh kiện phần cứng](#linh-kiện-phần-cứng)
3. [Sơ đồ đấu nối (Pinout)](#sơ-đồ-đấu-nối-pinout)
4. [Phân tích thuật toán điều khiển](#phân-tích-thuật-toán-điều-khiển)
5. [Cấu trúc mã nguồn](#cấu-trúc-mã-nguồn)
6. [Hướng dẫn cài đặt](#hướng-dẫn-cài-đặt)

---

## 🌟 Giới thiệu
Robot sử dụng 3 cảm biến siêu âm HC-SR04 đặt ở 3 hướng: **Trái - Giữa - Phải**. Dữ liệu từ các cảm biến này được xử lý theo thời gian thực để điều khiển mạch cầu H L298N, từ đó điều chỉnh hướng và tốc độ của hai động cơ DC. Điểm đặc biệt của dự án là khả năng **ưu tiên bám tường trái**, cho phép robot tự tìm đường thoát trong các không gian có cấu trúc.

---

## 🛠 Linh kiện phần cứng
| Linh kiện | Số lượng | Chú thích |
| :--- | :--- | :--- |
| **Arduino Uno/Nano** | 1 | Bộ não điều khiển trung tâm |
| **HC-SR04** | 3 | Cảm biến đo khoảng cách siêu âm |
| **L298N Motor Driver** | 1 | Điều khiển hướng và tốc độ động cơ |
| **Động cơ DC Gear** | 2 | Động cơ truyền động bánh xe |
| **Pin Li-ion 18650** | 2-3 | Nguồn cấp cho robot (7.4V - 11.1V) |
| **Khung xe Robot** | 1 | Loại 2 bánh hoặc 4 bánh |

---

## 📌 Sơ đồ đấu nối (Pinout)

### 1. Cảm biến siêu âm (Ultrasonic Sensors)
- **Cảm biến Trái (Left):** Trig -> `A1`, Echo -> `A0`
- **Cảm biến Giữa (Middle):** Trig -> `A2`, Echo -> `A3`
- **Cảm biến Phải (Right):** Trig -> `A4`, Echo -> `A5`

### 2. Mạch điều khiển động cơ (L298N)
- **Motor A (Trái):** IN1 -> `5`, IN2 -> `3`, ENA -> `6` (PWM)
- **Motor B (Phải):** IN3 -> `9`, IN4 -> `10`, ENB -> `11` (PWM)

---

## 🧠 Phân tích thuật toán điều khiển

Thuật toán của robot được chia thành 3 giai đoạn chính trong mỗi vòng lặp `loop()`:

### 1. Thu thập dữ liệu (Data Acquisition)
Robot gửi các xung trigger 5 micro-giây đến từng cảm biến và đo thời gian phản hồi (pulseIn). Khoảng cách (cm) được tính bằng công thức:
`Distance = (Time * 0.034) / 2` (trong code là `pingTime / 29 / 2`).

### 2. Phân cấp quyết định (Decision Hierarchy)
Robot đưa ra quyết định dựa trên các điều kiện ưu tiên từ cao xuống thấp:

*   **ƯU TIÊN 1 (Phản xạ khẩn cấp):** Nếu vật cản phía trước quá gần (`middleDistance <= 7cm`), robot sẽ ngay lập tức **Lùi lại** (`back`) để tránh va chạm.
*   **ƯU TIÊN 2 (Phân tích hướng):**
    *   Nếu bên trái có vật cản nhưng bên phải trống -> **Rẽ phải**.
    *   Nếu bên phải có vật cản nhưng bên trái trống -> **Rẽ trái**.
*   **ƯU TIÊN 3 (Duy trì hành trình):** Nếu cả 3 hướng đều thoáng, robot chuyển sang chế độ **Bám tường trái** (`bamtrai`).

### 3. Thuật toán Bám tường trái (Left-Wall Following Algorithm)
Đây là "trí thông minh" giúp robot đi dọc theo các bức tường mà không bị đâm vào hoặc đi quá xa.

1. **Kiểm tra khoảng cách trái:** Robot liên tục so sánh `leftDistance` với giá trị đích là **5cm**.
2. **Hiệu chỉnh (Micro-adjustments):**
    - Nếu `leftDistance < 5cm`: Robot thực hiện lệnh `right(3)` (rẽ phải trong 3ms) để nhích ra xa tường.
    - Nếu `leftDistance > 5cm`: Robot thực hiện lệnh `left(3)` (rẽ trái trong 3ms) để nhích lại gần tường.
3. **Kết quả:** Quá trình này diễn ra liên tục hàng trăm lần mỗi giây, tạo ra chuyển động bám tường mượt mà.

---

## 📂 Cấu trúc mã nguồn
- `void setup()`: Khởi tạo các chân Input/Output và Serial.
- `void loop()`: Đọc cảm biến liên tục và kiểm tra điều kiện rẽ.
- `void right(int a)`, `void left(int a)`...: Các hàm điều khiển chuyển động cơ bản với tham số `a` là thời gian trễ (delay).
- `void bamtrai()`: Hàm xử lý logic bám tường.

---

## 🚀 Hướng dẫn cài đặt
1.  Tải xuống file `Test02.ino`.
2.  Mở bằng **Arduino IDE**.
3.  Kết nối Arduino với máy tính qua cổng USB.
4.  Chọn đúng Board (Uno/Nano) và Port tương ứng.
5.  Nhấn **Upload** để nạp code.
6.  Mở **Serial Monitor** (baudrate 9600) để theo dõi các thông số khoảng cách thực tế từ 3 cảm biến.

---

## ⚖️ Tinh chỉnh (Tuning)
Nếu robot di chuyển không như ý, bạn có thể điều chỉnh các thông số sau:
- `LeftSpeed` / `RightSpeed`: Tăng giảm để robot đi thẳng hơn (do sai số động cơ).
- Khoảng cách `7cm` trong các câu lệnh `if`: Tăng lên nếu robot di chuyển với tốc độ cao để tránh va chạm kịp thời.

---
*Dự án được phát triển bởi **Wangtran106**.*
