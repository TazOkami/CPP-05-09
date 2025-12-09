#include "ScalarConverter.hpp"

// ============================================
// OCF (Privé - classe non instanciable)
// ============================================

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter::~ScalarConverter() {}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
    (void)other;
    return *this;
}

// ============================================
// Détection de type
// ============================================

bool ScalarConverter::isPseudoLiteral(const std::string& literal) {
    return (literal == "nan" || literal == "nanf" ||
            literal == "+inf" || literal == "-inf" ||
            literal == "+inff" || literal == "-inff");
}

bool ScalarConverter::isChar(const std::string& literal) {
    return (literal.length() == 1 && 
            std::isprint(literal[0]) && 
            !std::isdigit(literal[0]));
}

bool ScalarConverter::isValidNumber(const std::string& literal) {
    if (literal.empty()) return false;

    size_t i = 0;
    
    // Signe optionnel
    if (literal[i] == '+' || literal[i] == '-')
        i++;
    
    // Au moins un chiffre
    bool hasDigit = false;
    bool hasDot = false;
    
    while (i < literal.length()) {
        char c = literal[i];
        
        // Point décimal (un seul autorisé)
        if (c == '.') {
            if (hasDot) return false;
            hasDot = true;
        }
        // Chiffre
        else if (std::isdigit(c)) {
            hasDigit = true;
        }
        // 'f' final pour float
        else if (c == 'f' && i == literal.length() - 1) {
            break;
        }
        else {
            return false;
        }
        i++;
    }
    
    return hasDigit;
}

// ============================================
// Parsing sécurisé (C++98)
// ============================================

double ScalarConverter::parseValue(const std::string& literal) {
    // Cas char
    if (isChar(literal))
        return static_cast<double>(literal[0]);

    // Validation du format
    if (!isValidNumber(literal))
        throw std::invalid_argument("Invalid format");

    // Parsing avec strtod/strtof
    std::string str = literal;
    bool isFloat = (!str.empty() && str[str.length() - 1] == 'f');
    
    if (isFloat)
        str = str.substr(0, str.length() - 1);

    char* end = NULL;
    errno = 0;
    
    double result = strtod(str.c_str(), &end);

    // Vérification des erreurs
    if (errno == ERANGE)
        throw std::invalid_argument("Out of range");
    
    if (*end != '\0')
        throw std::invalid_argument("Invalid characters");

    return result;
}

// ============================================
// Affichage avec exceptions
// ============================================

void ScalarConverter::printChar(double value) {
    std::cout << "char: ";

    // Cas impossibles
    if (std::isnan(value) || std::isinf(value))
        throw std::invalid_argument("impossible");
    
    // Vérifier si convertible en int
    if (value != static_cast<int>(value))
        throw std::invalid_argument("impossible");
    
    int intValue = static_cast<int>(value);
    
    // Hors de la plage ASCII
    if (intValue < 0 || intValue > 127)
        throw std::invalid_argument("impossible");
    
    // Non affichable
    if (!std::isprint(intValue))
        throw std::invalid_argument("Non displayable");
    
    // Affichage OK
    std::cout << "'" << static_cast<char>(intValue) << "'" << std::endl;
}

void ScalarConverter::printInt(double value) {
    std::cout << "int: ";

    // Cas impossibles
    if (std::isnan(value) || std::isinf(value))
        throw std::invalid_argument("impossible");
    
    // Overflow
    if (value < INT_MIN || value > INT_MAX)
        throw std::invalid_argument("impossible");
    
    std::cout << static_cast<int>(value) << std::endl;
}

void ScalarConverter::printFloat(double value) {
    std::cout << "float: ";
    
    if (std::isnan(value)) {
        std::cout << "nanf" << std::endl;
        return;
    }
    
    if (std::isinf(value)) {
        std::cout << (value > 0 ? "+inff" : "-inff") << std::endl;
        return;
    }

    // ✅ Conversion obligatoire avant affichage
    float f = static_cast<float>(value);
    
    // ✅ Forcer la notation décimale
    std::cout << std::fixed << std::setprecision(1);
    std::cout << f << "f" << std::endl;
}


void ScalarConverter::printDouble(double value) {
    std::cout << "double: ";

    if (std::isnan(value)) {
        std::cout << "nan" << std::endl;
        return;
    }
    
    if (std::isinf(value)) {
        std::cout << (value > 0 ? "+inf" : "-inf") << std::endl;
        return;
    }

    // Formatage identique à float
    if (value == static_cast<int>(value) && 
        value >= -1000000 && value <= 1000000) {
        std::cout << std::fixed << std::setprecision(1);
    }
    
    std::cout << std::fixed << std::setprecision(1);
    std::cout << value << std::endl;
}

// ============================================
// Cas spéciaux : pseudo-littéraux
// ============================================

void ScalarConverter::handlePseudoLiteral(const std::string& literal) {
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;

    // Déterminer le type
    bool isNan = (literal == "nan" || literal == "nanf");
    bool isPosInf = (literal == "+inf" || literal == "+inff");
    bool isNegInf = (literal == "-inf" || literal == "-inff");

    // Float
    std::cout << "float: ";
    if (isNan)
        std::cout << "nanf";
    else if (isPosInf)
        std::cout << "+inff";
    else if (isNegInf)  // ✅ Maintenant utilisé !
        std::cout << "-inff";
    std::cout << std::endl;

    // Double
    std::cout << "double: ";
    if (isNan)
        std::cout << "nan";
    else if (isPosInf)
        std::cout << "+inf";
    else if (isNegInf)  // ✅ Maintenant utilisé !
        std::cout << "-inf";
    std::cout << std::endl;
}

// ============================================
// Fonction principale
// ============================================

void ScalarConverter::convert(const std::string& literal) {
    // Cas 1 : Pseudo-littéraux
    if (isPseudoLiteral(literal)) {
        handlePseudoLiteral(literal);
        return;
    }

    // Cas 2 : Parsing du nombre
    double value;
    try {
        value = parseValue(literal);
    } catch (const std::exception& e) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

    // Cas 3 : Conversions avec gestion d'erreurs
    try {
        printChar(value);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        printInt(value);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        printFloat(value);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        printDouble(value);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
