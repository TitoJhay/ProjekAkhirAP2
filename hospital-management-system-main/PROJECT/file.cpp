#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Fungsi untuk menulis data ke file
void tulisKeFile(const string& data) {
    ofstream file;
    string namaFile = "data.txt";
    file.open(namaFile, ios::app); // Membuka file dalam mode append
    if (file.is_open()) {
        file << data << endl;
        file.close();
        cout << "Data berhasil disimpan ke file." << endl;
    } else {
        cout << "Gagal membuka file untuk menulis." << endl;
    }
}

// Fungsi untuk membaca data dari file
void bacaDariFile() {
    ifstream file;
    string namaFile = "data.txt";
    file.open(namaFile);
    if (file.is_open()) {
        string baris;
        cout << "Isi dari file:" << endl;
        while (getline(file, baris)) {
            cout << baris << endl;
        }
        file.close();
    } else {
        cout << "Gagal membuka file untuk membaca." << endl;
    }
}

int main() {
    string data;

    cout << "Masukkan data yang ingin disimpan: ";
    getline(cin, data);

    tulisKeFile(data);
    bacaDariFile();

    return 0;
}
