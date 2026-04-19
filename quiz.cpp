#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

namespace tokoBuku {
    struct Buku {
        int id;
        string judul;
        string kategori;
        double harga;
        int stok;
    };

    struct Transaksi{
        int idTransaksi;
        int idBuku;
        int jumlah;
        double totalHarga;
        string tanggal;
    };

    // file handling untuk menyimpan transaksi penjualan dan data buku
    void simpanTransaksi(const Transaksi transaksi) {
        ofstream outFile("dataTransaksi.txt", ios::app); // Buka file dalam mode append
        if (outFile.is_open()) {
            outFile << transaksi.idTransaksi << ","
                    << transaksi.idBuku << ","
                    << transaksi.jumlah << ","
                    << transaksi.totalHarga << ","
                    << transaksi.tanggal << "\n";
            outFile.close();
            cout << "Transaksi berhasil disimpan ke file!\n";
        }
    }
    
    void tampilkanTransaksi() {
        ifstream inFile("dataTransaksi.txt");
        if (inFile.is_open()) {
            string line;
            cout << "========================== DAFTAR TRANSAKSI ==========================\n";
            cout << left << setw(15) << "ID Transaksi" << setw(10) << "ID Buku" 
                 << setw(10) << "Jumlah" << right << setw(15) << "Total Harga" << right << setw(20) << "Tanggal" << "\n";
            cout << string(70, '-') << "\n";

            while (getline(inFile, line)) {
                if (line.empty()) continue;

                stringstream ss(line);
                string idTransaksiStr, idBukuStr, jumlahStr, totalHargaStr, tanggalStr;

                if (!getline(ss, idTransaksiStr, ',')) continue;
                if (!getline(ss, idBukuStr, ',')) continue;
                if (!getline(ss, jumlahStr, ',')) continue;
                if (!getline(ss, totalHargaStr, ',')) continue;
                if (!getline(ss, tanggalStr, ',')) continue;

                try {
                    int idTransaksi = stoi(idTransaksiStr);
                    int idBuku = stoi(idBukuStr);
                    int jumlah = stoi(jumlahStr);
                    double totalHarga = stod(totalHargaStr);

                    cout << left << setw(15) << idTransaksi 
                         << setw(10) << idBuku 
                         << setw(10) << jumlah 
                         << right << setw(15) << fixed << setprecision(0) << totalHarga 
                         << setw(20) << tanggalStr 
                         << "\n";
                } catch (...) {
                    // Lewati baris yang tidak valid
                    continue;
                }
            }
            inFile.close();
        } else {
            cout << "Tidak ada data transaksi yang tersedia.\n";
        }
    }

    // Simpan ke array buku ke file dalam format teks 
    void saveToFile(const Buku daftar[], int jumlah) {
        ofstream outFile("dataBuku.txt"); 
        if (outFile.is_open()) {
            for (int i = 0; i < jumlah; i++) {
                // Menggunakan delimiter '|' agar judul yang pakai spasi tidak berantakan
                outFile << daftar[i].id << "|" 
                        << daftar[i].judul << "|" 
                        << daftar[i].kategori << "|" 
                        << daftar[i].harga << "|" 
                        << daftar[i].stok << "\n";
            }
            outFile.close();
            cout << "Data berhasil disimpan ke file!\n";
        }
    }

    // Baca dari file dan kembalikan jumlah buku yang terbaca
    int loadFromFile(Buku daftar[], int kapasitas) {
        ifstream inFile("dataBuku.txt");
        int i = 0;
        if (inFile.is_open()) {
            string line;
            // Format file: id|judul|kategori|harga|stok
            while (i < kapasitas && getline(inFile, line)) {
                if (line.empty()) {
                    continue;
                }

                stringstream ss(line);
                string idStr;
                string hargaStr;
                string stokStr;

                if (!getline(ss, idStr, '|')) continue;
                if (!getline(ss, daftar[i].judul, '|')) continue;
                if (!getline(ss, daftar[i].kategori, '|')) continue;
                if (!getline(ss, hargaStr, '|')) continue;
                if (!getline(ss, stokStr, '|')) continue;

                try {
                    daftar[i].id = stoi(idStr);
                    daftar[i].harga = stod(hargaStr);
                    daftar[i].stok = stoi(stokStr);
                    i++;
                } catch (...) {
                    // Lewati baris yang tidak valid.
                    continue;
                }
            }
            inFile.close();
        }
        return i; // Mengembalikan berapa banyak buku yang berhasil dimuat
    }


