#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;
    double phi_do;

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

    void tinh_phi();
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0), phi_do(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg), phi_do(0) {
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
    static const int MAX_XE = 3;
    int ma_bai;
    char kich_thuoc;
    phuong_tien ds_xe[MAX_XE];
    int so_xe;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    void dat_ma(int ma);
    char lay_kich_thuoc() const;
    void dat_kich_thuoc(char kt);
    int lay_so_xe() const;
    int lay_suc_chua() const;

    bool day() const;
    bool them(const phuong_tien& v);
    int tim_vi_tri_xe(int ma_xe) const;
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi(bool chi_tiet = true) const;
    void hien_thi_loai(string loai) const;
    bool co_loai(string loai, int& dem, double& tong) const;
    void bao_cao() const;
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), so_xe(0) {}

bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(toupper(kt)), so_xe(0) {}

int bai_xe::lay_ma() const { return ma_bai; }
void bai_xe::dat_ma(int ma) { ma_bai = ma; }
char bai_xe::lay_kich_thuoc() const { return kich_thuoc; }
void bai_xe::dat_kich_thuoc(char kt) { kich_thuoc = toupper(kt); }
int bai_xe::lay_so_xe() const { return so_xe; }
int bai_xe::lay_suc_chua() const { return (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3; }

bool bai_xe::day() const { return so_xe >= lay_suc_chua(); }

bool bai_xe::them(const phuong_tien& v) {
    if (day()) return false;
    ds_xe[so_xe++] = v;
    return true;
}

int bai_xe::tim_vi_tri_xe(int ma_xe) const {
    for (int i = 0; i < so_xe; ++i)
        if (ds_xe[i].lay_ma_xe() == ma_xe) return i;
    return -1;
}

bool bai_xe::xoa(int ma_xe) {
    int vt = tim_vi_tri_xe(ma_xe);
    if (vt == -1) return false;
    for (int i = vt; i < so_xe - 1; ++i)
        ds_xe[i] = ds_xe[i + 1];
    --so_xe;
    return true;
}

bool bai_xe::chua(int ma_xe) const { return tim_vi_tri_xe(ma_xe) != -1; }

void bai_xe::hien_thi(bool chi_tiet) const {
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] " << so_xe << "/" << lay_suc_chua() << " xe\n";
    if (!chi_tiet) return;
    if (so_xe == 0) cout << "  (Bai trong)\n";
    for (int i = 0; i < so_xe; ++i)
        ds_xe[i].hien_thi();
}

void bai_xe::hien_thi_loai(string loai) const {
    for (int i = 0; i < so_xe; ++i) {
        if (ds_xe[i].lay_loai_xe() == loai) {
            cout << "  [Bai " << ma_bai << "]";
            ds_xe[i].hien_thi();
        }
    }
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
    for (int i = 0; i < so_xe; ++i) {
        if (ds_xe[i].lay_loai_xe() == loai) {
            ++dem;
            tong += ds_xe[i].lay_phi_do();
        }
    }
    return dem > 0;
}

void bai_xe::bao_cao() const {
    int d; double s;
    string loai[3] = {"Car", "Motorcycle", "Bicycle"};
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "]:\n";
    for (int i = 0; i < 3; ++i) {
        co_loai(loai[i], d, s);
        cout << "  " << loai[i] << ": ";
        if (!d) cout << "khong co xe\n";
        else cout << d << " xe | TB: $" << fixed << setprecision(2) << s / d << "\n";
    }
}

class SystemInterface {
private:
    static const int MAX_BAI = 10;
    bai_xe ds_bai[MAX_BAI];
    int so_bai;

    int nhap_so(string tb) const;
    string chuan_hoa(string s) const;
    void in_tb_he_thong(string loai) const;

public:
    SystemInterface();
    bool trung_ma_bai(int ma) const;
    bool trung_ma_xe(int ma) const;
    int tao_ma_ngau_nhien() const;
    void runMenu();
};

SystemInterface::SystemInterface() : so_bai(0) {
    srand(static_cast<unsigned int>(time(0)));
}

int SystemInterface::nhap_so(string tb) const {
    int x;
    while (true) {
        cout << tb;
        cin >> x;
        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Du lieu khong hop le! Vui long nhap so nguyen.\n";
    }
}

string SystemInterface::chuan_hoa(string s) const {
    for (char& c : s) c = tolower(c);
    if (s == "car") return "Car";
    if (s == "motorcycle") return "Motorcycle";
    if (s == "bicycle") return "Bicycle";
    return "";
}

bool SystemInterface::trung_ma_bai(int ma) const {
    for (int i = 0; i < so_bai; ++i)
        if (ds_bai[i].lay_ma() == ma) return true;
    return false;
}

bool SystemInterface::trung_ma_xe(int ma) const {
    for (int i = 0; i < so_bai; ++i)
        if (ds_bai[i].chua(ma)) return true;
    return false;
}

int SystemInterface::tao_ma_ngau_nhien() const {
    int ma;
    do {
        ma = 1000 + rand() % 9000;
    } while (trung_ma_bai(ma) || trung_ma_xe(ma));
    return ma;
}

void SystemInterface::in_tb_he_thong(string loai) const {
    int dem = 0, d; double tong = 0, s;
    for (int i = 0; i < so_bai; ++i) {
        if (ds_bai[i].co_loai(loai, d, s)) {
            dem += d;
            tong += s;
        }
    }
    cout << "  " << loai << ": ";
    if (!dem) cout << "khong co xe\n";
    else cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
}

