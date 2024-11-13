#include <iostream>
#include <windows.h>
#include <string>
#include <iomanip>

#include "select.h"
using namespace std;

struct Laptop {
    int laptop_id;
    string merk;
    string model;
    string spesifikasi;
    int stok;
    double harga;
    Laptop* next;

    Laptop(int id, string m, string mdl, string spec, int stk, double hrg)
        : laptop_id(id), merk(m), model(mdl), spesifikasi(spec), stok(stk), harga(hrg), next(nullptr) {}
};

struct Pesanan {
    int pesanan_id;
    string pelanggan_nama;
    string pelanggan_alamat;
    string pelanggan_telepon;
    int laptop_id;
    int jumlah;
    double total_harga;
    Pesanan* next;

    Pesanan(int id, string nama, string alamat, string telepon, int l_id, int qty, double total)
        : pesanan_id(id), pelanggan_nama(nama), pelanggan_alamat(alamat), pelanggan_telepon(telepon),
          laptop_id(l_id), jumlah(qty), total_harga(total), next(nullptr) {}
};

Laptop* laptopHead = nullptr;
Pesanan* pesananHead = nullptr;
static int lastLaptopId = 0;

void addLaptop(string merk, string model, string spesifikasi, int stok, double harga) {
    int id = ++lastLaptopId; 
    Laptop* newLaptop = new Laptop(id, merk, model, spesifikasi, stok, harga);
    newLaptop->next = laptopHead;
    laptopHead = newLaptop;
}

void displayLaptops() {
    Laptop* current = laptopHead;
    while (current != nullptr) {
        cout << "ID: " << current->laptop_id << ", Merk: " << current->merk
             << ", Model: " << current->model << ", Spesifikasi: " << current->spesifikasi
             << ", Stok: " << current->stok << ", Harga: Rp" << std::fixed << std::setprecision(2)<< current->harga << endl;
        current = current->next;
    }
}

void addPesanan(int pesanan_id, string nama, string alamat, string telepon, int laptop_id, int jumlah) {
    Laptop* laptop = laptopHead;
    while (laptop != nullptr && laptop->laptop_id != laptop_id) {
        laptop = laptop->next;
    }

    if (laptop == nullptr || laptop->stok < jumlah) {
        cout << "Laptop tidak tersedia atau stok kurang.\n";
        return;
    }

    double total_harga = laptop->harga * jumlah;
    Pesanan* newPesanan = new Pesanan(pesanan_id, nama, alamat, telepon, laptop_id, jumlah, total_harga);

    if (pesananHead == nullptr) {
        pesananHead = newPesanan;
    } else {
        Pesanan* current = pesananHead;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newPesanan;
    }

    laptop->stok -= jumlah;
    cout << "Pesanan berhasil dibuat.\n";
}

void displayPesanan() {
    Pesanan* current = pesananHead;
    while (current != nullptr) {
        cout << "ID Pesanan: " << current->pesanan_id << ", Nama: " << current->pelanggan_nama
             << ", Alamat: " << current->pelanggan_alamat << ", Telepon: " << current->pelanggan_telepon
             << ", Laptop ID: " << current->laptop_id << ", Jumlah: " << current->jumlah
             << ", Total Harga: Rp"<< std::fixed << std::setprecision(2) << current->total_harga << endl;
        current = current->next;
    }
}

void completePesananFIFO() {
    if (pesananHead == nullptr) {
        cout << "Tidak ada pesanan untuk diselesaikan.\n";
        return;
    }

    Pesanan* toDelete = pesananHead;
    pesananHead = pesananHead->next;

    cout << "Pesanan dengan ID " << toDelete->pesanan_id << " telah diselesaikan.\n";
    delete toDelete;
}
void completePesananLIFO() {
    if (pesananHead == nullptr) {
        cout << "Tidak ada pesanan untuk diselesaikan.\n";
        return;
    }

    if (pesananHead->next == nullptr) {
        cout << "Pesanan dengan ID " << pesananHead->pesanan_id << " telah diselesaikan.\n";
        delete pesananHead;
        pesananHead = nullptr;
        return;
    }

    Pesanan* current = pesananHead;
    while (current->next->next != nullptr) {
        current = current->next;
    }

    Pesanan* toDelete = current->next;
    cout << "Pesanan dengan ID " << toDelete->pesanan_id << " telah diselesaikan.\n";
    delete toDelete;
    current->next = nullptr;
}

bool loginAdmin() {
    string username, password;
    cout << "Masukkan username admin: ";
    getline(cin,username);
    cout << "Masukkan password admin: ";
    getline(cin,password);
    return (username == "admin" && password == "admin123");
}

void inputPesanan(){
    string nama, alamat, telepon;
    int laptop_id, jumlah;
    cout << "Nama Pelanggan: ";
    getline(cin,nama);
    cout << "Alamat: ";
    getline(cin,alamat);
    cout << "Telepon: ";
    getline(cin,telepon);
    cout << "Masukkan ID Laptop yang ingin dibeli: ";
    cin >> laptop_id;cin.ignore();
    Laptop* laptop = laptopHead;
    while (laptop != nullptr && laptop->laptop_id != laptop_id) {
        laptop = laptop->next;
    }

    if (laptop == nullptr) {
        cout << "Laptop dengan ID " << laptop_id << " tidak ditemukan.\n";
        return;
    }

    cout << "Membeli " << laptop->merk << " " << laptop->model << endl;
    cout << "Masukkan jumlah: ";
    cin >> jumlah;cin.ignore();
    addPesanan(rand() % 1000 + 1, nama, alamat, telepon, laptop_id, jumlah);
}

