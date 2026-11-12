BÀI TẬP THỰC HÀNH OOP

HỆ THỐNG QUẢN LÝ BÃI ĐỖ XE

GIAI ĐOẠN 1

Đề bài chung cho tất cả các giai đoạn

Sinh viên sẽ thiết kế và xây dựng một hệ thống quản lý bãi đỗ xe bằng C++ theo nguyên lý OOP. Hệ thống cho phép:

• Tạo và quản lý nhiều bãi đỗ xe (parking lots) với các kích thước khác nhau.

• Tạo và quản lý nhiều phương tiện (vehicles) như ô tô, xe máy, xe đạp.

• Thực hiện các thao tác: thêm, xóa, tìm kiếm, hiển thị thông tin.

• Tính toán phí đỗ xe theo quy tắc nghiệp vụ.

• Thống kê và báo cáo dữ liệu.

Yêu cầu cốt lõi: Xây dựng các lớp đối tượng (ParkingLot, Vehicle, SystemInterface) và xử lý các thao tác thêm, xóa, hiển thị thông tin một cách có tổ chức, đúng đắn về mặt thiết kế OOP.

MỤC TIÊU & YÊU CẦU KỸ THUẬT
• Chủ đề: Đóng gói (Encapsulation), Thiết kế Lớp (Class), Biến đơn và Luồng điều khiển cơ bản.

• Mục tiêu: Thiết kế ứng dụng console hướng đối tượng quản lý bãi đỗ xe cho một công ty.

• Hạn chế bắt buộc (Strict Constraints):

  1. TÍNH ĐÓNG GÓI: Tất cả các thuộc tính (instance variables) của lớp phải ở phạm vi private. Tương tác dữ liệu bắt buộc thông qua các phương thức public (Getters, Setters, Constructors).

  2. KHÔNG SỬ DỤNG MẢNG VÀ CON TRỎ:Tuyệt đối KHÔNG sử dụng Mảng tĩnh(C-style array), MảngC++(std::array),Mảngđộng/Vector(std::vector),hay Con trỏ (pointers / new / delete).

  3. LƯU TRỮ: Quản lý số lượng đối tượng cố định thông qua các biến đối tượng đơn lẻ và biến cờ trạng thái (boolean flags).
CẤU TRÚC VÀ THIẾT KẾ CÁC LỚP (CLASS SPECIFICATIONS)
Chương trình gồm 3 lớp chính:

2.1 Lớp 1: Vehicle (Đại diện cho một phương tiện đỗ)

• Thuộc tính (private):

– int vehicleID: Mã định danh duy nhất của xe.

– std::string vehicleType: Loại xe (Chỉ nhận 3 giá trị: "Car", "Motorcycle", "Bicycle", không phân biệt chữ hoa/thường).

– int entryTime: Giờ vào bãi (Số nguyên từ 0 đến 23, trong đó 0 = 12am, 23 = 11pm).

– int parkingDuration: Số giờ đỗ dự kiến (Số nguyên từ 1 đến 23, đảm bảo trong cùng một ngày).

– double parkingFee: Phí đỗ xe được tính toán (đơn vị: VNĐ).

– bool isOccupied: Cờ xác định vị trí xe này có đang chứa dữ liệu thực hay không (mặc định false).

• Phương thức (public):

– Constructor mặc định và Constructor có tham số đầy đủ.

– Các hàm Getters / Setters cho tất cả thuộc tính.

– void calculateFee(): Hàm tính phí đỗ xe tự động theo quy tắc ở Mục 3.

– void display(): In thông tin chi tiết của xe ra màn hình.

2.2 Lớp 2: ParkingLot (Đại diện cho một bãi đỗ xe)

• Thuộc tính (private):

– int parkID: Mã định danh bãi đỗ xe.

– char size: Kích thước bãi đỗ (’S’- Nhỏ, ’M’- Trung bình, ’L’- Lớn):

∗ S (Small): Chứa tối đa 1 xe (vehicle1).

∗ M(Medium): Chứa tối đa 2 xe (vehicle1, vehicle2).

∗ L (Large): Chứa tối đa 3 xe (vehicle1, vehicle2, vehicle3).
– Vehicle vehicle1, Vehicle vehicle2, Vehicle vehicle3: Các biến đối tượng xe đơn lẻ.

