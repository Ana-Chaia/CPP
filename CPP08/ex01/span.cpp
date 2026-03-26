#include "span.hpp"

Span::Span(unsigned int n) : _maxSize(n), _numbers() {
    _numbers.reserve(n); // não é obrigatório, mas ajuda em performance
}

Span::Span(const Span &other)
    : _maxSize(other._maxSize), _numbers(other._numbers) {}

Span &Span::operator=(const Span &other) {
    if (this != &other) {
        _maxSize  = other._maxSize;
        _numbers  = other._numbers;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int value) {
    if (_numbers.size() >= _maxSize)
        throw std::runtime_error("Span is full: cannot add more numbers");
    _numbers.push_back(value);
}

unsigned int Span::shortestSpan() const {
    if (_numbers.size() < 2)
        throw std::runtime_error("Not enough numbers to find a span");

    // Copy and sort
    std::vector<int> sorted(_numbers);
    std::sort(sorted.begin(), sorted.end());

    // Compute minimal difference between consecutive elements
    unsigned int minSpan = static_cast<unsigned int>(sorted[1] - sorted[0]);
    for (std::size_t i = 1; i < sorted.size() - 1; ++i) {
        int diff = sorted[i + 1] - sorted[i];
        unsigned int udiff = static_cast<unsigned int>(diff);
        if (udiff < minSpan)
            minSpan = udiff;
    }
    return minSpan;
}

unsigned int Span::longestSpan() const {
    if (_numbers.size() < 2)
        throw std::runtime_error("Not enough numbers to find a span");

    std::vector<int>::const_iterator minIt =
        std::min_element(_numbers.begin(), _numbers.end());
    std::vector<int>::const_iterator maxIt =
        std::max_element(_numbers.begin(), _numbers.end());

    int diff = *maxIt - *minIt;
    return static_cast<unsigned int>(diff);
}
