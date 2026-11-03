#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

class Xe {
private:
    int maXe;
    string loaiXe;
    int gioVao;
    int thoiGianDo;
    double phiDoXe;
    bool dangChiemCho;
public:
    Xe();
    Xe(int ma, const string& loai, int gio, int thoiLuong);
    int layMaXe() const;
    string layLoaiXe() const;
    int layGioVao() const;
    int layThoiGianDo() const;
    double layPhiDoXe() const;
    bool layDangChiemCho() const;
    void ganMaXe(int ma);
    void ganLoaiXe(const string& loai);
    void ganGioVao(int gio);
    void ganThoiLuongDo(int thoiLuong);
    void ganPhiDoXe(double phi);
    void ganDangChiemCho(bool trangThai);
    static string chuanHoaLoaiXe(const string& loai);
    static bool laLoaiXeHopLe(const string& loai);
    void tinhPhiDoXe();
    void hienThi() const;
};

Xe::Xe() {
    maXe = 0;
    loaiXe = "";
    gioVao = 0;
    thoiGianDo = 1;
    phiDoXe = 0;
    dangChiemCho = false;
}

Xe::Xe(int ma, const string& loai, int gio, int thoiLuong) {
    maXe = ma;
    loaiXe = chuanHoaLoaiXe(loai);
    gioVao = gio;
    thoiGianDo = thoiLuong;
    dangChiemCho = false;
    tinhPhiDoXe();
}

int Xe::layMaXe() const { return maXe; }
string Xe::layLoaiXe() const { return loaiXe; }
int Xe::layGioVao() const { return gioVao; }
int Xe::layThoiGianDo() const { return thoiGianDo; }
double Xe::layPhiDoXe() const { return phiDoXe; }
bool Xe::layDangChiemCho() const { return dangChiemCho; }

void Xe::ganMaXe(int ma) { maXe = ma; }
void Xe::ganLoaiXe(const string& loai) { loaiXe = chuanHoaLoaiXe(loai); }
void Xe::ganGioVao(int gio) { gioVao = gio; }
void Xe::ganThoiLuongDo(int thoiLuong) { thoiGianDo = thoiLuong; }
void Xe::ganPhiDoXe(double phi) { phiDoXe = phi; }
void Xe::ganDangChiemCho(bool trangThai) { dangChiemCho = trangThai; }

string Xe::chuanHoaLoaiXe(const string& loai) {
    string s = loai;
    for (int i = 0; i < (int)s.size(); i++) {
        s[i] = tolower(s[i]);
    }
    if (s == "car") return "Car";
    if (s == "motorcycle") return "Motorcycle";
    if (s == "bicycle") return "Bicycle";
    return "";
}

bool Xe::laLoaiXeHopLe(const string& loai) {
    return chuanHoaLoaiXe(loai) != "";
}

void Xe::tinhPhiDoXe() {
    double donGia = 0;
    if (loaiXe == "Car") donGia = 6;
    if (loaiXe == "Motorcycle") donGia = 4;
    if (loaiXe == "Bicycle") donGia = 2;

    bool gioCaoDiem = (gioVao >= 6 && gioVao <= 9) || (gioVao >= 15 && gioVao <= 18);

    double heSo = 0.95;
    if (gioCaoDiem) heSo = 1.3;

    int gioDau = thoiGianDo;
    int gioSau = 0;
    if (thoiGianDo > 2) {
        gioDau = 2;
        gioSau = thoiGianDo - 2;
    }

    phiDoXe = gioDau * donGia * heSo + gioSau * donGia * 0.9;
}

void Xe::hienThi() const {
    cout << "  Ma xe: " << maXe
         << " | Loai: " << loaiXe
         << " | Gio vao: " << gioVao
         << " | Thoi gian do: " << thoiGianDo
         << " | Phi: " << fixed << setprecision(2) << phiDoXe << endl;
}

class BaiDoXe {
private:
    int maBai;
    char kichThuoc;
    Xe xe1, xe2, xe3;
    bool coXe1, coXe2, coXe3;
public:
    BaiDoXe();
    BaiDoXe(int ma, char size);
    int layMaBai() const;
    char layKichThuoc() const;
    int laySucChua() const;
    int demXe() const;
    bool themXe(const Xe& v);
    bool xoaXe(int vID);
    bool coXeVoiMa(int vID) const;
    void hienThiThongTinBai() const;
    int hienThiXeTheoLoai(const string& loai) const;
    int demXeTheoLoai(const string& loai) const;
    double tongPhiTheoLoai(const string& loai) const;
};

