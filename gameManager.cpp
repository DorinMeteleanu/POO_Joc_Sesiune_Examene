#include "gameManager.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <stdexcept>
using json = nlohmann::json;

GameManager* GameManager::instanta = nullptr;
GameManager* GameManager::getInstanta() {
    if(instanta == nullptr) {
        instanta = new GameManager();
    }
    return instanta;
};
GameManager::GameManager() {
    std::string nume_student;
    std::cout << "Salutare, student! Bag de seama ca esti aici pentru a te inscrie la sesiunea de examene din acest semestru! Spune-mi numele tau, te rog: ";
    std::getline(std::cin, nume_student);
    std::string specializare;
    std::cout << "Perfect, " << nume_student << "! Acum spune-mi si specializarea ta: ";
    std::getline(std::cin, specializare);
    int an_studiu;
    std::cout << "Ultimul lucru, spune-mi in ce an de studiu esti: ";
    std::cin >> an_studiu;
    std::cin.ignore();
    student = new Student(nume_student, 150, 20, specializare, an_studiu, 0, 0.0);
    ghiozdan = new Ghiozdan<Item>(5);

};

void GameManager::afiseazaMeniu() {
    std::cout << "\n[=============COLTUL TAU DE STUDIU=============]\n";
    std::cout << "1. Vezi status student\n";
    std::cout << "2. Invata (pierzi energie cat de 2 ori nr de ore de studiu)";
    std::cout << "3. !!!---MERGI LA EXAMEN---!!!\n";
    std::cout << "4. Magazin de aprovizionare\n";
    std::cout << "5. Salveaza progresul jocului\n";
    std::cout << "6. Incarca progres\n";
    std::cout << "7. Abandoneaza facultatea (Iesire)\n";
};

void GameManager::magazin() {
    std::cout << "[================MAGAZIN================]\n";
    std::cout << "1. Cumpara Cafea (Energie +20)\n";
    std::cout << "2. Cumpara Sticla de Apa (Energie +5)\n";
    std::cout << "3. Cumpara Copiuta (pentru examene scrise si grila)\n";
    std::cout << "Alegerea ta: ";
    int op;
    std::cin >> op;
    try {
        if(op == 1) {
            ghiozdan->adauga(new Cafea());
        }
        else if (op == 2) {
            ghiozdan->adauga(new SticlaApa());
        }
        else if(op == 3) {
            ghiozdan->adauga(new Copiuta());
        }
    } catch (const std::exception& e) {
        std::cout << "Eroare: " << e.what() << "\n";
    }

};

void GameManager::pornesteJocul() {
    int optiune = 0;
    while(optiune != 7) {
        afiseazaMeniu();
        std::cin >> optiune;
        switch(optiune) {
            case 1:
                student->afiseaza_status();
                break;
            case 2:
                int conf = 0;
                int ore = 0;
                while(conf == 0) {
                    std::cout << "Cate ore vrei sa inveti?: \n";
                    std::cin >> ore;
                    std::cout << "Vei avea nevoie de " << 2*ore << "energie. Confirmi?\n";
                    std::cout << "Apasa 1 pentru DA sau 0 pentru NU\n";
                    int inp;
                    std::cin >> inp;
                    conf = inp;
                }
                student->invata(ore);
            case 3:
                Examen* e = ExamenFactory::genereazaExamenAleatoriu();
                e->sustineExamen(student, ghiozdan);
                delete e;
                break;
            case 4:
                magazin();
                break;
            case 5: 
                salveazaJoc();
                break;
            case 6:
                incarcaJoc();
                break;
            case 7:
                std::cout << "Te mai asteptam pe la examen (nu scapi asa usor)\n";
            default:
                std::cout << "Optiune invalida\n";
        }
    }
};

GameManager::~GameManager(){
    delete student;
    delete ghiozdan;
}
