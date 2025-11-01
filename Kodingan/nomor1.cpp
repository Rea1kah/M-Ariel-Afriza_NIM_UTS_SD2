#include <iostream>
#include <string>
using namespace std;


struct pesanan 
{
    string nama;
    string menu;
    int urutan;
    int statusVIP;
};

struct DynamicQueue 
{
    pesanan *data;
    int ukuran;
    int kapasitas;
    DynamicQueue(int kapasitasnya = 2)
    {   
        kapasitas = kapasitasnya;
        data = new pesanan[kapasitas];
        ukuran = 0;
    }

    ~DynamicQueue()
    {
        delete[] data;
    }

    void resizeIfNeeded()
    {
        if(ukuran < kapasitas)
        {
            return;
        }
        int newKapasitas = kapasitas * 2;
        pesanan *sementara = new pesanan[newKapasitas];

        for(int i = 0; i < ukuran; i++)
        {
            sementara[i] = data[i];
        }

        delete[] data;
        data = sementara;
        kapasitas = newKapasitas;
    }

    void enqueue(const pesanan &item)
    {
        resizeIfNeeded();
        data[ukuran++] = item;
    }

    // Nyari index elemen yg akan di dequeue sesuai aturan
    int findNextIndex()
    {
        if(ukuran == 0) 
        {
            return -1;
        }

        int index = 0;
        for(int i = 1; i < ukuran; i++)
        {
            if(data[i].statusVIP > data[index].statusVIP)
            {
                index = i;
            } 
            else if(data[i].statusVIP == data[index].statusVIP)
            {
                if(data[i].urutan < data[index].urutan)
                {
                    index = i;
                }
            }
        }
        return index;
    }

    // Ngeluarkan elemen sesuai aturan dan ngembalikan order
    pesanan dequeue()
    {
        int index = findNextIndex();
        pesanan keluar = data[index];

        // geser elemen setelah index ke kiri
        for(int i = index; i < (ukuran - 1); i++)
        {
            data[i] = data[i + 1];
        }
        ukuran--;
        return keluar;
    }

    bool kosong()
    {
        return ukuran == 0;
    }
};

int main()
{
    int n;
    cout << "Masukkan Jumlah Pesanan : ";
    if(!(cin >> n))
    {
        cout << "\nInputannya gak valid lek!" << endl;
        return 0;
    }
    cin.ignore(); // Membuang newline dari buffer

    DynamicQueue q;
    for(int i = 1; i <= n; i++)
    {
        pesanan p;
        cout << "\n=== Pesanan ke-" << i << " === " << endl;
        cout << "Nama Hewan : ";getline(cin, p.nama);
        cout << "Menu Pesanan : ";getline(cin, p.menu);
        cout << "Status VIP (1 = Biasa, 2 = VIP) : ";cin >> p.statusVIP;
        cin.ignore(); // Membuang newline dari buffer

        p.urutan = i;
        q.enqueue(p);
        cout << "\n";
    }

    // Output pesanan sesuai aturan dequeue
    cout << "=== DAFTAR PESANAN ===" << endl;
    int nomor = 1;
    while(!q.kosong())
    {
        pesanan dilayani = q.dequeue();
        cout << nomor << ". " << dilayani.nama << " - " << dilayani.menu;
        if(dilayani.statusVIP == 2)
        {
            cout << " [VIP]";
        }
        cout << "\n";
        nomor++;
    }
}
