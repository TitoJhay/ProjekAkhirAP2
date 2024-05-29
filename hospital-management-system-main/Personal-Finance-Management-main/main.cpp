#include<iostream>

using namespace std;

struct PemasukanData {
    double jumlah_uang;
    string tanggal;
    string keterangan;
    bool validasi;
};

bool IsValidDateFormat(const string &date) {
    if (date.size() != 10) // Panjang harus 10 karakter untuk format DD-MM-YYYY
        return false;

    if (date[2] != '-' || date[5] != '-') // Pemeriksaan pemisah tanggal
        return false;

    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) // Langsung lewati karakter '-' yang digunakan sebagai pemisah
            continue;

        if (!isdigit(date[i])) // Periksa apakah karakter bukan digit
            return false;
    }

    return true;
}

string GetTodayDate() {
    string today_date;
    cout << "Silakan masukkan tanggal hari ini (DD-MM-YYYY): ";
    cin >> today_date;

    // Pemeriksaan validitas format tanggal hari ini
    if (!IsValidDateFormat(today_date)) {
        cout << "Format tanggal hari ini tidak valid. Aplikasi akan keluar.";
        exit(1); // Keluar dari aplikasi jika format tanggal hari ini tidak valid
    }

    return today_date;
}

void Pemasukan(string today_date) {
    PemasukanData data;
    char validasi;

    do
    {
        // Input Jumlah Uang
        cout << "> Masukkan Jumlah Uang: ";
        cin >> data.jumlah_uang;

        // Input Tanggal (Custom DD-MM-YYYY)
        cout << "> Tambahkan tanggal catatan\nIngin menggunakan tanggal hari ini? (y/n): ";
        cin >> validasi;

        if (validasi == 'y' || validasi == 'Y') {
            data.tanggal = today_date; // Menggunakan tanggal hari ini
        } else {
            // Input Tanggal (Custom DD-MM-YYYY)
            cout << "Masukkan Tanggal (DD-MM-YYYY): ";
            cin >> data.tanggal;
        }

        // Input Keterangan Catatan1
        cout << "Masukkan Keterangan Catatan: ";
        cin.ignore(); // Clear buffer
        getline(cin, data.keterangan);

        // Cek kembali input
        cout << "\n--- Detail Pemasukan ---\n";
        cout << "Jumlah Uang: " << data.jumlah_uang << endl;
        cout << "Tanggal: " << data.tanggal << endl;
        cout << "Keterangan: " << data.keterangan << endl;

        // Validasi format tanggal
        if (!IsValidDateFormat(data.tanggal)) {
            cout << "\nFormat tanggal tidak valid. Mohon masukkan tanggal dengan format DD-MM-YYYY." << endl;
            continue;
        }
        cout << "\nApakah data Anda sudah benar? (y/n): ";
        cin >> validasi;
    } while (validasi != 'y');

}

void MenuOperations(string today_date) {
    int choice = -1;
    while (choice != 0) {
        cout << "\n--opsi--\n";
        cout << "1. Catatan Pemasukan\n";
        cout << "2. Catatan Pengeluaran\n";
        cout << "3. Menu 3\n";
        cout << "4. Menu 4\n";
        cout << "5. Menu 5\n";
        cout << "0. Exit\n";
        cout << "Enter choice : ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Pemasukan(today_date);
                break;
            }

            case 2: {
                cout << "menu 1";
                break;
            }

            case 3: {
                cout << "menu 1";
                break;
            }

            case 4: {
                cout << "menu 1";
                break;
            }

            case 5: {
                cout << "menu 1";
                break;
            }

            case 0:
                break;

            default:
                cout << "\nNo such option:(";
                break;
        }
    }
}

int main() {
    string today_date = GetTodayDate();

    cout << "---Welcome to Keuangan Pribadi!!---\n";
    MenuOperations(today_date);
    return 0;
}