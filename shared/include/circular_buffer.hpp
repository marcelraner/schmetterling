#ifndef CIRCULAR_BUFFER_HPP_
#define CIRCULAR_BUFFER_HPP_

#include <queue>

template <class T, class Container = std::deque<T>>
class CircularBuffer : public std::queue<T, Container>
{
public:
    CircularBuffer(size_t max_size) : max_size{max_size} {}
    void push(const T &value)
    {
        if (this->size() >= this->max_size)
        {
            this->c.pop_front();
        }
        std::queue<T, Container>::push(value);
    }

private:
    size_t max_size;
};

#endif // CIRCULAR_BUFFER_HPP_
