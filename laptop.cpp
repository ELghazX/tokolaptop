#include <iostream>
#include <windows.h>
#include <string>
#include <iomanip>
#include <cmath>

#include "select.h"
using namespace std;
void cls(){
    system("cls");
}

// ===============================================STRUCT================================================ //
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
struct History{
    int pesanan_id;
    string pelanggan_nama;
    string pelanggan_alamat;
    string pelanggan_telepon;
    int laptop_id;
    int jumlah;
    double total_harga;
    History* next;

    History(int id, string nama, string alamat, string telepon, int l_id, int qty, double total)
        : pesanan_id(id), pelanggan_nama(nama), pelanggan_alamat(alamat), pelanggan_telepon(telepon),
          laptop_id(l_id), jumlah(qty), total_harga(total), next(nullptr) {}
};
// ============================================INISIALISASI HEAD================================================ //
Laptop* laptopHead = nullptr;
Pesanan* pesananHead = nullptr;
History* historyHead = nullptr;
int lastLaptopId = 0;
// ============================================FUNGSI FUNGSI================================================ //

void displayLaptops() {
    Laptop* current = laptopHead;
    if (current == nullptr) {
        cout << "Tidak ada laptop yang tersedia.\n";
        return;
    }
    while (current != nullptr) {
        cout << "ID: " << current->laptop_id << ", Brand: " << current->merk
             << ", Model: " << current->model << ", Spesifikasi: " << current->spesifikasi
             << ", Stok: " << current->stok << ", Harga: Rp" << std::fixed << std::setprecision(2)<< current->harga << endl;
        current = current->next;
    }

}
void addLaptop(string merk, string model, string spesifikasi, int stok, double harga) {
    int id = ++lastLaptopId;
    Laptop* newLaptop = new Laptop(id, merk, model, spesifikasi, stok, harga);

    if (laptopHead == nullptr) {
        laptopHead = newLaptop;
    } else {
        Laptop* current = laptopHead;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newLaptop;
    }
}
void addPesanan(int pesanan_id, string nama, string alamat, string telepon, int laptop_id, int jumlah) {
    Laptop* laptop = laptopHead;
    if (laptop == nullptr) {
        cout << "Tidak ada laptop yang tersedia.\n";
        return;
    }
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
void addHistory(int pesanan_id, string nama, string alamat, string telepon, int laptop_id, int jumlah, double total_harga) {
    History* newHistory = new History(pesanan_id, nama, alamat, telepon, laptop_id, jumlah, total_harga);

    if (historyHead == nullptr) {
        historyHead = newHistory;
    } else {
        History* current = historyHead;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newHistory;
    }
}
void displayHistory() {
    History* current = historyHead;
    if (current == nullptr) {
        cout << "Tidak ada riwayat pesanan.\n";
        return;
    }
    while (current != nullptr) {
        cout << "ID Pesanan: " << current->pesanan_id << ", Nama: " << current->pelanggan_nama
             << ", Alamat: " << current->pelanggan_alamat << ", Telepon: " << current->pelanggan_telepon
             << ", Laptop ID: " << current->laptop_id << ", Jumlah: " << current->jumlah
             << ", Total Harga: Rp"<< std::fixed << std::setprecision(2) << current->total_harga << endl;
        current = current->next;
    }
}

void displayPesanan() {
    Pesanan* current = pesananHead;
    if (current == nullptr) {
        cout << "Tidak ada pesanan yang sedang diproses.\n";
        return;
    }
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
    addHistory(toDelete->pesanan_id, toDelete->pelanggan_nama, toDelete->pelanggan_alamat, toDelete->pelanggan_telepon, toDelete->laptop_id, toDelete->jumlah, toDelete->total_harga);
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
    addHistory(toDelete->pesanan_id, toDelete->pelanggan_nama, toDelete->pelanggan_alamat, toDelete->pelanggan_telepon, toDelete->laptop_id, toDelete->jumlah, toDelete->total_harga);
    delete toDelete;
    current->next = nullptr;
}

bool loginAdmin() {
    string username, password;
    cout << "Masukkan username admin: ";
    getline(cin,username);
    cout << "Masukkan password admin: ";
    getline(cin,password);
    string admin[3][3] = {{"admin1", "admin1"},
                         {"admin2", "admin2"},
                         {"3","3"}};
    for (int i = 0; i < 3; ++i) {
        if (username == admin[i][0] && password == admin[i][1]) {
            return true;
        }
    }
    return false;
}

void inputPesanan(){
    string nama, alamat, telepon;
    int laptop_id, jumlah;
    cout << "\nNama Pelanggan: ";
    getline(cin,nama);
    cout << "Alamat: ";
    getline(cin,alamat);
    cout << "Telepon: ";
    getline(cin,telepon);
    cout << "Masukkan ID Laptop yang ingin dibeli: ";
    cin >> laptop_id;cin.ignore();
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInput tidak valid\nMasukkan ID Laptop yang ingin dibeli: ";
        cin >> laptop_id;cin.ignore();
    }
    Laptop* laptop = laptopHead;
    while (laptop != nullptr && laptop->laptop_id != laptop_id) {
        laptop = laptop->next;
    }
    if (laptop == nullptr) {
        cout << "Laptop dengan ID " << laptop_id << " tidak ditemukan.\n";
        _getch();
        cls();
        return;
    }

    cout << "\nMembeli " << laptop->merk << " " << laptop->model <<endl <<endl;
    cout << "Masukkan jumlah: ";
    cin >> jumlah;cin.ignore();
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInput tidak valid\nMasukkan jumlah: ";
        cin >> jumlah;cin.ignore();
    }
    addPesanan(rand() % 1000 + 1, nama, alamat, telepon, laptop_id, jumlah);
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
            while (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInput tidak valid\nStok: ";
                cin >> stok;cin.ignore();
            }
            cout << "Harga: ";
            cin >> harga;cin.ignore();
            while (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInput tidak valid\nHarga: ";
                cin >> harga;cin.ignore();
            }
}
Laptop* fiboSearchLaptopById(Laptop* head, int id) {
    if (head == nullptr) return nullptr;

    int fibMMm2 = 0;  // (m-2)'th Fibonacci No.
    int fibMMm1 = 1;  // (m-1)'th Fibonacci No.
    int fibM = fibMMm2 + fibMMm1;  // m'th Fibonacci

    int n = 0;
    Laptop* temp = head;
    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;
    Laptop* current = head;

    while (fibM > 1) {
        int i = std::min(offset + fibMMm2, n - 1);
        Laptop* temp = head;
        for (int j = 0; j < i; j++) {
            temp = temp->next;
        }

        if (temp->laptop_id < id) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (temp->laptop_id > id) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            return temp;
        }
    }

    if (fibMMm1 && offset < n - 1) {
        Laptop* temp = head;
        for (int j = 0; j <= offset; j++) {
            temp = temp->next;
        }
        if (temp->laptop_id == id) {
           return temp;
        }
    }

    return nullptr;
}
// void deleteLaptop(int id) {
//     if (laptopHead == nullptr) {
//         cout << "Tidak ada laptop untuk dihapus.\n";
//         return;
//     }
//     if (id > lastLaptopId) {
//         cout << "Laptop dengan ID " << id << " tidak ditemukan.\n";
//         return;
//     }

