/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:57:10 by anacaro5          #+#    #+#             */
/*   Updated: 2025/10/08 17:57:21 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <iostream>

int main() {
    for (int i = 0; i < 6; ++i) {
        Base* p = generate();

        std::cout << "identify(Base*): ";
        identify(p);

        std::cout << "identify(Base&): ";
        identify(*p);

        delete p;
    }

    std::cout << "identify(Base* NULL): ";
    identify(static_cast<Base*>(0));

    return 0;
}

