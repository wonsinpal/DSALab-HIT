#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int Chon;
    cout << "Chon Bai (1 hoac 2): "; cin >> Chon;

    if (Chon == 1) {
        int n; cout << "Nhap n: "; cin >> n;
        int* a = new int[n];
        long long sum = 0;

        for (int i = 0; i < n; i++) {
            cout << "a[" << i << "]: "; cin >> a[i];
            sum += a[i];
        }

        int minv = a[0], maxv = a[0];
        for (int i = 1; i < n; i++) {
            if (a[i] < minv) minv = a[i];
            if (a[i] > maxv) maxv = a[i];
        }

        cout << "Min: " << minv << "\nMax: " << maxv << "\nTong: " << sum << "\nTB: " << (double)sum / n << "\n";
        delete[] a;
    }
    else if (Chon == 2) {
        int n; cout << "Nhap kich thuoc nxn: "; cin >> n;
        int** A = new int* [n], ** B = new int* [n], ** C = new int* [n];
        for (int i = 0; i < n; i++) {
            A[i] = new int[n]; B[i] = new int[n]; C[i] = new int[n];
        }

        cout << "Nhap ma tran A:\n";
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> A[i][j];
        cout << "Nhap ma tran B:\n";
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> B[i][j];

        cout << "\nTich hai ma tran C:\n";
        for (int i = 0; i < n; i++) {
            cout << "| ";
            for (int j = 0; j < n; j++) {
                C[i][j] = 0;
                for (int k = 0; k < n; k++) C[i][j] += A[i][k] * B[k][j];
                cout << setw(6) << C[i][j] << " ";
            }
            cout << "|\n";
        }

        if (n == 3) {
            int detA = A[0][0] * (A[1][1] * A[2][2] - A[1][2] * A[2][1]) - A[0][1] * (A[1][0] * A[2][2] - A[1][2] * A[2][0]) + A[0][2] * (A[1][0] * A[2][1] - A[1][1] * A[2][0]);
            cout << "\ndet(A) = " << detA << "\n";
        }

        for (int i = 0; i < n; i++) { delete[] A[i]; delete[] B[i]; delete[] C[i]; }
        delete[] A; delete[] B; delete[] C;
    }
    return 0;
}