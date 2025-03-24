#include <iostream>
#include <string>
#include <iomanip> // Untuk setw() dan setfill()
#include <thread>  // Untuk jeda
#include <chrono>  // Untuk jeda
#include <map>     // Untuk menghitung jumlah akun per server
using namespace std;

#define MAX_USER 100
#define MAX_AKUN 100

// Struct untuk menyimpan data pengguna
struct User {
    string username;
    string password;
    string role; // "Admin" atau "User"
};

// Struct untuk menyimpan data akun server
struct Akun {
    string nama;
    string status; // Hanya "Aktif" atau "Tidak Aktif"
    string serverTujuan; // Hanya 5 pilihan server
    string password; // Minimal 8 karakter
    User user; // Nested struct untuk menghubungkan akun dengan pengguna
};

User users[MAX_USER]; // Array of struct untuk menyimpan data pengguna
Akun akun[MAX_AKUN]; // Array of struct untuk menyimpan data akun
int userCount = 0; // Jumlah pengguna yang terdaftar
int akunCount = 0; // Jumlah akun yang terdaftar

// Fungsi untuk register
void registerUser() {
    if (userCount < MAX_USER) {
        cout << "Masukkan username: ";
        cin >> users[userCount].username;
        cout << "Masukkan password: ";
        cin >> users[userCount].password;
        users[userCount].role = "Commoners"; // Default role adalah "User"
        userCount++;
        cout << "Registrasi berhasil!" << endl;
    } else {
        cout << "Kapasitas pengguna penuh! Tidak bisa menambah pengguna lagi." << endl;
    }
}

// Fungsi untuk login
User* login() {
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

        // Cek username dan password
        for (int i = 0; i < userCount; i++) {
            if (users[i].username == username && users[i].password == password) {
                cout << "Login berhasil! Selamat datang, " << users[i].role << "!" << endl;
                this_thread::sleep_for(chrono::seconds(2)); // Jeda 2 detik
                return &users[i]; // Mengembalikan pointer ke pengguna yang login
            }
        }

        percobaan++;
        cout << "Username atau password salah! Percobaan ke-" << percobaan << " dari " << maksPercobaan << "." << endl;
    }

    cout << "Anda telah melebihi batas percobaan login. Program berhenti." << endl;
    exit(0); // Menghentikan program jika gagal login 3 kali
}

