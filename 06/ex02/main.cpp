#include "Base.hpp"

int main(void)
{
    // Initialiser le seed une seule fois
    std::srand(std::time(NULL));
    
    std::cout << "=== Test 1: Multiple random objects ===" << std::endl;
    for (int i = 0; i < 10; i++)
    {
        Base* obj = generate();
        
        std::cout << "Object " << i + 1 << std::endl;
        std::cout << "  Pointer identification: ";
        identify(obj);
        std::cout << "  Reference identification: ";
        identify(*obj);
        std::cout << std::endl;
        
        delete obj;
    }
    
    std::cout << "\n=== Test 2: Known types ===" << std::endl;
    
    Base* a = new A();
    Base* b = new B();
    Base* c = new C();
    
    std::cout << "Type A:" << std::endl;
    std::cout << "  Pointer: ";
    identify(a);
    std::cout << "  Reference: ";
    identify(*a);
    
    std::cout << "\nType B:" << std::endl;
    std::cout << "  Pointer: ";
    identify(b);
    std::cout << "  Reference: ";
    identify(*b);
    
    std::cout << "\nType C:" << std::endl;
    std::cout << "  Pointer: ";
    identify(c);
    std::cout << "  Reference: ";
    identify(*c);
    
    delete a;
    delete b;
    delete c;
    
    std::cout << "\n=== Test 3: NULL pointer ===" << std::endl;
    Base* null_ptr = NULL;
    std::cout << "Identifying NULL pointer: ";
    identify(null_ptr);
    
    return 0;
}