#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;
    double phi_do;
    bool da_co;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    void dat_ma_xe(int ma);
    string lay_loai_xe() const;
    void dat_loai_xe(string loai);
    int lay_gio_vao() const;
    void dat_gio_vao(int gio);
    int lay_tg_do() const;
    void dat_tg_do(int tg);
    double lay_phi_do() const;
    void dat_phi_do(double phi);
    bool lay_da_co() const;
    void dat_da_co(bool tt);

    void tinh_phi();
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0), phi_do(0), da_co(false) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg), phi_do(0), da_co(true) {
    tinh_phi();
}

int phuong_tien::lay_ma_xe() const { return ma_xe; }
void phuong_tien::dat_ma_xe(int ma) { ma_xe = ma; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }
void phuong_tien::dat_loai_xe(string loai) { loai_xe = loai; tinh_phi(); }
int phuong_tien::lay_gio_vao() const { return gio_vao; }
void phuong_tien::dat_gio_vao(int gio) { gio_vao = gio; tinh_phi(); }
int phuong_tien::lay_tg_do() const { return tg_do; }
void phuong_tien::dat_tg_do(int tg) { tg_do = tg; tinh_phi(); }
double phuong_tien::lay_phi_do() const { return phi_do; }
void phuong_tien::dat_phi_do(double phi) { phi_do = phi; }
bool phuong_tien::lay_da_co() const { return da_co; }
void phuong_tien::dat_da_co(bool tt) { da_co = tt; }

void phuong_tien::tinh_phi() {
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    phi_do = 0;
    for (int h = 0; h < tg_do; ++h)
        phi_do += gia * (h < 2 ? (cao_diem ? 1.30 : 0.95) : 0.90);
}

void phuong_tien::hien_thi() const {
    cout << "  ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << phi_do << "\n";
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    phuong_tien pt1, pt2, pt3;
    bool co1, co2, co3;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    void dat_ma(int ma);
    char lay_kich_thuoc() const;
    void dat_kich_thuoc(char kt);

    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi(bool chi_tiet = true) const;
    void hien_thi_loai(string loai) const;
    bool co_loai(string loai, int& dem, double& tong) const;
    void bao_cao() const;
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), co1(false), co2(false), co3(false) {}

bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(toupper(kt)), co1(false), co2(false), co3(false) {}

int bai_xe::lay_ma() const { return ma_bai; }
void bai_xe::dat_ma(int ma) { ma_bai = ma; }
char bai_xe::lay_kich_thuoc() const { return kich_thuoc; }
void bai_xe::dat_kich_thuoc(char kt) { kich_thuoc = toupper(kt); }

bool bai_xe::them(phuong_tien v) {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    v.dat_da_co(true);
    if (cap >= 1 && !co1) { pt1 = v; co1 = true; return true; }
    if (cap >= 2 && !co2) { pt2 = v; co2 = true; return true; }
    if (cap >= 3 && !co3) { pt3 = v; co3 = true; return true; }
    return false;
}

bool bai_xe::xoa(int ma_xe) {
    if (co1 && pt1.lay_ma_xe() == ma_xe) {
        if (co2) { pt1 = pt2; if (co3) { pt2 = pt3; co3 = false; pt3 = phuong_tien(); } else { co2 = false; pt2 = phuong_tien(); } }
        else { co1 = false; pt1 = phuong_tien(); }
        return true;
    }
    if (co2 && pt2.lay_ma_xe() == ma_xe) {
        if (co3) { pt2 = pt3; co3 = false; pt3 = phuong_tien(); } else { co2 = false; pt2 = phuong_tien(); }
        return true;
    }
    if (co3 && pt3.lay_ma_xe() == ma_xe) { co3 = false; pt3 = phuong_tien(); return true; }
    return false;
}

bool bai_xe::chua(int ma_xe) const {
    return (co1 && pt1.lay_ma_xe() == ma_xe) || (co2 && pt2.lay_ma_xe() == ma_xe) || (co3 && pt3.lay_ma_xe() == ma_xe);
}

void bai_xe::hien_thi(bool chi_tiet) const {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    int so_xe = co1 + co2 + co3;
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] " << so_xe << "/" << cap << " xe\n";
    if (!chi_tiet) return;
    if (!so_xe) cout << "  (Bai trong)\n";
    if (co1) pt1.hien_thi();
    if (co2) pt2.hien_thi();
    if (co3) pt3.hien_thi();
}

