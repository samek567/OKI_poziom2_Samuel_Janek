#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int k = 173;

struct Zapytanie
{
    int l;
    int p;
    int idx;
    bool operator < (const Zapytanie &zapytanie) const
    {
        if (l / k == zapytanie.l / k)
            return p < zapytanie.p;
        return l / k < zapytanie.l / k;
    }
};

int n = 0, q = 0, lewy_wsk = 0, prawy_wsk = 0, ile_roznych = 0;
vector<int> A;
unordered_map<int,int> stat;
vector<int> wystapienia;
vector<Zapytanie> zapytania;
vector<int> wyn;

inline void wczytaj()
{
    cin >> n;
    A.assign(n,-1);
    for (int i = 0; i < n; ++i)
        cin >> A[i];

    cin >> q;
    zapytania.assign(q,{});
    for (int i = 0; i < q; ++i)
    {
        cin >> zapytania[i].l >> zapytania[i].p;
        zapytania[i].l--, zapytania[i].p--;
        zapytania[i].idx = i;
    }
}

inline void preprocesing()
{
    for (int i = 0; i < n; ++i)
    {
        if (auto it = stat.find(A[i]) == stat.end())
            stat[A[i]] = i;
        A[i] = stat[A[i]];
    }
    sort(zapytania.begin(), zapytania.end());
    wyn.assign(q,-1);
}

inline void mo()
{
    lewy_wsk = 0, prawy_wsk = 0, ile_roznych = 1;
    wystapienia.assign(n,0);
    wystapienia[A[0]]++;
    for (int i = 0; i < q; ++i)
    {
        int l = zapytania[i].l, p = zapytania[i].p;
        while(lewy_wsk > l)
        {
            lewy_wsk--;
            if (wystapienia[A[lewy_wsk]] == 0)
                ile_roznych++;
            wystapienia[A[lewy_wsk]]++;
        }
        while(lewy_wsk < l)
        {
            wystapienia[A[lewy_wsk]]--;
            if (wystapienia[A[lewy_wsk]] == 0)
                ile_roznych--;
            lewy_wsk++;
        }
        while(prawy_wsk > p)
        {
            wystapienia[A[prawy_wsk]]--;
            if (wystapienia[A[prawy_wsk]] == 0)
                ile_roznych--;
            prawy_wsk--;
        }
        while(prawy_wsk < p)
        {
            prawy_wsk++;
            if (wystapienia[A[prawy_wsk]] == 0)
                ile_roznych++;
            wystapienia[A[prawy_wsk]]++;
        }
        wyn[zapytania[i].idx] = ile_roznych;
    }
}

inline void wypisz()
{
    for (int i = 0; i < q; ++i)
        cout << wyn[i] << '\n';
}

int main()
{
    // Zaimplementuj Mo, sprawdzarka np. zadanie d-query SPOJ: https://www.spoj.com/problems/DQUERY/
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    wczytaj();
    preprocesing();
    mo();
    wypisz();

    return 0;
}
