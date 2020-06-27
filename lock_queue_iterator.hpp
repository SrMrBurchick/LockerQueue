#ifndef lock_queue_iterator_hpp
#define lock_queue_iterator_hpp
#include "lock_queue_item.hpp"

template <typename IteratorItemType>
class LockQueueIterator {
   private:
    LockerQueueItem<IteratorItemType>** m_ptr;

   public:
    LockQueueIterator<IteratorItemType>(LockerQueueItem<IteratorItemType>** ptr)
        : m_ptr(ptr) {}
    LockQueueIterator<IteratorItemType>& operator++() {
        m_ptr = &(*m_ptr)->m_next;
        return *this;
    }
    LockQueueIterator<IteratorItemType>& operator--() {
        m_ptr = &(*m_ptr)->m_prev;
        return *this;
    }
    LockerQueueItem<IteratorItemType>* operator*() { return *m_ptr; }
    LockerQueueItem<IteratorItemType>** operator->() { return m_ptr; }
    LockerQueueItem<IteratorItemType>** get() { return m_ptr; }
    bool operator==(const LockQueueIterator<IteratorItemType>& rhs) {
        return *m_ptr == nullptr? false : *m_ptr == *rhs.m_ptr;
    }
    bool operator!=(const LockQueueIterator<IteratorItemType>& rhs) {
        return *m_ptr == nullptr? false : *m_ptr != *rhs.m_ptr;
    }
    ~LockQueueIterator() { };
};

#endif  // lock_queue_item_hpp