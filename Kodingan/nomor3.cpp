#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Graf kecil tetap dibuat pada index 0..4 untuk A..E
// edges: A-B (4), A-C (2), B-D (3), C-D (1), D-E (5)

const int N = 5;
vector<pair<int, int>> adj[N]; // Buat adjecency listnya yg isinya pasangan (node, weight)

// supaya outpunya lebih cantik
string nama2[N] = {"A", "B", "C", "D", "E"};
string namaLengkap[N] = 
{
    "Warung Kopi Pak Harry (A)",
    "Kedai Coding IKLC (B)",
    "Catfe Alya (C)",
    "Studio Fasilkom-TI (D)",
    "Wi-Fi Gratis Sejagat (E)"
};

// Nambahin edge gak berarah
void addEdge(int u, int v, int w)
{
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

// Nyari bobot antara u dan v, yang merupakan graf kecil pake linear search
int getWeight(int u, int v)
{
    for(auto &p : adj[u])
    {
        if(p.first == v)
        {
            return p.second;
        }
    }

    // Kalau gak terhubung secara langsung
    return -1;
}

// Pakai DFS Rekursif untuk dapetin urutan kunjungannya
void dfsUtil(int u, vector<int> &visited, vector<int> &order)
{
    visited[u] = 1;
    order.push_back(u);

    // lakuin iterasi neighbour-nya sesuai urutan biar lebih konsisten
    for(auto &p : adj[u])
    {
        int v = p.first;
        if(!visited[v])
        {
            dfsUtil(v, visited, order);
        }
    }
}

vector<int> lakuinDFS(int start)
{
    vector<int> visited(N, 0);
    vector<int> order;
    dfsUtil(start, visited, order);
    return order;
}

// BFS untuk jalur terpendeknya, yang berdasarkan jumlah edge-nya dari s ke targetnya
vector<int> lakuinBFS(int s, int target)
{
    const int INF_edge = INT_MAX/4;
    const long long INF_w = (1LL << 60);

    vector<int> parent(N, -1);
    vector<int> distEdge(N, INF_edge);
    vector<long long> distWeight(N, INF_w);
    queue<int> q;

    distEdge[s] = 0;
    distWeight[s] = 0;
    q.push(s);

    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        
        for(auto &p : adj[u])
        {
            int v = p.first;
            int w = p.second;
            int candEdge = distEdge[u] + 1;
            long long candWeight = distWeight[u] + w;

            // Kalau lebih baik dari segi jumlah edge
            if(distEdge[v] > candEdge)
            {
                distEdge[v] = candEdge;
                distWeight[v] = candWeight;
                parent[v] = u;
                q.push(v);                
            }
            // Kalau sama jumlah edge tapi bobot lebih kecil, maka diperbarui
            else if(distEdge[v] == candEdge && distWeight[v] > candWeight)
            {
                distWeight[v] = candWeight;
                parent[v] = u;

                // sudah pernah kunjungi di level edge yg sama, lakuin push lagi agar bobot diperbaiki
                q.push(v);
            }
        }
    }

    if(distEdge[target] == INF_edge)
    {
        return {}; // Gak ada jalur
    }

    // buat rekontruksi jalur dari target ke s
    vector<int> jalur;
    int sekarang = target;
    
    while(sekarang != -1)
    {
        jalur.push_back(sekarang);
        sekarang = parent[sekarang];
    }

    reverse(jalur.begin(), jalur.end());
    return jalur;
}

int main(void)
{
    // Graf sesuai soal aja dulu
    addEdge(0, 1, 4); // A-B 4
    addEdge(0, 2, 2); // A-C 2
    addEdge(1, 3, 3); // B-D 3
    addEdge(2, 3, 1); // C-D 1
    addEdge(3, 4, 5); // D-E 5

    // 1. DFS dari A, dari index ke-0
    vector<int> urutanDFS = lakuinDFS(0);
    cout << "=== Penjelajahan si Parul dari A (DFS) ===" << endl;
    for(int i = 0; i < urutanDFS.size(); i++)
    {
        cout << nama2[urutanDFS[i]];
        if((i + 1) < urutanDFS.size())
        {
            cout << " -> ";
        }
    }
    cout << "\n\n";

    // 2. BFS untuk jalur terpendaknya dari A (0) ke E (4)
    vector<int> jalur = lakuinBFS(0, 4);
    if(jalur.empty())
    {
        cout << "Gak ada jalur dari A ke E!" << endl;
        return 0;
    }
    
    // Nampilin jalurnya secara vertikal dengan bobot masing masing antar node
    cout << "=== Jalur Tercepat Parul dari A ke E (BFS) === " << endl;
    for(int i = 0; i < jalur.size(); i++)
    {
        int u = jalur[i];
        cout << namaLengkap[u] << "\n";
        if(i + 1 < jalur.size())
        {
            int v = jalur[i + 1];
            int w = getWeight(u, v);
            
            if(w >= 0)
            {
                cout << w << "m\n";
            }
            else
            {
                cout << "(error: bobot gak ketemu lek!)\n";
            }
        }
    }

    // Kesimpulannya => jalur sebagai sequence, jumlah edge, total jarak
    cout << "\n=== Jalur Terpendek ===\n";
    for(int i = 0; i < jalur.size(); i++)
    {
        cout << nama2[jalur[i]];
        if(i + 1 < jalur.size())
        {
            cout << " -> ";
        }
    }
    cout << "\n";
    int totalEdge = (int)jalur.size() - 1;
    long long totalJarak = 0;

    for(int i = 0; (i + 1) < jalur.size(); i++)
    {
        int u = jalur[i], v = jalur[i + 1];
        totalJarak += getWeight(u, v);
    }

    cout << "Total langkah : " << totalEdge << " edge\n";
    cout << "Total Jarak   : " << totalJarak << " meter\n";

    return 0;
}