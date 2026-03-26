#include <iostream>
#include <vector>
#include <cstdlib> // rand, srand
#include <ctime>
#include "span.hpp"

int main() {
    try {
        std::cout << "== Basic tests ==" << std::endl;
        Span sp(5);

        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
        std::cout << "longestSpan : " << sp.longestSpan() << std::endl;

        // This should throw: Span is full
        try {
            sp.addNumber(42);
        } catch (const std::exception &e) {
            std::cout << "adding extra: " << e.what() << std::endl;
        }

        std::cout << "\n== Range add test ==" << std::endl;
        std::vector<int> vec;
        vec.push_back(100);
        vec.push_back(200);
        vec.push_back(300);

        Span sp2(10);
        sp2.addNumber(vec.begin(), vec.end()); // add range
        sp2.addNumber(50);
        sp2.addNumber(400);

        std::cout << "shortestSpan: " << sp2.shortestSpan() << std::endl;
        std::cout << "longestSpan : " << sp2.longestSpan() << std::endl;

        std::cout << "\n== Large random test (10000 numbers) ==" << std::endl;
        Span big(10000);
        std::srand(static_cast<unsigned int>(std::time(NULL)));

        for (int i = 0; i < 10000; ++i)
            big.addNumber(std::rand());

        std::cout << "shortestSpan: " << big.shortestSpan() << std::endl;
        std::cout << "longestSpan : " << big.longestSpan() << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << "Unhandled exception: " << e.what() << std::endl;
    }

    return 0;
}
