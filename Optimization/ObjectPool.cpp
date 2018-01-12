#include <cassert>
#include <cstdint>
#include <cstdio>

#include <chrono>
#include <iostream>

#include "PoolAllocatorT.hpp"

struct Vector {
    float x, y, z;
};

struct Bullet {
    float speed;
    float size;
    Vector direction;
};

inline double GetElapsedTime(
    std::chrono::high_resolution_clock::time_point start,
    std::chrono::high_resolution_clock::time_point end) {
    return std::chrono::duration_cast<
               std::chrono::duration<double, std::milli>>(end - start)
        .count();
}

template <typename T>
void TestSpeed(size_t num_blocks) {
    std::cout << "Object size: " << sizeof(T) << " bytes" << std::endl;
    std::cout << "Object alignment: " << alignof(T) << " bytes" << std::endl;
    std::cout << "Object number: " << num_blocks << std::endl;
    std::cout << "Total size: " << sizeof(T) * num_blocks / (1024 * 1024.f)
              << " MiB" << std::endl
              << std::endl;

    T** pointers = (T**)malloc(sizeof(T) * num_blocks);

    std::cout << "POOL TEST" << std::endl;
    PoolAllocatorT<T> pool(num_blocks);
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < num_blocks; i++) {
            pointers[i] = pool.Allocate();
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        double elapsed = GetElapsedTime(start_time, end_time);
        std::cout << '\t' << "Allocating: " << elapsed << " ms." << std::endl;
    }
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < num_blocks; i++) {
            pool.Deallocate(pointers[i]);
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        double elapsed = GetElapsedTime(start_time, end_time);
        std::cout << '\t' << "Deallocating: " << elapsed << " ms." << std::endl;
    }

    std::cout << "MALLOC/FREE TEST" << std::endl;
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < num_blocks; i++) {
            pointers[i] = (T*)malloc(sizeof(T));
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        double elapsed = GetElapsedTime(start_time, end_time);
        std::cout << '\t' << "Allocating: " << elapsed << " ms." << std::endl;
    }
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < num_blocks; i++) {
            free(pointers[i]);
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        double elapsed = GetElapsedTime(start_time, end_time);
        std::cout << '\t' << "Deallocating: " << elapsed << " ms." << std::endl;
    }

    free(pointers);
}

int main(int argc, const char* argv[]) {
    TestSpeed<Bullet>(10000000);

    return 0;
}
