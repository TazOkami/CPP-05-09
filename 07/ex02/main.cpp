#include "Array.tpp"
#include "Array.hpp"

int main() {
    // Test 1 : Constructeur par défaut
    std::cout << "=== Test 1 : Empty array ===" << std::endl;
    Array<int> empty;
    std::cout << "Size: " << empty.size() << std::endl;  // Doit afficher 0

    // Test 2 : Constructeur avec taille
    std::cout << "\n=== Test 2 : Array with size ===" << std::endl;
    Array<int> numbers(5);
    std::cout << "Size: " << numbers.size() << std::endl;  // Doit afficher 5
    
    // Test 3 : Initialisation par défaut
    std::cout << "\n=== Test 3 : Default initialization ===" << std::endl;
    for (unsigned int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << " ";  // Qu'affiche-t-il ?
    }
    std::cout << std::endl;

    // Test 4 : Modification
    std::cout << "\n=== Test 4 : Modification ===" << std::endl;
    numbers[0] = 42;
    numbers[1] = 21;
    std::cout << numbers[0] << " " << numbers[1] << std::endl;

    // Test 5 : Constructeur de copie
    std::cout << "\n=== Test 5 : Copy constructor ===" << std::endl;
    Array<int> copy(numbers);
    copy[0] = 99;
    std::cout << "Original[0]: " << numbers[0] << std::endl;  // Doit rester 42
    std::cout << "Copy[0]: " << copy[0] << std::endl;         // Doit être 99

    // Test 6 : Opérateur d'affectation
    std::cout << "\n=== Test 6 : Assignment operator ===" << std::endl;
    Array<int> assigned;
    assigned = numbers;
    assigned[0] = 77;
    std::cout << "Original[0]: " << numbers[0] << std::endl;   // Doit rester 42
    std::cout << "Assigned[0]: " << assigned[0] << std::endl;  // Doit être 77

    // Test 7 : Exception (out of bounds)
    std::cout << "\n=== Test 7 : Out of bounds ===" << std::endl;
    try {
        std::cout << numbers[10] << std::endl;  // Index invalide
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    // Test 8 : Tableau de string
    std::cout << "\n=== Test 8 : Array of strings ===" << std::endl;
    Array<std::string> strings(3);
    strings[0] = "Hello";
    strings[1] = "World";
    strings[2] = "42";
    for (unsigned int i = 0; i < strings.size(); i++) {
        std::cout << strings[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
