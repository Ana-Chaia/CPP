/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 20:23:13 by anacaro5          #+#    #+#             */
/*   Updated: 2025/11/02 14:06:15 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// main.cpp
#include <iostream>
#include <string>
#include <stdexcept>
#include "array.hpp" 

// helper para imprimir Array<T> de forma segura
template <typename T>
void printArray(const Array<T>& a, const std::string& title) {
    std::cout << title << " (size=" << a.size() << "): [";
    for (unsigned int i = 0; i < a.size(); ++i) {
        std::cout << a[i];
        if (i + 1 < a.size()) std::cout << ", ";
    }
    std::cout << "]\n";
}

void test_ints() {
    std::cout << "\n=== test_ints ===\n";
    Array<int> a(5);             // construtor com tamanho
    for (unsigned int i = 0; i < a.size(); ++i) a[i] = (int)(i * 10);
    printArray(a, "a");

    // copy ctor (deep copy)
    Array<int> b = a;
    printArray(b, "b (copia de a)");

    // modifica b e mostra que a não mudou (prova de deep copy)
    b[0] = 999;
    printArray(a, "a (apos mudar b[0])");
    printArray(b, "b (apos mudar b[0])");

    // operator=
    Array<int> c;
    c = a;
    printArray(c, "c (atribuido de a)");
    c[1] = 777;
    printArray(a, "a (apos mudar c[1])");
    printArray(c, "c (apos mudar c[1])");
}

void test_strings() {
    std::cout << "\n=== test_strings ===\n";
    Array<std::string> s(3);
    s[0] = "Matheus";
    s[1] = "Julia";
    s[2] = "Pedro";
    printArray(s, "s");

    // const access (usa operator[] const)
    const Array<std::string> t = s;
    std::cout << "t[1] (const leitura): " << t[1] << "\n";

    // t[1] = "X"; // <- deve falhar na compilacao (teste comentado)
}

void test_bounds() {
    std::cout << "\n=== test_bounds ===\n";
    Array<int> a(3);
    for (unsigned int i = 0; i < a.size(); ++i) a[i] = (int)i;

    try {
        std::cout << "Acessando a[2]: " << a[2] << "\n";
        std::cout << "Acessando a[3] (fora do limite):\n";
        std::cout << a[3] << "\n"; // deve lançar exceção
    } catch (const std::out_of_range& e) {
        std::cout << "Excecao capturada: " << e.what() << "\n";
    }
}

void test_self_assignment() {
    std::cout << "\n=== test_self_assignment ===\n";
    Array<int> a(2);
    a[0] = 1; a[1] = 2;
    printArray(a, "a (antes)");
    // a = a; // auto-atribuicao 
    //-Werror transforma o warning em erro. Para testar auto-atribuição sem essa denúncia estática, use um alias (o compilador não crava que é o mesmo objeto)
    Array<int>& alias = a;
    a = alias; // testa o mesmo caminho de código, sem o warning
    
    printArray(a, "a (depois de a = a)");
}

void test_empty() {
    std::cout << "\n=== test_empty ===\n";
    Array<int> v;              // size = 0
    printArray(v, "v vazio");
    std::cout << "v.size() = " << v.size() << "\n";

    // copiar e atribuir arrays vazios
    Array<int> cpy = v;
    printArray(cpy, "cpy (copia de vazio)");
    Array<int> assignment;
    assignment = v;
    printArray(assignment, "assignment (atribuido de vazio)");

    // acessar deve lançar
    try {
        std::cout << v[0] << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Excecao ao acessar v[0]: " << e.what() << "\n";
    }
}

int main() {
    std::cout << "demonstration of template class Array<T>\n";
    test_ints();
    test_strings();
    test_bounds();
    test_self_assignment();
    test_empty();
    std::cout << "\nthe end.\n";
    return 0;
}
