#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <stdint.h>  // Pour uintptr_t
#include "Data.hpp"

class Serializer {
private:
    // ===== Classe NON-INSTANCIABLE =====
    Serializer();                                    // Constructeur privé
    Serializer(const Serializer& other);             // Copy privé
    Serializer& operator=(const Serializer& other);  // Assignation privée
    ~Serializer();                                   // Destructeur privé

public:
    // ===== MÉTHODES STATIQUES =====
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};

#endif
