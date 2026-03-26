/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 11:51:11 by anacaro5          #+#    #+#             */
/*   Updated: 2026/03/25 11:57:25 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Error: use" << argv[0] << " \"<expression>\"" << std::endl;
		return 1;
	}
	
	try {
		RPN rpn;

		std::cout << rpn.evaluate(argv[1]) << std::endl;
	} catch (const std::exception &e) {
		std::cerr << "Error " << e.what() << std::endl;
		return 1;
	}
	return 0;
}