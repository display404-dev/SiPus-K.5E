#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

struct Anggota {
	string id;
	string nama;
	int umur;
};

int bacaAngka(const string& pesan) {
	string baris;
	int angka;
	char sisa;
	while (true) {
		cout << pesan;
		getline(cin, baris);
		stringstream input(baris);
		if (input >> angka && !(input >> sisa)) return angka;
		cout << "Masukkan angka yang valid.\n";
	}
}

int cariAnggota(const Anggota* data, int jumlah, const string& id) {
	for (int i = 0; i < jumlah; ++i)
		if (data[i].id == id) return i;
	return -1;
}

string buatIdAnggota(const Anggota* data, int jumlah) {
	for (int nomor = 1; nomor <= 999; ++nomor) {
		stringstream id;
		id << "AG-" << setw(3) << setfill('0') << nomor;
		if (cariAnggota(data, jumlah, id.str()) == -1) return id.str();
	}
	return "";
}

void tambahAnggota(Anggota*& data, int& jumlah, int& kapasitas) {
	string id = buatIdAnggota(data, jumlah);
	if (id.empty()) {
		cout << "Kapasitas ID anggota sudah penuh.\n";
		return;
	}

	Anggota anggota;
	anggota.id = id;
	cout << "ID anggota: " << anggota.id << '\n';
	cout << "Nama: ";
	getline(cin, anggota.nama);
	anggota.umur = bacaAngka("Umur: ");

	if (jumlah == kapasitas) {
		int kapasitasBaru = kapasitas + 1;
		Anggota* dataBaru = new Anggota[kapasitasBaru];
		for (int i = 0; i < jumlah; ++i) dataBaru[i] = data[i];
		delete[] data;
		data = dataBaru;
		kapasitas = kapasitasBaru;
	}
	data[jumlah] = anggota;
	++jumlah;
	cout << "Data anggota berhasil ditambahkan.\n";
}

void ubahAnggota(Anggota* data, int jumlah) {
	string id;
	cout << "Masukkan ID anggota yang akan diubah (AG-000): ";
	getline(cin, id);
	int indeks = cariAnggota(data, jumlah, id);
	if (indeks == -1) {
		cout << "Anggota tidak ditemukan.\n";
		return;
	}
	cout << "Nama baru: ";
	getline(cin, data[indeks].nama);
	data[indeks].umur = bacaAngka("Umur baru: ");
	cout << "Data anggota berhasil diubah.\n";
}

void tampilkanAnggota(const Anggota& anggota) {
	cout << "ID: " << anggota.id << " | Nama: " << anggota.nama
		 << " | Umur: " << anggota.umur << '\n';
}

void tampilkanSemua(const Anggota* data, int jumlah) {
	if (jumlah == 0) {
		cout << "Belum ada data anggota.\n";
		return;
	}
	cout << "\n=== DATA ANGGOTA ===\n";
	for (int i = 0; i < jumlah; ++i) tampilkanAnggota(data[i]);
}

int main() {
	int kapasitas = 4;
	Anggota* data = new Anggota[kapasitas];
	int jumlah = 0;
	while (true) {
		cout << "\n=== KELOLA ANGGOTA ===\n"
			 << "1. Tambah anggota\n"
			 << "2. Ubah anggota\n"
			 << "3. Tampilkan anggota\n"
			 << "0. Keluar\n";
		int pilihan = bacaAngka("Pilih menu: ");
		switch (pilihan) {
			case 1: tambahAnggota(data, jumlah, kapasitas); break;
			case 2: ubahAnggota(data, jumlah); break;
			case 3: tampilkanSemua(data, jumlah); break;
			case 0:
				delete[] data;
				cout << "Program selesai.\n";
				return 0;
			default: cout << "Pilihan tidak tersedia.\n";
		}
	}
}

