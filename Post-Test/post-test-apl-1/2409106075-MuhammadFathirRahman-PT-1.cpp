#include <iostream>
#include <string>
using namespace std;

bool login(){
    string username = "MuhammadFathirRahman";
    string password = "2409106075";
    string user;
    string pass;
    int percobaan = 3;

    while (percobaan > 0) {
        string masukkan_username;
        string masukkan_password;
        cout << "Username: ";
        cin >> masukkan_username;
        cout << "password: ";
        cin >> masukkan_password;

        if (masukkan_username == username && masukkan_password == password) {
            cout << "Login anda berhasil\n";
            return true;
        } 
        else {
            percobaan--;
            cout << "Login anda gagal, silahkan coba kembali, sisa percobaan: " << percobaan << endl;
        }
    }
    cout << "Anda telah mencoba untuk login sebanyak 3 kali. program akan berhenti\n";
}

int main() {
    if (!login()) {
        return 0;
    }

    while (true) {
        cout << "\nMenu Utama:\n";
        cout << "1. Konversi Mata Uang\n";
        cout << "2. Konversi Jarak\n";
        cout << "3. Konversi Waktu\n";
        cout << "4. Konversi Suhu\n";
        cout << "5. Logout\n";
        cout << "Opsi pilihan (1-5): ";

        int pilihan;
        cin >> pilihan;

        if (pilihan == 1) {
            double jumlah;
            cout << "Masukkan Jumlah Mata Uang: ";
            cin >> jumlah;

            cout << "\n1. Rupiah ke Dolar AS\n";
            cout << "2. Rupiah ke Euro\n";
            cout << "3. Dolar AS ke Rupiah\n";
            cout << "4. Dolar AS ke Euro\n";
            cout << "5. Euro ke Rupiah\n";
            cout << "6. Euro ke Dolar AS\n";
            cout << "Opsi Pilihan (1-6): ";

            int sub_pilihan;
            cin >> sub_pilihan;

            double hasil = 0;
            if (sub_pilihan == 1) {
                hasil = jumlah / 16295;
            } else if (sub_pilihan == 2) {
                hasil = jumlah / 17676;
            } else if (sub_pilihan == 3) {
                hasil = jumlah * 16295;
            } else if (sub_pilihan == 4) {
                hasil = jumlah * 0.92;
            } else if (sub_pilihan == 5) {
                hasil = jumlah * 17676;
            } else if (sub_pilihan == 6) {
                hasil = jumlah / 0.92;
            } else {
                cout << "Pilihan tidak ditemukan\n";
                continue;
            }
            cout << "Hasil konversi: " << hasil << endl;
        } else if (pilihan == 2) {
            double jumlah;
            cout << "Masukkan jumlah: ";
            cin >> jumlah;

            cout << "\n1. Kilometer ke Meter\n";
            cout << "2. Kilometer ke Centimeter\n";
            cout << "3. Meter ke Kilometer\n";
            cout << "4. Meter ke Centimeter\n";
            cout << "5. Centimeter ke Kilometer\n";
            cout << "6. Centimeter ke Meter\n";
            cout << "Pilih opsi (1-6): ";

            int sub_pilihan;
            cin >> sub_pilihan;

            double hasil = 0;
            if (sub_pilihan == 1) {
                hasil = jumlah * 1000;
            } else if (sub_pilihan == 2) {
                hasil = jumlah * 100000;
            } else if (sub_pilihan == 3) {
                hasil = jumlah / 1000;
            } else if (sub_pilihan == 4) {
                hasil = jumlah * 100;
            } else if (sub_pilihan == 5) {
                hasil = jumlah / 100000;
            } else if (sub_pilihan == 6) {
                hasil = jumlah / 100;
            } else {
                cout << "Pilihan tidak ditemukan\n";
                continue;
            }
            cout << "Hasil konversi: " << hasil << endl;
        } else if (pilihan == 3) {
            double jumlah;
            cout << "Masukkan jumlah: ";
            cin >> jumlah;

            cout << "\n1. Jam ke Menit\n";
            cout << "2. Jam ke Detik\n";
            cout << "3. Menit ke Jam\n";
            cout << "4. Menit ke Detik\n";
            cout << "5. Detik ke Jam\n";
            cout << "6. Detik ke Menit\n";
            cout << "Pilih opsi (1-6): ";

            int sub_pilihan;
            cin >> sub_pilihan;

            double hasil = 0;
            if (sub_pilihan == 1) {
                hasil = jumlah * 60;
            } else if (sub_pilihan == 2) {
                hasil = jumlah * 3600;
            } else if (sub_pilihan == 3) {
                hasil = jumlah / 60;
            } else if (sub_pilihan == 4) {
                hasil = jumlah * 60;
            } else if (sub_pilihan == 5) {
                hasil = jumlah / 3600;
            } else if (sub_pilihan == 6) {
                hasil = jumlah / 60;
            } else {
                cout << "Pilihan tidak ditemukan\n";
                continue;
            }
            cout << "Hasil konversi: " << hasil << endl;
        } else if (pilihan == 4) {
            double suhu;
            cout << "Masukkan suhu: ";
            cin >> suhu;

            cout << "\n1. Celsius ke Fahrenheit\n";
            cout << "2. Celsius ke Kelvin\n";
            cout << "3. Fahrenheit ke Celsius\n";
            cout << "4. Fahrenheit ke Kelvin\n";
            cout << "5. Kelvin ke Celsius\n";
            cout << "6. Kelvin ke Fahrenheit\n";
            cout << "Pilih opsi (1-6): ";

            int sub_pilihan;
            cin >> sub_pilihan;

            double hasil = 0;
            if (sub_pilihan == 1) {
                hasil = (suhu * 9/5) + 32;
            } else if (sub_pilihan == 2) {
                hasil = suhu + 273.15;
            } else if (sub_pilihan == 3) {
                hasil = (suhu - 32) * 5/9;
            } else if (sub_pilihan == 4) {
                hasil = (suhu - 32) * 5/9 + 273.15;
            } else if (sub_pilihan == 5) {
                hasil = suhu - 273.15;
            } else if (sub_pilihan == 6) {
                hasil = (suhu - 273.15) * 9/5 + 32;
            } else {
                cout << "Pilihan tidak ditemukan\n";
                continue;
            }
            cout << "Hasil konversi: " << hasil << endl;
        } else if (pilihan == 5) {
            cout << "Logout berhasil. Program berhenti.\n";
            break;
        } else {
            cout << "Pilihan tidak ditemukan\n";
        }
    }

    return 0;
}