#include "gameManager.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <stdexcept>
#include "ui_util.h"
using json = nlohmann::json;

GameManager* GameManager::instanta = nullptr;
GameManager* GameManager::getInstanta() {
    if(instanta == nullptr) {
        instanta = new GameManager();
    }
    return instanta;
};
GameManager::GameManager() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    std::cout << YELLOW << "=================================\n";
    std::cout << "      SIMULATOR DE SESIUNE (JOC HORROR)       \n";
    std::cout << "=================================\n" << RESET;
    std::cout << "1. Joc Nou\n";
    std::cout << "2. Continua (Incarca Salvare)\n";
    std::cout << "Alege: ";

    int op;
    std::cin >> op;
    std::cin.ignore(10000, '\n');
    ghiozdan = new Ghiozdan<Item>(5);
    student = nullptr;
    if(op == 2) {
        std::ifstream file("salvare.json");
        if(file) {
            incarcaJoc();
            std::cout << "\nApasa ENTER pentru a reintra in sesiune...";
            std::cin.get();
            return;
        } else {
            std::cout << RED << "Nu s-a gasit nicio salvare. Incepem un joc nou!\n\n";
        }
    }

    std::string nume_student;
    std::cout << "Salutare, student! Bag de seama ca esti aici pentru a te inscrie la sesiunea de examene din acest semestru! Spune-mi numele tau, te rog: ";
    std::getline(std::cin, nume_student);
    std::string specializare;
    std::cout << "Perfect, " << nume_student << "! Acum spune-mi si specializarea ta: ";
    std::getline(std::cin, specializare);
    int an_studiu;
    std::cout << "Ultimul lucru, spune-mi in ce an de studiu esti: ";
    std::cin >> an_studiu;
    std::cin.ignore(10000, '\n');
    student = new Student(nume_student, 150, 20, specializare, an_studiu, 0, 0.0);
    ghiozdan = new Ghiozdan<Item>(5);
    std::cout << "Regulile sunt simple. Sesiunea aceasta trebuie sa strangi 20 de credite pentru a promova.\n";
    std::cout << "Poti sa redai examene, nu conteaza la ce materii le iei atat timp cat atingi pragul de credite\n";
    std::cout << "Insa ai grija, zilele acestea orice te costa energie. Daca ramai pe 0... ne vedem la toamna.\n";
    std::cout << "Apasa ENTER pentru a incepe tortura...";
    std::cin.get();

};

void GameManager::afiseazaMeniu() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    std::cout << "\n[=============COLTUL LUI " << student->getNume() << " DE STUDIU=============]\n";
    std::cout << "1. " << BLUE << "Vezi status student" << RESET << "\n";
    std::cout << "2. " << BLUE << "Invata" << RESET << " (perzi de 2 ori energie si castigi de 3 ori stres)\n";
    std::cout << "3. " << RED << "!!!---MERGI LA EXAMEN---!!!" << RESET << "\n";
    std::cout << "4. " << BLUE << "Relaxare " << RESET <<  "(-20 lei)\n";
    std::cout << "5. " << BLUE << "Magazin de aprovizionare" << RESET << "\n";
    std::cout << "|==============================================|\n";
    std::cout << "6. " << YELLOW << "Salveaza progresul jocului" << RESET << "\n";
    std::cout << "7. " << YELLOW << "Incarca progres" << RESET << "\n";
    std::cout << "8. " << BLUE << "Retrage-ti dosarul de la facultate" << RESET << " (Iesire)\n";
    std::cout << "[==============================================]\n";
};

void GameManager::magazin() {
    std::cout << "[================MAGAZIN================]\n";
    std::cout << YELLOW << "Bani in portofel: " << RESET << student->getBani() << " lei\n";
    std::cout << "1. Cumpara Cafea (-20 lei, Energie +20)\n";
    std::cout << "2. Cumpara Sticla de Apa (-7 lei, Energie +5)\n";
    std::cout << "3. Cumpara Copiuta (-40 lei, pentru examene scrise si grila (din surse sigure evident))\n";
    std::cout << "Alegerea ta: ";
    int op;
    std::cin >> op;
    try {
        if(op == 1) {
            if(student->getBani() < 20) {
                std::cout << "Nu ai destui bani pentru o cafea.\n";
            }
            else {
                student->modificaBani(-20);
                ghiozdan->adauga(new Cafea());
            }
        }
        else if (op == 2) {
                if(student->getBani() < 7) {
                std::cout << "Nu ai destui bani pentru o apa (chiar asa?).\n";
            }
            else {
                student->modificaBani(-7);
                ghiozdan->adauga(new SticlaApa());
            }
        }
        else if(op == 3) {
            if(student->getBani() < 40) {
                std::cout << "Vezi ca astea sunt scumpe vere, nu cresc in copaci.\n";
            }
            else {
                student->modificaBani(-40);
                ghiozdan->adauga(new Copiuta());
            }
        }
    } catch (const std::exception& e) {
        std::cout << "Eroare: " << e.what() << "\n";
    }

};

void GameManager::evenimentAleatoriu() {
    int sansa = rand() % 100;
    if(sansa < 20) {
        int tip = rand() % 2;
        std::cout << "\n[EVENIMENT NEASTEPTAT] \n";
        if(tip == 0) {
            std::cout << "Ai gasit 15 lei pe jos. Brusc nu te mai simti sarac.\n";
            student->modificaBani(15);
        }
        else if(tip == 1) {
            std::cout << "Profesorul a intarziat 20 de minute. Ai dormit cu capul pe banca. (+10 energie)\n";
            student->modificaEnergie(10);
        }
    }
};

