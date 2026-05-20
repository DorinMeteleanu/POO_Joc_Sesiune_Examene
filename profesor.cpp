#include "profesor.h"
Profesor::Profesor(std::string nume, int rabdare, int exigenta, std::string titlu) : Persoana(nume, rabdare, exigenta), titlu(titlu) {};

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