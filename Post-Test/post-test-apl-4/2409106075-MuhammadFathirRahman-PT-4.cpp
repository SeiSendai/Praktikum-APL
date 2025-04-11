#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>
#include <map>
#include <limits>
using namespace std;

#define MAX_USER 100
#define MAX_AKUN 100

struct User {
    string username;
    string password;
    string role;
};

struct Akun {
    string nama;
    string status;
    string serverTujuan;
    string password;
    User user;
};

User users[MAX_USER];
Akun akun[MAX_AKUN];
int userCount = 0;
int akunCount = 0;

// Deklarasi fungsi
void registerUser(User users[], int &userCount);
User* login(User users[], int userCount);
int tampilkanMenu(User* user);
int tampilkanAkun(Akun akun[], int akunCount);
void tampilkanDaftarServer(Akun akun[], int akunCount);
string pilihServerTujuan();
int tambahAkun(Akun akun[], int &akunCount, User* user);
int ubahAkun(Akun akun[], int akunCount, User* user);
int hapusAkun(Akun akun[], int &akunCount, User* user);
void keluarProgram(int countdown); // Fungsi rekursif
void keluarProgram(); // Overloading
void tampilkanHeader(); // Overloading
void tampilkanHeader(string judul); // Overloading
void clearScreen();

// Implementasi fungsi

void clearScreen() {
    system("cls || clear");
}

// Fungsi rekursif untuk keluar program
void keluarProgram(int countdown) {
    if (countdown <= 0) {
        cout << "Program berhenti." << endl;
        exit(0);
    }
    cout << "Program akan berhenti dalam " << countdown << " detik..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    keluarProgram(countdown - 1);
}

// Overloading fungsi keluarProgram
void keluarProgram() {
    keluarProgram(3); // Default 3 detik
}

// Overloading fungsi tampilkanHeader
void tampilkanHeader() {
    cout << "====================================" << endl;
    cout << "      PS ENDFIELD MANAGEMENT       " << endl;
    cout << "====================================" << endl;
}

void tampilkanHeader(string judul) {
    cout << "====================================" << endl;
    cout << "         " << judul << "         " << endl;
    cout << "====================================" << endl;
}

void registerUser(User users[], int &userCount) {
    if (userCount < MAX_USER) {
        cout << "Masukkan username: ";
        cin >> users[userCount].username;
        cout << "Masukkan password: ";
        cin >> users[userCount].password;
        users[userCount].role = "Commoners";
        userCount++;
        cout << "Registrasi berhasil!" << endl;
    } else {
        cout << "Kapasitas pengguna penuh!" << endl;
    }
}

User* login(User users[], int userCount) {
    string username, password;
    int percobaan = 0;
    const int maksPercobaan = 3;

    while (percobaan < maksPercobaan) {
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        for (int i = 0; i < userCount; i++) {
            if (users[i].username == username && users[i].password == password) {
                cout << "Login berhasil! Selamat datang, " << users[i].role << "!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                return &users[i];
            }
        }

        percobaan++;
        cout << "Username atau password salah! Percobaan ke-" << percobaan << " dari " << maksPercobaan << "." << endl;
    }

    cout << "Anda telah melebihi batas percobaan login." << endl;
    keluarProgram();
    return nullptr;
}

int tampilkanMenu(User* user) {
    tampilkanHeader("MENU UTAMA");
    int pilihan;
    cout << "1. Tampilkan Akun" << endl;
    if (user->role == "Endministrator") {
        cout << "2. Tambah Akun" << endl;
        cout << "3. Ubah Akun" << endl;
        cout << "4. Hapus Akun" << endl;
    }
    cout << "5. Keluar" << endl;
    cout << "Pilihan: ";
    cin >> pilihan;
    return pilihan;
}

int tampilkanAkun(Akun akun[], int akunCount) {
    if (akunCount == 0) {
        cout << "Belum ada akun" << endl;
        return 0;
    }

    cout << "+-------+---------------------+---------------------+---------------------+---------------------+" << endl;
    cout << "| No.   | Nama Akun           | Status              | Server Tujuan       | Password            |" << endl;
    cout << "+-------+---------------------+---------------------+---------------------+---------------------+" << endl;

    for (int i = 0; i < akunCount; i++) {
        cout << "| " << setw(5) << left << i + 1
             << " | " << setw(20) << left << akun[i].nama
             << "| " << setw(20) << left << akun[i].status
             << "| " << setw(20) << left << akun[i].serverTujuan
             << "| " << setw(20) << left << akun[i].password << "|" << endl;
    }

    cout << "+-------+---------------------+---------------------+---------------------+---------------------+" << endl;
    return 1;
}

