#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;


class SinhVien {
private:
    string maSV;
    string tenSV;
    int tuoi;
    float diem;

public:
    SinhVien() {}
    // H�m nhap th�ng tin sinh vi�n
    friend istream& operator>>(istream& is, SinhVien& sv) {
        cout << "Nhap ma sinh vien: ";
        is >> sv.maSV;
        cout << "Nhap ten sinh vien: ";
        is.ignore(); 
        getline(is, sv.tenSV);
        cout << "Nhap tuoi sinh vien: ";
        is >> sv.tuoi;
        cout << "Nhap diem sinh vien: ";
        is >> sv.diem;
        return is;
    }

    // H�m xuat th�ng tin sinh vi�n
    friend ostream& operator<<(ostream& os, const SinhVien& sv) {
        os << "Ma SV: " << sv.maSV << ", Ten: " << sv.tenSV 
           << ", Tuoi: " << sv.tuoi << ", Diem: " << sv.diem;
        return os;
    }

    // To�n tu so s�nh < theo diem
    bool operator<(const SinhVien& sv) const {
        return this->diem < sv.diem;
    }

    // Lay m� sinh vi�n
    string getMaSV() const {
        return maSV;
    }

    // Lay diem sinh vi�n
    float getDiem() const {
        return diem;
    }
};

// Lap DanhSachSinhVien quan l� danh s�ch sinh vi�n
class DanhSachSinhVien {
private:
    vector<SinhVien> ds;  // D�ng vector de luu danh s�ch sinh vi�n

public:
    // H�m nhap danh s�ch sinh vi�n
    void nhapDS(int n) {
        for (int i = 0; i < n; ++i) {
            SinhVien sv;
            cout << "Nhap thong tin sinh vien thu " << i + 1 << ":" << endl;
            cin >> sv;
            ds.push_back(sv);
        }
    }

    // H�m xuat danh s�ch sinh vi�n
    void xuatDS() const {
        for (const auto& sv : ds) {
            cout << sv << endl;
        }
    }

    // Sap xep danh s�ch theo diem
    void sapXepTheoDiem() {
        sort(ds.begin(), ds.end());
    }

    // T�m sinh vi�n c� diem cao nhat
    SinhVien timMaxDiem() const {
        return *max_element(ds.begin(), ds.end());
    }

    // T�m sinh vi�n c� diem thap nhat
    SinhVien timMinDiem() const {
        return *min_element(ds.begin(), ds.end());
    }

    // T�m sinh vi�n theo m� sinh vi�n
    SinhVien* timKiemTheoMa(const string& ma) {
        for (auto& sv : ds) {
            if (sv.getMaSV() == ma) {
                return &sv;
            }
        }
        return nullptr;  // Tra ve null neu kh�ng t�m th?y
    }

    // X�a sinh vi�n theo m�
    void xoaTheoMa(const string& ma) {
        auto it = remove_if(ds.begin(), ds.end(), [&](const SinhVien& sv) {
            return sv.getMaSV() == ma;
        });
        if (it != ds.end()) {
            ds.erase(it, ds.end());
            cout << "Da xoa sinh vien co ma " << ma << endl;
        } else {
            cout << "Khong tim thay sinh vien co ma " << ma << endl;
        }
    }
};
// Lap App de quan l� menu v� thao t�c
class App {
public:
    void run() {
        DanhSachSinhVien dssv;
        int choice;

        do {
            cout << "\n===== Menu Quan Ly Sinh Vien =====" << endl;
            cout << "1. Nhap danh sach sinh vien" << endl;
            cout << "2. Xuat danh sach sinh vien" << endl;
            cout << "3. Sap xep danh sach theo diem" << endl;
            cout << "4. Tim sinh vien co diem cao nhat" << endl;
            cout << "5. Tim sinh vien co diem thap nhat" << endl;
            cout << "6. Tim sinh vien theo ma" << endl;
            cout << "7. Xoa sinh vien theo ma" << endl;
            cout << "0. Thoat" << endl;
            cout << "Nhap lua chon: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                int n;
                cout << "Nhap so luong sinh vien: ";
                cin >> n;
                dssv.nhapDS(n);
                break;
            }
            case 2:
                dssv.xuatDS();
                break;
            case 3:
                dssv.sapXepTheoDiem();
                cout << "Danh sach da duoc sap xep theo diem." << endl;
                break;
            case 4: {
                SinhVien sv = dssv.timMaxDiem();
                cout << "Sinh vien co diem cao nhat: " << endl;
                cout << sv << endl;
                break;
            }
            case 5: {
                SinhVien sv = dssv.timMinDiem();
                cout << "Sinh vien co diem thap nhat: " << endl;
                cout << sv << endl;
                break;
            }
            case 6: {
                string ma;
                cout << "Nhap ma sinh vien can tim: ";
                cin >> ma;
                SinhVien* sv = dssv.timKiemTheoMa(ma);
                if (sv) {
                    cout << "Tim thay sinh vien: " << endl;
                    cout << *sv << endl;
                } else {
                    cout << "Khong tim thay sinh vien co ma " << ma << endl;
                }
                break;
            }
            case 7: {
                string ma;
                cout << "Nhap ma sinh vien can xoa: ";
                cin >> ma;
                dssv.xoaTheoMa(ma);
                break;
            }
            case 0:
                cout << "Thoat chuong trinh!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
            }
        } while (choice != 0);
    }
};

// H�m main
int main() {
    App app;
    app.run();
    return 0;
}
