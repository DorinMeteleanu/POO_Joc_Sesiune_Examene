#include "tipuriExamen.h"
#include "ghiozdan.h"
#include <iostream>
#include <cstdlib>

//EXAMEN SCRIS
ExamenScris :: ExamenScris(std::string materie) : Examen(materie, 60, 15, 5) {}
void ExamenScris::sustineExamen(Student* student, Ghiozdan<Item>* ghiozdan) {
    int dificultate = getDificultate();
    std::cout << "==================================\n";
    std::cout << "INCEPE EXAMENUL SCRIS LA " << getNume() << "!\n";
    std::cout << "Dificultate: " << dificultate << "\n";
    std::cout << "Tocmai ai primit foaia de examen! Timpul se scurge...\n";
    while (dificultate > 0 && student->getEnergie() > 0) {
        std::cout << "-> Dificultate ramasa: " << dificultate << "\n";
        std::cout << "-> Energia ramasa: " << student->getEnergie() << "\n";

        std::cout << "Alege o actiune: \n";
        std::cout << "1. Raspunzi la o cerinta (-15 dificultate, -10 energie, -15 timp)\n";
        std::cout << "2. Iei o pauza de respirat (+5 energie, -5 timp)\n";
        std::cout << "3. Incerci sa copiezi (Risc! 50% sanse de succes)\n";
        std::cout << "4. Folosesti un item de ajutor? (+? energie, -5 timp)\n";
        std::cout << "Alegerea ta: ";
        int alegere;
        std::cin >> alegere;

        if(alegere == 1) {
            std::cout << "\n[!] Ai umplut o pagina de formule!\n";
            dificultate -= 20;
            student->modificaEnergie(-10);
        }
        else if (alegere == 2) {
            std::cout << "\n[!] Te uiti pe pereti 5 minute sa te calmezi.\n";
            student->modificaEnergie(5);
        }
        else if(alegere == 3) {
            if(rand() % 2 == 0) {
                std::cout << "\n[SUCCESS] Ai vazut raspunsul! Scazi 30 pct din examen!\n";
                dificultate -= 30;
            }
            else {
                std::cout << "\n[FAIL] Ai primit avertisment! Te-ai panicat maxim si pierzi 20 energie!\n";
                student->modificaEnergie(-20);
                dificultate += 10;
            }
        }
        else if(alegere == 4) {
            if(ghiozdan->esteGol()) {
                std::cout << "\n[!] Ghiozdanul tau este gol! Nu ai ce folosi!\n";
                continue;
            }
            std::cout << "[!] Ce item doresti sa folosesti? \n";
            ghiozdan->afiseazaElemente();
            std::cout << "Alegerea ta: ";
            int index_item;
            std::cin >> index_item;
            // cautare obiect, adaug mai tarziu logica
            
        }
        else {
            std::cout << "Alegere invalida. Pierzi timpul!\n";
        }
        std::cout << "-> Stresul examenului iti mai consuma 5 energie.\n";
        student->modificaEnergie(-5);
    }
    if (student->getEnergie() <= 0) {
        std::cout << "\n[GAME OVER] Ai cedat nervos la " << getNume() << "...\n";
    } else if (dificultate <= 0) {
        std::cout << "\n[VICTORIE] Ai luat examenul la " << getNume() << "! Castigi " << getCredite() << " credite!\n";
    }
};

//EXAMEN ORAL

//EXAMEN GRILA