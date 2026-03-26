/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 11:37:58 by anacaro5          #+#    #+#             */
/*   Updated: 2026/03/25 11:55:47 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <stack>

class RPN {
	private:
		std::stack<int> _stack;

		int         _applyOperator(const std::string &op, int a, int b) const;
		int         _pop();
        static bool isOperator(const std::string &token);

	public:
		RPN();
		~RPN();
		RPN(const RPN &rpn);
		RPN &operator=(const RPN &rpn);

		int evaluate(const std::string &expression);
};

#endif