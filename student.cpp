#include "student.h"
Student::Student(std::string nume, int energie, int stres, std::string specializare, int an_studiu, int credite, double media)
    : Persoana(nume, energie, stres), specializare(specializare), an_studiu(an_studiu), credite_acumulate(credite), media_generala(media), bani(50), bonus_pregatire(0), stres_curent(0) {}
void Student::afiseaza_status() const {
    std::cout << "Student: " << nume << "\n";
    std::cout << "Nivel ENERGIE: " << nivel_energie << "/ 150\n";
    std::cout << "Nivel STRES: " << stres_curent << "\n";
    std::cout << "Nivel energie: " << nivel_energie << "\n";
    std::cout << "Bonus din pregatire: " << bonus_pregatire << "\n";
    std::cout << "=================================\n";
    std::cout << "Specializare: " << specializare << "\n";
    std::cout << "An studiu: " << an_studiu << "\n";
    std::cout << "CREDITE acumulate: " << credite_acumulate << "\n";
    std::cout << "Media generala: " << media_generala << "\n";
};
void Student::invata(int ore) {
        nivel_energie -= ore * 2;
        stres_curent += ore * 3;
        bonus_pregatire += ore * 2;
        std::cout << nume << " a invatat pentru " << ore << " ore";
        if (nivel_energie < 20) {
            std::cout << "\n ar fi o idee buna sa bea o cafelutza! \n";
        }
        if(stres_curent >= 23) {
            std::cout << "\n [!!] Atentie, nivelul de stres este foarte mare, trebuie sa te relaxezi inainte sa mai inveti iar singur si sa iei bonus\n";
        }
};
int Student::getEnergie() const {
    return nivel_energie;
};
void Student::modificaEnergie(int cantitate) {
    nivel_energie += cantitate;
    if (nivel_energie < 0) {
        nivel_energie = 0;
    }
};

int Student::getCredite() const {
    return credite_acumulate;
};

void Student::adaugaCredite(int n) {
    credite_acumulate += n;
};

int Student::getBani() const {
    return bani;
};

void Student::modificaBani(int cantitate) {
    bani += cantitate;
};

int Student::getBonus() const {
    return bonus_pregatire;
};

void Student::reseteazaBonus(int reducere) {
    bonus_pregatire -= reducere;
};

void Student::relaxare() {
    stres_curent -= 20;
    if(stres_curent < 0) {
        stres_curent = 0;
    }
    nivel_energie += 10;
    std::cout << "Relaxarea a avut efect, surprinzator. Stresul a scazut.\n";
}

