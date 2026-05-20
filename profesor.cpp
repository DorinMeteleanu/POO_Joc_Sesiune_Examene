#include "profesor.h"
Profesor::Profesor(std::string nume, int rabdare, int exigenta, std::string titlu) : Persoana(nume, rabdare, exigenta), titlu(titlu) {};

void Profesor::afiseaza_status() const {
    std::cout << getTitluComplet() << "\n";
    std::cout << "Rabdare: " << nivel_energie;
    std::cout << "Exigenta: " << rezistenta_stres;
};

void Profesor::puneNota(Student* s, int dificultate_ramasa) {
        int nota = 10 - (dificultate_ramasa / 10);
        if(nota < 1) {
            nota = 1;
        }
        std::cout << YELLOW << "[CATALOG]" << RESET << "Profesorul " << nume << " ti-a trecut nota " << nota << " in carnet.\n";
};

std::string Profesor::getTitluComplet() const {
    return titlu + " " + nume;
};

void Profesor::exmatriculeaza(Student* s) {
    std::cout << RED << "[!!!] Profesorul " << nume << " a tipat la tine. Ai pierdut toata energia!\n" << RESET;
    s->modificaEnergie(-1000);
};

int Profesor::getRabdare() const {
    return nivel_energie;
};

int Profesor::getExigenta() const {
    return rezistenta_stres;
};

void Profesor::scadeRabdare(int valoare) {
    nivel_energie -= valoare;
};