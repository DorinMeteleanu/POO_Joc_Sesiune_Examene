#include "profesor.h"
#include "tipuriProfesor.h"
ProfesorExigent::ProfesorExigent(std::string n) : Profesor(n, 30, 7, "Dr.") {};
ProfesorRelaxat::ProfesorRelaxat(std::string n) : Profesor(n, 60, 3, "Asist.") {};
void ProfesorExigent::reactioneaza(Student* s, int& d) {
    std::cout << YELLOW << "[!] Profesorul te supravegheaza atent. Pierzi 5 energie din cauza stresului.\n" << RESET;
    s->modificaEnergie(-5);
};
void ProfesorRelaxat::reactioneaza(Student* s, int& d) {
    if(rand() % 4 == 0) {
        std::cout << GREEN << "[!] Profesorul citeste ziarul (cine mai citeste ziare??). Ai putut sa scrii mai usor (-5 dificulatete)\n" << RESET;
        d -= 5;
    } 
};