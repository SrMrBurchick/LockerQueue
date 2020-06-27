#ifndef lock_queue_hpp
#define lock_queue_hpp

#include "lock_queue_item.hpp"
#include "lock_queue_iterator.hpp"

template <typename ItemType>
class LockerQueue {
   private:
    LockerQueueItem<ItemType>* m_firstItem;
    LockerQueueItem<ItemType>* m_lastItem;
    int m_count;

   public:
    LockerQueue(const LockerQueue&) = delete;
    LockerQueue(LockerQueue&&) = delete;
    LockerQueue& operator=(const LockerQueue&) = delete;
    LockerQueue& operator=(LockerQueue&&) = delete;

    LockerQueue(/* args */)
        : m_firstItem{nullptr}, m_lastItem{nullptr}, m_count{0} {};

    LockQueueIterator<ItemType> begin() {
        return LockQueueIterator<ItemType>(&m_firstItem);
    };
    LockQueueIterator<ItemType> end() {
        return LockQueueIterator<ItemType>(&m_lastItem);
    };

    const LockQueueIterator<ItemType> cbegin() const {
        return LockQueueIterator<ItemType>(&m_firstItem);
    };
    const LockQueueIterator<ItemType> cend() const {
        return LockQueueIterator<ItemType>(&m_lastItem);
    };

    void push(const ItemType& item) {
        LockQueueIterator<ItemType> iterator = begin();
        LockQueueIterator<ItemType> prevItem = end();
        while (iterator != end()) {
            prevItem = iterator;
            ++iterator;
        }
        (*iterator.get()) = new LockerQueueItem<ItemType>(new ItemType(item));
        if ((*prevItem.get()) != nullptr) {
            (*iterator.get())->m_prev = (*prevItem.get());
        }
        ++m_count;
    }
    LockerQueueItem<ItemType>&& pop() {
        auto iterator = begin();
        auto item = (*iterator.get());
        if (iterator != end()) {
            m_firstItem = (*iterator.get())->m_next;
            --m_count;
        }
        return std::move(*item);
    };
    bool removeFromQueue(const ItemType& item) {
        LockQueueIterator<ItemType> iterator = find(item);
        if (iterator != end()) {
            delete (*iterator.get());
            return true;
        }
        return false;
    };

    LockQueueIterator<ItemType> find(const ItemType& item) {
        LockQueueIterator<ItemType> iterator = begin();
        while (iterator != end()) {
            if ((*(*iterator.get())->m_item) == item) {
                return iterator;
            }
            ++iterator;
        }
        return end();
    }

    void clear() {
        while (m_firstItem != nullptr) {
            auto item = m_firstItem->m_next;
            delete m_firstItem;
            m_firstItem = item;
        }
    }
    ~LockerQueue() { clear(); };
};

#endif  // lock_queue_hpp