BaiDoXe::BaiDoXe() {
    maBai = 0;
    kichThuoc = 'S';
    coXe1 = false;
    coXe2 = false;
    coXe3 = false;
}

BaiDoXe::BaiDoXe(int ma, char size) {
    maBai = ma;
    kichThuoc = toupper(size);
    coXe1 = false;
    coXe2 = false;
    coXe3 = false;
}

int BaiDoXe::layMaBai() const { return maBai; }
char BaiDoXe::layKichThuoc() const { return kichThuoc; }

int BaiDoXe::laySucChua() const {
    if (kichThuoc == 'S') return 1;
    if (kichThuoc == 'M') return 2;
    return 3;
}

int BaiDoXe::demXe() const {
    int dem = 0;
    if (coXe1) dem++;
    if (coXe2) dem++;
    if (coXe3) dem++;
    return dem;
}

bool BaiDoXe::themXe(const Xe& v) {
    int sucChua = laySucChua();
    if (!coXe1) {
        xe1 = v;
        xe1.ganDangChiemCho(true);
        coXe1 = true;
        return true;
    }
    if (!coXe2 && sucChua >= 2) {
        xe2 = v;
        xe2.ganDangChiemCho(true);
        coXe2 = true;
        return true;
    }
    if (!coXe3 && sucChua >= 3) {
        xe3 = v;
        xe3.ganDangChiemCho(true);
        coXe3 = true;
        return true;
    }
    return false;
}

bool BaiDoXe::xoaXe(int vID) {
    if (coXe1 && xe1.layMaXe() == vID) {
        coXe1 = false;
        return true;
    }
    if (coXe2 && xe2.layMaXe() == vID) {
        coXe2 = false;
        return true;
    }
    if (coXe3 && xe3.layMaXe() == vID) {
        coXe3 = false;
        return true;
    }
    return false;
}

bool BaiDoXe::coXeVoiMa(int vID) const {
    if (coXe1 && xe1.layMaXe() == vID) return true;
    if (coXe2 && xe2.layMaXe() == vID) return true;
    if (coXe3 && xe3.layMaXe() == vID) return true;
    return false;
}

void BaiDoXe::hienThiThongTinBai() const {
    cout << "Bai ID: " << maBai << " | Kich thuoc: " << kichThuoc
         << " | So xe: " << demXe() << "/" << laySucChua() << endl;
    if (coXe1) xe1.hienThi();
    if (coXe2) xe2.hienThi();
    if (coXe3) xe3.hienThi();
}

int BaiDoXe::hienThiXeTheoLoai(const string& loai) const {
    int dem = 0;
    if (coXe1 && xe1.layLoaiXe() == loai) {
        cout << "Bai ID " << maBai << ":";
        xe1.hienThi();
        dem++;
    }
    if (coXe2 && xe2.layLoaiXe() == loai) {
        cout << "Bai ID " << maBai << ":";
        xe2.hienThi();
        dem++;
    }
    if (coXe3 && xe3.layLoaiXe() == loai) {
        cout << "Bai ID " << maBai << ":";
        xe3.hienThi();
        dem++;
    }
    return dem;
}

int BaiDoXe::demXeTheoLoai(const string& loai) const {
    int dem = 0;
    if (coXe1 && xe1.layLoaiXe() == loai) dem++;
    if (coXe2 && xe2.layLoaiXe() == loai) dem++;
    if (coXe3 && xe3.layLoaiXe() == loai) dem++;
    return dem;
}

double BaiDoXe::tongPhiTheoLoai(const string& loai) const {
    double tong = 0;
    if (coXe1 && xe1.layLoaiXe() == loai) tong += xe1.layPhiDoXe();
    if (coXe2 && xe2.layLoaiXe() == loai) tong += xe2.layPhiDoXe();
    if (coXe3 && xe3.layLoaiXe() == loai) tong += xe3.layPhiDoXe();
    return tong;
}

class GiaoDien {
private:
    BaiDoXe baiDo1, baiDo2, baiDo3;
    bool coBai1, coBai2, coBai3;

    BaiDoXe& layBai(int vt);
    bool coBai(int vt) const;
    int timBaiTheoMa(int maBai);
    bool xeDaTonTai(int maXe);
    int docSo(const string& thongBao);

