#ifndef lock_queue_item_hpp
#define lock_queue_item_hpp

#include <iostream>

template <typename ItemType>
class LockerQueueItem {
   public:
    ItemType* m_item;
    LockerQueueItem* m_next;
    LockerQueueItem* m_prev;
    LockerQueueItem(const LockerQueueItem& dest) = delete;
    LockerQueueItem(LockerQueueItem&& dest) {
        if (m_item != nullptr) {
            delete m_item;
        }
        m_item = dest.m_item;
        dest.m_item = nullptr;
        if (dest.m_prev) {
            dest.m_prev->m_next = dest.m_next;
        }
        if (dest.m_next) {
            dest.m_next->m_prev = dest.m_prev;
        }
        m_prev = dest.m_prev = nullptr;
        m_next = dest.m_next = nullptr;
    }
    LockerQueueItem(ItemType* const newItem)
        : m_item{newItem}, m_next{nullptr}, m_prev{nullptr} {}

    LockerQueueItem& operator=(const LockerQueueItem& dest) = delete;
    LockerQueueItem& operator=(LockerQueueItem&& dest) {
        if (m_item != nullptr) {
            delete m_item;
        }
        m_item = dest.m_item;
        dest.m_item = nullptr;
        if (dest.m_prev) {
            dest.m_prev->m_next = dest.m_next;
        }
        if (dest.m_next) {
            dest.m_next->m_prev = dest.m_prev;
        }
        dest.m_prev = nullptr;
        dest.m_next = nullptr;
        return *this;
    }
    bool operator==(const LockerQueueItem& item) {
        return m_item == nullptr ? false : *m_item == *item.m_item;
    }

    ~LockerQueueItem() {
        if (m_item != nullptr) {
            delete m_item;
        }
        if (m_prev) {
            m_prev->m_next = m_next;
        }
        if (m_next) {
            m_next->m_prev = m_prev;
        }
        std::cout << "Delete QUEUE Item" << std::endl;
        m_prev = nullptr;
        m_next = nullptr;
    };
};

#endif  // lock_queue_item_hpp