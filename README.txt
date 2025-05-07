# Họ và tên: Đào Tiến Tưởng - MSV: 24022841
# SDL Project - Brick Breaker

## Giới thiệu về game
Brick Breaker là một game đơn giản được phát triển bằng ngôn ngữ lập trình C++ sử dụng thư viện SDL2, nơi người chơi điều khiển một thanh trượt để đỡ quả bóng, phá vỡ các viên gạch bằng một quả bóng. Trò chơi mang lại trải nghiệm thú vị và thư giãn với các cơ chế va chạm vật lý cơ bản. Người chơi có thể dùng game này để giải trí và thư giãn sau một ngày học tập và làm việc mệt mỏi nên game không có quá nhiều sự cạnh tranh và căng thẳng nên không có phần high score và đồ họa game được thiết kế dựa trên chủ đề thiên nhiên,âm thanh vui nhộn.	 

---

## 🗂️Cấu trúc dự án
Dưới đây là cấu trúc thư mục và mô tả các thành phần chính:

```
├── src/                # Mã nguồn chính của game
│   ├── main.cpp        # khởi tạo,vòng lặp chính,hiển thị menu screen&win screen
│   ├── brick.cpp       # Xử lý gạch trong game:tao gạch,check va chạm,kiểm tra điều kiện level up
│   ├── gameover_screen.cpp      # xử lí màn hình khi game over
│   ├── collision.cpp   # Xử lý logic va chạm bóng với gạch kĩ hơn,fix bug bóng chạy xuyên gạch
│   ├── levelup_effect.cpp       # Xử lý hiệu ứng chữ "level up"
│   ├── menu.cpp        # Xử lý logic menu
│   ├── resource.cpp    # Quản lí tài nguyên
│   ├── varball+bar.cpp # Thiết lập các giá trị cơ bản cho bóng và thanh
│   ├── win_screen.cpp  # Thiết lập màn hình win game
├── header              # Chứa các tệp header
├── assets/             # Tài nguyên của game(bao gồm cả âm thanh và hình ảnh dùng trong game)
├── MinGW/              # Công cụ và thư viện để biên dịch các ứng dụng C++
├── game.exe            # File game.exe
├── PixelGame.ttf       # Font chữ sử dụng trong game
├── README.md           # Hướng dẫn chi tiết
```

---

## **Tính năng chính của game**

- **Điều khiển đơn giản:**  
  Trong màn hình menu, sử dụng mũi tên lên xuống để trỏ vào Start hoặc Exit sau đó nhấn Enter để chọn.
  Chỉ cần dùng phím mũi tên trái/phải là điều khiển paddle. Dễ chơi, ai cũng làm quen nhanh.

- **Bóng bật vui tai:**  
  Bóng sẽ nảy qua lại khi va vào paddle hoặc gạch.
  Bóng va chạm vào paddle sẽ có âm thanh pop.

- **Phá gạch để tăng level:**  
  Mỗi level sẽ có số lượng gạch khác nhau ,sau khi phá hết sẽ level up.
  Khi level up số lượng gạch sẽ thăng thêm,đông thời tốc độ bóng cũng sẽ tăng

- **Âm thanh & giao diện:**  
  Có nhạc nền nghe chill khi chơi, kèm theo hiệu ứng âm thanh mỗi lần bóng va chạm. Game over cũng có nhạc riêng. Giao diện thì đơn giản, gắn với thiên nhiên, dễ nhìn, tập trung vào gameplay.

- **Cách chơi đơn giản:**
 Chỉ cần dùng thanh paddle đỡ bóng sao cho không rơi khỏi màn hình là được.

- **Khi game over:**  
  Khi bóng rơi khỏi màn hình,sẽ có màn hình thông báo:
  + Nhấn ESC để thoát game 
  + Bấm bất kì phím nào để tiếp tục chơi lại level hiện tại(bấm nhầm sẽ khiến người chơi chơi tiếp mà không nỡ thoát :) )

---

## Hướng dẫn cài đặt và chạy game
### Yêu cầu hệ thống
- Hệ điều hành: Windows

### Cài đặt
1. **Clone dự án từ GitHub:**
   ```bash
   git clone https://github.com/tuongpsa/btlk2.git
   ```

2. Cài đặt thư viện SDL2:
- Hướng dẫn cài đặt 
+ Đối với VS Code chỉ cần clone về mà không yêu cầu cài đặt SDL2 từ trước vì trong project đã có đầy đủ.
Chỉ cần thay đổi các đường dẫn trong các file .json phù hợp với máy clone về.
+ Đối với Code:Blocks tham khảo link (https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/codeblocks/index.php)