void tampilkanDaftarServer(Akun akun[], int akunCount) {
    map<string, int> jumlahAkunPerServer;

    for (int i = 0; i < akunCount; i++) {
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

int tambahAkun(Akun akun[], int &akunCount, User* user) {
    if (akunCount < MAX_AKUN) {
        cout << "Masukkan nama akun: ";
        cin.ignore();
        getline(cin, akun[akunCount].nama);

        string passwordInput;
        do {
            cout << "Masukkan password akun (minimal 8 karakter): ";
            getline(cin, passwordInput);
            if (passwordInput.length() < 8) {
                cout << "Password harus minimal 8 karakter!" << endl;
            }
        } while (passwordInput.length() < 8);
        akun[akunCount].password = passwordInput;

        akun[akunCount].serverTujuan = pilihServerTujuan();
        akun[akunCount].status = "Aktif";
        akun[akunCount].user = *user;

        akunCount++;
        cout << "Akun berhasil ditambahkan" << endl;
        return 1;
    } else {
        cout << "Kapasitas penuh!" << endl;
        return 0;
    }
}

int ubahAkun(Akun akun[], int akunCount, User* user) {
    int index;
    if (akunCount == 0) {
        cout << "Belum ada akun untuk diubah." << endl;
        return 0;
    }

    tampilkanAkun(akun, akunCount);
    cout << "Masukkan nomor akun yang akan diubah: ";
    cin >> index;

    if (index > 0 && index <= akunCount) {
        if (user->role == "Endministrator" || akun[index - 1].user.username == user->username) {
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
                case 2: {
                    string statusInput;
                    do {
                        cout << "Masukkan status akun (Aktif/Tidak Aktif): ";
                        getline(cin, statusInput);
                        if (statusInput != "Aktif" && statusInput != "Tidak Aktif") {
                            cout << "Status tidak valid!" << endl;
                        }
                    } while (statusInput != "Aktif" && statusInput != "Tidak Aktif");
                    akun[index - 1].status = statusInput;
                    break;
                }
                case 3:
                    akun[index - 1].serverTujuan = pilihServerTujuan();
                    break;
                case 4: {
                    string passwordInput;
                    do {
                        cout << "Masukkan password akun baru (minimal 8 karakter): ";
                        getline(cin, passwordInput);
                        if (passwordInput.length() < 8) {
                            cout << "Password harus minimal 8 karakter!" << endl;
                        }
                    } while (passwordInput.length() < 8);
                    akun[index - 1].password = passwordInput;
                    break;
                }
                default:
                    cout << "Pilihan tidak valid!" << endl;
                    return 0;
            }

            cout << "Akun berhasil diubah" << endl;
            return 1;
        } else {
            cout << "Anda tidak memiliki izin untuk mengubah akun ini." << endl;
            return 0;
        }
    } else {
        cout << "Nomor akun tidak valid" << endl;
        return 0;
    }
}

int hapusAkun(Akun akun[], int &akunCount, User* user) {
    int index;
    if (akunCount == 0) {
        cout << "Belum ada akun untuk dihapus." << endl;
        return 0;
    }

    tampilkanAkun(akun, akunCount);
    cout << "Masukkan nomor akun yang akan dihapus: ";
    cin >> index;

    if (index > 0 && index <= akunCount) {
        if (user->role == "Endministrator" || akun[index - 1].user.username == user->username) {
            for (int i = index - 1; i < akunCount - 1; i++) {
                akun[i] = akun[i + 1];
            }
            akunCount--;
            cout << "Akun berhasil dihapus" << endl;
            return 1;
        } else {
            cout << "Anda tidak memiliki izin untuk menghapus akun ini." << endl;
            return 0;
        }
    } else {
        cout << "Nomor akun tidak valid" << endl;
        return 0;
    }
}

int main() {
    // Admin default
    users[userCount].username = "MuhammadFathirRahman";
    users[userCount].password = "2409106075";
    users[userCount].role = "Endministrator";
    userCount++;

    User* loggedInUser = nullptr;

    while (true) {
        clearScreen();
        tampilkanHeader();
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilihan: ";
        int pilihan;
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid!" << endl;
            system("pause");
            continue;
        }

        switch (pilihan) {
            case 1:
                registerUser(users, userCount);
                break;
            case 2:
                loggedInUser = login(users, userCount);
                if (loggedInUser) {
                    int pilihanMenu;
                    do {
                        clearScreen();
                        tampilkanHeader("DASHBOARD");
                        tampilkanDaftarServer(akun, akunCount);
                        pilihanMenu = tampilkanMenu(loggedInUser);

                        switch (pilihanMenu) {
                            case 1:
                                tampilkanAkun(akun, akunCount);
                                break;
                            case 2:
                                if (loggedInUser->role == "Endministrator") {
                                    tambahAkun(akun, akunCount, loggedInUser);
                                } else {
                                    cout << "Akses ditolak!" << endl;
                                }
                                break;
                            case 3:
                                if (loggedInUser->role == "Endministrator") {
                                    ubahAkun(akun, akunCount, loggedInUser);
                                } else {
                                    cout << "Akses ditolak!" << endl;
                                }
                                break;
                            case 4:
                                if (loggedInUser->role == "Endministrator") {
                                    hapusAkun(akun, akunCount, loggedInUser);
                                } else {
                                    cout << "Akses ditolak!" << endl;
                                }
                                break;
                            case 5:
                                cout << "Keluar dari menu." << endl;
                                break;
                            default:
                                cout << "Pilihan tidak valid" << endl;
                                break;
                        }
                        if (pilihanMenu != 5) {
                            system("pause");
                        }
                    } while (pilihanMenu != 5);
                }
                break;
            case 3:
                keluarProgram();
                return 0;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
        if (pilihan != 3) {
            system("pause");
        }
    }

    return 0;
}