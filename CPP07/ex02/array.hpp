/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 20:23:59 by anacaro5          #+#    #+#             */
/*   Updated: 2025/11/02 13:55:56 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
class Array{
    public:
    Array();                           // size = 0
    explicit Array(unsigned int n);    // explict declaration Array a(5) and not Array a = 5
    Array(const Array& other);         // deep copy
    Array& operator=(const Array&);    
    ~Array();
    
    
    T& operator[](unsigned int i);
    T const& operator[](unsigned int i) const;
    
    unsigned int size() const;
    
    private:
    T*              _data;
    unsigned int    _n;
    
};  

#include "array.tpp"

#endif