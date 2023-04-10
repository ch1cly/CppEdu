#include <iostream>
#include <ios>
#include <vector>
#include <queue>
#include <cmath>
#include <random>
#include <map>
#include <algorithm>

using namespace std;


struct index {
    int l = 0;
    int r = 0;
    index(int _i, int _j) :l(_i), r(_j) {};
    index() {};
};


int urand(int l, int r) {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(l, r);

    return distrib(gen);
}
template <class t, class t1>
t dint(t a, t1 b) {
    return (a + b - 1) / b;
}


void partition3(vector<int>& v, int& pivotl, int&pivotr, int& l, int &r) {
    swap(v[pivotl], v[l]);
    swap(pivotl, l);
    l = pivotl + 1;
    pivotr = pivotl;
    while (l < r) {
        while (v[l] <= v[pivotl] && l < r) {
            if (v[l] == v[pivotl]) {
                pivotr++;
                swap(v[l], v[pivotr]);
                l++;
            }
            else
                ++l;
        }
        while (v[r] >= v[pivotr] && l < r) {
            if (v[r] == v[pivotr]) {
                pivotr++;
                swap(v[r], v[pivotr]);
                if (l == pivotr)
                    l++;
            }
            else
                --r;
        }
        if (v[l] > v[pivotl] && v[r] < v[pivotr])
            swap(v[l], v[r]);
    }
}

void qinsert3(queue<index> &q,vector<int>& v, int& pivotl, int& pivotr, int& l, int& r) {
    if (v[l] > v[pivotl]) {
        l--;
    }
    else
        r++;

    auto i = q.front();
    q.pop();

    index s(0, 0), f(0, 0);
    bool bs(0), bf(0);

    if (pivotr < l) {
        f.l = i.l ;
        f.r = i.l + l - pivotr - 1;
        bf = true;
    }
    if (r < i.r) {
        s.l = r;
        s.r = i.r;
        bs = true;
    }

    for (int j = pivotl; j <= pivotr; ++j) {
        swap(v[j], v[l]);
        l--;
    }
    if (bf && !bs)
        q.push(f);
    else if (!bf && bs)
        q.push(s);
    else if (bf && bs) {
        q.push(s);
        q.push(f);
    }

}

void qsort3(vector<int>& v) {
    int pivot;
    queue<index> q;
    if (v.size() < 2)
        return;

    q.push(index(0, v.size() - 1));

    while (q.size() > 0) {
        auto i = q.front();        
        int l = i.l, r = i.r;
        if (r - l < 2) {
            if (v[l] > v[r])
            {
                swap(v[l], v[r]);
            }
            q.pop();
            continue;
        }
        int pivotl = urand(i.l, i.r);
        //int pivotl = 6;
        int pivotr = pivotl;
        partition3(v, pivotl, pivotr, l, r);
        qinsert3(q,v, pivotl, pivotr, l, r);

    }
}

void ttest(vector<int>& v) {
    for (int i = 1; i < v.size(); i++) {
        if (v[i] < v[i - 1]) {
            cout << "NO!" << endl;
            return;
        }
    }
    cout << "!YES!YES!" << endl;
}

void test() {
    int n = 0;
    cin >> n;
    
    vector<int> v(n, 0);
    for (int i = 0; i < n; i++)       v[i] = rand() % 100 + 1;
    //vector<int> v = {2,2,0,0,1,1};
    //vector<int> v = {0,0,2,2,1,1};
    

    qsort3(v);
    ttest(v);
    cout << endl << "answer" << endl << endl;

    for (auto a : v)
        cout << a << ' ';
}