void SystemInterface::runMenu() {
    while (true) {
        cout << "\n===== QUAN LY BAI DO XE =====\n"
             << "1. Tao bai do\n2. Them xe\n3. Xoa bai do\n4. Lay xe ra\n"
             << "5. Hien thi tat ca bai do\n6. Hien thi xe theo bai\n"
             << "7. Liet ke xe theo loai\n8. Bao cao phi trung binh\n9. Thoat\n";
        int chon = nhap_so("Chon: ");
        switch (chon) {
            case 1: {
                if (so_bai >= MAX_BAI) { cout << "Da dat toi da " << MAX_BAI << " bai!\n"; break; }
                int ma = nhap_so("Ma bai: ");
                if (trung_ma_bai(ma)) {
                    ma = tao_ma_ngau_nhien();
                    cout << "Canh bao: Ma bai da ton tai! Tu dong gan ma moi: " << ma << "\n";
                }
                char kt;
                cout << "Kich thuoc (S/M/L): "; cin >> kt;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                kt = toupper(kt);
                if (kt != 'S' && kt != 'M' && kt != 'L') { cout << "Kich thuoc khong hop le!\n"; break; }
                ds_bai[so_bai++] = bai_xe(ma, kt);
                cout << "Da tao bai " << ma << "\n";
                break;
            }
            case 2: {
                if (so_bai == 0) { cout << "Chua co bai do nao!\n"; break; }
                int ma = nhap_so("Ma xe: ");
                if (trung_ma_xe(ma)) {
                    ma = tao_ma_ngau_nhien();
                    cout << "Canh bao: Ma xe da ton tai! Tu dong gan ma moi: " << ma << "\n";
                }
                string loai;
                cout << "Loai (Car/Motorcycle/Bicycle): "; cin >> loai;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                loai = chuan_hoa(loai);
                if (loai == "") { cout << "Loai xe khong hop le!\n"; break; }
                int gio = nhap_so("Gio vao (0-23): ");
                if (gio < 0 || gio > 23) { cout << "Gio vao khong hop le!\n"; break; }
                int tg = nhap_so("Thoi luong (1-23): ");
                if (tg < 1 || tg > 23) { cout << "Thoi luong khong hop le!\n"; break; }
                phuong_tien v(ma, loai, gio, tg);
                bool ok = false;
                for (int i = 0; i < so_bai; ++i) {
                    if (ds_bai[i].them(v)) {
                        cout << "Da them xe " << ma << " vao bai " << ds_bai[i].lay_ma()
                             << " | Phi: $" << fixed << setprecision(2) << v.lay_phi_do() << "\n";
                        ok = true;
                        break;
                    }
                }
                if (!ok) cout << "Canh bao: Tat ca bai da day!\n";
                break;
            }
            case 3: {
                int ma = nhap_so("Ma bai can xoa: ");
                int vt = -1;
                for (int i = 0; i < so_bai; ++i)
                    if (ds_bai[i].lay_ma() == ma) { vt = i; break; }
                if (vt == -1) { cout << "Khong tim thay bai!\n"; break; }
                for (int i = vt; i < so_bai - 1; ++i)
                    ds_bai[i] = ds_bai[i + 1];
                --so_bai;
                cout << "Da xoa bai " << ma << "\n";
                break;
            }
            case 4: {
                int ma = nhap_so("Ma xe can lay ra: ");
                bool ok = false;
                for (int i = 0; i < so_bai; ++i) {
                    if (ds_bai[i].xoa(ma)) { ok = true; break; }
                }
                cout << (ok ? "Da lay xe ra\n" : "Khong tim thay xe\n");
                break;
            }
            case 5: {
                if (so_bai == 0) { cout << "Chua co bai do nao!\n"; break; }
                for (int i = 0; i < so_bai; ++i)
                    ds_bai[i].hien_thi(false);
                break;
            }
            case 6: {
                int ma = nhap_so("Ma bai: ");
                bool ok = false;
                for (int i = 0; i < so_bai; ++i) {
                    if (ds_bai[i].lay_ma() == ma) { ds_bai[i].hien_thi(); ok = true; break; }
                }
                if (!ok) cout << "Khong tim thay bai!\n";
                break;
            }
            case 7: {
                string loai;
                cout << "Loai xe: "; cin >> loai;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                loai = chuan_hoa(loai);
                if (loai == "") { cout << "Loai xe khong hop le!\n"; break; }
                int d, tong_xe = 0; double s;
                for (int i = 0; i < so_bai; ++i) {
                    if (ds_bai[i].co_loai(loai, d, s)) {
                        ds_bai[i].hien_thi_loai(loai);
                        tong_xe += d;
                    }
                }
                if (!tong_xe) cout << "Khong co xe loai " << loai << "\n";
                break;
            }
            case 8: {
                if (so_bai == 0) { cout << "Chua co du lieu!\n"; break; }
                cout << "--- TOAN HE THONG ---\n";
                in_tb_he_thong("Car");
                in_tb_he_thong("Motorcycle");
                in_tb_he_thong("Bicycle");
                cout << "--- CHI TIET TUNG BAI ---\n";
                for (int i = 0; i < so_bai; ++i)
                    ds_bai[i].bao_cao();
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
