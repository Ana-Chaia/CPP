/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 11:33:59 by anacaro5          #+#    #+#             */
/*   Updated: 2026/03/25 11:34:00 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <map>
# include <fstream>

class BitcoinExchange {
    private:
        std::map<std::string, double> _exchangeRates;

        void loadDataBase(const std::string &dataBaseFile);
        double getExchangeRates(const std::string &date) const;

		static bool isLeapYear(int year);
        static int  daysInMonth(int year, int month);
        static bool isValidDate(const std::string &date);
        static bool isValidValue(const std::string &value, double &outValue);

    public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);

        void printData(const std::string &pathInputFile) const;
};

#endif