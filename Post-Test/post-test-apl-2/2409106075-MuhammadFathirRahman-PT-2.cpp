#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>
#include <map>
using namespace std;

#define MAX_AKUN 100

struct Akun {
    string nama;
    string status; // Hanya "Aktif" atau "Tidak Aktif"
    string serverTujuan; // Hanya 5 pilihan server
    string password; // Minimal 8 karakter
};

Akun akun[MAX_AKUN];
int panjang = 0;

bool login() {
    string username, password;
    int percobaan = 0;
    const int maksPercobaan = 3;

    cout << "Selamat datang di PS Endfield" << endl;
    cout << "Silakan login terlebih dahulu." << endl;

    while (percobaan < maksPercobaan) {
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
  
        if (username == "MuhammadFathirRahman" && password == "2409106075") {
            cout << "Login berhasil!" << endl;
            cout << "Selamat datang, Endministrator!" << endl;
            this_thread::sleep_for(chrono::seconds(2)); // Jeda 2 detik
            return true;
        } else {
            percobaan++;
            cout << "Username atau password salah, anda berapada di percobaan ke-" << percobaan << " dari " << maksPercobaan << " sebelum program berhenti." << endl;
        }
    }

    cout << "Anda telah melebihi batas percobaan login. Program berhenti." << endl;
    return false;
}

int tampilkanMenu() {
    int pilihan;
    cout << "Menu Program" << endl;
    cout << "1. Tampilkan Akun" << endl;
    cout << "2. Tambah Akun" << endl;
    cout << "3. Ubah Akun" << endl;
    cout << "4. Hapus Akun" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilihan: ";
    cin >> pilihan;
    return pilihan;
}

int tampilkanAkun() {
    if (panjang == 0) {
        cout << "Belum ada akun" << endl;
        return 0; // Mengembalikan 0 jika tidak ada akun
    } else {
        cout << "+-------+---------------------+---------------------+---------------------+---------------------+" << endl;
        cout << "| No.   | Nama Akun           | Status              | Server Tujuan       | Password            |" << endl;
        cout << "+-------+---------------------+---------------------+---------------------+---------------------+" << endl;

        for (int i = 0; i < panjang; i++) {
            cout << "| " << setw(5) << left << i + 1
                 << " | " << setw(20) << left << akun[i].nama
                 << "| " << setw(20) << left << akun[i].status
                 << "| " << setw(20) << left << akun[i].serverTujuan
                 << "| " << setw(20) << left << akun[i].password << "|" << endl;
        }

        cout << "+-------+---------------------+---------------------+---------------------+---------------------+" << endl;
        return 1;
    }
}

void tampilkanDaftarServer() {
    map<string, int> jumlahAkunPerServer;

    for (int i = 0; i < panjang; i++) {
        jumlahAkunPerServer[akun[i].serverTujuan]++;
    }

    cout << "+---------------------+---------------------+" << endl;
    cout << "| Server Tujuan       | Jumlah Akun         |" << endl;
    cout << "+---------------------+---------------------+" << endl;

    for (const auto& server : jumlahAkunPerServer) {
        cout << "| " << setw(20) << left << server.first
             << "| " << setw(20) << left << server.second << "|" << endl;
    }

    cout << "+---------------------+---------------------+" << endl;
}

string pilihServerTujuan() {
    int pilihan;
    cout << "Pilih server tujuan:" << endl;
    cout << "1. OMV Dijiang" << endl;
    cout << "2. Rhodes Island" << endl;
    cout << "3. Endfield Industries" << endl;
    cout << "4. Hongshan" << endl;
    cout << "5. TGCC" << endl;
    cout << "Pilihan: ";
    cin >> pilihan;

    switch (pilihan) {
        case 1: return "OMV Dijiang";
        case 2: return "Rhodes Island";
        case 3: return "Endfield Industries";
        case 4: return "Hongshan";
        case 5: return "TGCC";
        default:
            cout << "Pilihan tidak valid, default ke OMV Dijiang." << endl;
            return "OMV Dijiang";
    }
}

