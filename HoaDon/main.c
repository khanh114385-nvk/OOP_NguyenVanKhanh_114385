#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct NguoiBan {
    string tenCuaHang;
    string tenNguoiBan;
    string diaChi;
    string soDienThoai;
};

struct KhachHang {
    string hoTen;
    string diaChi;
    string soDienThoai;
};

struct MatHang {
    string tenHang;
    string donViTinh;
    int soLuong;
    long long donGia;
    long long thanhTien;
};

struct HoaDon {
    string soHoaDon;
    string ngayLap;
    NguoiBan nguoiBan;
    KhachHang khachHang;
    MatHang *dsMatHang;
    int soMatHang;
    long long tongTienHang;
    int thueGTGT;
    long long tienThue;
    long long tongThanhToan;
};

void nhapHoaDon(HoaDon &hd) {
    cout << "=== NHAP THONG TIN HOA DON ===\n";
    cout << "So hoa don: ";
    getline(cin >> ws, hd.soHoaDon);
    cout << "Ngay lap (dd/mm/yyyy): ";
    getline(cin >> ws, hd.ngayLap);

    cout << "\n--- Thong tin nguoi ban ---\n";
    cout << "Ten cua hang / doanh nghiep: ";
    getline(cin >> ws, hd.nguoiBan.tenCuaHang);
    cout << "Ho ten nguoi ban hang: ";
    getline(cin >> ws, hd.nguoiBan.tenNguoiBan);
    cout << "Dia chi cua hang: ";
    getline(cin >> ws, hd.nguoiBan.diaChi);
    cout << "So dien thoai cua hang: ";
    getline(cin >> ws, hd.nguoiBan.soDienThoai);

    cout << "\n--- Thong tin khach hang ---\n";
    cout << "Ho ten khach hang: ";
    getline(cin >> ws, hd.khachHang.hoTen);
    cout << "Dia chi khach hang: ";
    getline(cin >> ws, hd.khachHang.diaChi);
    cout << "So dien thoai khach hang: ";
    getline(cin >> ws, hd.khachHang.soDienThoai);

    cout << "\n--- Nhap danh sach mat hang ---\n";
    cout << "Nhap so luong mat hang: ";
    cin >> hd.soMatHang;

    hd.dsMatHang = new MatHang[hd.soMatHang];
    hd.tongTienHang = 0;

    for (int i = 0; i < hd.soMatHang; i++) {
        cout << "\nMat hang thu " << i + 1 << ":\n";
        cout << "  Ten hang hoa: ";
        getline(cin >> ws, hd.dsMatHang[i].tenHang);
        cout << "  Don vi tinh (Cai, Hop, Chiec...): ";
        getline(cin >> ws, hd.dsMatHang[i].donViTinh);
        cout << "  So luong: ";
        cin >> hd.dsMatHang[i].soLuong;
        cout << "  Don gia: ";
        cin >> hd.dsMatHang[i].donGia;

        hd.dsMatHang[i].thanhTien = hd.dsMatHang[i].soLuong * hd.dsMatHang[i].donGia;
        hd.tongTienHang += hd.dsMatHang[i].thanhTien;
    }

    cout << "\nNhap thue GTGT (%): ";
    cin >> hd.thueGTGT;

    hd.tienThue = hd.tongTienHang * hd.thueGTGT / 100;
    hd.tongThanhToan = hd.tongTienHang + hd.tienThue;
}

void inHoaDon(const HoaDon &hd) {
    cout << "\n=========================================================================\n";
    cout << "CUA HANG: " << hd.nguoiBan.tenCuaHang << "\n";
    cout << "Dia chi: " << hd.nguoiBan.diaChi << " | DT: " << hd.nguoiBan.soDienThoai << "\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << "                         HOA DON BAN HANG                                \n";
    cout << "So HD: " << left << setw(35) << hd.soHoaDon << "Ngay: " << hd.ngayLap << "\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << "Khach hang : " << hd.khachHang.hoTen << "\n";
    cout << "Dia chi    : " << hd.khachHang.diaChi << "\n";
    cout << "Dien thoai : " << hd.khachHang.soDienThoai << "\n";
    cout << "-------------------------------------------------------------------------\n";

    cout << left << setw(5) << "STT"
         << setw(30) << "Ten hang hoa"
         << setw(8) << "DVT"
         << right << setw(6) << "SL"
         << setw(12) << "Don gia"
         << setw(12) << "Thanh tien" << "\n";
    cout << "-------------------------------------------------------------------------\n";

    for (int i = 0; i < hd.soMatHang; i++) {
        cout << left << setw(5) << i + 1
             << setw(30) << hd.dsMatHang[i].tenHang
             << setw(8) << hd.dsMatHang[i].donViTinh
             << right << setw(6) << hd.dsMatHang[i].soLuong
             << setw(12) << hd.dsMatHang[i].donGia
             << setw(12) << hd.dsMatHang[i].thanhTien << "\n";
    }

    string nhanThue = "Thue GTGT (" + to_string(hd.thueGTGT) + "%): ";

    cout << "-------------------------------------------------------------------------\n";
    cout << right << setw(61) << "Cong tien hang: " << setw(12) << hd.tongTienHang << "\n";
    cout << right << setw(61) << nhanThue << setw(12) << hd.tienThue << "\n";
    cout << right << setw(61) << "TONG THANH TOAN: " << setw(12) << hd.tongThanhToan << "\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << "Nguoi mua hang: " << left << setw(30) << hd.khachHang.hoTen
         << "Nguoi ban hang: " << hd.nguoiBan.tenNguoiBan << "\n";
    cout << "=========================================================================\n";
}

int main() {
    HoaDon hd;
    nhapHoaDon(hd);
    inHoaDon(hd);
    delete[] hd.dsMatHang;
    hd.dsMatHang = nullptr;
    return 0;
}