void GameManager::pornesteJocul() {
    int optiune = 0;
    while(optiune != 8) {
        evenimentAleatoriu();
        afiseazaMeniu();
        std::cin >> optiune;
        switch(optiune) {
            case 1:
                student->afiseaza_status();
                break;
            case 2: {
                int ore = 0;
                std::cout << "Cate ore vrei sa inveti?: \n";
                std::cin >> ore;
                if(ore > 0) {
                    std::cout << "Vei avea nevoie de " << 2*ore << " energie si iti va aduce " << 3 * ore << " stres. Confirmi?\n";
                    std::cout << "Apasa 1 pentru DA sau 0 pentru NU\n";
                    int inp;
                    std::cin >> inp;
                    if(inp == 1) {
                        student->invata(ore);
                    } else {
                        std::cout << "E ok daca te-ai razgandit. Poti invata altcandva.\n";
                    }
                }
                break;
            }
            case 3: {
                Examen* e = ExamenFactory::genereazaExamenAleatoriu();
                e->sustineExamen(student, ghiozdan);
                delete e;
                if(student->getCredite() >= 20) {
                    std::cout << "\n================================\n";
                    std::cout << "FELICITARI! Ai adunat " << student->getCredite() << " credite!\n";
                    std::cout << "Ai promovat anul si ai scapat de sesiune (deocamdata...)!!\n";
                    std::cout << "\n================================\n";
                    optiune = 7;
                }
                break;
            }
            case 4: {
                if(student->getBani() < 20) {
                    std::cout << "Nu ai destui bani ca sa te relaxezi in oras. Fa rost de bani\n";
                }
                else {
                    std::cout << "Te va costa 20 de lei o iesire in oras care sa iti scada stresul. Accepti? (1 pentru DA sau 0 pentru NU)\n";
                    int op;
                    std::cin >> op;
                    if(op) {
                        student->modificaBani(-20);
                        student->relaxare();
                    }
                    break;
                }
            }

            case 5:
                magazin();
                break;
            case 6: 
                salveazaJoc();
                break;
            case 7:
                incarcaJoc();
                break;
            case 8:
                std::cout << "Te mai asteptam pe la examen (nu scapi asa usor)\n";
                break;
            default:
                std::cout << "Optiune invalida\n";
        }

        if(student->getEnergie() <= 0) {
            std::cout << "\n==================================================\n";
            std::cout << RED << "[GAME OVER] " << RESET << "Ai ramas complet fara energie. Ai adormit pe holurile facultatii si te-au exmatriculat.";
            std::cout << "\n==================================================\n";
            std::cout << "\nApasa ENTER pentru a iesi...";
            std::cin.ignore(10000, '\n'); 
            std::cin.get();
            optiune = 8;
        }
        else if(student->getStresCurent() >= 25) {
            std::cout << "\n==================================================\n";
            std::cout << RED << "[GAME OVER] " << RESET << "Burnout total!!. Stresul a ajuns la " << student->getStresCurent() << "\n";
            std::cout << "Ai cedat nervos, ti-ai impachetat lucrurile si te-ai intors acasa.\n";
            std::cout << "==================================================\n";
            std::cout << "\nApasa ENTER pentru a iesi...";
            std::cin.ignore(10000, '\n'); 
            std::cin.get();
            optiune = 8;
        }

        if (optiune != 8) { 
            std::cout << "\nApasa ENTER pentru a continua...";
            std::cin.ignore(10000, '\n'); 
            std::cin.get();             
        }
    }
};

void GameManager::salveazaJoc() {
    json j;
    j["nume"] = student->getNume();
    j["specializare"] = student->getSpecializare();
    j["an_studiu"] = student->getAnStudiu();
    j["energie"] = student->getEnergie();
    j["stres"] = student->getStresCurent();
    j["bani"] = student->getBani();
    j["credite"] = student->getCredite();
    j["bonus"] = student->getBonus();
    j["medie"] = student->getMedieGenerala();
    json iteme = json::array();
    for(int i = 0; i < ghiozdan->getNrElemente(); ++i) {
        iteme.push_back(ghiozdan->inspectElement(i)->getNume());
    }
    j["inventar"] = iteme;
    std::ofstream file("salvare.json");
    file << j.dump(4);
    std::cout << YELLOW << "[ATENTIE] Progres salvat!" << RESET << "\n";

};

void GameManager::incarcaJoc() {
    std::ifstream file("salvare.json");
    if(!file) {
        std::cout << RED << "Nu exista progres de joc salvat" << RESET << "\n";
        return;
    }
    json j;
    file >> j;
    if(student != nullptr) { 
        delete student;
    }
    student = new Student(j["nume"], j["energie"], 20, j["specializare"], j["an_studiu"], j["credite"], j["medie"]);
    student->setStres(j["stres"]);
    student->setBani(j["bani"]);
    student->setBonus(j["bonus"]);

    delete ghiozdan;
    ghiozdan = new Ghiozdan<Item>(5);
    if(j.contains("inventar")) {
        for(const auto& nume_item : j["inventar"]) {
            if(nume_item == "Cafea") {
                ghiozdan->adauga(new Cafea());
            }
            else if(nume_item == "Sticla de Apa") {
                ghiozdan->adauga(new SticlaApa());
            }
            else if(nume_item == "Copiuta") {
                ghiozdan->adauga(new Copiuta());
            }
        }
    }

    std::cout << BLUE << "[ATENTIE] Progres incarcat cu succes!" << RESET << "\n";
    
};

GameManager::~GameManager(){
    delete student;
    delete ghiozdan;
}
