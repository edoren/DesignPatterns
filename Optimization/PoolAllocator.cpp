#include "PoolAllocator.hpp"

PoolAllocator::PoolAllocator(size_t obj_size, size_t obj_num, uint8_t alignment)
      : m_start(nullptr),
        m_size(obj_size * obj_num),
        m_used_memory(0),
        m_num_allocations(0),
        m_obj_size(obj_size),
        m_obj_num(obj_num),
        m_alignment(alignment),
        m_free_list(nullptr) {
    assert(obj_size >= sizeof(void*));
    // alignment must be power of 2
    assert(alignment != 0 && (alignment & (alignment - 1)) == 0);

    m_start = malloc(obj_size * obj_num + alignment);
    assert(m_start != nullptr ||
           "the requested memory block could not be reserved.");

    uintptr_t raw_address = reinterpret_cast<uintptr_t>(m_start);
    size_t mask = (alignment - 1);
    uintptr_t misalignment = raw_address & mask;
    uintptr_t adjustment = alignment - misalignment;

    m_free_list = reinterpret_cast<void**>(raw_address + adjustment);

    void** p = m_free_list;

    for (size_t i = 0; i < obj_num - 1; i++) {
        *p = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(p) + obj_size);
        p = reinterpret_cast<void**>(*p);
    }

    *p = nullptr;
}

PoolAllocator::~PoolAllocator() {
    free(m_start);
}

void* PoolAllocator::Allocate() {
    if (m_free_list == nullptr) return nullptr;

    void* p = reinterpret_cast<void*>(m_free_list);

    m_free_list = reinterpret_cast<void**>(*m_free_list);

    m_used_memory += m_obj_size;
    m_num_allocations += 1;

    return p;
}

void PoolAllocator::Deallocate(void* pointer) {
    void** new_list_head = reinterpret_cast<void**>(pointer);
    *new_list_head = m_free_list;
    m_free_list = new_list_head;

    m_used_memory -= m_obj_size;
    m_num_allocations -= 1;
}

void* PoolAllocator::GetStart() const {
    return m_start;
}

size_t PoolAllocator::GetSize() const {
    return m_size;
}

size_t PoolAllocator::GetUsedMemory() const {
    return m_used_memory;
}

size_t PoolAllocator::GetNumAllocations() const {
    return m_num_allocations;
}
