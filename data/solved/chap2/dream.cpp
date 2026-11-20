#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/dream?tab=metadata

/*


rule:
1. output "Yes" kalau skenario konsisten dengan telah apa yang terjadi
2. output "r Just A Dream" (hypothetical dream), jika misalkan saat memproses skenario S future dreams "D r" kita apply.
jika ada banyak "D r" line, pilih nilai r yang palin kecil
3. output "Plot Error" jika skenario gak konsisten dengan telah apa yang terjadi

contoh sample input 1:
10
E business_as_usual
E bobby_dies
S 1 bobby_died
E stuff_happens
E jr_does_bad_things
S 2 !bobby_dies business_as_usual
E it_goes_on_and_on
D 4
S 1 !bobby_dies
S 2 !bobby_dies it_goes_on_and_on


Skenario 1:
S 1 bobby_died
stack = [business_as_usual, bobby_dies] (paling kanan=top)
check bobby_died in stack? no -> assume "D 4" sudah terjadi (pop last 4 items or at max size dari stack) -> masis konsisten? no -> "Plot Error"


Skenario 2:
S 2 !bobby_dies business_as_usual
stack = [business_as_usual, bobby_dies, stuff_happens, jr_does_bad_things ]
!bobby_dies in stack? no -> assume "D 4" sudah terjadi:
pop 4 last item or at max sampai kita found events/stack nya konsisten dengan skenario
stack setelah hypothetical dream = [business_as_usual]
r = jumlah pop sampai skenario konsisten dengan events = 3
!bobby_dies (or bobby_dies notin stack)? yes && bussines_as_usual in stack ? yes -> output "3 Just A Dream"

Skenario 3:
S 1 !bobby_dies
stack = [business_as_usual, bobby_dies, stuff_happens, jr_does_bad_things, it_goes_on_and_on ]
disini karena dibawah baris "D 4":
pop semua last 4 events:
stack setelah "D 4" =  [business_as_usual]
bobby_dies notin stack ? yes -> output "Yes" (disini output "Yes" karena kita gak pakai hypothetical dream apapun)


Skenario 3:
S 2 !bobby_dies it_goes_on_and_on
stack setelah "D 4" =  [business_as_usual]
S 2 !bobby_dies it_goes_on_and_on
bobby_dies notin stack ? yes && it_goes_on_and_on in stack ? no -> output "Plot Error"


Sample Input 2:
11
S 1 !something
E one
E two
E three
E four
E five
S 3 three !four one
D 1
S 3 three !four one
D 1
S 3 three !four one


Skenario 1:
S 1 !something
stack = []
something notin stack? yes -> output "yes"

Skenario 2:
S 3 three !four one
stack = [one,two,three,four,five]
three in stack? yes && four notin stack? no ->
pakai hypothetical dream "D 1":

stack setelah "D 1"= [one,two,three,four]
three in stack? yes && four notin stack? no ->
pakai hypothetical dream "D 1" kedua:

stack setelah "D 1" kedua = [one,two,three]

three in stack? yes && four notin stack? yes && one in stack ? yes -> Output "2 Just A Dream" (2 karena pakai 2 r=1 hypothetical dream)


Skenario 3:
S 3 three !four one
disini "D 1" sudah apply
stack setelah "D 1"= [one,two,three,four]
three in stack? yes && four notin stack? no ->
pakai hypothetical dream "D 1":


stack setelah "D 1"= [one,two,three]
three in stack? yes && four notin stack? yes && one in stack ? yes -> Output "1 Just A Dream" (2 karena pakai 1 r=1 hypothetical dream)


Skenario 4:
S 3 three !four one
disini kedua "D 1" sudah apply

three in stack? yes && four notin stack? yes && one in stack ? yes -> Output "Yes"

karena kita bisa assume "r is an integer between 1 and R where R is the total number of events that have happened so far", kita bisa optimize:
gak perlu pop stack sebanyak 1 kali untuk pakai hypothetical dream:
bikin map untuk map event ke index dari event di dalam stack.
setiap kali skenario:
maintain:

event! yang harus dihapus (yang memiliki "!") memnuhi:
r = jumlah pops

map[event!] >= stack.size() - 1 - r + 1 (posisi event! yang harus dihapus harus lebih besar sama dengan ukuran pops)
r >= stack.size() - 1 - map[event!] + 1
r >= stack.size() - map[event!], untuk setiap event yang memiliki "!" di skenario

rMin = max(stack.size() - map[event!]),  untuk setiap event yang memiliki "!" di skenario



untuk setiap event yang bukan "!" di skenario dan konsisten dengan event yang sudah terjadi (simulasi kalau stack masih berisi event yang harus konsisten dengan events di skenario)
stack.size()-r >=  map[event] + 1
r <= stack.size() -  map[event] - 1, untuk setiap event yang bukan "!" di skenario

rMax = min(stack.size() -  map[event] - 1),  untuk setiap event yang memiliki "!" di skenario

rMax = jumlah pops ketika "event" yang harus ada di skenario berada di posisi indeks tertinggi

stack.size() - map[event!] <= r <= stack.size() -  map[event] - 1
rMin <= rMax



output "Yes" atau "r Just a Dream" ketika:
terdapat event di skenario yang konsistent (ada di dalam stack) & rMin <= rMax

else:
output "Plot Error"




*/

