#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <climits>
#include <cerrno>
#include <cstdlib>

class ScalarConverter {
private:
    // OCF (privé car classe statique)
    ScalarConverter();
    ScalarConverter(const ScalarConverter& other);
    ScalarConverter& operator=(const ScalarConverter& other);
    ~ScalarConverter();

    // Détection de type
    static bool isPseudoLiteral(const std::string& literal);
    static bool isChar(const std::string& literal);
    static bool isValidNumber(const std::string& literal);

    // Parsing sécurisé C++98
    static double parseValue(const std::string& literal);

    // Conversions avec exceptions
    static void printChar(double value);
    static void printInt(double value);
    static void printFloat(double value);
    static void printDouble(double value);

    // Cas spéciaux
    static void handlePseudoLiteral(const std::string& literal);

public:
    static void convert(const std::string& literal);
};

#endif
