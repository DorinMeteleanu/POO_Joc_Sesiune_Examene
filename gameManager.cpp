#include "gameManager.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <stdexcept>
#include "ui_util.h"
#include "strategieInvatare.h"
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
    std::cout << "SIMULATOR DE SESIUNE (JOC HORROR)\n";
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
    std::cout << "\n[<><><><><><><><><>COLTUL LUI " << student->getNume() << " DE STUDIU<><><><><><><><><>]\n";
    std::cout << "1. Vezi status student\n";
    std::cout << "2. Invata (perzi de 2 ori energie si castigi de 3 ori stres)\n";
    std::cout << "3. !!!---MERGI LA EXAMEN---!!!\n";
    std::cout << "4. Relaxare (-20 lei)\n";
    std::cout << "5. Magazin de aprovizionare\n";
    std::cout << "6. Vezi ce iteme ai in ghiozdan\n";
    std::cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><>\n";
    std::cout << "7. " << YELLOW << "Salveaza progresul jocului" << RESET << "\n";
    std::cout << "8. " << YELLOW << "Incarca progres" << RESET << "\n";
    std::cout << "9. " << YELLOW << "Retrage-ti dosarul de la facultate" << RESET << " (Iesire)\n";
    std::cout << "10. " << YELLOW << "TIPS" << RESET << "\n";
    std::cout << "[<><><><><><><><><><><><><><><><><><><><><><><><><><><>]\n";
};

void GameManager::magazin() {
    std::cout << "[><><><><><><><><MAGAZIN><><><><><><><><]\n";
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
    if(rand() % 4 == 1) {
        int tip = rand() % 2;
        std::cout << MAGENTA << "\n[EVENIMENT NEASTEPTAT] \n" << RESET;
        if(tip == 0) {
            std::cout << "Ai gasit 15 lei pe jos. Brusc nu te mai simti sarac.\n";
            student->modificaBani(15);
        }
        else if(tip == 1) {
            std::cout << "Profesorul a intarziat 20 de minute. Ai dormit cu capul pe banca. (+10 energie)\n";
            student->modificaEnergie(10);
        }
        std::cout << "\nApasa ENTER pentru a continua...";
            std::cin.ignore(10000, '\n'); 
            std::cin.get(); 
    }
};

