#pragma once

#include "PoolAllocator.hpp"

template <typename T>
class PoolAllocatorT {
public:
    PoolAllocatorT(size_t obj_num) : m_alloc(sizeof(T), obj_num, alignof(T)) {}

    T* Allocate() {
        return reinterpret_cast<T*>(m_alloc.Allocate());
    }

    void Deallocate(T* pointer) {
        m_alloc.Deallocate(pointer);
    }

    T* GetStart() const {
        return reinterpret_cast<T*>(m_alloc.GetStart());
    }

    size_t GetSize() const {
        return m_alloc.GetSize();
    }

    size_t GetUsedMemory() const {
        return m_alloc.GetUsedMemory();
    }

    size_t GetNumAllocations() const {
        return m_alloc.GetNumAllocations();
    }

private:
    PoolAllocatorT(const PoolAllocatorT& other) = delete;
    PoolAllocatorT& operator=(const PoolAllocatorT& other) = delete;

    PoolAllocator m_alloc;
};
