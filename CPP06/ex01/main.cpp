/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:55:54 by anacaro5          #+#    #+#             */
/*   Updated: 2025/10/08 17:55:57 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "serializer.hpp"
#include "data.hpp"

static void printData(const char* tag, const Data* d) {
    std::cout << tag << " { id: " << d->id
              << ", name: " << d->name
              << ", score: " << d->score
              << " } @ " << d << std::endl;
}

int main() {
    Data d;
    d.id = 42;
    d.name = "forty-two";
    d.score = 98.0;

    Data* original = &d;
    printData("original", original);

    uintptr_t raw = Serializer::serialize(original);
    std::cout << "serialized uintptr_t: " << raw << std::endl;

    Data* roundtrip = Serializer::deserialize(raw);
    printData("roundtrip", roundtrip);

    if (roundtrip == original) {
        std::cout << "[OK] preserved poiter after serialize/deserialize." << std::endl;
    } else {
        std::cout << "[FAIL] different pointer!" << std::endl;
        return 1;
    }

    std::cout << "ptr (hex) : " << original << "\n";            
    std::cout << "raw (hex) : 0x" << std::hex << raw << std::dec << "\n"; 
    std::cout << "raw (dex) : " << raw << "\n";                      

    //std::cout << (raw == reinterpret_cast<uintptr_t>(original) ? "same same" : "diff") << "\n";
    
    Data* a = NULL;
    std::cout << (a == original ? "[OK]" : "[FAIL]") << std::endl;
    a = Serializer::deserialize(raw);
    //std::cout << (a == original ? "[OK]" : "[FAIL]") << std::endl;
    return 0;
}
