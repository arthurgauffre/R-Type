/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** NetworkQueue
*/

#ifndef NETWORKQUEUE_HPP_
#define NETWORKQUEUE_HPP_

#include <NetworkingCommon.hpp>

namespace rtype {
    namespace network {
        template <typename T>
        class ServerQueue {
            public:
                ServerQueue() = default;

                const T &front() {
                    std::scoped_lock lock(mutexQueue);
                    return queue.front();
                }

                const T &back() {
                    std::scoped_lock lock(mutexQueue);
                    return queue.back();
                }

                T popFront() {
                    std::scoped_lock lock(mutexQueue);
                    auto value = std::move(queue.front());
                    queue.pop_front();
                    return value;
                }

                T popBack() {
                    std::scoped_lock lock(mutexQueue);
                    auto value = std::move(queue.back());
                    queue.pop_back();
                    return value;
                }

                void pushFront(const T &value) {
                    std::scoped_lock lock(mutexQueue);
                    auto movedValue = std::move(value);
                    queue.emplace_front(movedValue);
                    std::unique_lock<std::mutex> blockingLock(blockingMutex);
                    blockingCondition.notify_one();
                }

                void pushBack(const T &value) {
                    std::scoped_lock lock(mutexQueue);
                    auto movedValue = std::move(value);
                    queue.emplace_back(movedValue);
                    std::unique_lock<std::mutex> blockingLock(blockingMutex);
                    blockingCondition.notify_one();
                }

                bool empty() {
                    std::scoped_lock lock(mutexQueue);
                    return queue.empty();
                }

                size_t queueSize() {
                    std::scoped_lock lock(mutexQueue);
                    return queue.size();
                }

                void clear() {
                    std::scoped_lock lock(mutexQueue);
                    queue.clear();
                }

                void wait() {
                    while(empty()) {
                        std::unique_lock<std::mutex> blockingLock(blockingMutex);
                        blockingCondition.wait(blockingLock);
                    }
                }

            protected:
                std::mutex mutexQueue;
                std::deque<T> queue;
                std::condition_variable blockingCondition;
                std::mutex blockingMutex;

        };
    }
}

#endif /* !NETWORKQUEUE_HPP_ */
