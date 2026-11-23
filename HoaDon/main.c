#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;
class Nguoi {
protected:
    string hoTen;
    string diaChi;
    string soDienThoai;
public:
    void nhapThongTinChung() {
        cout << "  Ho ten: ";
        getline(cin >> ws, hoTen);
        cout << "  Dia chi: ";
        getline(cin >> ws, diaChi);
        cout << "  So dien thoai: ";
        getline(cin >> ws, soDienThoai);
    }

    string getHoTen() const { return hoTen; }
    string getDiaChi() const { return diaChi; }
    string getSoDienThoai() const { return soDienThoai; }
};

class NguoiBan : public Nguoi {
private:
    string tenCuaHang;
public:
    void nhap() {
        cout << "  Ten cua hang / cong ty: ";
        getline(cin >> ws, tenCuaHang);
        nhapThongTinChung();
    }

    string getTenCuaHang() const { return tenCuaHang; }
};

class KhachHang : public Nguoi {
public:
    void nhap() {
        nhapThongTinChung();
    }
};

class MatHang {
private:
    string tenHang;
    string donViTinh;
    int soLuong;
    long long donGia;
public:
    MatHang() {
        soLuong = 0;
        donGia = 0;
    }
    void nhap() {
        cout << "  Ten hang hoa: ";
        getline(cin >> ws, tenHang);
        cout << "  Don vi tinh: ";
        getline(cin >> ws, donViTinh);
        cout << "  So luong: ";
        cin >> soLuong;
        cout << "  Don gia: ";
        cin >> donGia;
    }
    long long tinhThanhTien() const {
        return soLuong * donGia;
    }

    void xuat(int stt) const {
        cout << left << setw(5) << stt
             << setw(30) << tenHang
             << setw(8) << donViTinh
             << right << setw(6) << soLuong
             << setw(12) << donGia
             << setw(12) << tinhThanhTien() << "\n";
    }
};

class HoaDon {
private:
    string soHoaDon;
    string ngayLap;
    NguoiBan nguoiBan;
    KhachHang khachHang;
    MatHang *dsMatHang;
    int soMatHang;
    int thueGTGT;
public:
    HoaDon() {
        dsMatHang = NULL;
        soMatHang = 0;
        thueGTGT = 0;
    }
    ~HoaDon() {
        if (dsMatHang != NULL) {
            delete[] dsMatHang;
            dsMatHang = NULL;
        }
    }
    void nhap() {
        cout << "=== NHAP THONG TIN HOA DON ===\n";
        cout << "So hoa don: ";
        getline(cin >> ws, soHoaDon);
        cout << "Ngay lap (dd/mm/yyyy): ";
        getline(cin >> ws, ngayLap);

        cout << "\n--- Thong tin nguoi ban ---\n";
        nguoiBan.nhap();

        cout << "\n--- Thong tin khach hang ---\n";
        khachHang.nhap();

        cout << "\n--- Danh sach mat hang ---\n";
        cout << "Nhap so luong mat hang: ";
        cin >> soMatHang;

        dsMatHang = new MatHang[soMatHang];
        for (int i = 0; i < soMatHang; i++) {
            cout << "\nMat hang thu " << i + 1 << ":\n";
            dsMatHang[i].nhap();
        }
        cout << "\nNhap thue GTGT (%): ";
        cin >> thueGTGT;
    }
    long long tinhTongTienHang() const {
        long long tong = 0;
        for (int i = 0; i < soMatHang; i++) {
            tong += dsMatHang[i].tinhThanhTien();
        }
        return tong;
    }
    long long tinhTienThue() const {
        return tinhTongTienHang() * thueGTGT / 100;
    }

    long long tinhTongThanhToan() const {
        return tinhTongTienHang() + tinhTienThue();
    }
    void xuat() const {
        cout << "\n===\n";
        cout << "CUA HANG: " << nguoiBan.getTenCuaHang() << "\n";
        cout << "Dia chi: " << nguoiBan.getDiaChi() << " | DT: " << nguoiBan.getSoDienThoai() << "\n";
        cout << "---\n";
        cout << "                         HOA DON BAN HANG                                \n";
        cout << "So HD: " << left << setw(35) << soHoaDon << "Ngay: " << ngayLap << "\n";
        cout << "---\n";
        cout << "Khach hang : " << khachHang.getHoTen() << "\n";
        cout << "Dia chi    : " << khachHang.getDiaChi() << "\n";
        cout << "Dien thoai : " << khachHang.getSoDienThoai() << "\n";
        cout << "---\n";

        cout << left << setw(5) << "STT"
             << setw(30) << "Ten hang hoa"
             << setw(8) << "DVT"
             << right << setw(6) << "SL"
             << setw(12) << "Don gia"
             << setw(12) << "Thanh tien" << "\n";
        cout << "---\n";
        for (int i = 0; i < soMatHang; i++) {
            dsMatHang[i].xuat(i + 1);
        }
        stringstream ss;
        ss << "Thue GTGT (" << thueGTGT << "%): ";
        string nhanThue = ss.str();
        cout << "---\n";
        cout << right << setw(61) << "Cong tien hang: " << setw(12) << tinhTongTienHang() << "\n";
        cout << right << setw(61) << nhanThue << setw(12) << tinhTienThue() << "\n";
        cout << right << setw(61) << "TONG THANH TOAN: " << setw(12) << tinhTongThanhToan() << "\n";
        cout << "---\n";
        cout << "Nguoi mua hang: " << left << setw(30) << khachHang.getHoTen()
             << "Nguoi ban hang: " << nguoiBan.getHoTen() << "\n";
        cout << "===\n";
    }
};
int main() {
    HoaDon hd;
    hd.nhap();
    hd.xuat();
    return 0;
}
