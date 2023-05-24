#include <iostream>
#include <vector>
#include <stack>

using namespace std;
typedef long long ll;

struct Element
{
    int wartosc;
    int idx;
};

int n = 0;
ll wyn = 0;
vector<int> A;
vector<int> ile_lewo;
vector<int> ile_prawo;
stack<Element> Q;

inline void napelniaj_lewo()
{
    for (int i = 0; i < n; ++i)
    {
        while(!Q.empty())
        {
            if (Q.top().wartosc < A[i])
                Q.pop();
            else
                break;
        }
        if (Q.empty())
            ile_lewo[i] = i+1;
        else
            ile_lewo[i] = i - Q.top().idx;
        Q.push({A[i],i});
    }
}

inline void napelniaj_prawo()
{
    Q = stack<Element>();
    for (int i = n-1; i >= 0; --i)
    {
        while(!Q.empty())
        {
            if (Q.top().wartosc <= A[i])
                Q.pop();
            else
                break;
        }
        if (Q.empty())
            ile_prawo[i] = n-i;
        else
            ile_prawo[i] = Q.top().idx - i;
        Q.push({A[i],i});
    }
}

inline void dodawaj_wynik()
{
    for (int i = 0; i < n; ++i)
        wyn += (ll)ile_lewo[i] * (ll)ile_prawo[i] * (ll)A[i];
}

int main()
{
    // https://szkopul.edu.pl/problemset/problem/0qINw7rrL7Bz0W90zn2L5BiV/site/?key=statement
    // O(N), stos monotonniczny. Podobna zasada co kolejka monotoniczna, Jesli przetwarzamy A[i], to wyrzucamy wszystkie < A[i],
    // bo one nigdy nie beda maxem. Szukamy pierwszego >= na lewo, i pierwszego > na prawo, zeby nie liczyc podwojnie.
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    A.assign(n,-1);
    for (int i = 0; i < n; ++i)
        cin >> A[i];

    ile_lewo.assign(n,-1);
    ile_prawo.assign(n,-1);

    napelniaj_lewo();
    napelniaj_prawo();
    dodawaj_wynik();

    cout << wyn << '\n';

    return 0;
}