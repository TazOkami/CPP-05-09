#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main() {
    // ===== TEST 1 : Sérialisation/Désérialisation simple =====
    std::cout << "===== Test 1 : Basic Serialization =====" << std::endl;
    
    Data original;
    original.id = 42;
    original.name = "Test Data";
    original.value = 3.14;

    std::cout << "Original pointer: " << &original << std::endl;
    std::cout << "Original data: id=" << original.id 
              << ", name=" << original.name 
              << ", value=" << original.value << std::endl;

    // Sérialisation (pointeur → entier)
    uintptr_t raw = Serializer::serialize(&original);
    std::cout << "Serialized (uintptr_t): " << raw << std::endl;

    // Désérialisation (entier → pointeur)
    Data* deserialized = Serializer::deserialize(raw);
    std::cout << "Deserialized pointer: " << deserialized << std::endl;

    // Vérification de l'égalité des pointeurs
    if (deserialized == &original) {
        std::cout << "✅ SUCCESS: Pointers are equal!" << std::endl;
    } else {
        std::cout << "❌ FAIL: Pointers are different!" << std::endl;
    }

    // Vérification de l'accès aux données
    std::cout << "Deserialized data: id=" << deserialized->id 
              << ", name=" << deserialized->name 
              << ", value=" << deserialized->value << std::endl;

    std::cout << std::endl;

    // ===== TEST 2 : Avec allocation dynamique =====
    std::cout << "===== Test 2 : Dynamic Allocation =====" << std::endl;
    
    Data* dynamicData = new Data();
    dynamicData->id = 100;
    dynamicData->name = "Dynamic";
    dynamicData->value = 2.71;

    std::cout << "Dynamic pointer: " << dynamicData << std::endl;

    uintptr_t raw2 = Serializer::serialize(dynamicData);
    Data* deserialized2 = Serializer::deserialize(raw2);

    if (deserialized2 == dynamicData) {
        std::cout << "✅ SUCCESS: Dynamic pointers are equal!" << std::endl;
    } else {
        std::cout << "❌ FAIL: Dynamic pointers are different!" << std::endl;
    }

    std::cout << "Deserialized data: id=" << deserialized2->id 
              << ", name=" << deserialized2->name 
              << ", value=" << deserialized2->value << std::endl;

    delete dynamicData;

    std::cout << std::endl;

    // ===== TEST 3 : Tentative d'instanciation (doit échouer) =====
    std::cout << "===== Test 3 : Non-Instantiable Class =====" << std::endl;
     //Serializer s;  // ❌ Erreur de compilation
    std::cout << "✅ Class is non-instantiable (compile-time check)" << std::endl;

    return 0;
}
