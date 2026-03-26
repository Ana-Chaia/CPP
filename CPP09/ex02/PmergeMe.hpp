/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:33:08 by anacaro5          #+#    #+#             */
/*   Updated: 2026/03/25 19:43:07 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>

class PmergeMe {
    private:
        std::vector<int> _vec;
        std::deque<int>  _deq;
    
        void sortVector();
        void sortDeque();

        void mergeInsertVector(std::vector<int> &vec);
        void mergeInsertDeque(std::deque<int> &deq);

        void binaryInsertVector(std::vector<int> &vec, int value, int end);
        void binaryInsertDeque(std::deque<int> &deq, int value, int end);
    
    
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe &pmergeMe);
        PmergeMe &operator=(const PmergeMe &pmergeMe);

        void fill(int argc, char **argv);
        void sort();
};

#endif