void bai_xe::hien_thi_loai(string loai) const {
    if (co1 && pt1.lay_loai_xe() == loai) { cout << "  [Bai " << ma_bai << "]"; pt1.hien_thi(); }
    if (co2 && pt2.lay_loai_xe() == loai) { cout << "  [Bai " << ma_bai << "]"; pt2.hien_thi(); }
    if (co3 && pt3.lay_loai_xe() == loai) { cout << "  [Bai " << ma_bai << "]"; pt3.hien_thi(); }
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
    if (co1 && pt1.lay_loai_xe() == loai) { ++dem; tong += pt1.lay_phi_do(); }
    if (co2 && pt2.lay_loai_xe() == loai) { ++dem; tong += pt2.lay_phi_do(); }
    if (co3 && pt3.lay_loai_xe() == loai) { ++dem; tong += pt3.lay_phi_do(); }
    return dem > 0;
}

void bai_xe::bao_cao() const {
    int d; double s;
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "]:\n";
    co_loai("Car", d, s);
    cout << "  Car: " << (d ? to_string(d) + " xe | TB: $" : "khong co xe\n");
    if (d) cout << fixed << setprecision(2) << s / d << "\n";
    co_loai("Motorcycle", d, s);
    cout << "  Motorcycle: " << (d ? to_string(d) + " xe | TB: $" : "khong co xe\n");
    if (d) cout << fixed << setprecision(2) << s / d << "\n";
    co_loai("Bicycle", d, s);
    cout << "  Bicycle: " << (d ? to_string(d) + " xe | TB: $" : "khong co xe\n");
    if (d) cout << fixed << setprecision(2) << s / d << "\n";
}

class SystemInterface {
private:
    bai_xe bai1, bai2, bai3;
    bool co1, co2, co3;

    string chuan_hoa(string s) const;
    void in_tb_he_thong(string loai) const;

public:
    SystemInterface();
    void runMenu();
};

SystemInterface::SystemInterface() : co1(false), co2(false), co3(false) {}

string SystemInterface::chuan_hoa(string s) const {
    for (char& c : s) c = tolower(c);
    if (s == "car") return "Car";
    if (s == "motorcycle") return "Motorcycle";
    if (s == "bicycle") return "Bicycle";
    return "";
}

void SystemInterface::in_tb_he_thong(string loai) const {
    int dem = 0, d; double tong = 0, s;
    if (co1 && bai1.co_loai(loai, d, s)) { dem += d; tong += s; }
    if (co2 && bai2.co_loai(loai, d, s)) { dem += d; tong += s; }
    if (co3 && bai3.co_loai(loai, d, s)) { dem += d; tong += s; }
    cout << "  " << loai << ": ";
    if (!dem) cout << "khong co xe\n";
    else cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
}

