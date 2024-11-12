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
    int stock;
    int price;
};

struct Accounts {
    Account akun;
    Accounts *next;
};

struct Laptops {
    Laptop data;
    Laptops *next;
};

struct Brand {
    string brand;
};

struct Brands {
    Brand data;
    Brands *next;
};


int getLength(Laptops *head) {
    int length = 0;
    Laptops *temp = head;
    while (temp != nullptr) {
        length++;
        temp = temp->next;
    }
    return length;
}

Laptops** listToArray(Laptops *head, int length) {
    Laptops **arr = new Laptops*[length];
    Laptops *temp = head;
    for (int i = 0; i < length; i++) {
        arr[i] = temp;
        temp = temp->next;
    }
    return arr;
}

void arrayToList(Laptops **arr, Laptops *&head, int length) {
    head = arr[0];
    Laptops *temp = head;
    for (int i = 1; i < length; i++) {
        temp->next = arr[i];
        temp = temp->next;
    }
    temp->next = nullptr;
    delete[] arr;
}

void shellSort(Laptops *&head, bool ascending = true) {
    int n = getLength(head);
    if (n <= 1) return;

    Laptops **arr = listToArray(head, n);

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Laptops *temp = arr[i];
            int j;
            if (ascending) {
                for (j = i; j >= gap && arr[j - gap]->data.price > temp->data.price; j -= gap) {
                    arr[j] = arr[j - gap];
                }
            } else {
                for (j = i; j >= gap && arr[j - gap]->data.price < temp->data.price; j -= gap) {
                    arr[j] = arr[j - gap];
                }
            }
            arr[j] = temp;
        }
    }

    arrayToList(arr, head, n);
}

void mergeSortName(Laptops *&head) {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Laptops *mid = head;
    Laptops *temp = head->next;
    while (temp != nullptr && temp->next != nullptr) {
        mid = mid->next;
        temp = temp->next->next;
    }

    Laptops *left = head;
    Laptops *right = mid->next;
    mid->next = nullptr;

    mergeSortName(left);
    mergeSortName(right);

    Laptops *sorted = nullptr;
    Laptops *tail = nullptr;
    while (left != nullptr && right != nullptr) {
        Laptops *temp = nullptr;
        if (left->data.brand.compare(right->data.brand) < 0) {
            temp = left;
            left = left->next;
        } else {
            temp = right;
            right = right->next;
        }

        if (sorted == nullptr) {
            sorted = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }

    if (left != nullptr) {
        tail->next = left;
    } else if (right != nullptr) {
        tail->next = right;
    }

    head = sorted;
}

int login(Accounts *akun) {
    string username, password;
    cout << "Username: ";
    getline(cin,username);
    cout << "Password: ";
    getline(cin,password);
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
    getline(cin, new_akun.username);
    cout << "Password: ";
    getline(cin, new_akun.password);
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
                return;
        }
    }
}

void listLaptop(Laptops *head){
   if(head == nullptr){
         cout<<"List Laptop kosong"<<endl;
   }else{ 
        int no = 1;
        cout << "No\tID\tBrand\tModel\tStok\tHarga" << endl;
            while(head != nullptr){
                cout << no << "\t" << head->data.id << "\t" << head->data.brand << "\t" << head->data.model << "\t"<< head->data.stock << "\t" << head->data.price << endl;
                no++;
                head = head->next;
            }
        cout<<endl;
    }
}

Brand* linkedListToArray(Brands *head, int jumlahBrand) {
    if (head == nullptr || jumlahBrand == 0) {
        return nullptr;
    }

    Brand* array = new Brand[jumlahBrand];
    Brands* current = head;
    int index = 0;

    while (current != nullptr) {
        array[index] = current->data;
        current = current->next;
        index++;
    }

    return array;
}

void addBrand(Brands *&head, string brand){
    Brands *brandBaru = new Brands();
    brandBaru->data.brand = brand;
    brandBaru->next = nullptr;

    if(head == nullptr){
        head = brandBaru;
        return;
    }

    Brands *temp = head;
    while(temp->next != nullptr){
        temp = temp->next;
    }
    temp->next = brandBaru;
}

