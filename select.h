#ifndef UIUX_H
#define UIUX_H

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

void warna(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y){
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int showmenu(int jumlah_opsi, string opsi[], string opsi_header){
    int pilih = 0;
    const int putih = 15;
    const int highlightkuning = 14;
    bool chosen = false;
        gotoxy(10, 5);
    cout << opsi_header;

    while (!chosen){

        for (int i = 0; i < jumlah_opsi; i++){
            gotoxy(10, 7 + i);

            if (i == pilih)
                warna(highlightkuning);
            else
                warna(putih);

            cout << (i + 1) << ". " << opsi[i];
        }

        int key = _getch(); 

        switch (key){
        case 72: // ascii arrow up
            if (pilih > 0)
                pilih--;
            break;
        case 80: // ascii arrow down
            if (pilih < jumlah_opsi - 1)
                pilih++;
            break;
        case 13: // ascii enter
            chosen = true;
            break;
        }
    }

    warna(putih);
    system("cls");
    return pilih;
}

#endif