void SystemInterface::runMenu() {
    int chon;
    while (true) {
        cout << "\n===== QUAN LY BAI DO XE =====\n"
             << "1. Tao bai do\n2. Them xe\n3. Xoa bai do\n4. Lay xe ra\n"
             << "5. Hien thi tat ca bai do\n6. Hien thi xe theo bai\n"
             << "7. Liet ke xe theo loai\n8. Bao cao phi trung binh\n9. Thoat\nChon: ";
        cin >> chon;
        switch (chon) {
            case 1: {
                if (co1 && co2 && co3) { cout << "Da dat toi da 3 bai!\n"; break; }
                int ma; char kt;
                cout << "Ma bai: "; cin >> ma;
                if ((co1 && bai1.lay_ma() == ma) || (co2 && bai2.lay_ma() == ma) || (co3 && bai3.lay_ma() == ma)) {
                    cout << "Ma bai da ton tai!\n"; break;
                }
                cout << "Kich thuoc (S/M/L): "; cin >> kt; kt = toupper(kt);
                if (kt != 'S' && kt != 'M' && kt != 'L') { cout << "Kich thuoc khong hop le!\n"; break; }
                if (!co1) { bai1 = bai_xe(ma, kt); co1 = true; }
                else if (!co2) { bai2 = bai_xe(ma, kt); co2 = true; }
                else { bai3 = bai_xe(ma, kt); co3 = true; }
                cout << "Da tao bai " << ma << "\n";
                break;
            }
            case 2: {
                if (!co1 && !co2 && !co3) { cout << "Chua co bai do nao!\n"; break; }
                int ma, gio, tg; string loai;
                cout << "Ma xe: "; cin >> ma;
                if ((co1 && bai1.chua(ma)) || (co2 && bai2.chua(ma)) || (co3 && bai3.chua(ma))) {
                    cout << "Ma xe da ton tai!\n"; break;
                }
                cout << "Loai (Car/Motorcycle/Bicycle): "; cin >> loai; loai = chuan_hoa(loai);
                if (loai == "") { cout << "Loai xe khong hop le!\n"; break; }
                cout << "Gio vao (0-23): "; cin >> gio;
                if (gio < 0 || gio > 23) { cout << "Gio vao khong hop le!\n"; break; }
                cout << "Thoi luong (1-23): "; cin >> tg;
                if (tg < 1 || tg > 23) { cout << "Thoi luong khong hop le!\n"; break; }
                phuong_tien v(ma, loai, gio, tg);
                bool ok = (co1 && bai1.them(v)) || (co2 && bai2.them(v)) || (co3 && bai3.them(v));
                if (ok) cout << "Da them xe " << ma << " | Phi: $" << fixed << setprecision(2) << v.lay_phi_do() << "\n";
                else cout << "Tat ca bai da day!\n";
                break;
            }
            case 3: {
                int ma; cout << "Ma bai can xoa: "; cin >> ma;
                if (co1 && bai1.lay_ma() == ma) {
                    if (co2) { bai1 = bai2; if (co3) { bai2 = bai3; co3 = false; } else co2 = false; } else co1 = false;
                    cout << "Da xoa bai " << ma << "\n";
                } else if (co2 && bai2.lay_ma() == ma) {
                    if (co3) { bai2 = bai3; co3 = false; } else co2 = false;
                    cout << "Da xoa bai " << ma << "\n";
                } else if (co3 && bai3.lay_ma() == ma) {
                    co3 = false; cout << "Da xoa bai " << ma << "\n";
                } else cout << "Khong tim thay bai!\n";
                break;
            }
            case 4: {
                int ma; cout << "Ma xe can lay ra: "; cin >> ma;
                bool ok = (co1 && bai1.xoa(ma)) || (co2 && bai2.xoa(ma)) || (co3 && bai3.xoa(ma));
                cout << (ok ? "Da lay xe ra\n" : "Khong tim thay xe\n");
                break;
            }
            case 5: {
                if (!co1 && !co2 && !co3) { cout << "Chua co bai do nao!\n"; break; }
                if (co1) bai1.hien_thi(false);
                if (co2) bai2.hien_thi(false);
                if (co3) bai3.hien_thi(false);
                break;
            }
            case 6: {
                int ma; cout << "Ma bai: "; cin >> ma;
                if (co1 && bai1.lay_ma() == ma) bai1.hien_thi();
                else if (co2 && bai2.lay_ma() == ma) bai2.hien_thi();
                else if (co3 && bai3.lay_ma() == ma) bai3.hien_thi();
                else cout << "Khong tim thay bai!\n";
                break;
            }
            case 7: {
                string loai; cout << "Loai xe: "; cin >> loai; loai = chuan_hoa(loai);
                if (loai == "") { cout << "Loai xe khong hop le!\n"; break; }
                int d, tong_xe = 0; double s;
                if (co1 && bai1.co_loai(loai, d, s)) { bai1.hien_thi_loai(loai); tong_xe += d; }
                if (co2 && bai2.co_loai(loai, d, s)) { bai2.hien_thi_loai(loai); tong_xe += d; }
                if (co3 && bai3.co_loai(loai, d, s)) { bai3.hien_thi_loai(loai); tong_xe += d; }
                if (!tong_xe) cout << "Khong co xe loai " << loai << "\n";
                break;
            }
            case 8: {
                if (!co1 && !co2 && !co3) { cout << "Chua co du lieu!\n"; break; }
                cout << "--- TOAN HE THONG ---\n";
                in_tb_he_thong("Car"); in_tb_he_thong("Motorcycle"); in_tb_he_thong("Bicycle");
                cout << "--- CHI TIET TUNG BAI ---\n";
                if (co1) bai1.bao_cao();
                if (co2) bai2.bao_cao();
                if (co3) bai3.bao_cao();
                break;
            }
            case 9: return;
            default: cout << "Chon sai (1-9)!\n";
        }
    }
}

int main() {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