    void taoBaiMoi();
    void themXeVaoBai();
    void xoaBai();
    void layXeRa();
    void hienThiTatCaBai();
    void hienThiXeTheoBai();
    void lietKeTheoLoai();
    void baoCaoPhi();
    void baoCaoMotLoai(const string& loai);
public:
    GiaoDien();
    void runMenu();
};

GiaoDien::GiaoDien() {
    coBai1 = false;
    coBai2 = false;
    coBai3 = false;
}

BaiDoXe& GiaoDien::layBai(int vt) {
    if (vt == 1) return baiDo1;
    if (vt == 2) return baiDo2;
    return baiDo3;
}

bool GiaoDien::coBai(int vt) const {
    if (vt == 1) return coBai1;
    if (vt == 2) return coBai2;
    return coBai3;
}

int GiaoDien::timBaiTheoMa(int maBai) {
    for (int vt = 1; vt <= 3; vt++) {
        if (coBai(vt) && layBai(vt).layMaBai() == maBai) return vt;
    }
    return 0;
}

bool GiaoDien::xeDaTonTai(int maXe) {
    for (int vt = 1; vt <= 3; vt++) {
        if (coBai(vt) && layBai(vt).coXeVoiMa(maXe)) return true;
    }
    return false;
}

int GiaoDien::docSo(const string& thongBao) {
    int x;
    cout << thongBao;
    cin >> x;
    while (cin.fail()) {
        if (cin.eof()) exit(0);
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Vui long nhap so nguyen: ";
        cin >> x;
    }
    return x;
}

void GiaoDien::taoBaiMoi() {
    int vt = 0;
    if (!coBai1) vt = 1;
    else if (!coBai2) vt = 2;
    else if (!coBai3) vt = 3;

    if (vt == 0) {
        cout << "Da co du 3 bai do, khong the tao them!" << endl;
        return;
    }

    int ma = docSo("Nhap parkID: ");
    if (timBaiTheoMa(ma) != 0) {
        cout << "parkID da ton tai!" << endl;
        return;
    }

    char size;
    cout << "Nhap size (S/M/L): ";
    cin >> size;
    size = toupper(size);
    if (size != 'S' && size != 'M' && size != 'L') {
        cout << "Kich thuoc khong hop le!" << endl;
        return;
    }

    layBai(vt) = BaiDoXe(ma, size);
    if (vt == 1) coBai1 = true;
    if (vt == 2) coBai2 = true;
    if (vt == 3) coBai3 = true;
    cout << "Tao bai do thanh cong!" << endl;
}

void GiaoDien::themXeVaoBai() {
    int ma = docSo("Nhap vehicleID: ");
    if (xeDaTonTai(ma)) {
        cout << "vehicleID da ton tai!" << endl;
        return;
    }

    string loai;
    cout << "Nhap vehicleType (Car/Motorcycle/Bicycle): ";
    cin >> loai;
    if (!Xe::laLoaiXeHopLe(loai)) {
        cout << "Loai xe khong hop le!" << endl;
        return;
    }

    int gio = docSo("Nhap entryTime (0-23): ");
    if (gio < 0 || gio > 23) {
        cout << "Gio vao khong hop le!" << endl;
        return;
    }

    int thoiLuong = docSo("Nhap parkingDuration (1-23): ");
    if (thoiLuong < 1 || thoiLuong > 23) {
        cout << "Thoi gian do khong hop le!" << endl;
        return;
    }

    Xe xe(ma, loai, gio, thoiLuong);

    for (int vt = 1; vt <= 3; vt++) {
        if (coBai(vt) && layBai(vt).themXe(xe)) {
            cout << "Da xep xe vao bai " << layBai(vt).layMaBai() << endl;
            cout << "Phi do xe: " << fixed << setprecision(2) << xe.layPhiDoXe() << endl;
            return;
        }
    }
    cout << "Khong con bai nao con cho phu hop!" << endl;
}

void GiaoDien::xoaBai() {
    int ma = docSo("Nhap parkID can xoa: ");
    int vt = timBaiTheoMa(ma);
    if (vt == 0) {
        cout << "Khong tim thay bai do!" << endl;
        return;
    }
    if (vt == 1) coBai1 = false;
    if (vt == 2) coBai2 = false;
    if (vt == 3) coBai3 = false;
    cout << "Da xoa bai do!" << endl;
}

