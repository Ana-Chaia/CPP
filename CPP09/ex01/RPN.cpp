/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 11:42:53 by anacaro5          #+#    #+#             */
/*   Updated: 2026/03/25 11:53:44 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <stdexcept>
#include <sstream>

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &rpn) {
	*this = rpn;
}

RPN &RPN::operator=(const RPN &rpn) {
	if (this != &rpn)
		_stack = rpn._stack;
	return *this;
}

bool RPN::isOperator(const std::string &token) {
	return token == "+" || token == "-" || token == "*" || token == "/";
}

int RPN::_applyOperator(const std::string &op, int a, int b) const {
	if (op == "+") return a + b;
	if (op == "-") return a - b;
	if (op == "*") return a * b;
	if (op == "/") {
		if (b == 0)
			throw std::runtime_error("division by zero");
		return a / b;
	}
	throw std::runtime_error("invalid operator");
}

int RPN::_pop() {
	if (_stack.empty())
		throw std::runtime_error("invalid expression");
	int top = _stack.top();
	_stack.pop();
	return top;
}

int RPN::evaluate(const std::string &expression) {
	while (!_stack.empty())
		_stack.pop();

	std::istringstream iss(expression);
	std::string token;

	while (iss >> token) {
		if (token.size() == 1 && std::isdigit(token[0])) {
			_stack.push(token[0] - '0');
			continue;
		}
        if (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))
            throw std::runtime_error("negative numbers not allowed: " + token);
		if (isOperator(token)) {
			if (_stack.size() < 2)
				throw std::runtime_error("invalid expression");
			int b = _pop();
			int a = _pop();
			_stack.push(_applyOperator(token, a, b));
		} else {
			throw std::runtime_error("invalid token: " + token);
		}
	}
	if (_stack.size() != 1)
		throw std::runtime_error("invalid expression");
	return _stack.top();
}