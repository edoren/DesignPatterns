#pragma once

#include <cstdlib>
#include <cstdint>
#include <cassert>

class PoolAllocator {
public:
    PoolAllocator(const size_t obj_size, size_t obj_num, uint8_t alignment = 4);
    ~PoolAllocator();

    void* Allocate();

    void Deallocate(void* pointer);

    void* GetStart() const;

    size_t GetSize() const;

    size_t GetUsedMemory() const;

    size_t GetNumAllocations() const;

private:
    PoolAllocator(const PoolAllocator& other) = delete;
    PoolAllocator& operator=(const PoolAllocator& other) = delete;

    void* m_start;
    size_t m_size;

    size_t m_used_memory;
    size_t m_num_allocations;

    const size_t m_obj_size;
    size_t m_obj_num;
    uint8_t m_alignment;

    void** m_free_list;
};