    //=========================================================
    // Template Function, Inline Function, Overloading Function, Default Argument
   
    // TEMPLATE FUNCTION untuk menghitung total harga berdasarkan jumlah dan harga satuan
    template <typename T, typename U>
    auto hitungTotal(T qty, U harga) -> decltype(qty * harga) {
        return qty * harga;
    }
 
    // inline function untuk konversi harga ke USD
    inline double keUSD(double hargaIDR, double kurs = 17000.0) {
        return hargaIDR / kurs;
    }

    // Menampilkan pesan default
    void cetakStatus(string msg = "Operasi Berhasil") {
        cout << "[STATUS]: " << msg << endl;
    }

    // Menampilkan status dengan kode angka (Overloading)
    void cetakStatus(int code) {
        cout << "[STATUS CODE]: " << code << (code == 200 ? " (OK)" : " (Error)") << endl;
    }

    // ========================================================

     // fungsi menampilkan daftar buku
    void tampilkanDaftarBuku(const Buku daftar[], int jumlah) {
        if (jumlah == 0) {
            cout << "\n[!] Tidak ada data buku di dalam file atau memori.\n";
            return;
        }

        cout << "========================== DAFTAR BUKU TOKO ==========================\n";
           cout << left << setw(5) << "ID" << setw(30) << "Judul" << setw(15) << "Kategori"
               << right << setw(12) << "Harga" << setw(8) << "Stok" << "\n";
           cout << string(70, '-') << "\n";

        for (int i = 0; i < jumlah; i++) {
            cout << left << setw(5) << daftar[i].id
                  << setw(30) << daftar[i].judul
                 << setw(15) << daftar[i].kategori
                  << right << setw(12) << fixed << setprecision(0) << daftar[i].harga
                  << setw(8) << daftar[i].stok << "\n";
        }
    }

    // fungsi untuk menambahkan buku baru ke dalam daftar
    void tambahBuku(Buku daftar[], int &jumlah, int kapasitas) {
        if (jumlah >= kapasitas) {
            cout << "Kapasitas buku sudah penuh. Tidak bisa menambah buku baru.\n";
            return;
        }
        Buku baru;
        cout << "Masukkan ID buku: "; cin >> baru.id;
        cin.ignore(); // Bersihkan newline dari input sebelumnya
        cout << "Masukkan judul buku: "; getline(cin, baru.judul);
        cout << "Masukkan kategori buku: "; getline(cin, baru.kategori);
        cout << "Masukkan harga buku: "; cin >> baru.harga;
        cout << "Masukkan stok buku: "; cin >> baru.stok;
        cin.ignore(); // Bersihkan newline dari input sebelumnya

        daftar[jumlah] = baru;
        jumlah++;
        cout << "Buku berhasil ditambahkan!\n";
    }

    // Menambahkan transaksi penjualan
    void tambahTransaksi(Buku daftar[], int jumlahBuku) {
        if (jumlahBuku == 0) {
            cout << "Data buku kosong!\n";
            return;
        }

        Transaksi t;
        cout << "Masukkan ID Transaksi: "; cin >> t.idTransaksi;
        cout << "Masukkan ID Buku: "; cin >> t.idBuku;

        int indeksBuku = -1;
        for (int i = 0; i < jumlahBuku; i++) {
            if (daftar[i].id == t.idBuku) {
                indeksBuku = i;
                break;
            }
        }

        if (indeksBuku == -1) {
            cetakStatus(404); // Menggunakan Overloading
            return;
        }

        cout << "Buku ditemukan: " << daftar[indeksBuku].judul << "\n";
        cout << "Jumlah beli: "; cin >> t.jumlah;
        
        cout << "Masukkan Tanggal (Format: DD-MM-YYYY): ";
        cin.ignore(); // Membersihkan buffer agar getline tidak terlewati
        getline(cin, t.tanggal);

        if (t.jumlah > daftar[indeksBuku].stok) {
            cout << "Error: Stok tidak mencukupi!\n";
            return;
        }

        // Menggunakan Template Function
        t.totalHarga = hitungTotal(t.jumlah, daftar[indeksBuku].harga);
        daftar[indeksBuku].stok -= t.jumlah;

        simpanTransaksi(t);
        cout << "Total Bayar: Rp" << fixed << setprecision(0) << t.totalHarga << "\n";
        cetakStatus(); // Menggunakan Default Argument
    }

