#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>

struct A {
    std::int8_t a{1};
    std::int8_t c{2};
    std::int8_t b{3};
    char d[33 * 1000];
};

struct B {
    std::int8_t a{1};
    char d[33 * 1000];
    std::int8_t c{2};
    std::int8_t b{3};
};

template<class T>
long doStuff(const std::vector<T>&s) {
    long v = 0;
    for (auto i: s) {
        v += i.a % i.b * i.c;
        (void) v;
    }
    return v;
}

template<class T>
double bench() {
    auto result = std::vector<long>();
    auto s = std::vector<T>();
    s.resize(100 * 1000, T{});
    for (int i = 0; i < 1000; ++i) {
        auto now = std::chrono::steady_clock::now();
        auto v = doStuff(s);
        auto delta = std::chrono::steady_clock::now() - now;
        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(delta);
        std::cout << v;
        result.push_back(microseconds.count());
    }
    double sum = std::accumulate(result.begin(), result.end(), 0l);
    return sum / result.size();
}

int main() {
    auto resultB = bench<B>();
    auto resultA = bench<A>();
    std::cout << sizeof(A) << " " << sizeof(B) <<"\n";
    std::cout << "Struct A: " << resultA << "\n" << "Struct B: " << resultB <<  "\n";

    return 0;
}