int tambahAkun() {
    if (panjang < MAX_AKUN) {
        cout << "Masukkan nama akun: ";
        cin.ignore();
        getline(cin, akun[panjang].nama);

        string passwordInput;
        do {
            cout << "Masukkan password akun (minimal 8 karakter): ";
            getline(cin, passwordInput);
            if (passwordInput.length() < 8) {
                cout << "Password harus minimal 8 karakter!" << endl;
            }
        } while (passwordInput.length() < 8);
        akun[panjang].password = passwordInput;

        akun[panjang].serverTujuan = pilihServerTujuan();

        akun[panjang].status = "Aktif";

        panjang++;
        cout << "Akun berhasil ditambahkan" << endl;
        return 1;
    } else {
        cout << "Kapasitas penuh! Tidak bisa menambah akun lagi." << endl;
        return 0;
    }
}

int ubahAkun() {
    int index;
    if (panjang == 0) {
        cout << "Belum ada akun untuk diubah." << endl;
        return 0;
    } else {
        tampilkanAkun();
        cout << "Masukkan nomor akun yang akan diubah: ";
        cin >> index;

        if (index > 0 && index <= panjang) {
            int pilihanUbah;
            cout << "Pilih yang ingin diubah:" << endl;
            cout << "1. Nama Akun" << endl;
            cout << "2. Status Akun" << endl;
            cout << "3. Server Tujuan" << endl;
            cout << "4. Password" << endl;
            cout << "Pilihan: ";
            cin >> pilihanUbah;
            cin.ignore();

            switch (pilihanUbah) {
                case 1:
                    cout << "Masukkan nama akun baru: ";
                    getline(cin, akun[index - 1].nama);
                    break;
                case 2:
                    {
                        string statusInput;
                        do {
                            cout << "Masukkan status akun (Aktif/Tidak Aktif): ";
                            getline(cin, statusInput);
                            if (statusInput != "Aktif" && statusInput != "Tidak Aktif") {
                                cout << "Status tidak valid! Harap masukkan 'Aktif' atau 'Tidak Aktif'." << endl;
                            }
                        } while (statusInput != "Aktif" && statusInput != "Tidak Aktif");
                        akun[index - 1].status = statusInput;
                    }
                    break;
                case 3:
                    akun[index - 1].serverTujuan = pilihServerTujuan();
                    break;
                case 4:
                    {
                        string passwordInput;
                        do {
                            cout << "Masukkan password akun baru (minimal 8 karakter): ";
                            getline(cin, passwordInput);
                            if (passwordInput.length() < 8) {
                                cout << "Password harus minimal 8 karakter!" << endl;
                            }
                        } while (passwordInput.length() < 8);
                        akun[index - 1].password = passwordInput;
                    }
                    break;
                default:
                    cout << "Pilihan tidak valid!" << endl;
                    return 0;
            }

            cout << "Akun berhasil diubah" << endl;
            return 1;
        } else {
            cout << "Nomor akun tidak valid" << endl;
            return 0;
        }
    }
}

int hapusAkun() {
    int index;
    if (panjang == 0) {
        cout << "Belum ada akun untuk dihapus." << endl;
        return 0;
    } else {
        tampilkanAkun();
        cout << "Masukkan nomor akun yang akan dihapus: ";
        cin >> index;

        if (index > 0 && index <= panjang) {
            for (int i = index - 1; i < panjang - 1; i++) {
                akun[i] = akun[i + 1];
            }
            panjang--;
            cout << "Akun berhasil dihapus" << endl;
            return 1;
        } else {
            cout << "Nomor akun tidak valid" << endl;
            return 0; 
        }
    }
}

int main() {

    if (!login()) {
        return 0;
    }

    int pilihan;
    do {
        system("cls");
        cout << "Selamat datang di PS Endfield" << endl;
        cout << "Daftar Server dan Jumlah Akun:" << endl;
        tampilkanDaftarServer();
        pilihan = tampilkanMenu();

        switch (pilihan) {
            case 1:
                tampilkanAkun();
                break;
            case 2:
                tambahAkun();
                break;
            case 3:
                ubahAkun();
                break;
            case 4:
                hapusAkun();
                break;
            case 5:
                cout << "Program selesai" << endl;
                break;
            default:
                cout << "Pilihan tidak valid" << endl;
                break;
        }
        system("pause");
    } while (pilihan != 5);

    return 0;
}