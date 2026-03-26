#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept>
#include <algorithm> // std::sort, std::min_element, std::max_element
#include <cstddef>   // std::size_t, std::ptrdiff_t

class Span {
public:
    // Constructors / destructor
    Span(unsigned int n);
    Span(const Span &other);
    Span &operator=(const Span &other);
    ~Span();

    // Add a single number
    void addNumber(int value);

    // Add a range of numbers [first, last)
    template <typename InputIterator>
    void addNumber(InputIterator first, InputIterator last) {
        // Add one by one, reusing single-element addNumber()
        while (first != last) {
            this->addNumber(*first);
            ++first;
        }
    }

    // Span calculations
    unsigned int shortestSpan() const;
    unsigned int longestSpan() const;

private:
    unsigned int     _maxSize;
    std::vector<int> _numbers;
};

#endif // SPAN_HPP
