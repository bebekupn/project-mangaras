#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <limits>

using namespace std;

struct BPJS {
    string no_bpjs;
    string nik;
    string nama;
    string tempat_lahir;
    string tanggal_lahir;
    string alamat;
    string no_hp;
};

BPJS bpjs1[100];
int total_bpjs = 0;

void simpanFile(const string &namaFile) {
    ofstream fout(namaFile);
    if (!fout) {
        cout << "Error: Tidak bisa membuka file untuk disimpan!" << endl;
        return;
    }
    fout << total_bpjs << "\n";
    for (int i = 0; i < total_bpjs; i++) {
        BPJS *ptr = &bpjs1[i];
        fout << ptr->no_bpjs << "|" << ptr->nik << "|" << ptr->nama << "|"
             << ptr->tempat_lahir << "|" << ptr->tanggal_lahir << "|"
             << ptr->alamat << "|" << ptr->no_hp << "\n";
    }
    fout.close();
    cout << "Data berhasil disimpan ke file " << namaFile << endl;
}

void muatFile(const string &namaFile) {
    ifstream fin(namaFile);
    if (!fin) {
        cout << "File tidak ditemukan. Memulai dengan data kosong." << endl;
        return;
    }
    fin >> total_bpjs;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < total_bpjs; i++) {
        BPJS *ptr = &bpjs1[i];
        string line;
        getline(fin, line);
        
        size_t pos = 0;
        pos = line.find('|');
        ptr->no_bpjs = line.substr(0, pos);
        line.erase(0, pos + 1);
        
        pos = line.find('|');
        ptr->nik = line.substr(0, pos);
        line.erase(0, pos + 1);
        
        pos = line.find('|');
        ptr->nama = line.substr(0, pos);
        line.erase(0, pos + 1);
        
        pos = line.find('|');
        ptr->tempat_lahir = line.substr(0, pos);
        line.erase(0, pos + 1);
        
        pos = line.find('|');
        ptr->tanggal_lahir = line.substr(0, pos);
        line.erase(0, pos + 1);
        
        pos = line.find('|');
        ptr->alamat = line.substr(0, pos);
        line.erase(0, pos + 1);
        
        ptr->no_hp = line;
    }
    fin.close();
    cout << "Data berhasil dimuat dari file " << namaFile << endl;
}

void bubbleSort(BPJS arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].no_bpjs > arr[j + 1].no_bpjs) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int binarySearch(BPJS arr[], int kiri, int kanan, string x) {
    if (kanan >= kiri) {
        int mid = kiri + (kanan - kiri) / 2;
        if (arr[mid].no_bpjs == x) return mid;
        if (arr[mid].no_bpjs > x) return binarySearch(arr, kiri, mid - 1, x);
        return binarySearch(arr, mid + 1, kanan, x);
    }
    return -1;
}

bool cekNoBPJSSudahAda(string noBPJS) {
    for (int i = 0; i < total_bpjs; i++) {
        if (bpjs1[i].no_bpjs == noBPJS) {
            return true;
        }
    }
    return false;
}

