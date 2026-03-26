/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 13:27:35 by anacaro5          #+#    #+#             */
/*   Updated: 2025/11/02 14:09:34 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//////////////////////definitions of template methods


#pragma once


template <typename T>
Array<T>::Array() : _data(NULL), _n(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : _data(NULL), _n(n) {
    _data = (_n ? new T[_n] : NULL);
}

template <typename T>   //copy constructor
Array<T>::Array(const Array& other) : _data(NULL), _n(other._n) {
    if (_n) {
        _data = new T[_n];
        for (unsigned int i = 0; i < _n; ++i)
            _data[i] = other._data[i];
    }
}

template <typename T>     //atribution operator Array<T> a = b
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        T* newbuf = (other._n ? new T[other._n] : NULL);
        for (unsigned int i = 0; i < other._n; ++i)
            newbuf[i] = other._data[i];
        delete[] _data;
        _data = newbuf;
        _n = other._n;
    }
    return *this;
}

template <typename T>
Array<T>::~Array() { delete[] _data; }

template <typename T>   //operador de indexação  Array<int> arr(5); arr[2] = 10;
T& Array<T>::operator[](unsigned int i) {
    if (i >= _n)
        throw std::out_of_range("Array index out of range");
    return _data[i];
}
  
template <typename T>   //operador de indexação CONST    const Array<int> arr(5); int x = arr[2]; // ✅ permitido // arr[2] = 10; // ❌ erro: o array é const

T const& Array<T>::operator[](unsigned int i) const {
    if (i >= _n)
        throw std::out_of_range("Array index out of range");
    return _data[i];
}

template <typename T>     //const depois dos parênteses (... ) const) indica que o método não altera o objeto — ele apenas lê o valor
unsigned int Array<T>::size() const { return _n; }
