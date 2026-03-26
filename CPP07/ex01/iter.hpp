/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 20:23:59 by anacaro5          #+#    #+#             */
/*   Updated: 2025/10/26 21:00:22 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef> 

//for mutable arrays: allows functors that take T& (modification)
template <typename T, typename F>
void iter(T* array, std::size_t length, F func) {
    if (!array) return;
    for (std::size_t i = 0; i < length; ++i)
        func(array[i]);
}

// version for const arrays (read-only)
template <typename T, typename F>
void iter(T const* array, std::size_t length, F func) {
    if (!array) return;
    for (std::size_t i = 0; i < length; ++i)
        func(array[i]);
}

#endif