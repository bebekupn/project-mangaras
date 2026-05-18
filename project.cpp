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

void InputData() {
    system("cls");
    int jum_baru;
    cout << "\nBerapa banyak data? ";
    cin >> jum_baru;

    if (cin.fail() || jum_baru < 1 || (total_bpjs + jum_baru) > 100) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid atau kapasitas penuh (Maks 100)!" << endl;
        return;
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
}

void TampilkanData() {
    system("cls");
    if (total_bpjs == 0) {
        cout << "Data masih kosong" << endl;
    } else {
        cout << "\n===== DAFTAR PASIEN BPJS (SORTED) =====" << endl;
        for (int i = 0; i < total_bpjs; i++) {
            BPJS *ptr = &bpjs1[i];
            cout << i + 1 << ". [" << ptr->no_bpjs << "] " << ptr->nama << " - " << ptr->alamat << endl;
            cout << "   " << "tempat lahir :" << ptr->tempat_lahir << endl;
            cout << "   " << "tanggal lahir :" << ptr->tanggal_lahir << endl;
            cout << "   " << "no hp :" << ptr->no_hp << endl;
        }
    }
}

void CariBPJS() {
    system("cls");
    if (total_bpjs == 0) {
        cout << "Data masih kosong" << endl;
    } else {
        string cari;
        cout << "Masukkan No BPJS yang dicari: ";
        cin >> cari;
        int hasil = binarySearch(bpjs1, 0, total_bpjs - 1, cari);
        if (hasil != -1) {
            cout << "Data Ditemukan! " << endl;
            BPJS *ptr = &bpjs1[hasil];
            cout << hasil + 1 << ". [" << ptr->no_bpjs << "] " << ptr->nama << " - " << ptr->alamat << endl;
            cout << "   " << "tempat lahir :" << ptr->tempat_lahir << endl;
            cout << "   " << "tanggal lahir :" << ptr->tanggal_lahir << endl;
            cout << "   " << "no hp :" << ptr->no_hp << endl;
        } else {
            cout << "Data tidak ditemukan." << endl;
        }
    }
}

void UbahDetailBPJS() {
    system("cls");
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
}

// ============================================================
// FUNGSI BARU: Hapus Data Pasien BPJS
// ============================================================
void HapusData() {
    system("cls");
    if (total_bpjs == 0) {
        cout << "Data masih kosong! Tidak ada yang bisa dihapus." << endl;
        return;
    }

    string cari;
    cout << "\n===== HAPUS DATA PASIEN BPJS =====" << endl;
    cout << "Masukkan No BPJS yang ingin dihapus: ";
    cin >> cari;

    // Cari data menggunakan binary search (array sudah terurut)
    int hasil = binarySearch(bpjs1, 0, total_bpjs - 1, cari);

    if (hasil == -1) {
        cout << "Data dengan No BPJS '" << cari << "' tidak ditemukan." << endl;
        return;
    }

    // Tampilkan data yang akan dihapus
    BPJS *ptr = &bpjs1[hasil];
    cout << "\nData yang akan dihapus:" << endl;
    cout << "  No BPJS      : " << ptr->no_bpjs << endl;
    cout << "  Nama         : " << ptr->nama << endl;
    cout << "  NIK          : " << ptr->nik << endl;
    cout << "  Tempat Lahir : " << ptr->tempat_lahir << endl;
    cout << "  Tanggal Lahir: " << ptr->tanggal_lahir << endl;
    cout << "  Alamat       : " << ptr->alamat << endl;
    cout << "  No HP        : " << ptr->no_hp << endl;

    // Konfirmasi penghapusan
    char konfirmasi;
    cout << "\nApakah Anda yakin ingin menghapus data ini? (y/n): ";
    cin >> konfirmasi;

    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        cout << "Penghapusan dibatalkan." << endl;
        return;
    }

    // Geser semua elemen setelah index 'hasil' ke kiri satu posisi
    // Ini menimpa elemen yang dihapus dan menutup celah di array
    for (int i = hasil; i < total_bpjs - 1; i++) {
        bpjs1[i] = bpjs1[i + 1];
    }

    // Kurangi counter dan kosongkan slot terakhir yang sudah tidak terpakai
    total_bpjs--;
    bpjs1[total_bpjs] = BPJS(); // reset slot terakhir ke nilai default

    cout << "\nData dengan No BPJS '" << cari << "' berhasil dihapus!" << endl;
    cout << "Total data sekarang: " << total_bpjs << " pasien." << endl;

    // Simpan perubahan ke file
    simpanFile("data_bpjs.txt");
}

int main() {
    cout << "Login successful!" << endl;
    muatFile("data_bpjs.txt");
    int menu;

    do {
        system("pause");
        system("cls");
        cout << "\n== Manajemen BPJS Rumah Sakit ==" << endl;
        cout << "MENU UTAMA" << endl;
        cout << " 1. Input data BPJS" << endl;
        cout << " 2. Tampilkan data BPJS (sorted)" << endl;
        cout << " 3. Cari BPJS berdasarkan id" << endl;
        cout << " 4. Ubah detail BPJS" << endl;
        cout << " 5. Hapus data BPJS" << endl;       // <-- menu baru
        cout << " 6. Simpan dan keluar" << endl;      // <-- digeser dari 5 ke 6
        cout << "Pilih menu: ";
        if (!(cin >> menu)) {
            cout << "Error: Masukkan angka (1-6)!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (menu) {
            case 1: {
                InputData();
                break;
            }
            case 2: {
                TampilkanData();
                break;
            }
            case 3: {
                CariBPJS();
                break;
            }
            case 4: {
                UbahDetailBPJS();
                break;
            }
            case 5: {
                HapusData();        // <-- fungsi hapus dipanggil di sini
                break;
            }
            case 6: {
                system("cls");
                cout << "Menyimpan data sebelum keluar..." << endl;
                simpanFile("data_bpjs.txt");
                cout << "Program akan berhenti, keluar dari program.\n" << endl;
                return 0;
            }
            default: {
                cout << "Pilihan tidak valid! Coba lagi." << endl;
            }
        }
    } while (menu != 6);

    return 0;
}