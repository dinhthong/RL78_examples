# Intro
- Author: Dong Trinh Sy
# Dong's comments
- Chương trình cấu hình đầy đủ tất cả các chân và chức năng của dtap phiên bản mới
- Chương trình chỉ porting "keyboard.c" và "keyboard.h"
- Các file khác được thêm vào, chỉ có chức năng hỗ trợ cho 2 file trên (chưa được porting hoàn toàn)
- Hàm main(). Chương trình cho gọi hàm read_keyboard() trong "keyboard.c" để xác minh tính đúng đắn của file "keyboard.c"
- Chương trình demo bằng cách, cắm dây uart vào máy tính, chọn baud 9600. Nối dây từ mạch bàn phím vào board renesas. Bấm phím nào từ bàn phím thì màn hình uart sẽ hiển thị số đó.
# Peripherals pin
- GPIO interrupt: P55. On starter kit: wire P55 with P01 (INTP5 button), to use button SW2 as interrupt source.
- UART2: P04. TXD2