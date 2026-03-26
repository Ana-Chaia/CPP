/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 11:34:14 by anacaro5          #+#    #+#             */
/*   Updated: 2026/03/25 11:34:15 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include "colors.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << RED << "Use: ./btc <file>" << END << std::endl;
		return 1;
	}
	std::ifstream check(argv[1]);
    if (!check.is_open()) {
        std::cerr << RED << "Error: could not open file." << END << std::endl;
        return 1;
	}
	if (check.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << RED << "Error: empty file." << END << std::endl;
        return 1;
    }
	check.close();
	try {
		BitcoinExchange exchange;
		exchange.printData(argv[1]);
	} catch (const std::exception &e) {
		std::cerr << RED << e.what() << END << std::endl;
	}

	return 0;
}