//     if (laptopHead->laptop_id == id) {
//         Laptop* toDelete = laptopHead;
//         laptopHead = laptopHead->next;
//         delete toDelete;
//         cout << "Laptop dengan ID " << id << " berhasil dihapus.\n";
//         return;
//     }

//     Laptop* current = fiboSearchLaptopById(laptopHead, id);
//     if (current->next == nullptr) {
//         cout << "Laptop dengan ID " << id << " tidak ditemukan.\n";
//         return;
//     }

//     Laptop* toDelete = current->next;
//     current->next = current->next->next;
//     delete toDelete;
//     cout << "Laptop dengan ID " << id << " berhasil dihapus.\n";
// }

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

    Laptop* current = fiboSearchLaptopById(laptopHead, id);

    if (current == nullptr || current->laptop_id != id) {
        cout << "Laptop dengan ID " << id << " tidak ditemukan.\n";
        return;
    }

    Laptop* prev = laptopHead;
    while (prev->next != nullptr && prev->next != current) {
        prev = prev->next;
    }

    if (prev->next == current) {
        prev->next = current->next;
        delete current;
        cout << "Laptop dengan ID " << id << " berhasil dihapus.\n";
    } else {
        cout << "Laptop dengan ID " << id << " tidak ditemukan.\n";
    }
}

