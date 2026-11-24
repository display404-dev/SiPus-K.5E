#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>

using namespace std;

struct Buku {
	string id;
	string judul;
	string penulis;
	int tahun;
};

const int KAPASITAS_BUKU = 4;

int bacaAngka(const string& pesan) {
	string masukan;
	while (true) {
		cout << pesan;
		if (!getline(cin, masukan)) throw runtime_error("Input berakhir.");
		stringstream ss(masukan);
		int angka;
		char sisa;
		if (ss >> angka && !(ss >> sisa)) return angka;
		cout << "Masukkan angka yang valid.\n";
	}
}

string bacaTeks(const string& pesan) {
	string teks;
	while (true) {
		cout << pesan;
		if (!getline(cin, teks)) throw runtime_error("Input berakhir.");
		if (!teks.empty()) return teks;
		cout << "Data tidak boleh kosong.\n";
	}
}

int cariBuku(const Buku buku[], int jumlahBuku, const string& id) {
	for (int i = 0; i < jumlahBuku; ++i)
		if (buku[i].id == id) return i;
	return -1;
}

void tambahKapasitas(Buku*& buku, int jumlahBuku, int& kapasitas) {
	int kapasitasBaru = kapasitas * 2;
	Buku* bukuBaru = new Buku[kapasitasBaru];
	for (int i = 0; i < jumlahBuku; ++i) bukuBaru[i] = buku[i];
	delete[] buku;
	buku = bukuBaru;
	kapasitas = kapasitasBaru;
}

string buatId(int nomor) {
	stringstream ss;
	ss << "BK-" << setfill('0') << setw(3) << nomor;
	return ss.str();
}

void tampilkan(const Buku buku[], int jumlahBuku) {
	if (jumlahBuku == 0) {
		cout << "Belum ada data buku.\n";
		return;
	}
	cout << '\n' << left << setw(8) << "ID" << setw(30) << "Judul"
		 << setw(25) << "Penulis" << setw(8) << "Tahun" << '\n'
		 << string(71, '-') << '\n';
	for (int i = 0; i < jumlahBuku; ++i) {
		const Buku& item = buku[i];
		cout << left << setw(8) << item.id << setw(30) << item.judul.substr(0, 29)
			 << setw(25) << item.penulis.substr(0, 24) << setw(8) << item.tahun << '\n';
	}
}

int main() {
	Buku* buku = nullptr;
	try {
		int kapasitas = KAPASITAS_BUKU;
		buku = new Buku[kapasitas];
		int jumlahBuku = 0;
		int idBerikutnya = 1;
		int pilihan;
		do {
			cout << "\n=== Kelola Data Buku ===\n"
				 << "1. Tambah buku\n2. Ubah buku\n3. Hapus buku\n"
				 << "4. Tampilkan buku\n0. Keluar\n";
			pilihan = bacaAngka("Pilih menu: ");

			switch (pilihan) {
			case 1: {
				if (jumlahBuku >= kapasitas)
					tambahKapasitas(buku, jumlahBuku, kapasitas);
				Buku baru{buatId(idBerikutnya), bacaTeks("Judul buku: "),
					bacaTeks("Nama penulis: "), bacaAngka("Tahun terbit: ")};
				buku[jumlahBuku++] = baru;
				++idBerikutnya;
				cout << "Buku berhasil ditambahkan dengan ID " << baru.id << ".\n";
				break;
			}
			case 2: {
				int indeks = cariBuku(buku, jumlahBuku,
					bacaTeks("Masukkan ID buku yang ingin diubah (BK-001): "));
				if (indeks < 0) {
					cout << "Buku dengan ID tersebut tidak ditemukan.\n";
					break;
				}
				buku[indeks].judul = bacaTeks("Judul baru: ");
				buku[indeks].penulis = bacaTeks("Nama penulis baru: ");
				buku[indeks].tahun = bacaAngka("Tahun terbit baru: ");
				cout << "Data buku berhasil diubah.\n";
				break;
			}
			case 3: {
				int indeks = cariBuku(buku, jumlahBuku,
					bacaTeks("Masukkan ID buku yang ingin dihapus (Contoh : BK-001): "));
				if (indeks < 0) {
					cout << "Buku dengan ID tersebut tidak ditemukan.\n";
					break;
				}
				for (int i = indeks; i < jumlahBuku - 1; ++i)
					buku[i] = buku[i + 1];
				--jumlahBuku;
				cout << "Buku berhasil dihapus.\n";
				break;
			}
			case 4:
				tampilkan(buku, jumlahBuku);
				break;
			case 0:
				cout << "Program selesai.\n";
				break;
			default:
				cout << "Pilihan menu tidak tersedia.\n";
			}
		} while (pilihan != 0);
	} catch (const exception& e) {
		delete[] buku;
		cerr << "Terjadi kesalahan: " << e.what() << '\n';
		return 1;
	}
	delete[] buku;
	return 0;
}