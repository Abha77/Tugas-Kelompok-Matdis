#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

struct data_akun{
    string NIM;
    string nama;
    int saldo;
    string PIN;
};

const int MAKS = 10;
int n;
data_akun user[MAKS];

void tampilan1(int *p);
void update_top_up(int *saldo, int nominal);
void transfer(int i, string NIM, int nominal);
int read_data();
void write_data();
void menu(int i);
void login();
void sign_up();

string enkripsi(string plaintext){
    int panjang_pesan = plaintext.length();
    string chiphertext = "";
    int shift = 13;
    char text;
    for(int i = 0; i < panjang_pesan; i++){
        text = plaintext[i];
        if(isalpha(text)){
            if(isupper(text)){
                text = (text - 'A' + shift) % 26 + 'A';
                chiphertext += text;
            }else{
                text = (text - 'a' + shift) % 26 + 'a';
                chiphertext += text;
            }
        }else if(isdigit(text)){
            text = (text - '0' + shift) %10 + '0';
            chiphertext += text;
        }else if(text == ' '){
            chiphertext += text;
        }
    }
    return chiphertext;
}

string dekripsi(string ciphertext){
    int panjang_pesan = ciphertext.length();
    string plaintext = "";
    int shift = 13;
    char text;
    for(int i = 0; i < panjang_pesan; i++){
        text = ciphertext[i];
        if(isalpha(text)){
            if(isupper(text)){
                text = (text - 'A' + 26 - shift) % 26 + 'A';
                plaintext += text;
            }else{
                text = (text - 'a' + 26 - shift) % 26 + 'a';
                plaintext += text;
            }
        }else if(isdigit(text)){
            text = (((text - '0') - (shift % 10)) + 10) % 10 + '0';
            plaintext += text;
        }else if(text == ' '){
            plaintext += text;
        }
    }
    return plaintext;
}

int main(){
    lanjut:
    system("cls");
    int pilihan = 0;
    tampilan1(&pilihan);
    switch(pilihan){
        case 1:
            login();
            goto lanjut;
        case 2:
            sign_up();
            goto lanjut;
    }

}

void tampilan1(int *p){
    system("cls");
    int pilihan;
    cout << "==============================" << endl;
    cout << "|      QuantumDigital        |" << endl;
    cout << "==============================" << endl;
    cout << "| 1. Login                   |" << endl;
    cout << "| 2. SignUp                  |" << endl;
    cout << "| 3. Exit                    |" << endl;
    cout << "==============================" << endl;
    cout << " \nMasukan Pilihan Anda : ";
    cin >> pilihan;
    *p = pilihan;
}

void update_top_up(int *saldo, int nominal){
    *saldo += nominal;
}

void transfer(int i, string NIM, int nominal){
    int turn = 0;
    for(int j = 0; j < MAKS; j++){
        if(NIM == user[j].NIM){
            user[j].saldo += nominal;
            user[i].saldo -= nominal;
            turn++;
            break;
        }
    }
    if(turn == 0){
        cout << "NIM tidak ditemukan, transfer anda gagal !!!" << endl;
    }else{
        cout << "Transfer telah berhasil dilakukan" << endl;
    }
}

int read_data(){
    string NIM, nama, saldo, PIN;
    ifstream baca;

    baca.open("D:\\database.txt");
    int i = 0;
    while (!baca.eof()){
        getline(baca, NIM);
        getline(baca, nama);
        getline(baca, saldo); saldo = dekripsi(saldo); int int_saldo = atoi(saldo.c_str());
        getline(baca, PIN);

        user[i].NIM = dekripsi(NIM);
        user[i].nama = dekripsi(nama);
        user[i].saldo = int_saldo;
        user[i].PIN = dekripsi(PIN);

        if(NIM.empty()){
            break;
        }
        i++;
    }
    baca.close();
    n = i;
    return n;
}

void write_data(){
    ofstream tulis;
    tulis.open("D:\\database.txt");

    int i = 0;
    while(user[i].NIM != "\0"){
        tulis << enkripsi(user[i].NIM) << endl;
        tulis << enkripsi(user[i].nama) << endl;
        tulis << enkripsi(to_string(user[i].saldo)) << endl;
        tulis << enkripsi(user[i].PIN) << endl;
        i++;
    }
    tulis.close();
}

void menu(int i){
    ulang:
    read_data();
    system ("cls");
    cout << "==============================" << endl;
    cout << "|      QuantumDigital        |" << endl;
    cout << "==============================" << endl;
    cout << "| 1. TopUp                   |" << endl;
    cout << "| 2. Transfer                |" << endl;
    cout << "| 3. Exit                    |" << endl; 
    cout << "==============================" << endl;
    cout << "Selamat Datang" << endl;
    cout << "Saldo Anda : " << user[i].saldo << endl;
    cout << "\nMasukan Pilihan anda : ";
    int pilihan, nominal;
    string NIM;
    cin >> pilihan;
    switch (pilihan){
        case 1 :
            cout << "\n============ TopUp ============" << endl;
            cout << "Masukkan Nominal : "; cin >> nominal;
            cin.ignore();
            update_top_up(&user[i].saldo, nominal);
            write_data();
            cout << "\nSaldo telah berhasil ditambahkan" << endl;
            cin.get();
            goto ulang;
        case 2 :
            cout << "\n=========== Transfer ===========" << endl;
            cout << "Masukkan NIM Tujuan : "; cin >> NIM;
            cout << "Masukkan Nominal    : "; cin >> nominal;
            cin.ignore();
            transfer(i, NIM, nominal);
            write_data();
            cin.get();
            goto ulang;
        case 3:
            break;
    }
}

void login(){
    read_data();
    system ("cls");
    string NIM, PIN;
    int turn = 0;
    cout << "==============================" << endl;
    cout << "|      QuantumDigital        |" << endl;
    cout << "|          Login             |" << endl;
    cout << "==============================" << endl;
    cout << "Masukkan NIM : "; cin >> NIM;
    cout << "Masukkan PIN : "; cin >> PIN;
    cin.ignore();
    for(int i = 0; i < MAKS; i++){
        if(NIM == user[i].NIM){
            if(PIN == user[i].PIN){
                cout << "\nLogin Berhasil";
                cin.get();
                menu(i);
                cin.get();
                turn++;
                break;
            }else{
                cout << "\nPIN yang Anda masukan salah!" << endl;
                cout << "Silahkan Login ulang!" << endl;
                cin.get();
                turn++;
                break;
            }
        }
    }
    if(turn == 0){
        cout << "\nNIM tidak berhasil ditemukan !!!\nSilahkan Login Ulang !" << endl;
    }
}

void sign_up(){
    read_data();
    system ("cls");
    cout << "==============================" << endl;
    cout << "|      QuantumDigital        |" << endl;
    cout << "|          SignUp            |" << endl;
    cout << "==============================" << endl;
    cout << "Masukkan NIM  : "; cin >> user[n].NIM;
    cout << "Masukkan Nama : "; cin.ignore(); getline(cin, user[n].nama);
    cout << "Buat PIN      : "; cin >> user[n].PIN; cout << endl;
    cin.ignore();
    cout << "\nSelamat Akun Anda Berhasil dibuat" << endl;
    user[n].saldo = 0;
    write_data();
    cin.get();
}