void menuPelanggan() {
    int pilihan, laptop_id, jumlah;
    string nama, alamat, telepon;

int pilihanCariLaptop;

    do {
        string menuPelangganHeader = "Menu Pelanggan";
        string menuPelanggan[] = {"Lihat Laptop", "Beli Laptop", "Keluar"};
        string cariLaptopHeader = "Cari Laptop?";
        string cariLaptop[] = {"Ya", "Kembali"};
        pilihan = showmenu(3, menuPelanggan, menuPelangganHeader);
        switch (pilihan) {
            case 0:
                displayLaptops();
                pilihanCariLaptop = showmenu(2, cariLaptop, cariLaptopHeader);
                if (pilihanCariLaptop == 0){
                    // SEARCHING DISINI nanti 
                }
                break;
            case 1:
                displayLaptops();
                inputPesanan();
                _getch();
                system("cls");
                break;
            case 2:
                cout << "Terima kasih telah mengunjungi toko kami!\n";
                break;
        }
    } while (pilihan != 2);
}

void inputLaptop(string &merk, string &model, string &spesifikasi, int &stok, double &harga){
      cout << "Merk: ";
            getline(cin, merk);
            cout << "Model: ";
            getline(cin, model);
            cout << "Spesifikasi: ";
            getline(cin, spesifikasi);
            cout << "Stok: ";
            cin >> stok;cin.ignore();
            cout << "Harga: ";
            cin >> harga;cin.ignore();
}
void deleteLaptop(int id) {
    if (laptopHead == nullptr) {
        cout << "Tidak ada laptop untuk dihapus.\n";
        return;
    }

    if (laptopHead->laptop_id == id) {
        Laptop* toDelete = laptopHead;
        laptopHead = laptopHead->next;
        delete toDelete;
        cout << "Laptop dengan ID " << id << " berhasil dihapus.\n";
        return;
    }

    Laptop* current = laptopHead;
    while (current->next != nullptr && current->next->laptop_id != id) {
        current = current->next;
    }

    if (current->next == nullptr) {
        cout << "Laptop dengan ID " << id << " tidak ditemukan.\n";
        return;
    }

    Laptop* toDelete = current->next;
    current->next = current->next->next;
    delete toDelete;
    cout << "Laptop dengan ID " << id << " berhasil dihapus.\n";
}
void updateLaptop(int id) {
    Laptop* current = laptopHead;
    while (current != nullptr && current->laptop_id != id) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Laptop dengan ID " << id << " tidak ditemukan.\n";
        return;
    }

    cout << "Mengubah data untuk Laptop dengan ID " << id << ":\n";
    string merk, model, spesifikasi;
    int stok;
    double harga;
    inputLaptop(merk, model, spesifikasi, stok, harga);
    current->merk = merk;
    current->model = model;
    current->spesifikasi = spesifikasi;
    current->stok = stok;
    current->harga = harga;
    cout << "Laptop berhasil diperbarui.\n";
}
void menuAdmin() {
    int pilihan, stok;
    double harga;
    string merk, model, spesifikasi;

    do {
        string menuAdminHeader = "Menu Admin";
        string menuAdmin[] = {"Lihat Laptop", "Tambah Laptop","Ubah Laptop", "Hapus Laptop", "Lihat Pesanan", "Keluar"};
        pilihan = showmenu(6, menuAdmin, menuAdminHeader);
                string donePesananHeader = "Selesaikan Pesanan?";
                string donePesanan[] = {"FIFO", "LIFO"};
                int pilihanDonePesanan;
        switch (pilihan) {
            case 0:
                displayLaptops();
                break;
            case 1:
                cout << "Menambahkan Laptop baru:\n";
                inputLaptop(merk, model, spesifikasi, stok, harga);
                addLaptop(merk, model, spesifikasi, stok, harga);
                system("cls");
                cout << "Laptop berhasil ditambahkan.\n";
                break;
            case 2:
                displayLaptops();
                int id;
                // bawah ini ganti searching
                cout << "Masukkan ID Laptop yang ingin diubah: ";
                cin >> id;cin.ignore();
                updateLaptop(id);
                cout << "Perubahan berhasil disimpan.\n"; ;
                _getch();
                system("cls");
                break;
            case 3:
                displayLaptops();
                // bawah ini ganti searching
                cout << "Masukkan ID Laptop yang ingin dihapus: ";
                cin >> id;cin.ignore();
                deleteLaptop(id);
                system("cls");  
                break;
            case 4:
                displayPesanan();
                pilihanDonePesanan = showmenu(2, donePesanan, donePesananHeader);
                if (pilihanDonePesanan == 0){
                    completePesananFIFO();
                } else {
                    completePesananLIFO();
                }
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 5);
}

int main() {
    int pilihan;

    addLaptop("Dell", "Inspiron 14", "Intel i5, 8GB RAM, 256GB SSD", 10, 7000000);
    addLaptop("HP", "Pavilion 15", "Intel i7, 16GB RAM, 512GB SSD", 5, 12000000);

    do {
    system("cls");
        string menuMainHeader = "Selamat datang di Toko Laptop!";
        string menuMain[] = {"Menu Pelanggan", "Login Admin", "Keluar"};
        pilihan = showmenu(3, menuMain, menuMainHeader);
        switch (pilihan) {
            case 0:
                menuPelanggan();
                break;
            case 1:
                if (loginAdmin()) {
                    system("cls");
                    cout << "Login berhasil.\n";
                    menuAdmin();
                } else {
                    cout << "Username atau password salah.\n";
                }
                break;
            case 2:
                cout << "Terima kasih telah menggunakan sistem ini!\n";
                break;
        }
    } while (pilihan != 2);

    return 0;
}
