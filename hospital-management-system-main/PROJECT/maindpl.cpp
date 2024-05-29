#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<iomanip>
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

void BacaFile(DataCatatan*& head, double& saldo) {
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

void TampilkanSemuaCatatan(DataCatatan* head) {
    if (head == nullptr) {
        cout << "Tidak ada catatan.\n";
        return;
    }

    DataCatatan* current = head;
    while (current != nullptr) {
        cout << "\n--- Detail " << current->jenis << " ---\n";
        cout << "Jumlah Uang: " << current->jumlah_uang << endl;
        cout << "Tanggal: " << current->tanggal << endl;
        cout << "Keterangan: " << current->keterangan << endl;
        current = current->next;
    }
}

void LihatCatatanBulanIni(DataCatatan* head, const string& today_date) {
    string current_month = today_date.substr(3, 2); // Ambil bulan dari tanggal hari ini
    string current_year = today_date.substr(6, 4); // Ambil tahun dari tanggal hari ini

    cout << "\n--- Catatan Bulan Ini ---\n";
    DataCatatan* current = head;
    while (current != nullptr) {
        string record_month = current->tanggal.substr(3, 2);
        string record_year = current->tanggal.substr(6, 4);
        if (record_month == current_month && record_year == current_year) {
            cout << "\n--- Detail " << current->jenis << " ---\n";
            cout << "Jumlah Uang: " << current->jumlah_uang << endl;
            cout << "Tanggal: " << current->tanggal << endl;
            cout << "Keterangan: " << current->keterangan << endl;
        }
        current = current->next;
    }
}

void SortirBerdasarkanTanggal(DataCatatan*& head) {
    if (!head) return;

    // Convert linked list to array for sorting
    DataCatatan* current = head;
    int count = 0;
    while (current) {
        count++;
        current = current->next;
    }

    DataCatatan** arr = new DataCatatan*[count];
    current = head;
    for (int i = 0; i < count; ++i) {
        arr[i] = current;
        current = current->next;
    }

    // Sort array based on date
    sort(arr, arr + count, [](DataCatatan* a, DataCatatan* b) {
        return a->tanggal > b->tanggal;
    });

    // Reconstruct linked list
    head = arr[0];
    current = head;
    for (int i = 1; i < count; ++i) {
        current->next = arr[i];
        current = current->next;
    }
    current->next = nullptr;

    delete[] arr;

    cout << "\n--- Catatan Disortir Berdasarkan Tanggal Terbaru ---\n";
    TampilkanSemuaCatatan(head);
}

void SortirBerdasarkanNilaiUang(DataCatatan*& head) {
    if (!head) return;

    // Convert linked list to array for sorting
    DataCatatan* current = head;
    int count = 0;
    while (current) {
        count++;
        current = current->next;
    }

    DataCatatan** arr = new DataCatatan*[count];
    current = head;
    for (int i = 0; i < count; ++i) {
        arr[i] = current;
        current = current->next;
    }

    // Sort array based on value
    sort(arr, arr + count, [](DataCatatan* a, DataCatatan* b) {
        return a->jumlah_uang > b->jumlah_uang;
    });

    // Reconstruct linked list
    head = arr[0];
    current = head;
    for (int i = 1; i < count; ++i) {
        current->next = arr[i];
        current = current->next;
    }
    current->next = nullptr;

    delete[] arr;

    cout << "\n--- Catatan Disortir Berdasarkan Nilai Uang ---\n";
    TampilkanSemuaCatatan(head);
}

void HapusCatatan(DataCatatan*& head) {
    if (!head) {
        cout << "Tidak ada catatan untuk dihapus.\n";
        return;
    }

    TampilkanSemuaCatatan(head);
    int index;
    cout << "\nMasukkan nomor catatan yang ingin dihapus (dimulai dari 1): ";
    cin >> index;

    if (index <= 0) {
        cout << "Nomor catatan tidak valid.\n";
        return;
    }

    DataCatatan* current = head;
    DataCatatan* previous = nullptr;

    for (int i = 1; current != nullptr && i < index; ++i) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Nomor catatan tidak valid.\n";
        return;
    }

    if (previous == nullptr) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;

    // Tulis ulang file dengan data yang telah diperbarui
    ofstream outfile("data.txt");
    current = head;
    while (current != nullptr) {
        outfile << current->jenis << "," << current->jumlah_uang << "," << current->tanggal << "," << current->keterangan << endl;
        current = current->next;
    }
    outfile.close();

    cout << "Catatan berhasil dihapus.\n";
}

void LaporanCatatan(DataCatatan*& head, string today_date) {
    int choice = -1;
    while (choice != 0) {
        cout << "\n-- Laporan Catatan --\n";
        cout << "1. Lihat Catatan Bulan Ini\n";
        cout << "2. Sortir Berdasarkan Tanggal Terbaru\n";
        cout << "3. Sortir Berdasarkan Nilai Uang\n";
        cout << "4. Lihat dan Hapus Catatan\n";
        cout << "0. Kembali ke Menu Utama\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                LihatCatatanBulanIni(head, today_date);
                break;
            }

            case 2: {
                SortirBerdasarkanTanggal(head);
                break;
            }
            
            case 3: {
                SortirBerdasarkanNilaiUang(head);
                break;
            }

            case 4: {
                HapusCatatan(head);
                break;
            }

            case 0:
                break;

            default:
                cout << "\nTidak ada opsi seperti itu:(";
                break;
        }
    }
}

void MenuOperations(DataCatatan*& head, string today_date, double& saldo) {
    int choice = -1;
    while (choice != 0) {
        cout << "\n-- Menu Utama --\n";
        cout << "1. Catatan Pemasukan\n";
        cout << "2. Catatan Pengeluaran\n";
        cout << "3. Laporan Catatan\n";
        cout << "0. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                TambahPemasukan(head, today_date, saldo);
                break;
            }

            case 2: {
                CatatanPengeluaran(head, today_date, saldo);
                break;
            }

            case 3: {
                LaporanCatatan(head, today_date);
                break;
            }

            case 0:
                break;

            default:
                cout << "\nTidak ada opsi seperti itu:(";
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
