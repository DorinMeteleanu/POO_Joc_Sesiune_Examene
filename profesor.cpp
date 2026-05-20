#include "profesor.h"
Profesor::Profesor(std::string nume, int rabdare, int exigenta, std::string titlu) : Persoana(nume, rabdare, exigenta), titlu(titlu) {};

void Profesor::afiseaza_status() const {
    std::cout << getTitluComplet() << "\n";
    std::cout << "Rabdare: " << nivel_energie;
    std::cout << "Exigenta: " << rezistenta_stres;
};

int Profesor::puneNotaScris(int ture) {
        int nota = 10 - (ture > 4 ? (ture - 4) : 0);
        if(nota < 5) {
            nota = 4;
        }
        return nota;
};
int Profesor::puneNotaOral(int dificultate) {
        int nota = 10 - (dificultate/10);
        return nota;
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