#include "Intern.hpp"
#include "Bureaucrat.hpp"
#include <iostream>

int main() {
	std::cout << "\n=== Creating Intern ===" << std::endl;
	Intern intern;
	
	std::cout << "\n=== Valid Forms ===" << std::endl;
	
	AForm* form1 = intern.makeForm("shrubbery creation", "Home");
	AForm* form2 = intern.makeForm("robotomy request", "Bender");
	AForm* form3 = intern.makeForm("presidential pardon", "Ino");
	
	std::cout << "\n=== Invalid Form ===" << std::endl;

	AForm* form4 = intern.makeForm("invalid form name", "Target");

	if (!form4) {
		std::cout << "Form creation failed as expected" << std::endl;
	} else {
		std::cout << "ERROR: Form should not have been created!" << std::endl;
		delete form4;
	}

	std::cout << "\n=== Testing a form ===" << std::endl;
	
	if (form1) {
		Bureaucrat kiba("Kiba", 1);
		kiba.signForm(*form1);
		kiba.executeForm(*form1);
	}
	
	if (form2) {
		Bureaucrat sasuke("Sasuke", 1);
	sasuke.signForm(*form2);
	sasuke.executeForm(*form2);
	sasuke.executeForm(*form2);
	}

	if (form3) {
		Bureaucrat Naruto("Naruto", 1);
		Naruto.signForm(*form3);
		Naruto.executeForm(*form3);
	}
	std::cout << "\n=== Cleanup ===" << std::endl;
	
	delete form1;
	delete form2;
	delete form3;
	
	return 0;
}
