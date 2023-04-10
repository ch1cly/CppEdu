#include <iostream>
#include <ios>
#include <vector>
#include <queue>
#include <cmath>
#include <random>
#include <algorithm>


static constexpr double eps = 1e-10;

template <typename T> inline
T absM(const T& v) { return v < 0 ? -v : v; }


template <class t>
inline bool Eq(const t& f, const t& s) {
    return absM(s - f) < eps;
}

template <class t>
inline bool less(const t& f, const t& s) {
    return f - s < eps;
}

template <class t>
inline bool lessEq(const t& f, const t& s) {
    return less(f, s) || Eq(f, s);
}


    



struct index {
    size_t l = 0;
    size_t r = 0;
    index(size_t _i, size_t _j) :l(_i), r(_j) {};
    index() {};
};

size_t urand(size_t l, size_t r) {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(l, r);

    return distrib(gen);
}


template <class t>
void partition3(std::vector<t>& vec, size_t& pivotL, size_t& pivotR, size_t& leftInd, size_t& rightInd) {
    std::swap(vec[pivotL], vec[leftInd]);
    std::swap(pivotL, leftInd);
    leftInd = pivotL + 1;
    pivotR = pivotL;

    while (leftInd < rightInd) {
        while (lessEq(vec[leftInd], vec[pivotL]) && leftInd < rightInd) {
            if (vec[leftInd] == vec[pivotL]) {
                pivotR++;
                std::swap(vec[leftInd], vec[pivotR]);
                leftInd++;
            }
            else
                ++leftInd;
        }
        while (lessEq(vec[pivotR], vec[rightInd]) && leftInd < rightInd) {
            if (vec[rightInd] == vec[pivotR]) {
                pivotR++;
                std::swap(vec[rightInd], vec[pivotR]);
                if (leftInd == pivotR)
                    leftInd++;
            }
            else
                --rightInd;
        }
        if (lessEq(vec[pivotL], vec[leftInd]) && less(vec[rightInd], vec[pivotR]))
            std::swap(vec[leftInd], vec[rightInd]);
    }
}

template <class t>
void qinsert3(std::queue<index>& q, std::vector<t>& vec, size_t& pivotL, size_t& pivotR, size_t& leftInd, size_t& rightInd) {
    if (less(vec[pivotL], vec[leftInd])) {
        leftInd--;
    }
    else
        rightInd++;

    auto globIndex = q.front();
    q.pop();

    index rightHalfInd(0, 0), leftHalfInd(0, 0);
    bool isRightWideEnough(false), isLeftWideEnough(false);

    if (pivotR < leftInd) {
        leftHalfInd.l = globIndex.l;
        leftHalfInd.r = globIndex.l + leftInd - pivotR - 1;
        isLeftWideEnough = true;
    }
    if (rightInd < globIndex.r) {
        rightHalfInd.l = rightInd;
        rightHalfInd.r = globIndex.r;
        isRightWideEnough = true;
    }

    for (int i = pivotL; i <= pivotR; ++i) {
        std::swap(vec[i], vec[leftInd]);
        leftInd--;
    }
    if (isLeftWideEnough && !isRightWideEnough)
        q.push(leftHalfInd);
    else if (!isLeftWideEnough && isRightWideEnough)
        q.push(rightHalfInd);
    else if (isLeftWideEnough && isRightWideEnough) {
        q.push(rightHalfInd);
        q.push(leftHalfInd);
    }

}

template <class t> 
void qsort3(std::vector<t>& v) {
    int pivot;
    std::queue<index> q;
    if (v.size() < 2)
        return;

    q.push(index(0, v.size() - 1));

    while (q.size() > 0) {
        auto i = q.front();
        size_t leftInd = i.l, rightInd = i.r;
        if (rightInd - leftInd < 2) {
            if (less(v[rightInd], v[leftInd]))
            {
                std::swap(v[leftInd], v[rightInd]);
            }
            q.pop();
            continue;
        }
        size_t pivotL = urand(i.l, i.r);
        //int pivotl = 6;
        size_t pivotR = pivotL;
        partition3(v, pivotL, pivotR, leftInd, rightInd);
        qinsert3(q, v, pivotL, pivotR, leftInd, rightInd);

    }
}
template <class t>
void ttest(std::vector<t>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        if (!lessEq(v[i - 1],v[i])) {
            std::cout << "NO!" << std::endl;
            std::cout << v[i - 1] << ' ' << v[i] << ' ' << lessEq(v[i - 1], v[i]) << ' ' << Eq(v[i - 1], v[i]) << std::endl;
            return;
        }
    }
    std::cout << "!YES!YES!" << std::endl;
}


void test() {
    int n = 0;
    std::cin >> n;
    std::vector<int> v(n, 0);
    for (size_t i = 0; i < n; i++)       v[i] = rand() % 100 + 1;
    //vector<int> v = {2,2,0,0,1,1};
    //vector<int> v = {0,0,2,2,1,1};
    qsort3(v);
    ttest(v);
    std::cout << std::endl << "answer" << std::endl << std::endl;

    for (auto a : v)
        std::cout << a << ' ';
}

int main(void) {

    test();

    return 0;
}