// Fungsi untuk menampilkan menu
int tampilkanMenu(User* user) {
    int pilihan;
    cout << "Menu Program" << endl;
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

// Fungsi untuk menampilkan semua akun dalam bentuk tabel dengan nomor urut
int tampilkanAkun() {
    if (akunCount == 0) {
        cout << "Belum ada akun" << endl;
        return 0; // Mengembalikan 0 jika tidak ada akun
    } else {
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
        return 1; // Mengembalikan 1 jika berhasil menampilkan akun
    }
}

// Fungsi untuk menampilkan daftar server beserta jumlah akun
void tampilkanDaftarServer() {
    map<string, int> jumlahAkunPerServer;

    // Menghitung jumlah akun per server
    for (int i = 0; i < akunCount; i++) {
        jumlahAkunPerServer[akun[i].serverTujuan]++;
    }

    // Menampilkan daftar server beserta jumlah akun
    cout << "+---------------------+---------------------+" << endl;
    cout << "| Server Tujuan       | Jumlah Akun         |" << endl;
    cout << "+---------------------+---------------------+" << endl;

    for (const auto& server : jumlahAkunPerServer) {
        cout << "| " << setw(20) << left << server.first
             << "| " << setw(20) << left << server.second << "|" << endl;
    }

    cout << "+---------------------+---------------------+" << endl;
}

// Fungsi untuk memilih server tujuan dari 5 pilihan
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

// Fungsi untuk menambah akun
int tambahAkun(User* user) {
    if (akunCount < MAX_AKUN) {
        cout << "Masukkan nama akun: ";
        cin.ignore();
        getline(cin, akun[akunCount].nama);

        // Input password (minimal 8 karakter)
        string passwordInput;
        do {
            cout << "Masukkan password akun (minimal 8 karakter): ";
            getline(cin, passwordInput);
            if (passwordInput.length() < 8) {
                cout << "Password harus minimal 8 karakter!" << endl;
            }
        } while (passwordInput.length() < 8);
        akun[akunCount].password = passwordInput;

        // Input server tujuan (hanya 5 pilihan)
        akun[akunCount].serverTujuan = pilihServerTujuan();

        // Status akun default "Aktif" saat menambah akun
        akun[akunCount].status = "Aktif";

        // Menyimpan informasi pengguna yang membuat akun
        akun[akunCount].user = *user;

        akunCount++;
        cout << "Akun berhasil ditambahkan" << endl;
        return 1; // Mengembalikan 1 jika berhasil menambah akun
    } else {
        cout << "Kapasitas penuh! Tidak bisa menambah akun lagi." << endl;
        return 0; // Mengembalikan 0 jika gagal menambah akun
    }
}

// Fungsi untuk mengubah akun
int ubahAkun(User* user) {
    int index;
    if (akunCount == 0) {
        cout << "Belum ada akun untuk diubah." << endl;
        return 0;
    } else {
        tampilkanAkun();
        cout << "Masukkan nomor akun yang akan diubah: ";
        cin >> index;

        if (index > 0 && index <= akunCount) {
            // Hanya admin yang bisa mengubah
            if (user->role == "Endministrator" || akun[index - 1].user.username == user->username) {
                int pilihanUbah;
                cout << "Pilih yang ingin diubah:" << endl;
                cout << "1. Nama Akun" << endl;
                cout << "2. Status Akun" << endl;
                cout << "3. Server Tujuan" << endl;
                cout << "4. Password" << endl;
                cout << "Pilihan: ";
                cin >> pilihanUbah;
                cin.ignore(); // Membersihkan buffer

                switch (pilihanUbah) {
                    case 1: // Ubah nama akun
                        cout << "Masukkan nama akun baru: ";
                        getline(cin, akun[index - 1].nama);
                        break;
                    case 2: // Ubah status akun
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
                    case 3: // Ubah server tujuan
                        akun[index - 1].serverTujuan = pilihServerTujuan();
                        break;
                    case 4: // Ubah password
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
                return 1; // Mengembalikan 1 jika berhasil mengubah akun
            } else {
                cout << "Anda tidak memiliki izin untuk mengubah akun ini." << endl;
                return 0;
            }
        } else {
            cout << "Nomor akun tidak valid" << endl;
            return 0; // Mengembalikan 0 jika nomor akun tidak valid
        }
    }
}

// Fungsi untuk menghapus akun
int hapusAkun(User* user) {
    int index;
    if (akunCount == 0) {
        cout << "Belum ada akun untuk dihapus." << endl;
        return 0; // Mengembalikan 0 jika tidak ada akun
    } else {
        tampilkanAkun();
        cout << "Masukkan nomor akun yang akan dihapus: ";
        cin >> index;

        if (index > 0 && index <= akunCount) {
            // Hanya admin yang bisa menghapus
            if (user->role == "Endministrator" || akun[index - 1].user.username == user->username) {
                for (int i = index - 1; i < akunCount - 1; i++) {
                    akun[i] = akun[i + 1];
                }
                akunCount--;
                cout << "Akun berhasil dihapus" << endl;
                return 1; // Mengembalikan 1 jika berhasil menghapus akun
            } else {
                cout << "Anda tidak memiliki izin untuk menghapus akun ini." << endl;
                return 0;
            }
        } else {
            cout << "Nomor akun tidak valid" << endl;
            return 0; // Mengembalikan 0 jika nomor akun tidak valid
        }
    }
}

int main() {
    // Tambahkan admin default
    users[userCount].username = "MuhammadFathirRahman";
    users[userCount].password = "2409106075";
    users[userCount].role = "Endministrator";
    userCount++;

    User* loggedInUser = nullptr;

    // Menu utama
    while (true) {
        system("cls");
        cout << "Selamat datang di PS Endfield" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilihan: ";
        int pilihan;
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear(); // Menghapus flag error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
            cout << "Input tidak valid! Harap masukkan angka." << endl;
            system("pause");
            continue;
        }

        switch (pilihan) {
            case 1:
                registerUser();
                break;
            case 2:
                loggedInUser = login();
                if (loggedInUser) {
                    int pilihanMenu;
                    do {
                        system("cls");
                        cout << "Selamat datang di PS Endfield" << endl;
                        cout << "Daftar Server dan Jumlah Akun:" << endl;
                        tampilkanDaftarServer(); // Menampilkan daftar server beserta jumlah akun
                        pilihanMenu = tampilkanMenu(loggedInUser);

                        switch (pilihanMenu) {
                            case 1:
                                tampilkanAkun();
                                break;
                            case 2:
                                if (loggedInUser->role == "Endministrator") {
                                    tambahAkun(loggedInUser);
                                } else {
                                    cout << "Anda tidak memiliki izin untuk menambah akun." << endl;
                                }
                                break;
                            case 3:
                                if (loggedInUser->role == "Endministrator") {
                                    ubahAkun(loggedInUser);
                                } else {
                                    cout << "Anda tidak memiliki izin untuk mengubah akun." << endl;
                                }
                                break;
                            case 4:
                                if (loggedInUser->role == "Endministrator") {
                                    hapusAkun(loggedInUser);
                                } else {
                                    cout << "Anda tidak memiliki izin untuk menghapus akun." << endl;
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
                cout << "Program selesai." << endl;
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