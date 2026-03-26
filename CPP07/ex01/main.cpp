/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 20:23:13 by anacaro5          #+#    #+#             */
/*   Updated: 2025/11/02 12:47:00 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "iter.hpp"

// === Helper functions ======================================================

// Generic print (read-only)
template <typename T>
void print_const(T const& x) {
    std::cout << x << " ";
}

// Increment integer (modifies)
void inc_int(int& x) { ++x; }

// Functor to convert strings to uppercase
struct ToUpper {
    void operator()(std::string& s) const {
        for (std::size_t i = 0; i < s.size(); ++i) {
            if (s[i] >= 'a' && s[i] <= 'z')
                s[i] = static_cast<char>(s[i] - 'a' + 'A');
        }
    }
};

// Function to convert characters to uppercase
void to_upper_char(char& ch) {
    if (ch >= 'a' && ch <= 'z')
        ch = static_cast<char>(ch - 'a' + 'A');
}

// Simple section banner for readability
void banner(const std::string& title) {
    std::cout << "\n==================== " << title << " ====================\n";
}

// ===========================================================================

int main() {
    // A) MUTABLE int ARRAY + MODIFYING FUNCTION
    banner("Case 1: int[] (mutable) + function inc_int(int&)");
    int a[] = {1, 2, 3, 4};
    std::size_t n = sizeof(a) / sizeof(a[0]);

    std::cout << "Before: ";
    ::iter(a, n, print_const<int>);
    std::cout << "\n";

    // Calls iter(T*) — mutable version
    ::iter(a, n, inc_int);

    std::cout << "After inc_int (each element incremented by (1): ";
    ::iter(a, n, print_const<int>);
    std::cout << "\n";

    // -----------------------------------------------------------------------
    // B) MUTABLE std::string ARRAY + FUNCTOR (ToUpper)
    banner("Case 2: std::string[] (mutable) + functor ToUpper");
    std::string s[] = {"chaine1", "chaine2", "Oi"};
    std::size_t ns = sizeof(s) / sizeof(s[0]);

    std::cout << "Before: ";
    ::iter(s, ns, print_const<std::string>);
    std::cout << "\n";

    // Calls iter(T*) with a functor
    ::iter(s, ns, ToUpper());

    std::cout << "After ToUpper: ";
    ::iter(s, ns, print_const<std::string>);
    std::cout << "\n";

    // -----------------------------------------------------------------------
    // C) CONST double ARRAY + READ-ONLY FUNCTION
    banner("Case 3: const double[] (read-only) + function print_const()");
    const double d[] = {3.14, 2.71, 1.41};
    std::size_t nd = sizeof(d) / sizeof(d[0]);

    // The compiler automatically chooses iter(const T*)
    std::cout << "Array const (cannot be modified): ";
    ::iter(d, nd, print_const<double>);
    std::cout << "\n";

    // -----------------------------------------------------------------------
    // D) MUTABLE char ARRAY + MODIFYING FUNCTION
    banner("Case 4: char[] (mutable) + function to_upper_char(char&)");
    char c[] = {'a', 'b', 'c'};
    std::size_t nc = sizeof(c) / sizeof(c[0]);

    std::cout << "Before: ";
    ::iter(c, nc, print_const<char>);
    std::cout << "\n";

    // Calls the mutable version (T*)
    ::iter(c, nc, to_upper_char);

    std::cout << "After to_upper_char: ";
    ::iter(c, nc, print_const<char>);
    std::cout << "\n";

    // -----------------------------------------------------------------------
    // E) CONST-CORRECTNESS PROTECTION DEMO
    banner("Case 5: const array modification attempt (expected compile error)");
    const int constArr[] = {10, 20, 30};

    std::cout << "Calling iter(const int*, ...) with print_const -> OK\n";
    ::iter(constArr, 3, print_const<int>);
    std::cout << "\n";

    std::cout << "Calling iter(const int*, ...) with inc_int(int&) -> COMPILE ERROR\n";
    std::cout << "(Uncomment the line below to see it happen)\n";
    // ::iter(constArr, 3, inc_int); // ❌ does not compile: cannot bind non-const reference to const int

    std::cout << "\n==========================================================\n";
    std::cout << "End of tests.\n";

    return 0;
}
