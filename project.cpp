#include <iostream>
using namespace std;

struct Produk {
    int id;
    string nama;
    string kategori;
    int stok;
    int harga;
};

struct kategori {
    string nama_kategori;
    struct Produk produk[100];

};

struct rak {
    string nama_rak;
    struct kategori kategori1[100];
};

int binarySearch(Produk arr[], int kiri, int kanan, int x) {
    if (kanan >= kiri) {
        int mid = kiri + (kanan - kiri) / 2;

        if (arr[mid].id == x)
            return mid;

        if (arr[mid].id > x)
            return binarySearch(arr, kiri, mid - 1, x);

        return binarySearch(arr, mid + 1, kanan, x);
    }

    return -1;
}

int main(){
    cout <<  "hello\n";
    rak rak1[100];
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
    int menu;
    int jum_produk, jum_kategori, jum_rak;

    cout << "== manajemen produk ==" << endl;
    cout << "menu : " << endl;
    cout << " 1. input data barang" << endl;
    cout << " 2. tampilkan data barang(sorted)" << endl;
    cout << " 3. cari produk berdasarkan id" << endl;
    cout << " 4. tampilan stok produk berdasarkan kategori" << endl;
    cout << " 5. ubah detail produk" << endl;
    cout << " 6. hapus produk(berdasarkan id)" << endl;
    cout << " 7. keluar" << endl;
    cout << "pilih menu :";
    cin >> menu;

    switch (menu){
        case 1: {
          
            cout << "=== Input Data Barang ===" << endl;
            cout << "berapa bnyak rak yang ingin  ditambahkan? ";
            cin >> jum_rak;
            for (int i = 0; i < jum_rak; i++){
                cout << "Masukkan nama rak: ";
                cin >> rak1[i].nama_rak;
                cout << "berapa bnyak kategori yang ingin  ditambahkan? ";
                cin >> jum_kategori;
                for (int j = 0; j < jum_kategori; j++){
                    cout << "Masukkan nama kategori: ";
                    cin >> rak1[i].kategori1[j].nama_kategori;
                    cout << "berapa banyak data yang ingin diinput? ";
                    cin >> jum_produk;
                    for (int k = 0; k < jum_produk; k++){
                        cout << "Masukkan data produk ke-" << i + 1 << ":" << endl;
                        cout << "ID: "; cin >> rak1[i].kategori1[j].produk[k].id;
                        cout << "Nama: "; cin >> rak1[i].kategori1[j].produk[k].nama;
                        cout << "Kategori: "; cin >> rak1[i].kategori1[j].produk[k].kategori;
                        cout << "Stok: "; cin >> rak1[i].kategori1[j].produk[k].stok;
                        cout << "Harga: "; cin >> rak1[i].kategori1[j].produk[k].harga;
                    }
                }
            }

            for (int i = 0; i < jum_produk - 1; i++){
                for (int j = 0; j < jum_produk - (i+1); j++ ){
                    for (int k = 0; k < jum_produk - (i+1); k++){
                        if (rak1[i].kategori1[j].produk[k].id > rak1[i].kategori1[j].produk[k+1].id){
                        Produk temp = rak1[i].kategori1[j].produk[k];
                        rak1[i].kategori1[j].produk[k] = rak1[i].kategori1[j].produk[k+1];
                        rak1[i].kategori1[j].produk[k+1] = temp;
                        }
                    }
                }

            }
            break;
        } case 2: {
            cout << "tampilkan data barang(sorted)" << endl;
            for (int i = 0; i < jum_rak; i++){
                cout << "Rak: " << rak1[i].nama_rak << endl;
                for (int j = 0; j < jum_kategori; j++){
                    cout << "Kategori: " << rak1[i].kategori1[j].nama_kategori << endl;
                    for (int k = 0; k < jum_produk; k++){
                        cout << "ID: " << rak1[i].kategori1[j].produk[k].id << endl;
                        cout << "Nama: " << rak1[i].kategori1[j].produk[k].nama << endl;
                        cout << "Kategori: " << rak1[i].kategori1[j].produk[k].kategori << endl;
                        cout << "Stok: " << rak1[i].kategori1[j].produk[k].stok << endl;
                        cout << "Harga: " << rak1[i].kategori1[j].produk[k].harga << endl;
                    }
                }
            }
            break;
        }case 3: {
            int id_cari;
            cout << "masukkan id produk yang ingin dicari: ";
            cin >> id_cari;
            binarySearch(rak1[0].kategori1[0].produk, 0, jum_produk - 1, id_cari);
            break;
        }case 4:{
            cout << "tampilan stok produk berdasarkan kategori" << endl;
            break;
        }case 5:{
            cout << "ubah detail produk" << endl;
            break;
        }case 6:{
            cout << "hapus produk(berdasarkan id)" << endl;
            break;
        }case 7:{
            cout << "keluar" << endl;
            break;
        }default:{
            cout << "pilihan tidak valid" << endl;
        }
    }
    
}