#include<iostream>

using namespace std;

const int N = 1e6 + 10;

int n;
int q[N];
void quick_sort(int q[], int l, int r) {
    if (l >= r) return;
    // the right boundary can't be obtained
    int x = q[l + r >> 1], i = l - 1, j = r + 1;
    while (i < j) {
        do i++; while(q[i] < x);
        do j--; while(q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    quick_sort(q, l, j);
    quick_sort(q, j+1, r);
}

void quick_sort(int q[], int l, int r) {
    if (l >= r) return;
    // the left boundary can't be obtained
    int x = q[l + r + 1 >> 1], i = l - 1, j = r + 1;
    while (i < j) {
        do i++; while(q[i] < x);
        do j--; while(q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    quick_sort(q, l, i - 1);
    quick_sort(q, i, r);
}