int main(){
    string username, password;
    int salah = 0;

    // do{
    //     cout << "== login section ==" << endl;
    //     cout << "username: ";
    //     getline(cin, username);
    //     cout << "password: ";
    //     getline(cin, password);
    //     if (username == "admin" && password == "admin123"){
    //         cout << "Login successful!" << endl;
    //     } else {
    //         salah ++ ;
    //         cout << "Login failed. Invalid username or password." << endl;
    //     }   
    // }while (salah < 3 && salah != 0);
    // if (salah == 3){
    //     cout << "Too many failed login attempts. Access denied." << endl;
    //     return 0;
    // }

    cout << "Login successful!" << endl;
    muatFile("data_bpjs.txt");
    int menu;
     
    do {
        
            cout << "\n== Manajemen BPJS Rumah Sakit ==" << endl;
            cout << "MENU UTAMA" << endl;
            cout << " 1. Input data BPJS" << endl;
            cout << " 2. Tampilkan data BPJS (sorted)" << endl;
            cout << " 3. Cari BPJS berdasarkan id" << endl;
            cout << " 4. Ubah detail BPJS" << endl;
            cout << " 5. Simpan dan keluar" << endl;
            cout << "Pilih menu: ";
            if (!(cin >> menu)) {
                cout << "Error: Masukkan angka (1-5)!" << endl;
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                continue; 
            }
            if (menu < 1 || menu > 5) {
            cout << "Pilihan tidak valid! Coba lagi." << endl;
            continue; 
            }

        switch (menu){
            case 1: {  
                int jum_baru;
                cout << "\nBerapa banyak data? ";
                cin >> jum_baru;

                if (cin.fail() || jum_baru < 1 || (total_bpjs + jum_baru) > 100) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Input tidak valid atau kapasitas penuh (Maks 100)!" << endl;
                    break; 
                }

                    for (int j = 0; j < jum_baru; j++) {
                        int p = total_bpjs;
                        cout << "\nData ke-" << p + 1 << ":\n";
                        
                        string noBpjsBaru;
                        bool noBpjsValid = false;
                        while (!noBpjsValid) {
                            cout << "No BPJS: "; 
                            cin >> noBpjsBaru;
                            if (cekNoBPJSSudahAda(noBpjsBaru)) {
                                cout << "   ERROR: No BPJS '" << noBpjsBaru << "' sudah terdaftar! Coba nomor lain." << endl;
                            } else {
                                bpjs1[p].no_bpjs = noBpjsBaru;
                                noBpjsValid = true;
                            }
                        }
                        
                        cout << "Nama   : "; getline(cin >> ws, bpjs1[p].nama);
                        cout << "NIK    : "; cin >> bpjs1[p].nik;
                        cout << "tempat lahir :"; getline(cin >> ws, bpjs1[p].tempat_lahir);
                        cout << "tanggal lahir :"; getline(cin >> ws, bpjs1[p].tanggal_lahir); 
                        cout << "Alamat : "; getline(cin >> ws, bpjs1[p].alamat);
                        cout << "No HP  : "; cin >> bpjs1[p].no_hp;
                        total_bpjs++;
                    }
                    bubbleSort(bpjs1, total_bpjs);
                    cout << "\nData berhasil disimpan di memori!" << endl;
                    simpanFile("data_bpjs.txt");
                                                        
            break;
            }
            case 2: {
                    if(total_bpjs == 0){
                        cout << "data masih kosong" << endl;
                    }else{
                        cout << "\n===== DAFTAR PASIEN BPJS (SORTED) =====" << endl;
                        for (int i = 0; i < total_bpjs; i++) {
                            BPJS *ptr = &bpjs1[i];
                            cout << i + 1 << ". [" << ptr->no_bpjs << "] " << ptr->nama << " - " << ptr->alamat << endl;
                            cout << "   " << "tempat lahir :" << ptr->tempat_lahir << endl;
                            cout << "   " << "tanggal lahir :" << ptr->tanggal_lahir << endl;
                            cout << "   " << "no hp :" << ptr->no_hp << endl;
                        }
                    }

            break;
            } 
            case 3: {
                    if(total_bpjs == 0){
                        cout << "data masih kosong" << endl;
                    } else{
                        string cari;
                        cout << "Masukkan No BPJS yang dicari: ";
                        cin >> cari;
                        int hasil = binarySearch(bpjs1, 0, total_bpjs - 1, cari);
                        if (hasil != -1) {
                            cout << "Data Ditemukan! "<< endl;
                            BPJS *ptr = &bpjs1[hasil];
                            cout << hasil + 1 << ". [" << ptr->no_bpjs << "] " << ptr->nama << " - " << ptr->alamat << endl;
                            cout << "   " << "tempat lahir :" << ptr->tempat_lahir << endl;
                            cout << "   " << "tanggal lahir :" << ptr->tanggal_lahir << endl;
                            cout << "   " << "no hp :" << ptr->no_hp << endl;
                        } else {
                            cout << "Data tidak ditemukan." << endl;
                        }
                    }

            break;
            }
            case 4:{
            if (total_bpjs == 0) {
                cout << "Data masih kosong! Tidak ada yang bisa diubah." << endl;
            } else {
                string cari;
                cout << "\n===== UBAH DETAIL DATA BPJS =====" << endl;
                cout << "Masukkan No BPJS yang ingin diubah: ";
                cin >> cari;

                int hasil = binarySearch(bpjs1, 0, total_bpjs - 1, cari);

                if (hasil != -1) {
                    cout << "Data ditemukan! Silakan masukkan data baru." << endl;
                    BPJS *ptr = &bpjs1[hasil];

                    cout << "No BPJS       : " << ptr->no_bpjs << " (ID tidak dapat diubah)" << endl;
                    cout << "Nama Baru     : "; getline(cin >> ws, ptr->nama);
                    cout << "NIK Baru      : "; cin >> ptr->nik;
                    cout << "Tempat Lahir  : "; getline(cin >> ws, ptr->tempat_lahir);
                    cout << "Tanggal Lahir : "; getline(cin >> ws, ptr->tanggal_lahir);
                    cout << "Alamat Baru   : "; getline(cin >> ws, ptr->alamat);
                    cout << "No HP Baru    : "; cin >> ptr->no_hp;
                    cout << "\nData berhasil diperbarui!" << endl;

                    simpanFile("data_bpjs.txt");
                } else {
                    cout << "Data dengan No BPJS '" << cari << "' tidak ditemukan." << endl;
                }
            }
            break;
        }

            case 5:{
                cout << "Menyimpan data sebelum keluar..." << endl;
                simpanFile("data_bpjs.txt");
                cout << "Program akan berhenti, keluar dari program.\n" << endl;
                return 0;
            }
            default:{
                cout << "Pilihan tidak valid! Coba lagi." << endl;
            }
        } 
    }while (menu != 5);   
    
    return 0;
}