void GiaoDien::layXeRa() {
    int ma = docSo("Nhap vehicleID: ");
    for (int vt = 1; vt <= 3; vt++) {
        if (coBai(vt) && layBai(vt).xoaXe(ma)) {
            cout << "Da lay xe ra khoi bai " << layBai(vt).layMaBai() << endl;
            return;
        }
    }
    cout << "Khong tim thay xe!" << endl;
}

void GiaoDien::hienThiTatCaBai() {
    if (!coBai1 && !coBai2 && !coBai3) {
        cout << "Chua co bai do nao!" << endl;
        return;
    }
    for (int vt = 1; vt <= 3; vt++) {
        if (coBai(vt)) {
            cout << "Bai ID: " << layBai(vt).layMaBai()
                 << " | Kich thuoc: " << layBai(vt).layKichThuoc()
                 << " | So xe: " << layBai(vt).demXe() << endl;
        }
    }
}

void GiaoDien::hienThiXeTheoBai() {
    int ma = docSo("Nhap parkID: ");
    int vt = timBaiTheoMa(ma);
    if (vt == 0) {
        cout << "Khong tim thay bai do!" << endl;
        return;
    }
    layBai(vt).hienThiThongTinBai();
}

void GiaoDien::lietKeTheoLoai() {
    string loai;
    cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
    cin >> loai;
    loai = Xe::chuanHoaLoaiXe(loai);
    if (loai == "") {
        cout << "Loai xe khong hop le!" << endl;
        return;
    }

    int tong = 0;
    for (int vt = 1; vt <= 3; vt++) {
        if (coBai(vt)) tong += layBai(vt).hienThiXeTheoLoai(loai);
    }
    if (tong == 0) cout << "Khong co xe nao thuoc loai nay!" << endl;
}

void GiaoDien::baoCaoMotLoai(const string& loai) {
    int soXe = 0;
    double tongPhi = 0;
    for (int vt = 1; vt <= 3; vt++) {
        if (coBai(vt)) {
            soXe += layBai(vt).demXeTheoLoai(loai);
            tongPhi += layBai(vt).tongPhiTheoLoai(loai);
        }
    }

    cout << loai << ": ";
    if (soXe == 0) {
        cout << "chua co xe" << endl;
        return;
    }
    cout << "phi trung binh toan he thong = " << fixed << setprecision(2) << tongPhi / soXe << endl;

    for (int vt = 1; vt <= 3; vt++) {
        if (coBai(vt)) {
            int n = layBai(vt).demXeTheoLoai(loai);
            cout << "   Bai " << layBai(vt).layMaBai() << ": ";
            if (n == 0) cout << "khong co xe" << endl;
            else cout << fixed << setprecision(2) << layBai(vt).tongPhiTheoLoai(loai) / n << endl;
        }
    }
}

void GiaoDien::baoCaoPhi() {
    baoCaoMotLoai("Car");
    baoCaoMotLoai("Motorcycle");
    baoCaoMotLoai("Bicycle");
}

void GiaoDien::runMenu() {
    int chon;
    do {
        cout << endl;
        cout << "===== QUAN LY BAI DO XE =====" << endl;
        cout << "1. Tao bai do xe moi" << endl;
        cout << "2. Them xe vao bai do" << endl;
        cout << "3. Xoa mot bai do xe" << endl;
        cout << "4. Lay xe ra khoi bai do" << endl;
        cout << "5. Hien thi danh sach tat ca cac bai do" << endl;
        cout << "6. Hien thi danh sach xe theo bai cu the" << endl;
        cout << "7. Liet ke xe theo loai phuong tien" << endl;
        cout << "8. Bao cao phi do xe trung binh" << endl;
        cout << "9. Thoat chuong trinh" << endl;
        chon = docSo("Nhap lua chon: ");

        if (chon == 1) taoBaiMoi();
        else if (chon == 2) themXeVaoBai();
        else if (chon == 3) xoaBai();
        else if (chon == 4) layXeRa();
        else if (chon == 5) hienThiTatCaBai();
        else if (chon == 6) hienThiXeTheoBai();
        else if (chon == 7) lietKeTheoLoai();
        else if (chon == 8) baoCaoPhi();
        else if (chon != 9) cout << "Lua chon khong hop le!" << endl;
    } while (chon != 9);
}

int main() {
    GiaoDien gd;
    gd.runMenu();
    return 0;
}