3. Build dự án:
+VSCODE:
   Mở Terminal (CTRL + `) sau đó nhấn tổ hợp phím Ctrl+ Shift + B
+CODE:BLOCKS:
   1.Tạo Project mới
   2.Thêm mã nguồn
   3.Copy các file .dll có sắn trong project đã clone vào cùng thư mục với file .exe	
   4.Bấm Build (hoặc F9) để biên dịch.

4. Chạy trò chơi:
+VSCODE:
   Trong Terminal gõ lệnh ./game.exe
+CODE:BLOCKS:
   Bấm Run (hoặc Ctrl + F10) để chạy chương trình.
---

## 📚 Nguồn tham khảo

- **Logic va chạm:**  
  Một vài đoạn logic tham khảo từ [Lazy Foo' SDL Tutorials](https://lazyfoo.net/tutorials/SDL/)

- **Tài nguyên đồ họa:**  
  - Paddle, bóng, gạch tham khảo từ trang kennel.nl,
  - Background từ: [Free Nature Backgrounds Pixel Art](https://craftpix.net/freebies/free-nature-backgrounds-pixel-art/?num=1&count=52&sq=nature&pos=3)
- **Âm thanh:**
  Sưu tập trên Youtube
---

## Đóng góp
Nếu bạn có ý tưởng hoặc phát hiện lỗi, vui lòng tạo issue hoặc pull request trên repository này.
---

## Tác giả
- **Email**: [daotientuong2006@gmail.com]
---

## Ngưỡng điểm mong muốn 8 - 8.5
- Lý do em muốn được ngưỡng điểm này là vì:
🎮 1. Tự viết game từ đầu bằng SDL2
	-tự thiết kế cấu trúc game, không copy code mẫu sẵn.
	-dùng SDL2.
	-tự xử lý luồng game (main loop), logic cập nhật, render, hiệu ứng

🖼️ 2. Có đồ họa riêng
	-Dùng texture PNG cho bóng, thanh đỡ, gạch (thay vì chỉ vẽ hình chữ nhật).
	-Có nhiều background thay đổi theo level
	-Có màn hình riêng cho Game Over, Level Up, và có xử lý hiệu ứng nhấp nháy.

🔊 3. Âm thanh và nhạc nền
Dùng SDL_mixer để:
	-Phát nhạc nền cho menu, game, game over (Mix_Music).
	-Phát hiệu ứng khi đập trúng gạch, chọn menu... (Mix_Chunk).
	-Quản lý âm thanh có tổ chức (sử dụng Mix_AllocateChannels, play/halt nhạc khi đổi màn hình).

🎯 4. Xử lý va chạm có thuật toán
	-Xử lý va chạm bóng – gạch – thanh đỡ bằng thuật toán tính theo từng bước nhỏ (anti-tunneling do AI hướng dẫn).
	-Phân biệt va chạm theo trục X hay Y để đổi hướng bóng đúng cách.
	-Có tính toán phản xạ vật lý cơ bản.

⏱️ 5. Hiệu ứng chuyển động mượt (delta time)
	-Game tính deltaTime mỗi khung hình → chuyển động mượt, không phụ thuộc FPS.(tránh một số lỗi như bóng xuyên qua gạch hoặc bóng kẹt ở các cạnh)
	-Áp dụng cho bóng di chuyển và va chạm.

💡 6. Cấu trúc mã rõ ràng, chia thành module
	 -Đã chia thành các file riêng:
 menu.cpp, gameover_screen.cpp, levelup_effect.cpp, resources.cpp, collision.cpp,...
	-Tách cả .h và .cpp
🧱 7. Có hệ thống gạch với HP
	-Gạch không chỉ bị phá bởi 1 lần chạm mà có hp giảm dần.

🧩 8. Biến động theo level
	-Có biến leveltmp, thay đổi background theo level.
	-Có thể dễ dàng mở rộng số lượng level.
	-Có hiệu ứng “Level Up” nhấp nháy.

💫9. **Cải tiến có thể mở rộng**:  
   9.1 Thêm chức năng highscore đồng thời thay đổi khi game over phải reset lại level 1 nếu không thì highscore trở nên không có ý nghĩa gì.
   9.2 Thêm Hp cho người chơi.
   9.3 Hiện tại khi level thì sẽ tăng số lượng gạch và tăng tốc độ bóng,có thể rút ngắn chiều dài paddle để tăng độ khó.
   9.4 Thêm các hiệu ứng cho gạch khi bị vỡ (tạo nhiều particle bay ra).
   
