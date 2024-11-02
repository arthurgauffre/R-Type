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
template <typename T> class ServerQueue {
public:
  /**
   * @brief Default constructor for the ServerQueue class.
   *
   * This constructor initializes a new instance of the ServerQueue class with default values.
   */
  ServerQueue() = default;

  /**
   * @brief Deleted copy constructor to prevent copying of ServerQueue instances.
   *
   * This constructor is explicitly deleted to avoid copying of the ServerQueue
   * object, ensuring that each instance is unique and not accidentally duplicated.
   *
   * @param other The ServerQueue object to be copied (deleted).
   */
  ServerQueue(const ServerQueue<T> &other) = delete;

  /**
   * @brief Virtual destructor for the ServerQueue class.
   *
   * This destructor ensures that the queue is cleared when the ServerQueue object is destroyed.
   * It calls the clear() method to remove all elements from the queue.
   */
  virtual ~ServerQueue() { clear(); };

  /**
   * @brief Retrieves the front element of the queue.
   *
   * This function returns a constant reference to the front element of the queue.
   * It uses a scoped lock to ensure thread safety while accessing the queue.
   *
   * @return const T& A constant reference to the front element of the queue.
   */
  const T &front() {
    std::scoped_lock lock(mutexQueue);
    return queue.front();
  }

  /**
   * @brief Retrieves the last element in the queue.
   *
   * This function returns a constant reference to the last element in the queue.
   * It uses a scoped lock to ensure thread safety while accessing the queue.
   *
   * @return const T& A constant reference to the last element in the queue.
   */
  const T &back() {
    std::scoped_lock lock(mutexQueue);
    return queue.back();
  }

  /**
   * @brief Removes and returns the front element of the queue.
   *
   * This function acquires a scoped lock on the queue's mutex to ensure thread safety,
   * then moves the front element out of the queue and returns it. The front element
   * is removed from the queue in the process.
   *
   * @return T The front element of the queue.
   */
  T popFront() {
    std::scoped_lock lock(mutexQueue);
    auto value = std::move(queue.front());
    queue.pop_front();
    return value;
  }

  /**
   * @brief Removes and returns the last element from the queue.
   *
   * This function acquires a scoped lock on the mutex to ensure thread safety,
   * then moves the last element from the queue and removes it from the queue.
   *
   * @tparam T The type of the elements stored in the queue.
   * @return T The last element from the queue.
   */
  T popBack() {
    std::scoped_lock lock(mutexQueue);
    auto value = std::move(queue.back());
    queue.pop_back();
    return value;
  }

  /**
   * @brief Pushes an element to the front of the queue.
   *
   * This function adds a new element to the front of the queue. It locks the
   * queue to ensure thread safety, moves the value to avoid unnecessary copies,
   * and then notifies one waiting thread, if any, that a new element is available.
   *
   * @param value The element to be added to the front of the queue.
   */
  void pushFront(const T &value) {
    std::scoped_lock lock(mutexQueue);
    auto movedValue = std::move(value);
    queue.emplace_front(movedValue);
    std::unique_lock<std::mutex> blockingLock(blockingMutex);
    blockingCondition.notify_one();
  }

  /**
   * @brief Adds a new element to the end of the queue.
   *
   * This function safely adds a new element to the queue by acquiring a lock on the queue's mutex.
   * It then moves the provided value into the queue and notifies one waiting thread, if any, that
   * a new element has been added.
   *
   * @param value The element to be added to the queue.
   */
  void pushBack(const T &value) {
    std::scoped_lock lock(mutexQueue);
    auto movedValue = std::move(value);
    queue.emplace_back(movedValue);
    std::unique_lock<std::mutex> blockingLock(blockingMutex);
    blockingCondition.notify_one();
  }

  /**
   * @brief Checks if the queue is empty.
   *
   * This function acquires a scoped lock on the mutex to ensure thread safety
   * while checking if the queue is empty.
   *
   * @return true if the queue is empty, false otherwise.
   */
  bool empty() {
    std::scoped_lock lock(mutexQueue);
    return queue.empty();
  }

  /**
   * @brief Get the size of the queue.
   *
   * This function returns the number of elements currently in the queue.
   * It uses a scoped lock to ensure thread safety while accessing the queue.
   *
   * @return size_t The number of elements in the queue.
   */
  size_t queueSize() {
    std::scoped_lock lock(mutexQueue);
    return queue.size();
  }

  /**
   * @brief Clears all elements from the queue.
   *
   * This function acquires a scoped lock on the mutex to ensure thread safety
   * and then clears all elements from the queue.
   */
  void clear() {
    std::scoped_lock lock(mutexQueue);
    queue.clear();
  }

  /**
   * @brief Waits until the queue is not empty.
   *
   * This function blocks the calling thread until the queue becomes non-empty.
   * It uses a condition variable to wait for a notification that the queue has
   * been modified. The function acquires a unique lock on the blockingMutex
   * and waits on the blockingCondition until the queue is no longer empty.
   */
  void wait() {
    while (empty()) {
      std::unique_lock<std::mutex> blockingLock(blockingMutex);
      blockingCondition.wait(blockingLock);
    }
  }

protected:
  /**
   * @brief A mutex to protect access to the queue.
   *
   * This mutex is used to ensure that access to the queue is thread-safe.
   * It should be locked before accessing or modifying the queue and unlocked
   * after the operation is complete.
   */
  std::mutex mutexQueue;

  /**
   * @brief A double-ended queue (deque) that stores elements of type T.
   *
   * This container allows for fast insertion and deletion of elements at both
   * the front and the back. It provides random access to elements and is
   * implemented as a sequence of contiguous blocks of memory.
   *
   * @tparam T The type of elements stored in the deque.
   */
  std::deque<T> queue;

  /**
   * @brief A condition variable for blocking and notifying threads.
   *
   * This condition variable is used to block one or more threads until another
   * thread modifies a shared variable and notifies the condition variable.
   * It is typically used in conjunction with a std::mutex to protect shared data.
   *
   * @see std::mutex
   * @see std::unique_lock
   */
  std::condition_variable blockingCondition;

  /**
   * @brief A mutex to ensure thread-safe access to shared resources.
   *
   * This mutex is used to block and synchronize access to critical sections
   * of code, preventing race conditions and ensuring that only one thread
   * can access the protected resource at a time.
   */
  std::mutex blockingMutex;
};
} // namespace network
} // namespace rtype

#endif /* !NETWORKQUEUE_HPP_ */
