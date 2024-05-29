#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include <iomanip>
using namespace std;

struct DataCatatan {
    string jenis;
    double jumlah_uang;
    string tanggal;
    string keterangan;
    DataCatatan* next;
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

void SimpanKeFile(DataCatatan* data) {
    ofstream outfile;
    outfile.open("data.txt", ios::app); // Buka file dalam mode append

    if (outfile.is_open()) {
        outfile << data->jenis << "," << data->jumlah_uang << "," << data->tanggal << "," << data->keterangan << endl;
        outfile.close();
    } else {
        cout << "Gagal membuka file." << endl;
    }
}

void BacaFile(DataCatatan*& head, double& saldo ) {
    ifstream infile("data.txt");
    if (!infile.is_open()) {
        cout << "Gagal membuka file.\n";
        return;
    }

    string line;
    while (getline(infile, line)) {
        DataCatatan* newData = new DataCatatan();

        // Memisahkan baris menjadi bagian-bagian
        stringstream ss(line);
        getline(ss, newData->jenis, ',');
        ss >> newData->jumlah_uang;
        ss.ignore(); // Mengabaikan koma
        getline(ss, newData->tanggal, ',');
        getline(ss, newData->keterangan, ',');

        // Memasukkan data ke linked list
        newData->next = head;
        head = newData;

        // Menghitung total pemasukan dan pengeluaran
        if (newData->jenis == "Pemasukan") {
            saldo += newData->jumlah_uang;
        } else if (newData->jenis == "Pengeluaran") {
            saldo -= newData->jumlah_uang;
        }
    }

    infile.close();
}

void CatatanPengeluaran(DataCatatan*& head, string today_date, double& saldo) {
    DataCatatan* newData = new DataCatatan();
    char validasi;
    do {
        newData->jenis = "Pengeluaran";
        
        // Input Jumlah Uang
        cout << "> Masukkan Jumlah Uang: ";
        cin >> newData->jumlah_uang;
        
        // Input Tanggal (Custom DD-MM-YYYY)
        cout << "> Tambahkan tanggal catatan\nIngin menggunakan tanggal hari ini? (y/n): ";
        cin >> validasi;

        if (validasi == 'y' || validasi == 'Y') {
            newData->tanggal = today_date; // Menggunakan tanggal hari ini
        } else {
            // Input Tanggal (Custom DD-MM-YYYY)
            cout << "Masukkan Tanggal (DD-MM-YYYY): ";
            cin >> newData->tanggal;
        }

        // Input Keterangan Catatan
        cout << "Masukkan Keterangan Catatan: ";
        cin.ignore(); // Clear buffer
        getline(cin, newData->keterangan);

        // Cek kembali input
        cout << "\n--- Detail Pengeluaran ---\n";
        cout << "Jumlah Uang: " << newData->jumlah_uang << endl;
        cout << "Tanggal: " << newData->tanggal << endl;
        cout << "Keterangan: " << newData->keterangan << endl;

        // Validasi format tanggal
        if (!IsValidDateFormat(newData->tanggal)) {
            cout << "\nFormat tanggal tidak valid. Mohon masukkan tanggal dengan format DD-MM-YYYY." << endl;
            continue;
        }

        cout << "\nApakah data Anda sudah benar? (y/n): ";
        cin >> validasi;
    } while (validasi != 'y');

    newData->next = head;
    head = newData;

    SimpanKeFile(newData);

    // Kurangi saldo dengan jumlah pengeluaran
    saldo -= newData->jumlah_uang;

    // Tampilkan saldo terbaru
    cout << "Saldo Anda setelah pengeluaran: " << std::fixed << std::setprecision(2) << saldo << endl;
}

void TambahPemasukan(DataCatatan*& head, string today_date, double& saldo) {
    DataCatatan* newData = new DataCatatan();
    char validasi;
    do {
        newData->jenis = "Pemasukan";

        // Input Jumlah Uang
        cout << "> Masukkan Jumlah Uang: ";
        cin >> newData->jumlah_uang;

        // Input Tanggal (Custom DD-MM-YYYY)
        cout << "> Tambahkan tanggal catatan\nIngin menggunakan tanggal hari ini? (y/n): ";
        cin >> validasi;

        if (validasi == 'y' || validasi == 'Y') {
            newData->tanggal = today_date; // Menggunakan tanggal hari ini
        } else {
            // Input Tanggal (Custom DD-MM-YYYY)
            cout << "Masukkan Tanggal (DD-MM-YYYY): ";
            cin >> newData->tanggal;
        }

        // Input Keterangan Catatan
        cout << "Masukkan Keterangan Catatan: ";
        cin.ignore(); // Clear buffer
        getline(cin, newData->keterangan);

        // Cek kembali input
        cout << "\n--- Detail Pemasukan ---\n";
        cout << "Jumlah Uang: " << newData->jumlah_uang << endl;
        cout << "Tanggal: " << newData->tanggal << endl;
        cout << "Keterangan: " << newData->keterangan << endl;

        // Validasi format tanggal
        if (!IsValidDateFormat(newData->tanggal)) {
            cout << "\nFormat tanggal tidak valid. Mohon masukkan tanggal dengan format DD-MM-YYYY." << endl;
            continue;
        }

        cout << "\nApakah data Anda sudah benar? (y/n): ";
        cin >> validasi;
    } while (validasi != 'y');

    newData->next = head; 
    head = newData;

    SimpanKeFile(newData);

    // Tambahkan saldo dengan jumlah pemasukan
    saldo += newData->jumlah_uang;

    // Tampilkan saldo terbaru
    cout << "Saldo Anda setelah pemasukan: " << std::fixed << std::setprecision(2) << saldo << endl;
}

void TampilkanPemasukan(DataCatatan* head) {
    if (head == nullptr) {
        cout << "Tidak ada catatan pemasukan.\n";
        return;
    }

    DataCatatan* current = head;
    while (current != nullptr) {
        cout << "\n--- Detail Pemasukan ---\n";
        cout << "Jumlah Uang: " << current->jumlah_uang << endl;
        cout << "Tanggal: " << current->tanggal << endl;
        cout << "Keterangan: " << current->keterangan << endl;
        current = current->next;
    }
}

void MenuOperations(DataCatatan*& head, string today_date, double& saldo) {
    int choice = -1;
    while (choice != 0) {
        cout << "\n--opsi--\n";
        cout << "1. Catatan Pemasukan\n";
        cout << "2. Tampilkan Semua Pemasukan\n";
        cout << "3. Catatan Pengeluaran\n";
        cout << "0. Exit\n";
        cout << "Enter choice : ";
        cin >> choice;

        switch (choice) {
            case 1: {
                TambahPemasukan(head, today_date, saldo);
                break;
            }

            case 2: {
                TampilkanPemasukan(head);
                break;
            }
            
            case 3: {
                CatatanPengeluaran(head, today_date, saldo);
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
    DataCatatan* head = nullptr; // Initialize the head of the linked list
    string today_date = GetTodayDate();
     
    double saldo = 0.0;

    BacaFile(head, saldo);
    cout << "Saldo Anda: " << std::fixed << std::setprecision(2) << saldo << endl;
    MenuOperations(head, today_date, saldo);
    
    // Membersihkan linked list
    while (head != nullptr) {
        DataCatatan* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
    