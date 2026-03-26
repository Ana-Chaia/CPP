/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:40:59 by anacaro5          #+#    #+#             */
/*   Updated: 2026/03/25 21:23:20 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "colors.hpp"
#include <iostream>
#include <sstream>
#include <sys/time.h>
#include <climits>
#include <iomanip> 

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &pmergeMe) {
	*this = pmergeMe;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &pmergeMe) {
    if (this != &pmergeMe) {
        _vec = pmergeMe._vec;
        _deq = pmergeMe._deq;
    }
    return *this;
}

void PmergeMe::fill(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]);

        if (arg.empty())
            continue;

        if (arg.find('.') != std::string::npos)
            throw std::runtime_error("float not allowed: " + arg);

        for (size_t j = 0; j < arg.size(); j++) {
            if (!std::isdigit(arg[j]))
                throw std::runtime_error("invalid input: " + arg);
        }

        std::stringstream ss(arg);
        long num;
        ss >> num;
        if (ss.fail() || num > INT_MAX || num < 0)
            throw std::runtime_error("invalid number: " + arg);

        _vec.push_back((int)num);
        _deq.push_back((int)num);
    }
}

void PmergeMe::sort() {

    std::cout << "Before: ";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;

    struct timeval start, end;
    gettimeofday(&start, NULL);
    sortVector();
    gettimeofday(&end, NULL);
    double time_vec = ((end.tv_sec - start.tv_sec) * 1000000.0
                    + (end.tv_usec - start.tv_usec)) / 1000000.0;

    gettimeofday(&start, NULL);
    sortDeque();
    gettimeofday(&end, NULL);
    double time_deq = ((end.tv_sec - start.tv_sec) * 1000000.0
                    + (end.tv_usec - start.tv_usec)) / 1000000.0;

    std::cout << "After:  ";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << CYAN << _vec.size() << END
              << " elements with " << CYAN << "std::vector" << END << ": "
              << std::fixed << std::setprecision(6) << time_vec << " s" << std::endl;
    std::cout << "Time to process a range of " << CYAN << _deq.size() << END
              << " elements with " << CYAN << "std::deque" << END << ": "
              << std::fixed << std::setprecision(6) << time_deq << " s" << std::endl;
}

void PmergeMe::sortVector() {
    mergeInsertVector(_vec);
}
        
void PmergeMe::sortDeque() {
    mergeInsertDeque(_deq);
}

void PmergeMe::mergeInsertVector(std::vector<int> &vec) {
    if (vec.size() <= 1)
        return;

    std::vector<int> uppers;
    std::vector<int> lowers;

    for (size_t i = 0; i + 1 < vec.size(); i += 2) {
        if (vec[i] > vec[i + 1]) {
            uppers.push_back(vec[i]);
            lowers.push_back(vec[i + 1]);
        } else {
            uppers.push_back(vec[i + 1]);
            lowers.push_back(vec[i]);
        }
    }

    bool hasExtra = vec.size() % 2 != 0;
    int extra = hasExtra ? vec.back() : 0;

    mergeInsertVector(uppers);

    // gera Jacobsthal
    std::vector<int> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    while (jacobsthal.back() < (int)lowers.size()) {
        int n = jacobsthal.size();
        jacobsthal.push_back(jacobsthal[n-1] + 2 * jacobsthal[n-2]);
    }

    // insere na ordem de Jacobsthal
    std::vector<bool> inserted(lowers.size(), false);

    for (size_t i = 1; i < jacobsthal.size(); i++) {
        int idx = jacobsthal[i] - 1;
        // insere do idx para baixo até achar não inserido
        for (int j = idx; j >= 0; j--) {
            if (j < (int)lowers.size() && !inserted[j]) {
                binaryInsertVector(uppers, lowers[j], (int)uppers.size());
                inserted[j] = true;
            }
        }
    }

    // insere qualquer lower que ficou para trás
    for (size_t i = 0; i < lowers.size(); i++) {
        if (!inserted[i])
            binaryInsertVector(uppers, lowers[i], (int)uppers.size());
    }

    if (hasExtra)
        binaryInsertVector(uppers, extra, (int)uppers.size());

    vec = uppers;
}

void PmergeMe::mergeInsertDeque(std::deque<int> &deq) {
    if (deq.size() <= 1)
        return;

    std::deque<int> uppers;
    std::deque<int> lowers;

    for (size_t i = 0; i + 1 < deq.size(); i += 2) {
        if (deq[i] > deq[i + 1]) {
            uppers.push_back(deq[i]);
            lowers.push_back(deq[i + 1]);
        } else {
            uppers.push_back(deq[i + 1]);
            lowers.push_back(deq[i]);
        }
    }

    bool hasExtra = deq.size() % 2 != 0;
    int extra = hasExtra ? deq.back() : 0;

    mergeInsertDeque(uppers);

    // gera Jacobsthal
    std::deque<int> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    while (jacobsthal.back() < (int)lowers.size()) {
        int n = jacobsthal.size();
        jacobsthal.push_back(jacobsthal[n-1] + 2 * jacobsthal[n-2]);
    }

    // insere na ordem de Jacobsthal
    std::deque<bool> inserted(lowers.size(), false);

    for (size_t i = 1; i < jacobsthal.size(); i++) {
        int idx = jacobsthal[i] - 1;
        for (int j = idx; j >= 0; j--) {
            if (j < (int)lowers.size() && !inserted[j]) {
                binaryInsertDeque(uppers, lowers[j], (int)uppers.size());
                inserted[j] = true;
            }
        }
    }

    // insere qualquer lower que ficou para trás
    for (size_t i = 0; i < lowers.size(); i++) {
        if (!inserted[i])
            binaryInsertDeque(uppers, lowers[i], (int)uppers.size());
    }

    if (hasExtra)
        binaryInsertDeque(uppers, extra, (int)uppers.size());

    deq = uppers;
}

void PmergeMe::binaryInsertVector(std::vector<int> &vec, int value, int end) {
    int lower = 0;
    int higher = end;    
    
    while (lower < higher) {
        int mid = lower + (higher - lower) / 2;
        if (vec[mid] < value)
            lower = mid + 1;
        else
            higher = mid;
    }
    vec.insert(vec.begin() + lower, value);
    
}
        
void PmergeMe::binaryInsertDeque(std::deque<int> &deq, int value, int end) {
    int lower = 0;
    int higher = end;
    
    while (lower < higher) {
        int mid = lower + (higher - lower) / 2;
        if (deq[mid] < value)
            lower = mid + 1;
        else
            higher = mid;
    }
    deq.insert(deq.begin() + lower, value);
    
}
