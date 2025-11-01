#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Node
{
    string nama;
    int harga;
    int jumlah;
    Node *next;
    Node(const string &n, int h, int j) : nama(n), harga(h), jumlah(j), next(nullptr) {}
};

// Tambah Di belakang
void addLast(Node *&head, const string &nama, int harga, int jumlah)
{
    Node *node = new Node(nama, harga, jumlah);
    if(!head)
    {
        head = node;
        return;
    }

    Node *sekarang = head;
    while (sekarang->next)
    {
        sekarang = sekarang->next;
    }
    sekarang->next = node;
}

// Tambah Di Depan
void addFront(Node *&head, const string &nama, int harga, int jumlah)
{
    Node *node = new Node(nama, harga, jumlah);
    node->next = head;
    head = node;
}

// Tambah setelah nama tertentu, kalau gak ketemu tambah di akhir
bool addAfter(Node *&head, const string &afterNama, const string &nama, int harga, int jumlah)
{
    Node *sekarang = head;
    while(sekarang)
    {
        if(sekarang->nama == afterNama)
        {
            Node *node = new Node(nama, harga, jumlah);
            node->next = sekarang->next;
            sekarang->next = node;
            return true;
        }
        sekarang = sekarang->next;
    }

    // kalau gak ketemu, tambah di akhir
    addLast(head, nama, harga, jumlah);
    return false;
}

// Hapus berdasarkan nama tertentu yang pertaama kali ketemu
bool deleteByName(Node *&head, const string &keyName)
{
    if(!head)
    {
        return false;
    }

    // kalau head yg dihapus
    if(head->nama == keyName)
    {
        Node *sementara = head;
        head = head->next;
        delete sementara;
        return true;
    }

    Node *sebelumnya = head;
    Node *sekarang = head->next;
    while(sekarang)
    {
        if(sekarang->nama == keyName)
        {
            sebelumnya->next = sekarang->next;
            delete sekarang;
            return true;
        }
        sebelumnya = sekarang;
        sekarang = sekarang->next;
    }
    return false; // tandanya gak ketemu
}

void tampilkanKeranjang(Node *head)
{
    if(!head)
    {
        cout << "Keranjang belanjanya kosong lek!" << endl;
        return;
    }

    Node *sekarang = head;
    int index = 1;
    while(sekarang)
    {
        cout << index << ". " << sekarang->nama << " - Rp. " << sekarang->harga << " x " << sekarang->jumlah << endl;
        cout << " \n";
        sekarang = sekarang->next;
        index++;
    }
}

void hitungTotal(Node *head, int &distinctCount, long long &totalHarga)
{
    distinctCount = 0;
    totalHarga = 0;
    Node *sekarang = head;
    while(sekarang)
    {
        distinctCount++;
        totalHarga += (long long)sekarang->harga * sekarang->jumlah;
        sekarang = sekarang->next;
    }
}

void bebaskanList(Node *&head)
{
    while(head)
    {
        Node *sementara = head;
        head = head->next;
        delete sementara;
    }
}

int main(void)
{
    Node *head = nullptr;
    int n;
    cout << "Masukkan Jumlah Barang Awal : ";
    if(!(cin >> n))
    {
        return 0;
    }
    cin.ignore(); // buang newline setelah input angka

    for(int i = 1; i <= n; i++)
    {
        string nama;
        int harga, jumlah;
        cout << "\n=== Barang ke-"  << i << " === " << endl;
        cout << "Nama Barang  : ";getline(cin, nama);
        cout << "Harga Satuan : ";cin >> harga;
        cout << "Jumlah Beli  : ";cin >> jumlah;
        cin.ignore(); // buang newline setelah input angka

        addLast(head, nama, harga, jumlah);
        cout << "\n";
    }

    // Tanyain mau hapus barang atau gak
    char jawaban;
    cout << "Apakah ingin menghapus barang dari keranjang? (y/n) : ";
    cin >> jawaban;
    cin.ignore(); // buang newline setelah input char

    if(jawaban == 'y' || jawaban == 'Y')
    {
        string hapusNama;
        cout << "Masukkan Nama Barang Yang Ingin Dihapus : ";getline(cin, hapusNama);
        bool oke = deleteByName(head, hapusNama);

        if(oke)
        {
            cout << "Barang \"" << hapusNama << "\" berhasil dihapus!" << endl;
        }
        else
        {
            cout << "Barang \"" << hapusNama << "\" tidak ditemukan di keranjang!" << endl;
        }
    }

    cout << "\n=== Isi Keranjang Belanja ===" << endl;
    tampilkanKeranjang(head);

    int banyakJenis;
    long long total;
    hitungTotal(head, banyakJenis, total);
    cout << "\nTotal Jenis Barang : " << banyakJenis << endl;
    cout << "Total Harga : Rp." << total << endl;

    bebaskanList(head);
    return 0;

}
