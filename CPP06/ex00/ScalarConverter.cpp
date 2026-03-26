/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:35:31 by anacaro5          #+#    #+#             */
/*   Updated: 2025/09/30 20:04:15 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <climits> 
#include <cfloat>    
#include <cstdlib>   
#include <cctype>    
#include <iomanip> 

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
    (void)other;
    return *this;
}

ScalarConverter::~ScalarConverter() {}

static bool isOneChar(const std::string& str) {
    return (str.size() == 1 && !std::isdigit(static_cast<unsigned char>(str[0])));
}

static bool isInt(const std::string& str) {
    if (str.empty()) return false;
    size_t i = 0;
    if (str[i] == '+' || str[i] == '-') {
        if (str.size() == 1) return false;
        ++i;
    }
    for (; i < str.size(); i++) {
        if (!std::isdigit(static_cast<unsigned char>(str[i]))) return false;
    }
    return true;
}

static bool isPseudoFloat(const std::string& s) {
    return (s == "nanf" || s == "+inff" || s == "-inff");
}

static bool isPseudoDouble(const std::string& s) {
    return (s == "nan" || s == "+inf" || s == "-inf");
}

static bool isFloat(const std::string& str) {
    if (isPseudoFloat(str)) return true;
    if (str.empty()) return false;
    if (str.size() < 3) return false;
    if (str[str.size()-1] != 'f') return false;
    
    std::string core = str.substr(0, str.size()-1);
    size_t i = 0;
    if (core[i] == '+' || core[i] == '-') {
        if (core.size() == 1) return false;
        ++i;
    }
    
    bool hasDot = false;
    bool hasDigit = false;
    
    for (; i < core.size(); i++) {
       char c = core[i];
       if (c == '.') {
            if (hasDot) return false;
            hasDot = true;
       } else if (std::isdigit(static_cast<unsigned char>(c))) {
            hasDigit = true;
       } else {
            return false;
       }
    }
    return (hasDot && hasDigit);
}

static bool isDouble(const std::string& str) {
    if (isPseudoDouble(str)) return true;
    if (str.empty()) return false;
    if (str.size() < 3) return false;

    size_t i = 0;
    if (str[i] == '+' || str[i] == '-') {
        if (str.size() == 1) return false;
        ++i;
    }
    bool hasDot = false;
    bool hasDigit = false;
    for (; i < str.size(); ++i) {
        char c = str[i];
        if (c == '.') {
            if (hasDot) return false;
            hasDot = true;
        } else if (std::isdigit(static_cast<unsigned char>(c))) {
            hasDigit = true;
        } else {
            return false;
        }
    }
    return (hasDot && hasDigit);
}

static bool isNan(double d) {
    return (d != d);
}

static bool isInf(double d) {
    return (!isNan(d) && (d > 1e308 || d < -1e308));
}

static void printChar(double d, bool special) {
    std::cout << "char: ";
    if (special || d < 0.0 || d > 127.0) {
        std::cout << "Impossible" << std::endl;
        return;
    }
    char c = static_cast<char>(d);
    if (!std::isprint(static_cast<unsigned char>(c))) {
        std::cout << "Non displayable" << std::endl;
        return;
    }
    std::cout << "'" << c << "'" << std::endl;
}

static void printInt(double d, bool special) {
    std::cout << "int: ";
    if (special || d < static_cast<double>(INT_MIN) || d > static_cast<double>(INT_MAX)) {
        std::cout << "Impossible" << std::endl;
        return;
    }
    int v = static_cast<int>(d);
    std::cout << v << std::endl;
}

static void printFloat(double d, bool special, const std::string& pseudo = "") {
    std::cout << "float: ";
    if (special) {
        if (pseudo.size()) {
            std::cout << pseudo << std::endl;
        } else {
            if (isNan(d)) std::cout << "nanf" << std::endl;
            else if (d > 0) std::cout << "+inff" << std::endl;
            else std::cout << "-inff" << std::endl;
        }
        return;
    }
    float f = static_cast<float>(d);
    std::cout << std::fixed << std::setprecision(1) << f << "f" << std::endl;
}

static void printDouble(double d, bool special, const std::string& pseudo = "") {
    std::cout << "double: ";
    if (special) {
        if (pseudo.size()) {
            std::cout << pseudo << std::endl;
        } else {
            if (isNan(d)) std::cout << "nan" << std::endl;
            else if (d > 0) std::cout << "+inf" << std::endl;
            else std::cout << "-inf" << std::endl;
        }
        return;
    }
    std::cout << std::fixed << std::setprecision(1) << d << std::endl;
}

static void fromChar(char c) {
    double d = static_cast<unsigned char>(c);
    bool special = false;
    
    printChar(d, special);
    printInt(d, special);
    printFloat(d, special);
    printDouble(d, special);
}

static void fromInt(const std::string& s) {
    char* end = 0;
    long lv = std::strtol(s.c_str(), &end, 10);
    (void)end; 
    double d = static_cast<double>(lv);
    bool special = false;

    printChar(d, special);
    printInt(d, special);
    printFloat(d, special);
    printDouble(d, special);
}

static void fromDouble(const std::string& s) {
    if (isPseudoDouble(s)) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::string pf = (s == "nan") ? "nanf" : (s == "+inf" ? "+inff" : "-inff");
        printFloat(0.0, true, pf);
        printDouble(0.0, true, s);
        return;
    }
    char* end = 0;
    double d = std::strtod(s.c_str(), &end);
    bool special = (isNan(d) || isInf(d));

    printChar(d, special);
    printInt(d, special);
    printFloat(d, special);
    printDouble(d, special);
}

static void fromFloat(const std::string& s) {
    if (isPseudoFloat(s)) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::string dPseudo = (s == "nanf") ? "nan" : (s == "+inff" ? "+inf" : "-inf");
        printFloat(0.0, true, s);
        printDouble(0.0, true, dPseudo);
        return;
    }
    std::string core = s.substr(0, s.size()-1);
    char* end = 0;
    double d = std::strtod(core.c_str(), &end);
    bool special = (isNan(d) || isInf(d));

    printChar(d, special);
    printInt(d, special);
    printFloat(d, special);
    printDouble(d, special);
}

    
void ScalarConverter::convert(const std::string& literal) {
    if (isOneChar(literal)) {
        fromChar(literal[0]);
    } else if (isInt(literal)) {
        fromInt(literal);
    } else if (isFloat(literal)) {
        fromFloat(literal);
    } else if (isDouble(literal)) {
        fromDouble(literal);
    } else {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
    }
}
