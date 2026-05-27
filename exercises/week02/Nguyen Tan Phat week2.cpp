#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

struct Vector {
    int* data, size, capacity;
    void init() { size = 0; capacity = 2; data = new int[capacity]; }
    void push_back(int v) {
        if (size == capacity) {
            capacity *= 2;
            int* nData = new int[capacity];
            for (int i = 0; i < size; i++) nData[i] = data[i];
            delete[] data; data = nData;
        }
        data[size++] = v;
    }
    void pop_back() { if (size > 0) size--; }
    int at(int i) { return (i >= 0 && i < size) ? data[i] : -1; }
    void free() { delete[] data; }
};

struct SinhVien { string ten, mssv; double diem; };

void resizeSV(SinhVien*& arr, int oldS, int newS) {
    if (newS < 0) return;
    SinhVien* nArr = (newS > 0) ? new SinhVien[newS] : nullptr;
    for (int i = 0; i < oldS && i < newS; i++) nArr[i] = arr[i];
    delete[] arr; arr = nArr;
}

int main() {
    int Chon;
    cout << "Chon Bai (1->4): "; cin >> Chon;

    if (Chon == 1) {
        int n; cout << "Nhap n: "; cin >> n;
        int* a = new int[n]; long long sum = 0;
        for (int i = 0; i < n; i++) { cout << "a[" << i << "]: "; cin >> a[i]; sum += a[i]; }
        int minv = a[0], maxv = a[0];
        for (int i = 1; i < n; i++) {
            if (a[i] < minv) minv = a[i];
            if (a[i] > maxv) maxv = a[i];
        }
        cout << "Min: " << minv << "\nMax: " << maxv << "\nTong: " << sum << "\nTB: " << (double)sum / n << "\n";
        delete[] a;
    }
    else if (Chon == 2) {
        int n; cout << "Nhap nxn: "; cin >> n;
        int** A = new int* [n], ** B = new int* [n], ** C = new int* [n];
        for (int i = 0; i < n; i++) { A[i] = new int[n]; B[i] = new int[n]; C[i] = new int[n]; }
        cout << "Nhap ma tran A:\n"; for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> A[i][j];
        cout << "Nhap ma tran B:\n"; for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> B[i][j];
        cout << "Tich C:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = 0;
                for (int k = 0; k < n; k++) C[i][j] += A[i][k] * B[k][j];
                cout << setw(6) << C[i][j] << " ";
            }
            cout << "\n";
        }
        if (n == 3) {
            int det = A[0][0] * (A[1][1] * A[2][2] - A[1][2] * A[2][1]) - A[0][1] * (A[1][0] * A[2][2] - A[1][2] * A[2][0]) + A[0][2] * (A[1][0] * A[2][1] - A[1][1] * A[2][0]);
            cout << "det(A) = " << det << "\n";
        }
        for (int i = 0; i < n; i++) { delete[] A[i]; delete[] B[i]; delete[] C[i]; }
        delete[] A; delete[] B; delete[] C;
    }
    else if (Chon == 3) {
        Vector v; v.init();
        cout << "Push 10, 20, 30...\n";
        v.push_back(10); v.push_back(20); v.push_back(30);
        cout << "Mang hien tai: "; for (int i = 0; i < v.size; i++) cout << v.at(i) << " ";
        cout << "\nPop phan tu cuoi...\n"; v.pop_back();
        cout << "Mang sau pop: "; for (int i = 0; i < v.size; i++) cout << v.at(i) << " ";
        cout << "\n"; v.free();
    }
    else if (Chon == 4) {
        int count = 0, menu; SinhVien* ds = nullptr;
        do {
            cout << "\n1.Them 2.Sua/Xoa 3.Tim 4.Sort 5.Xuat 6.Thoat. Chon: "; cin >> menu;
            if (menu == 1) {
                resizeSV(ds, count, count + 1);
                cout << "Nhap mssv (viet lien): "; cin >> ds[count].mssv;
                cout << "Nhap ten (dung gach_duoi hoac viet_lien): "; cin >> ds[count].ten;
                cout << "Nhap diem: "; cin >> ds[count].diem;
                count++;
            }
            else if (menu == 2) {
                if (count == 0) { cout << "Danh sach trong!\n"; continue; }
                string imssv; cout << "Nhap MSSV can tim: "; cin >> imssv; int idx = -1;
                for (int i = 0; i < count; i++) if (ds[i].mssv == imssv) { idx = i; break; }
                if (idx != -1) {
                    int opt; cout << "1.Sua 2.Xoa: "; cin >> opt;
                    if (opt == 1) {
                        cout << "Ten moi: "; cin >> ds[idx].ten;
                        cout << "Diem moi: "; cin >> ds[idx].diem;
                    }
                    else {
                        for (int i = idx; i < count - 1; i++) ds[i] = ds[i + 1];
                        resizeSV(ds, count, count - 1); count--;
                    }
                }
                else cout << "Khong tim thay!\n";
            }
            else if (menu == 3) {
                if (count == 0) { cout << "Danh sach trong!\n"; continue; }
                string kw; cout << "Nhap tu khoa (MSSV/Ten): "; cin >> kw;
                for (int i = 0; i < count; i++)
                    if (ds[i].mssv == kw || ds[i].ten.find(kw) != string::npos)
                        cout << ds[i].mssv << " - " << ds[i].ten << " - " << ds[i].diem << "\n";
            }
            else if (menu == 4) {
                if (count == 0) { cout << "Danh sach trong!\n"; continue; }
                for (int i = 0; i < count - 1; i++)
                    for (int j = 0; j < count - i - 1; j++)
                        if (ds[j].diem > ds[j + 1].diem) swap(ds[j], ds[j + 1]);
                cout << "Da sap xep tang dan theo diem!\n";
            }
            else if (menu == 5) {
                if (count == 0) { cout << "Danh sach trong!\n"; continue; }
                double maxD = ds[0].diem, minD = ds[0].diem, sumD = 0;
                for (int i = 0; i < count; i++) {
                    if (ds[i].diem > maxD) maxD = ds[i].diem;
                    if (ds[i].diem < minD) minD = ds[i].diem;
                    sumD += ds[i].diem;
                }
                cout << "\nMax: " << maxD << " | Min: " << minD << " | TB: " << sumD / count << "\n";
                ofstream f("diem_sinhvien.txt");
                if (f.is_open()) f << "Max: " << maxD << " | Min: " << minD << " | TB: " << sumD / count << "\n";
                for (int i = 0; i < count; i++) {
                    cout << ds[i].mssv << "\t" << ds[i].ten << "\t" << ds[i].diem << "\n";
                    if (f.is_open()) f << ds[i].mssv << "\t" << ds[i].ten << "\t" << ds[i].diem << "\n";
                }
                if (f.is_open()) { f.close(); cout << "Da xuat file 'diem_sinhvien.txt'\n"; }
            }
        } while (menu != 6);
        delete[] ds;
    }
    return 0;
}