Laptop* jumpSearchLaptopById(Laptop* head, int id) {
    if (head == nullptr) return nullptr;

    int step = sqrt(lastLaptopId);
    Laptop* prev = nullptr;
    Laptop* current = head;

    while (current != nullptr && current->laptop_id < id) {
        prev = current;
        for (int i = 0; i < step && current->next != nullptr; i++) {
            current = current->next;
        }
    }

    while (current != nullptr && current->laptop_id < id) {
        current = current->next;
    }

    if (current != nullptr && current->laptop_id == id) {
        return current;
    }

    return nullptr;
}

void updateLaptop(int id) {
    if (id > lastLaptopId) {
        cout << "Laptop dengan ID " << id << " tidak ditemukan.\n";
        return;
    }

    Laptop* current = jumpSearchLaptopById(laptopHead, id);
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
    cout << "List laptop berhasil diperbarui.\n";
}
void toLowerCase(std::string &str) {
    for (char &c : str) {
        if (c >= 'A' && c <= 'Z') {
            c = c + ('a' - 'A');  // Convert uppercase to lowercase
        }
    }
}

void buildBadCharTable(const std::string& pattern, int badChar[]) {
    int size = pattern.size();
    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;
    }
    for (int i = 0; i < size; i++) {
        badChar[(int)pattern[i]] = i;
    }
}

bool boyerMooreSearch(const std::string& text, const std::string& pattern) {
    int badChar[256];
    std::string textLower = text;
    std::string patternLower = pattern;

    toLowerCase(textLower);
    toLowerCase(patternLower);

    buildBadCharTable(patternLower, badChar);

    int m = patternLower.size();
    int n = textLower.size();
    int shift = 0;

    while (shift <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && patternLower[j] == textLower[shift + j]) {
            j--;
        }

        if (j < 0) {
            return true;
            shift += (shift + m < n) ? m - badChar[textLower[shift + m]] : 1;
        } else {
            shift += std::max(1, j - badChar[textLower[shift + j]]);
        }
    }
    return false;
}