void GameManager::pornesteJocul() {
    int optiune = 0;
    while(optiune != 9) {
        evenimentAleatoriu();
        afiseazaMeniu();
        std::cin >> optiune;
        switch(optiune) {
            case 1:
                student->afiseaza_status();
                break;
            case 2: {
                std::cout << "Alege stilul: 1. Normal (CD: " << student->getSTNormal() << ") | 2. Hardcore (CD: " << student->getSTHardcore() << ") | 3. Relaxat (CD: " <<
      student->getSTRelaxat() << ")\n";
                int stil;
                std::cin >> stil;
                if(stil == 1 && student->getSTNormal() > 0) {
                    std::cout << YELLOW << "[!] Epuizat! Mai ai de dat " << student->getSTNormal() << " examene.\n" << RESET;
                    break;
                }
                if(stil == 2 && student->getSTHardcore() > 0) {
                    std::cout << YELLOW << "[!] Epuizat! Mai ai de dat " << student->getSTHardcore() << " examene.\n" << RESET;
                    break;
                }
                if(stil == 1 && student->getSTRelaxat() > 0) {
                    std::cout << YELLOW << "[!] Epuizat! Mai ai de dat " << student->getSTRelaxat() << " examene.\n" << RESET;
                    break;
                }
                if(stil == 1) {
                    student->setStrategie(new StrategieNormala()); 
                    student->setSTNormal(2); 
                }
                if(stil == 2) {
                    student->setStrategie(new StrategieHardcore()); 
                    student->setSTHardcore(3); 
                }
                if(stil == 3) {
                    student->setStrategie(new StrategieRelaxata()); 
                    student->setSTRelaxat(1); 
                }
                student->invata(5);
                break;

            }
            case 3: {
                Examen* e = ExamenFactory::genereazaExamenAleatoriu();
                e->sustineExamen(student, ghiozdan);
                delete e;
                if(student->getCredite() >= 20) {
                    std::cout << "\n[!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!]\n";
                    std::cout << GREEN << "FELICITARI!" << RESET << "Ai adunat " << student->getCredite() << " credite!\n";
                    std::cout << "Ai promovat anul si ai scapat de sesiune (deocamdata...)!!\n";
                    std::cout << "\n[!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!]\n";
                    optiune = 7;
                }
                student->scadeCooldowns();
                break;
            }
            case 4: {
                if(student->getBani() < 20) {
                    std::cout << YELLOW << "[!] Nu ai destui bani ca sa te relaxezi in oras. Fa rost de bani\n" << RESET;
                }
                else {
                    std::cout << "[!] Te va costa 20 de lei o iesire in oras care sa iti scada stresul. Accepti? (1 pentru DA sau 0 pentru NU)\n";
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
            case 6: {
            if(ghiozdan->esteGol()) {
                std::cout << YELLOW << "\n[!] Ghiozdanul tau este gol! Ar fi o idee buna sa cumperi niste iteme pentru examen!\n" << RESET;
                continue;
            }
            std::cout << "[><><><><><><><><GHIOZDANUL LUI " << student->getNume() << "><><><><><><><><\n";
            ghiozdan->afiseazaElemente();
            break;

            }
            case 7: 
                salveazaJoc();
                break;
            case 8:
                incarcaJoc();
                break;
            case 9:
                std::cout << "[hehe] Te mai asteptam pe la examene (nu scapi asa usor)\n";
                std::cout << "\nApasa ENTER pentru a iesi din joc...";
                std::cin.ignore(10000, '\n'); 
                std::cin.get();
                break;
            case 10:
                tips();
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
            optiune = 9;
        }
        else if(student->getStresCurent() >= 25) {
            std::cout << "\n==================================================\n";
            std::cout << RED << "[GAME OVER] " << RESET << "Burnout total!!. Stresul a ajuns la " << student->getStresCurent() << "\n";
            std::cout << "Ai cedat nervos, ti-ai impachetat lucrurile si te-ai intors acasa.\n";
            std::cout << "==================================================\n";
            std::cout << "\nApasa ENTER pentru a iesi...";
            std::cin.ignore(10000, '\n'); 
            std::cin.get();
            optiune = 9;
        }

        if (optiune != 8) { 
            std::cout << "\nApasa ENTER pentru a continua...";
            std::cin.ignore(10000, '\n'); 
            std::cin.get();             
        }
    }
};

void GameManager::tips() {
    std::cout << YELLOW << "INFORMATII UTILE\n\n" << RESET;
    std::cout << "Ai 3 tipuri de examene pe care le poti sustine: Scris, Oral, Grila. indiferent de tip, trebuie sa nu ramai cu energia la 0.\n";
    std::cout << "De asemenea sunt 2 tipuri de profesor care te pot asista la examen: cel Exigent (Ionescu) si cel Relaxat (Popescu), fiecare cu tabieturile sale\n";
    std::cout << "Daca il prinzi pe cel exigent, ai grija cum iti gestionezi resursele, este foarte imprevizibil.\n\n";
    std::cout << "Examenul scris este cel mai lung, sa raspunzi direct la o intrebare te costa foarte multa energie...\n";
    std::cout << "Examenul se termina daca reusesti sa reduci dificultatea acestuia la 0.\n";
    std::cout << "Fie te echipezi bine cu resurse, fie mergi pe putin noroc.\n\n";
    std::cout << "Examenul oral este mai simplu, dar depinde mult de tipul de profesor pe care il prinzi.\n";
    std::cout << "La fel, trebuie sa reduci dificultatea examenului la 0, dar ai grija si la rabdarea profesorului, aceasta NU trebuie sa ajunga la 0.\n\n";
    std::cout << "La examenul grila raspunzi la...grile. Diferenta e ca odata ce ai invins examenul, la final, trebuie sa ai peste 3 grile corecte ca sa aduni creditele.\n\n";
    std::cout << "Daca reusesti sa iei note mari, asta fiind usor daca dispui de resurse multe, poti primi o anumita bursa care sa te ajute sa mai iei cateva iteme.\n";
    std::cout << "Nu uita sa te echipezi cu iteme inainte sa intri intr-un examen.\n";
    std::cout << "Fii mereu atent la nivelul de resurse ramas.\n\n";
    std::cout << "Spor la strans credite!!\n";
    std::cout << "\nApasa ENTER pentru a continua...";
    std::cin.ignore(10000, '\n'); 
    std::cin.get();
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