    // Menghitung total pendapatan
    void hitungPendapatan() {
        ifstream inFile("dataTransaksi.txt");
        double totalPendapatan = 0;
        string line;

        if (inFile.is_open()) {
            while (getline(inFile, line)) {
                stringstream ss(line);
                string temp;
                for(int i=0; i<4; i++) {
                    getline(ss, temp, ',');
                    if(i == 3 && !temp.empty()) totalPendapatan += stod(temp);
                }
            }
            inFile.close();
            cout << "\nTotal Seluruh Pendapatan: Rp" << fixed << setprecision(0) << totalPendapatan << "\n";
        }
    }

    // hitung pendapatan harian berdasarkan tanggal yang dimasukkan user
    void hitungPendapatanHarian() {
        ifstream inFile("dataTransaksi.txt");
        string tglCari;
        double totalHarian = 0;
        string line;

        cout << "Masukkan tanggal yang ingin dicari (DD-MM-YYYY): ";
        cin >> tglCari;

        if (inFile.is_open()) {
            while (getline(inFile, line)) {
                if (line.empty()) continue;

                stringstream ss(line);
                string idT, idB, jml, total, tgl;

                // Memecah CSV: idT, idB, jml, total, tgl
                getline(ss, idT, ',');
                getline(ss, idB, ',');
                getline(ss, jml, ',');
                getline(ss, total, ',');
                getline(ss, tgl, ','); // Kolom ke-5 adalah tanggal

                // Jika tanggal di file sama dengan tanggal yang dicari
                if (tgl == tglCari) {
                    try {
                        totalHarian += stod(total);
                    } catch (...) { continue; }
                }
            }
            inFile.close();
            
            cout << "\n======================================" << endl;
            cout << "Total Pendapatan Tanggal " << tglCari << " : Rp" 
                << fixed << setprecision(0) << totalHarian << endl;
            cout << "======================================" << endl;
        } else {
            cout << "Gagal membuka file transaksi.\n";
        }
    }

    // Konversi Harga (Misal ke USD)
    // Menambahkan Default Argument pada parameter kurs
    void konversiHarga(const Buku daftar[], int jumlah, double kurs = 17000.0) {
        cout << "\n--- Daftar Harga dalam USD ($) ---\n";
        for (int i = 0; i < jumlah; i++) {
            // Memanggil Inline Function
            double hargaUSD = keUSD(daftar[i].harga, kurs);
            cout << daftar[i].judul << " : $" << fixed << setprecision(2) << hargaUSD << "\n";
        }
    }

}

int main() {
    int kapasitas = 100;
    // Membuat array dinamis
    tokoBuku::Buku* daftarBuku = new tokoBuku::Buku[kapasitas];

    // Load data dari file ke dalam array
    int jumlahSekarang = tokoBuku::loadFromFile(daftarBuku, kapasitas);
    int pilihan;

    do {
    
        cout << "===== Menu Toko Buku =====\n";
        cout << "1. Tampilkan Daftar Buku\n";
        cout << "2. Tambah Buku\n";
        cout << "3. Tambah Transaksi\n";
        cout << "4. Tampilkan Daftar Transaksi\n";
        cout << "5. Hitung Pendapatan Total\n";
        cout << "6. Hitung Pendapatan Harian\n";
        cout << "7. Konversi Harga ke USD\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tokoBuku::tampilkanDaftarBuku(daftarBuku, jumlahSekarang);
                break;
            case 2:
                tokoBuku::tambahBuku(daftarBuku, jumlahSekarang, kapasitas);
                break;
            case 3: 
                tokoBuku::tambahTransaksi(daftarBuku, jumlahSekarang);
                break;
            case 4:
                tokoBuku::tampilkanTransaksi();
                break;
            case 5:
                tokoBuku::hitungPendapatan();
                break;
            case 6:
                tokoBuku::hitungPendapatanHarian();
                break;
            case 7:
                tokoBuku::konversiHarga(daftarBuku, jumlahSekarang);
                break;
            case 0:
                cout << "Terima kasih telah menggunakan program ini!\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 0);
     
    // STEP 3: Simpan kembali ke file (jika ada perubahan)
    tokoBuku::saveToFile(daftarBuku, jumlahSekarang);

    return 0;
}