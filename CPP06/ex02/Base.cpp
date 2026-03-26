/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:57:01 by anacaro5          #+#    #+#             */
/*   Updated: 2025/10/08 17:57:30 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime> 

Base* generate(void) {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(0)));
        seeded = true;
    }
    int r = std::rand() % 3;
    switch (r) {
        case 0: return new A();
        case 1: return new B();
        default: return new C();
    }
}

void identify(Base* p) {
    if (!p) {
        std::cout << "NULL" << std::endl;
        return;
    }
    if (dynamic_cast<A*>(p))      std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p)) std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p)) std::cout << "C" << std::endl;
    else                          std::cout << "Unknown" << std::endl;
}

void identify(Base& p) {
    try { (void)dynamic_cast<A&>(p); std::cout << "A" << std::endl; return; }
    catch (...) {}

    try { (void)dynamic_cast<B&>(p); std::cout << "B" << std::endl; return; }
    catch (...) {}

    try { (void)dynamic_cast<C&>(p); std::cout << "C" << std::endl; return; }
    catch (...) {}

    std::cout << "Unknown" << std::endl;
}