int main()
{
    stack<string> peristiwaYangSudahBerlalu;
    unordered_map<string, int> peristiwaIdMap;

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string op;
        cin >> op;
        if (op == "D")
        {
            int r;
            cin >> r;
            for (int j = 0; j < r; j++)
            { // O(r), r= jumlah events yang "Just A Dream"
                string lastPeristiwa = peristiwaYangSudahBerlalu.top();
                peristiwaYangSudahBerlalu.pop();
                peristiwaIdMap.erase(lastPeristiwa);
            }
        }
        else if (op == "E")
        {
            string peristiwa;
            cin >> peristiwa;
            peristiwaIdMap[peristiwa] = peristiwaYangSudahBerlalu.size();
            peristiwaYangSudahBerlalu.push(peristiwa);
        }
        else if (op == "S")
        {

            int jumlahPeristiwaSkenario;
            cin >> jumlahPeristiwaSkenario;

            bool adaYangKonsisten = true;
            int minStackSize = 0;
            int rMin = 0;
            int rMax = peristiwaYangSudahBerlalu.size();
            for (int j = 0; j < jumlahPeristiwaSkenario; j++)
            {  // O(k), k=jumlah event dari peristiwa
                string peristiwaSkenario;
                cin >> peristiwaSkenario;

                bool negasi = false;
                if (peristiwaSkenario[0] == '!')
                {
                    negasi = true;
                    peristiwaSkenario = peristiwaSkenario.substr(1);
                }

                if (!negasi)
                {
                    if (peristiwaIdMap.find(peristiwaSkenario) == peristiwaIdMap.end())
                    {
                        adaYangKonsisten = false; // kalau ada satu peristiwa skenario yang tidak ada di list events stack (nama beda) -> tidak konsisten
                        continue;
                    }
                    // peristiwa skenario konsisten dengan stack events
                    int posisiPeristiwaSkenario = peristiwaIdMap[peristiwaSkenario];
                    rMax = min(rMax, int(peristiwaYangSudahBerlalu.size()) - posisiPeristiwaSkenario - 1);
                }
                else
                {
                    // apply hypothetical dream "D r" -> simulasi pop stack sampai peristiwaSkenario dihapus dari stack
                    if (peristiwaIdMap.find(peristiwaSkenario) != peristiwaIdMap.end())
                    {
                        int posisiPeristiwaSkenario = peristiwaIdMap[peristiwaSkenario];
                        rMin = max(rMin, int(peristiwaYangSudahBerlalu.size()) - posisiPeristiwaSkenario);
                    }
                }
            }

            if (adaYangKonsisten && rMin <= rMax)
            {

                if (rMin == 0)
                {
                    cout << "Yes" << endl; // gak perlu pop stack agar skenario konsisten
                }
                else
                {
                    cout << rMin << " Just A Dream" << endl;
                }
            }
            else
            {
                cout << "Plot Error" << endl;
            }
        }
    }

    return 0;
}