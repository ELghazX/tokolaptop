#include <iostream>
#include <windows.h>
#include "select.h"
using namespace std;

struct Account {
    string username;
    string password;
};

struct Laptop {
    int id;
    string brand;
    string model;
};

struct Accounts {
    Account akun;
    Accounts *next;
};

struct Laptops {
    Laptop data;
    Laptops *next;
};

// struct Database {
//     Accounts *admin;
//     Laptops *laptops;
// };

int login(Accounts *akun) {
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    Accounts *temp = akun;
    if (username == "admin" && password == "admin")
        return 1;

    while (temp != NULL) {
        if (temp->akun.username == username && temp->akun.password == password) {
            return 0;
        }
        temp = temp->next;
    }
    return -1;
}

void registerUser(Accounts *&akun) {
    Account new_akun;
    cout << "Username: ";
    cin >> new_akun.username;
    cout << "Password: ";
    cin >> new_akun.password;
    Accounts *temp = akun;
    while (temp != NULL) {
        if (temp->akun.username == new_akun.username) {
            cout << "Username sudah digunakan!" << endl;
            return;
        }
        temp = temp->next;
    }

    Accounts *new_account = new Accounts;
    new_account->akun = new_akun;
    new_account->next = akun;
    akun = new_account;
    system("cls");
}

void menuMain() {
    string opsi[] = {"Login", "Register", "Exit"};
    string opsi_header = "Selamat Datang di Jahron Cyber";
    int jumlah_opsi = 3, test;
    Accounts *akun = NULL;
    
    while (true)
    {
        int pilih = showmenu(jumlah_opsi, opsi, opsi_header);

        switch (pilih) {
            case 0:
                system("cls");
                test = login(akun);
                if (test == 1) {
                    cout << "Login berhasil! admin" << endl;
                    // menuAdmin();
                } else if (test == 0) {
                    cout << "Login berhasil! user" << endl;
                    // menuUser();
                } else {
                    cout << "Username atau password salah!" << endl;
                }
                break;
            case 1:
                registerUser(akun);
                break;
            case 2:
                // exit();
                break;
        }
    }
}

void menuAdmin() {
    string opsi[] = {"List Laptop", "Tambah Laptop", "Ubah Laptop", "Hapus Laptop", "Logout"};
    string opsi_header = "Menu Admin";
    int jumlah_opsi = 5;
    int pilih = showmenu(jumlah_opsi, opsi, opsi_header);
    switch (pilih) {
        case 0:
            // listLaptop();
            break;
        case 1:
            // tambahLaptop();
            break;
        case 2:
            // ubahLaptop();
            break;
        case 3:
            // hapusLaptop();
            break;
        case 4:
            // logout();
            break;
    }
}

void menuUser() {
    string opsi[] = {"Lihat Laptop", "Beli Laptop", "Cari Laptop", "Logout"};
    string opsi_header = "Menu User";
    int jumlah_opsi = 4;
    int pilih = showmenu(jumlah_opsi, opsi, opsi_header);
    switch (pilih) {
        case 0:
            // lihatLaptop();
            break;
        case 1:
            // beliLaptop();
            break;
        case 2:
            // CariLaptop();
            break;
        case 3:
            // logout();
            break;
    }
}

int main() {
    menuMain();
    return 0;
}