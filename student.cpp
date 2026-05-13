#include "student.h"
Student::Student(std::string nume, int energie, int stres, std::string specializare, int an_studiu, int credite, double media)
    : Persoana(nume, energie, stres), specializare(specializare), an_studiu(an_studiu), credite_acumulate(credite), media_generala(media) {}
void Student::afiseaza_status() const {
    std::cout << "Student: " << nume << "\n";
    std::cout << "Nivel energie: " << nivel_energie << "\n";
    std::cout << "=================================\n";
    std::cout << "Rezistenta stres: " << rezistenta_stres << "\n";
    std::cout << "Specializare: " << specializare << "\n";
    std::cout << "An studiu: " << an_studiu << "\n";
    std::cout << "Credite acumulate: " << credite_acumulate << "\n";
    std::cout << "Media generala: " << media_generala << "\n";
};
void Student::invata(int ore) {
        nivel_energie -= ore * 2;
        rezistenta_stres += ore;
        std::cout << nume << " a invatat pentru " << ore << " ore";
        if (nivel_energie < 20) {
            std::cout << "\n ar fi o idee buna sa bea o cafeluta! \n";
        }
};