void searchLaptopsByModel(const std::string& modelSearch) {
    Laptop* current = laptopHead;
    bool found = false;
    std::string modelSearchLower = modelSearch;
    toLowerCase(modelSearchLower); // Convert the search term to lowercase

    while (current != nullptr) {
        if (boyerMooreSearch(current->model, modelSearchLower)) {
            
            std::cout << "ID: " << current->laptop_id << ", Merk: " << current->merk
                      << ", Model: " << current->model << ", Spesifikasi: " << current->spesifikasi
                      << ", Stok: " << current->stok << ", Harga: Rp" << std::fixed << std::setprecision(2)
                      << current->harga << std::endl;
            found = true;
        }
        current = current->next;
    }
    if (!found) {
        cls();
        cout << "Tidak ada laptop dengan model yang mengandung kata \"" << modelSearch << "\" ditemukan.\n";
        string searchOptions[] = {"Lanjutkan tanpa search", "Search ulang"};
        int searchChoice = showmenu(2, searchOptions, "Pilih opsi:");
        if (searchChoice == 1) {
            string modelSearch;
            cout << "Masukkan model yang ingin dicari: ";
            getline(cin, modelSearch);
            searchLaptopsByModel(modelSearch);
            modelSearch.clear();
        }
        else{
            displayLaptops();
        }
    }
}
void splitList(Laptop* source, Laptop** frontRef, Laptop** backRef) {
    Laptop* fast;
    Laptop* slow;
    slow = source;
    fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

Laptop* sortedMergeById(Laptop* a, Laptop* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    Laptop* result = nullptr;
    if (a->laptop_id <= b->laptop_id) {
        result = a;
        result->next = sortedMergeById(a->next, b);
    } else {
        result = b;
        result->next = sortedMergeById(a, b->next);
    }
    return result;
}

Laptop* getTail(Laptop* cur) {
    while (cur != nullptr && cur->next != nullptr) {
        cur = cur->next;
    }
    return cur;
}

Laptop* partition(Laptop* head, Laptop* end, Laptop** newHead, Laptop** newEnd) {
    Laptop* pivot = end;
    Laptop* prev = nullptr, *cur = head, *tail = pivot;

    while (cur != pivot) {
        if (cur->laptop_id < pivot->laptop_id) {
            if ((*newHead) == nullptr) (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;
            Laptop* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if ((*newHead) == nullptr) (*newHead) = pivot;
    (*newEnd) = tail;
    return pivot;
}

Laptop* quickSortRecur(Laptop* head, Laptop* end) {
    if (!head || head == end) return head;

    Laptop* newHead = nullptr, *newEnd = nullptr;
    Laptop* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Laptop* temp = newHead;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = nullptr;
        newHead = quickSortRecur(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead;
}

void quickSortById(Laptop** headRef) {
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
}
Laptop* sortedMergeByBrand(Laptop* a, Laptop* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    Laptop* result = nullptr;
    if (a->merk <= b->merk) {
        result = a;
        result->next = sortedMergeByBrand(a->next, b);
    } else {
        result = b;
        result->next = sortedMergeByBrand(a, b->next);
    }
    return result;
}
void mergeSortByBrand(Laptop** headRef) {
    Laptop* head = *headRef;
    if (head == nullptr || head->next == nullptr) return;

    Laptop* a;
    Laptop* b;
    splitList(head, &a, &b);

    mergeSortByBrand(&a);
    mergeSortByBrand(&b);

    *headRef = sortedMergeByBrand(a, b);
}

void shellSortByPrice(Laptop** headRef) {
    int n = 0;
    Laptop* temp = *headRef;
    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Laptop* jNode = *headRef;
            for (int k = 0; k < i; k++) jNode = jNode->next;

            double currentHarga = jNode->harga;
            string currentMerk = jNode->merk, currentModel = jNode->model, currentSpesifikasi = jNode->spesifikasi;
            int currentStok = jNode->stok, currentLaptopId = jNode->laptop_id;

            int j;
            Laptop* gapNode;
            for (j = i; j >= gap; j -= gap) {
                gapNode = *headRef;
                for (int k = 0; k < j - gap; k++) gapNode = gapNode->next;

                if (gapNode->harga <= currentHarga) break;

                jNode->harga = gapNode->harga;
                jNode->merk = gapNode->merk;
                jNode->model = gapNode->model;
                jNode->spesifikasi = gapNode->spesifikasi;
                jNode->stok = gapNode->stok;
                jNode->laptop_id = gapNode->laptop_id;

                jNode = gapNode;
            }

            jNode->harga = currentHarga;
            jNode->merk = currentMerk;
            jNode->model = currentModel;
            jNode->spesifikasi = currentSpesifikasi;
            jNode->stok = currentStok;
            jNode->laptop_id = currentLaptopId;
        }
    }
}

void menuAdmin() {
    int pilihan, stok;
    double harga;
    string merk, model, spesifikasi;

    do {
        string menuAdminHeader = "Menu Admin";
        string menuAdmin[] = {"Lihat Laptop", "Tambah Laptop","Ubah Laptop", "Hapus Laptop", "Lihat Pesanan","History Pesanan", "Keluar"};
        int pilihanTambahLaptop, pilihanUbahLaptop, pilihanHapusLaptop;
        string model;
        string ubahLaptopHeader = "Ubah Laptop?";
        string tambahLaptopHeader = "Tambah Laptop?";
        string hapusLaptopHeader = "Hapus Laptop?";
        string tambahLaptop[] = {"Ya", "Kembali"};
        string ubahLaptop[] = {"Ya", "Kembali"};
        string hapusLaptop[] = {"Ya", "Kembali"};
        string metodeSort[] = {"Brand (Merge Sort)", "Harga (Shell Sort)", "Kembali"};
        pilihan = showmenu(7, menuAdmin, menuAdminHeader);
                string donePesananHeader = "Selesaikan Pesanan?";
                string donePesanan[] = {"Pesanan di Awal", "Pesanan di Akhir","Kembali"};
                int pilihanDonePesanan;
        switch (pilihan) {
            case 0:
                pilihan = showmenu(3, metodeSort, "Pilih cara pengurutan berdasarkan");
                if (pilihan == 0) {
                    mergeSortByBrand(&laptopHead);
                } else if (pilihan == 1) {
                    shellSortByPrice(&laptopHead);
                } else {
                    break;
                }
                displayLaptops();
                cout << "\n\nKlik untuk next\n";
                _getch();
                cls();
                break;
            case 1:
                pilihanTambahLaptop = showmenu(2, tambahLaptop, tambahLaptopHeader);
                cout << "Menambahkan Laptop baru:\n";
                if (pilihanTambahLaptop == 1){
                    cls();
                    break;
                }
                inputLaptop(merk, model, spesifikasi, stok, harga);
                addLaptop(merk, model, spesifikasi, stok, harga);
                cls();
                cout << "Laptop " <<merk<<" "<<model << " berhasil ditambahkan.\n";
                break;
            case 2:
                quickSortById(&laptopHead);
                pilihanUbahLaptop = showmenu(2, ubahLaptop, ubahLaptopHeader);
                if (pilihanUbahLaptop == 1){
                    cls();
                    break;
                }
                displayLaptops();
                if (laptopHead == nullptr) {
                    break;
                }
                int id;
                cout << "\nCari Laptop berdasarkan model: ";
                cin.clear();
                getline(cin, model);
                if(model.empty()){
                    cls();
                    cout << "Input tidak boleh kosong\n";
                    break;
                }
                searchLaptopsByModel(model);
                model.clear();
                
                cout << "\nMasukkan ID Laptop yang ingin diubah: ";
                cin >> id;cin.ignore();
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\nInput tidak valid\nMasukkan ID Laptop yang ingin diubah: ";
                    cin >> id;cin.ignore();
                }
                updateLaptop(id);
                _getch();
                cls();
                break;
            case 3:
                quickSortById(&laptopHead);
                pilihanHapusLaptop = showmenu(2, hapusLaptop, hapusLaptopHeader);
                if (pilihanHapusLaptop == 1){
                    cls();
                    break;
                }
                displayLaptops();
                if (laptopHead == nullptr) {
                    break;
                }
                cout << "\nCari Laptop berdasarkan model: ";
                cin.clear();
                getline(cin, model);
                if (model.empty()) {
                    cls();
                    cout << "Input tidak boleh kosong\n";
                    break;
                }
                searchLaptopsByModel(model);
                cout << "Masukkan ID Laptop yang ingin dihapus: ";
                cin >> id;cin.ignore();
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\nInput tidak valid\nMasukkan ID Laptop yang ingin dihapus: ";
                    cin >> id;cin.ignore();
                }
                deleteLaptop(id);
                _getch();
                cls();
                break;
            case 4:
                displayPesanan();
                if (pesananHead == nullptr) {
                    break;
                }
                pilihanDonePesanan = showmenu(3, donePesanan, donePesananHeader);
                if (pilihanDonePesanan == 0){
                    completePesananFIFO();
                } else if(pilihanDonePesanan == 1){
                    completePesananLIFO();
                }
                break;
            case 5:
                displayHistory();
                if (historyHead == nullptr) {
                    break;
                }
                cout << "\n\nKlik untuk next\n";
                _getch();
                cls();
                break;
            case 6:
                cout << "Telah Logout\n";
                break;
        }
    } while (pilihan != 6);
}
void menuPelanggan() {
    int pilihan, laptop_id, jumlah;
    string nama, alamat, telepon,model;

    int pilihanCariLaptop;

    do {
        string menuPelangganHeader = "Menu Pelanggan";
        string menuPelanggan[] = {"Lihat Laptop", "Beli Laptop", "Keluar"};
        string cariLaptopHeader = "Cari Laptop?";
        string cariLaptop[] = {"Ya", "Kembali"};
        string metodeSort[] = {"Brand", "Harga", "Kembali"};
        pilihan = showmenu(3, menuPelanggan, menuPelangganHeader);
        switch (pilihan) {
            case 0:
                pilihan = showmenu(3, metodeSort, "Urutkan Berdasarkan");
                if (pilihan == 0) {
                    mergeSortByBrand(&laptopHead);
                } else if (pilihan == 1) {
                    shellSortByPrice(&laptopHead);
                } else {
                    break;
                }
                displayLaptops();
                cout << "\n\nKlik untuk next\n";
                _getch();
                cls();
                if (laptopHead == nullptr) {
                    break;
                }
                break;
            case 1:
                displayLaptops();
                if (laptopHead == nullptr) {
                    break;
                }
                cout << "\nCari Laptop berdasarkan model: ";
                cin.clear();
                getline(cin, model);
                if (model.empty()) {
                    cls();
                    cout << "Input tidak boleh kosong\n";
                    break;
                }
                searchLaptopsByModel(model);
                inputPesanan();
                cout << "\n\nKlik untuk next\n";
                _getch();
                cls();
                break;
            case 2:
                cout << "Terima kasih telah mengunjungi toko kami!\n";
                break;
        }
    } while (pilihan != 2);
}
// ============================================MAIN================================================ //
int main() {
    int pilihan;

    addLaptop("Dell", "Inspiron 14", "Intel i5, 8GB RAM, 256GB SSD", 10, 7000000);
    addLaptop("HP", "Pavilion 15", "Intel i7, 16GB RAM, 512GB SSD", 5, 12000000);
    addLaptop("Asus", "VivoBook 14", "AMD Ryzen 5, 8GB RAM, 512GB SSD", 7, 8000000);
    addLaptop("Lenovo", "IdeaPad 5", "AMD Ryzen 7, 16GB RAM, 1TB SSD", 3, 15000000);
    addLaptop("Acer", "Aspire 5", "Intel i3, 4GB RAM, 128GB SSD", 8, 5000000);
    addLaptop("Apple", "MacBook Air", "Apple M1, 8GB RAM, 256GB SSD", 2, 15000000);
    addLaptop("MSI", "GF63 Thin", "Intel i5, 8GB RAM, 512GB SSD", 6, 9000000);
    addLaptop("Razer", "Blade 15", "Intel i7, 16GB RAM, 1TB SSD", 4, 20000000);
    do {
        cls();
        string menuMainHeader = "Selamat datang di Toko Laptop!";
        string menuMain[] = {"Menu Pelanggan", "Login Admin", "Keluar"};
        pilihan = showmenu(3, menuMain, menuMainHeader);
        switch (pilihan) {
            case 0:
                menuPelanggan();
                break;
            case 1:
                if (loginAdmin()) {
                    cls();
                    cout << "Login berhasil.\n";
                    menuAdmin();
                } else {
                    cls();
                    cout << "Username atau password salah.\n";
                    cout << "\n\nKlik untuk next\n";
                    _getch();
                }
                break;
            case 2:
                cout << "Terima kasih telah menggunakan sistem ini!\n";
                break;
        }
    } while (pilihan != 2);

    return 0;
}
