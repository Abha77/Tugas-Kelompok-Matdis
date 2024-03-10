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

int read_data(){
    string NIM, nama, saldo, PIN;
    ifstream baca;

    baca.open("D:\\database.txt");
    int i = 0;
    while (!baca.eof()){
        getline(baca, NIM);
        getline(baca, nama);
        getline(baca, saldo); int int_saldo = atoi(saldo.c_str());
        getline(baca, PIN);

        user[i].NIM = NIM;
        user[i].nama = nama;
        user[i].saldo = int_saldo;
        user[i].PIN = PIN;

        if(NIM.empty()){
            break;
        }

       cout << user[i].NIM << endl;
       cout << user[i].nama << endl;
       cout << user[i].saldo << endl;
       cout << user[i].PIN << endl;
        
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
        tulis << user[i].NIM << endl;
        tulis << user[i].nama << endl;
        tulis << user[i].saldo << endl;
        tulis << user[i].PIN << endl;
        i++;
    }
    tulis.close();
}

void menu(int i){
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
            update_top_up(&user[i].saldo, nominal);
            write_data();
            cout << "\nSaldo telah berhasil ditambahkan" << endl;
            break;
        case 2 :
            cout << "\n=========== Transfer ===========" << endl;
            cout << "Masukkan NIM Tujuan : "; cin >> NIM;
            cout << "Masukkan Nominal : "; cin >> nominal;
            write_data();
            break;
        case 3:
            break;
    }
    cin.get();
}

void login(){
    read_data();
    system ("cls");
    string NIM, PIN;
    cout << "==============================" << endl;
    cout << "|      QuantumDigital        |" << endl;
    cout << "|          Login             |" << endl;
    cout << "==============================" << endl;
    cout << "Masukkan NIM : "; cin >> NIM;
    cout << "Masukkan PIN : "; cin >> PIN;
    for(int i = 0; i < MAKS; i++){
        if(NIM == user[i].NIM){
            if(PIN == user[i].PIN){
                cout << "Login Berhasil";
                cin.get();
                menu(i);
                break;
            }else{
                cout << "PIN yang Anda masukan salah!" << endl;
                cout << "Silahkan Login ulang!" << endl;
                break;
            }
        }else{
            cout << "NIM yang Anda masukan salah!" << endl;
            cout << "Silahkan Login ulang!" << endl;
            break;
        }
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
    cout << "\nSelamat Akun Anda Berhasil dibuat" << endl;
    user[n].saldo = 0;
    write_data();
    cin.get();
}

int main(){
    lanjut:
    system("cls");
    int pilihan = 0;
    tampilan1(&pilihan);
    switch(pilihan){
        case 1:
            login();
            cin.get();
            goto lanjut;
        case 2:
            sign_up();
            cin.get();
            goto lanjut;
    }

}