#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    constexpr int sizeA = 10000;
    constexpr int sizeB = 100;

    vector<float> A(sizeA, 1.0f);
    vector<float> B(sizeA, 2.0f);
    vector<float> C1(sizeA, 0.0f);
    vector<float> C2(sizeB, 0.0f);

    volatile float sink = 0; // 防止编译器优化掉

    // 情况 A：内层循环大
    auto startA = high_resolution_clock::now();
    for (int i = 0; i < sizeB; ++i) {
        for (int j = 0; j < sizeA; ++j) {
            C1[j] += A[j] * B[j];
        }
    }
    auto endA = high_resolution_clock::now();
    auto timeA = duration_cast<milliseconds>(endA - startA).count();
    cout << "Case A (inner 10000): " << timeA << " ms" << endl;

    // 防止优化
    for (auto v : C1) sink += v;

    // 情况 B：外层循环大
    auto startB = high_resolution_clock::now();
    for (int i = 0; i < sizeA; ++i) {
        for (int j = 0; j < sizeB; ++j) {
            C2[j] += A[j] * B[j];
        }
    }
    auto endB = high_resolution_clock::now();
    auto timeB = duration_cast<milliseconds>(endB - startB).count();
    cout << "Case B (inner 100):  " << timeB << " ms" << endl;

    for (auto v : C2) sink += v;

    // 防止优化用
    cout << "sink = " << sink << endl;

    return 0;
}

