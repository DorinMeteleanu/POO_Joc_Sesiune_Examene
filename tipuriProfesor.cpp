#include "profesor.h"
#include "tipuriProfesor.h"
ProfesorExigent::ProfesorExigent(std::string n) : Profesor(n, 30, 7, "Dr.") {};
ProfesorRelaxat::ProfesorRelaxat(std::string n) : Profesor(n, 60, 3, "Asist.") {};
void ProfesorExigent::reactioneaza(Student* s, int& d) {
    if(rand() % 4 == 0) {
        int input = rand() % 4;
        if(input == 0) {
            std::cout << MAGENTA << "[REACTION!] Profesorul te supravegheaza atent. Iti scade energia numai cand te gandesti la asta (-5 energie)\n" << RESET;
            s->modificaEnergie(-5);
        } else if(input == 1) {
            std::cout << MAGENTA << "[REACTION!] Profesorul se uita pe foia ta de examen...si iti mai adauga o intrebare (are voie sa faca asta???) (+10 dificultate)\n" << RESET;
            d+=10;
        } else if(input == 2) {
            std::cout << MAGENTA << "[REACTION!] Profesorului nu-i place numele tau (ce bully)... Siii iti fura 5 lei din buzunar (uh cam ilegal dar ok..)\n" << RESET;
            s->modificaBani(-5);
        } else {
            std::cout << MAGENTA << "[REACTION!] Profesorul va verifica punctele bonus. Isi insuseste cate 2 de la fiecare (patetic) (-2 bonus)\n";
            s->reseteazaBonus(2); 
        }

    }
};
void ProfesorRelaxat::reactioneaza(Student* s, int& d) {
    if(rand() % 4 == 0) {
        int input = rand() % 4;
        if(input == 0) {
            std::cout << MAGENTA << "[REACTION!] Profesorul citeste ziarul (cine mai citeste ziare??). Ai putut sa scrii mai usor (-5 dificulatete)\n" << RESET;
            d -= 5;
        } else if(input == 1) {
            std::cout << MAGENTA << "[REACTION!] Profesorul te incurajeaza. Are incredere in tine (nu-mi dau seama de ce) (+5 energie)\n" << RESET;
            s->modificaEnergie(5);
        } else if(input == 2) {
            std::cout << MAGENTA << "[REACTION!] Profesorul te-a vazut invatand toata ziua pe holuri. Decide sa iti dea 4 puncte bonus. (+4 bonus)\n" << RESET;
            s->reseteazaBonus(-4);
        } else {
            std::cout << MAGENTA << "[REACTION!] Profesorul da cate 5 lei la toti, asa, de motivare... (vreau si eu la facultatea asta) (+5 lei)\n";
            s->modificaBani(5); 
        }

    }
};