– bool hasVehicle1, bool hasVehicle2, bool hasVehicle3: Cờ kiểm tra trạng thái ô trống.

• Phương thức (public):

– Constructor mặc định và Constructor khởi tạo bãi đỗ theo parkID và size.

– bool addVehicle(const Vehicle& v): Thêm xe vào ô trống phù hợp theo sức chứa của size.

– bool removeVehicle(int vID): Xóa xe khỏi bãi theo mã vehicleID.

– void displayLotInfo(): Hiển thị ID bãi, kích thước và danh sách các xe hiện có.

2.3 Lớp 3: SystemInterface (Giao diện và điều hành hệ thống)

• Thuộc tính (private):

– ParkingLot parkingLot1,ParkingLot parkingLot2, ParkingLot parkingLot3: Quản lý tối đa 3 bãi đỗ xe đơn lẻ.

– bool hasLot1, bool hasLot2, bool hasLot3: Cờ theo dõi bãi đỗ tồn tại.

• Phương thức (public):

– Lớp duy nhất chứa hàm main() và xử lý nhập/xuất Console(std::cin,std::cout).

– void runMenu(): Hiển thị menu và điều phối các chức năng chương trình.

QUY TẮC TÍNH PHÍ ĐỖ XE (PARKING FEE RULES)
Phí đỗ xe dựa trên Loại xe, Thời gian vào bãi (entryTime) và Thời lượng đỗ (parkingDuration):

Biểu phí cơ bản theo giờ:
• Ôtô (Car): $6.00 / giờ.

• Xe máy (Motorcycle): $4.00 / giờ.

• Xe đạp (Bicycle): $2.00 / giờ.

Khung giờ cao điểm (Peak Hours):
• Sáng: từ 6:00 đến trước 10:00 (khung giờ 6, 7, 8, 9).

• Chiều/Tối: từ 15:00 đến trước 19:00 (khung giờ 15, 16, 17, 18).

Công thức tính phí:
• Trong 2 giờ đầu tiên:

– Nếu vào Giờ cao điểm: Áp dụng mức tăng 30% (+30%) so với đơn giá chuẩn.

– Nếu vào Giờ thấp điểm: Áp dụng mức giảm 5% (-5%) so với đơn giá chuẩn.

• Từ giờ thứ 3 trở đi (áp dụng cho các giờ từ giờ thứ 3):

– Giảm giá 10% (-10%) cho đơn giá theo giờ, bất kể vào giờ cao điểm hay thấp điểm.

YÊU CẦU CHỨC NĂNG MENU (MAIN MENU REQUIREMENTS)
Chương trình hiển thị menu lặp lại liên tục cho đến khi người dùng chọn thoát:

Tạo Bãi đỗ xe mới: Nhập parkID và size (’S’, ’M’, ’L’). Tối đa 3 bãi. Kiểm tra trùng lặp ID hoặc vượt quá sức chứa.

Thêm xe vào bãi đỗ: Nhập thông tin xe (vehicleID, vehicleType, entryTime, parkingDuration). Tự động xếp vào bãi đỗ còn chỗ thích hợp dựa trên size. Tự động tính parkingFee.

Xóa một Bãi đỗ xe: Nhập parkID để xóa bãi đỗ ra khỏi hệ thống.

Lấy xe ra khỏi bãi đỗ: Nhập vehicleID để lấy xe ra khỏi bãi.

Hiển thị danh sách tất cả các Bãi đỗ xe: Liệt kê thông tin tổng quan của các bãi đỗ hiện có (ID, kích thước, số lượng xe).

Hiển thị danh sách xe theo bãi cụ thể: Nhập parkID, in ra thông tin chi tiết từng xe trong bãi đó.

Liệt kê xe theo loại phương tiện: Nhập loại xe (Car/Motorcycle/Bicycle), in danh sách các xe khớp loại và bãi đỗ tương ứng.

Xem báo cáo tóm tắt phí đỗ xe trung bình: Tính và hiển thị phí đỗ xe trung bình cho từng loại xe trên toàn hệ thống và phân tích chi tiết theo từng bãi đỗ.

Thoát chương trình.
