/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 11:33:53 by anacaro5          #+#    #+#             */
/*   Updated: 2026/03/25 11:33:54 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "BitcoinExchange.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib> 
#include "colors.hpp"

BitcoinExchange::BitcoinExchange() {
	loadDataBase("data.csv");
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other) {
		_exchangeRates = other._exchangeRates;
	}
	return *this;
}

bool BitcoinExchange::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int BitcoinExchange::daysInMonth(int year, int month) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year))
        return 29;
    return days[month - 1];
}

bool BitcoinExchange::isValidDate(const std::string &date) {
    if (date == "date")
        return false;
    if (date.empty())
        throw std::runtime_error("empty date.");
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        throw std::runtime_error("bad input => " + date);

    int year  = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());

    if (year < 1900)
        throw std::runtime_error("bad input => " + date);
    if (month < 1 || month > 12)
        throw std::runtime_error("bad input => " + date);
    if (day < 1 || day > daysInMonth(year, month))
        throw std::runtime_error("bad input => " + date);
    return true;
}

bool BitcoinExchange::isValidValue(const std::string &value, double &outValue) {
    std::stringstream ss(value);
    ss >> outValue;

    if (ss.fail())
        throw std::runtime_error("bad input => " + value);
    if (outValue < 0)
        throw std::runtime_error("not a positive number.");
    if (outValue > 1000)
        throw std::runtime_error("too large a number.");
    return true;
}

void BitcoinExchange::loadDataBase(const std::string &dataBaseFile) {
	std::ifstream file(dataBaseFile.c_str());
	if (!file.is_open()) {
		throw std::runtime_error("Error: could not open file.");
	}

	std::string line;
	while (std::getline(file, line)) {
		std::stringstream dataStr(line);
		std::string date;
		double rate;

		if (std::isdigit(dataStr.peek()) && std::getline(dataStr, date, ',')) {
			dataStr >> rate;
			_exchangeRates[date] = rate;
		}
	}
	file.close();
}

double BitcoinExchange::getExchangeRates(const std::string &date) const {
	std::map<std::string, double>::const_iterator it = _exchangeRates.find(date);
	if (it != _exchangeRates.end()) {
		return it->second;
	}

	it = _exchangeRates.lower_bound(date);
	if (it == _exchangeRates.begin()) {
		throw std::runtime_error("bad input => " + date);
	}
	--it;
	return it->second;
}

static std::string trimSpaces(const std::string &str) {
	std::string result;
	for (size_t i = 0; i < str.size(); i++)
		if (str[i] != ' ')
			result += str[i];
	return result;
}

void BitcoinExchange::printData(const std::string &pathInputFile) const {
	std::ifstream file(pathInputFile.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");

	std::string line;
	while (std::getline(file, line)) {
		if (line.empty())
			continue;

		try {
			if (line.find('|') == std::string::npos)
				throw std::runtime_error("bad input => " + line);

			std::stringstream ss(line);
			std::string date;
			std::string valueStr;

			std::getline(ss, date, '|');
			std::getline(ss, valueStr);

			date     = trimSpaces(date);
			valueStr = trimSpaces(valueStr);

			double value;
			if (isValidDate(date) && isValidValue(valueStr, value)) {
				double rate = getExchangeRates(date);
				std::cout << date << " => " << value << " = "
						  << rate * value << std::endl;
			}
		}
		catch (const std::exception &e) {
			std::cerr << BOLD_RED << "Error: " << RST
					  << e.what() << std::endl;
		}
	}
	file.close();
}