Laptops* inputData(int &lastId, Brands *&headbrand, int &jumlahBrand) {
    Laptops *laptopBaru = new Laptops();
    laptopBaru->data.id = ++lastId;
    Brand *opsi = linkedListToArray(headbrand, jumlahBrand);
    string brandOptions[jumlahBrand + 2];
    brandOptions[0] = "Tambah Brand";
    for (int i = 0; i < jumlahBrand; i++) {
        brandOptions[i + 1] = opsi[i].brand;
    }

    brandOptions[jumlahBrand + 1] = "Batal";
    int pilih = showmenu(jumlahBrand + 2, brandOptions, "Pilih Brand");
    if (pilih == 0) {
        string newBrand;
        cout << "Masukkan Brand Baru: ";
        getline(cin, newBrand);
        addBrand(headbrand, newBrand);
        jumlahBrand++;
        laptopBaru->data.brand = newBrand;
    } else if (pilih == jumlahBrand + 1) {
        delete laptopBaru;
        return nullptr;
    } else {
        laptopBaru->data.brand = brandOptions[pilih];
    }
    cout << "Model: ";
    getline(cin, laptopBaru->data.model);
    cout << "Stok: ";
    cin >> laptopBaru->data.stock;cin.ignore();
    cout << "Harga: ";
    cin >> laptopBaru->data.price;cin.ignore();
    cin.clear();
    return laptopBaru;
}

void addLaptopFirst(Laptops *&head, int &jumlahlaptop, int &lastId, Brands *&headbrand, int &jumlahBrand) {
    Laptops *laptopBaru = inputData(lastId, headbrand, jumlahBrand);
    if (laptopBaru == nullptr) {
        lastId--;
        return;
    }
    laptopBaru->next = head;
    head = laptopBaru;
    jumlahlaptop++;
}

void addLaptop(Laptops *&head, int &jumlahlaptop, int &lastId, Brands *&headbrand, int &jumlahBrand) {
    cout << "TAMBAH LAPTOP BARU" << endl;
    if (head == nullptr) {
        addLaptopFirst(head, jumlahlaptop, lastId, headbrand, jumlahBrand);
        return;
    }
    Laptops *laptopBaru = inputData(lastId, headbrand, jumlahBrand);
    if (laptopBaru == nullptr) {
        lastId--;
        return;
    }
    
    laptopBaru->next = nullptr;

    Laptops *temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = laptopBaru;
    jumlahlaptop++;
}

void menuAdmin(Laptops *head, int &jumlahLaptop, int &lastId, Brands *&headbrand, int &jumlahBrand) {
    string opsi[] = {"List Laptop", "Tambah Laptop", "Ubah Laptop", "Hapus Laptop","Selesaikan Pesanan", "Logout"};
    string sort[] = {"Brand", "Price"}; 
    string opsi_header = "Menu Admin";
    int jumlah_opsi = 6;
    int pilih = showmenu(jumlah_opsi, opsi, opsi_header);
    switch (pilih) {
        case 0:
            opsi_header = "Sort By";
            jumlah_opsi = 2;
            pilih = showmenu(jumlah_opsi, sort, opsi_header);
            if(pilih == 0){
                mergeSortName(head);
            } else {
                // mergeSortPrice(head);
            }

            listLaptop(head);
            break;
        case 1:
            addLaptop(head, jumlahLaptop, lastId, headbrand, jumlahBrand);
            break;
        case 2:
            // ubahLaptop();
            break;
        case 3:
            // hapusLaptop();
            break;
        case 4:
            // selesaikanPesanan();
            break;
        case 5:
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
    int jumlahLaptop = 0, jumlahAccount = 1 ,jumlahBrand = 0;
    int lastId = 0;
    Laptops *head = nullptr;
    Accounts *headakun = nullptr;
    Brands *headbrand = nullptr;
    // menuMain();
    while (true) {
    addLaptop(head, jumlahLaptop, lastId, headbrand, jumlahBrand);
    shellSort(head, false);
    listLaptop(head);
    _getch();
    }
    addLaptop(head, jumlahLaptop, lastId, headbrand, jumlahBrand);
    _getch();
    // menuMain();
    return 0;
}
