#include "tipuriExamen.h"
#include "ghiozdan.h"
#include <iostream>
#include <cstdlib>
#include "ui_util.h"
#include "tipuriProfesor.h"

//EXAMEN SCRIS
ExamenScris::ExamenScris(std::string materie, Profesor* p) : Examen(materie, 60, 30, 5, p) {}
void ExamenScris::sustineExamen(Student* student, Ghiozdan<Item>* ghiozdan) {
    int dificultate = getDificultate();
    std::cout << "===================================================================================\n";
    std::cout << "INCEPE EXAMENUL SCRIS LA " << getNume() << "!\n";
    std::cout << "Dificultate: " << dificultate << "\n";
    profesor->afiseaza_status();
    std::cout << "Examenele scrise sunt foarte grele si mananca multa energie, dar valoreaza multe credite.\n";
    std::cout << "Ai grija cum iti gestionezi energia. Unoeri, nu se stie cand, stresul examenului iti va lua automat putin din energie.\n";
    std::cout << "Sfat: Cand nu stai foarte bine cu energia, mai bine te concentrezi sa scapi de examen cu riscul de a nu lua creditele.\n";
    std::cout << "\nApasa ENTER pentru a continua...";
    std::cin.ignore(10000, '\n'); 
    std::cin.get(); 

    std::cout << "Tocmai ai primit foaia de examen! Timpul se scurge...\n";
    while (dificultate > 0 && student->getEnergie() > 0) {
        std::cout << "-> Dificultate ramasa: " << dificultate << "\n";
        std::cout << "-> Energia ramasa: " << student->getEnergie() << "\n\n";

        std::cout << "Alege o actiune: \n";
        std::cout << "1. Raspunzi la o cerinta (-15 dificultate, -20 energie)\n";
        std::cout << "2. Iei o pauza de respirat (+5 energie)\n";
        std::cout << "3. Incerci sa copiezi (Risc! 50 la suta sanse de succes)\n";
        std::cout << "4. Folosesti bonus de pregatire din ce ai studiat acasa (-7 bonus, -10 dificulate)\n";
        std::cout << "5. Folosesti un item de ajutor? (+? energie)\n";
        std::cout << "Alegerea ta: ";
        int alegere;
        std::cin >> alegere;

        if(alegere == 1) {
            std::cout << "\n[!] Ai umplut o pagina de formule!\n";
            dificultate -= 15;
            student->modificaEnergie(-20);
        }
        else if (alegere == 2) {
            std::cout << "\n[!] Te uiti pe pereti 5 minute sa te calmezi.\n";
            student->modificaEnergie(5);
        }
        else if(alegere == 3) {
            if(rand() % 2 == 0) {
                std::cout << "\n" << GREEN << "[SUCCESS] " << RESET << "Ai vazut raspunsul! Scazi 30 pct din examen!\n";
                dificultate -= 30;
            }
            else {
                std::cout << "\n" << RED << "[FAIL] " << RESET <<  "Ai primit avertisment! Te-ai panicat maxim, pierzi 20 energie, iar profesorul 10 rabdare!\n";
                student->modificaEnergie(-20);
                profesor->scadeRabdare(10);
                dificultate += 10;
            }
        }
        else if(alegere == 4) {
            int bonus = student->getBonus();
            if(bonus <= 6) {
                std::cout << YELLOW << "Nu te-ai pregatit suficient acasa. Nu ai destul bonus. loser loser\n" << RESET;
                continue;
            }
            else {
                dificultate -= 10;
                student->reseteazaBonus(7);
                if(dificultate < 5) {
                    dificultate = 5;
                }
            }
        }
        else if(alegere == 5) {
            if(ghiozdan->esteGol()) {
                std::cout << "\n[!] Ghiozdanul tau este gol! Nu ai ce folosi!\n";
                continue;
            }
            std::cout << "[!] Ce item doresti sa folosesti? \n";
            ghiozdan->afiseazaElemente();
            std::cout << "Alegerea ta: ";
            int index_item;
            std::cin >> index_item;
            try {
                Item* it = ghiozdan->getElement(index_item);
                it->foloseste(student, dificultate);
                delete it;
            } catch (const std::out_of_range& e) {
                    std::cout << "Index invalid! Pierzi timpul!\n";
            }
            
        }
        else {
            std::cout << "Alegere invalida. Pierzi timpul!\n";
        }
        profesor->reactioneaza(student, dificultate);
    }
    if (student->getEnergie() <= 0) {
        std::cout << "\n[GAME OVER] Ai cedat nervos la " << getNume() << "...\n";
    } else if (dificultate <= 0) {
        std::cout << "\n[VICTORIE] Ai luat examenul la " << getNume() << "! Castigi " << getCredite() << " credite!\n";
        student->adaugaCredite(getCredite());
        std::cout << "Total de credite curent: " << student->getCredite() << "\n";
    }
};

//EXAMEN ORAL
ExamenOral::ExamenOral(std::string materie, Profesor* p) : Examen(materie, 30, 10, 2, p) {}
void ExamenOral::sustineExamen(Student* student, Ghiozdan<Item>* ghiozdan) {
    std::cout << "==========================================================================\n";
    std::cout << "INCEPE EXAMENUL ORAL LA " << getNume() << "!\n";
    std::cout << "Dificultate: " << getDificultate() << "\n";
    std::cout << "Acest tip de examen este destul de usor de trecut, in consecinta nu valoreaza prea multe credite.\n";
    std::cout << "Te poti folosi si de noroc, insa aici conteaza foarte mult si de profesorul la care pici sa dai examenul oral.\n";
    std::cout << "\nApasa ENTER pentru a continua...";
    std::cin.ignore(10000, '\n'); 
    std::cin.get(); 
    std::cout << "Tocmai ai intrat in sala de examen! Profesorul incepe sa iti adreseze intrebari...\n";
    int dificultate = getDificultate();
    while (dificultate > 0 && student->getEnergie() > 0) {
        std::cout << "-> Dificultate ramasa: " << dificultate << "\n";
        std::cout << "-> Energia ramasa: " << student->getEnergie() << "\n";
        std::cout << "Alege o actiune: \n";
        std::cout << "1. Raspunzi direct la o intrebare (-10 dificultate, -15 energie) \n";
        std::cout << "2. Zambesti carismatic sperand sa te ajute (-5 energie, -10 dificultate (dar cu 50 la suta sanse)) \n";
        std::cout << "3. Folosesti bonus de pregatire din ce ai studiat acasa (-5 bonus, -5 dificultate) \n";
        std::cout << "4. Ceri voie la un item de ajutor? (50 la suta sanse sa te lase) \n";
        int alegere;
        std::cin >> alegere;

        if(alegere == 1) {
            std::cout << "\n[!] Profesorul pare impresionat. Tine-o tot asa daca poti!\n";
            dificultate -= 10;
            student->modificaEnergie(-15);
        }
        else if(alegere == 2) {
            if(rand() % 2 == 0) {
                std::cout << "\n[SUCCESS] Proful te vede emotionat, te iarta pentru intrebarea asta si trece la urmatoarea!\n";
                dificultate -= 10;
                student->modificaEnergie(-5);
            }
            else {
                std::cout << "\n[FAIL] Degeaba, nu-l poti fenta de data asta!\n";
                student->modificaEnergie(-5);
            }
        }
        else if(alegere == 3) {
            int bonus = student->getBonus();
            if(bonus <= 4) {
                std::cout << "Nu te-ai pregatit suficient acasa. Nu ai destul bonus. loser loser\n";
                continue;
            }
            else {
                dificultate -= 5;
                student->reseteazaBonus(5);
                if(dificultate < 5) {
                    dificultate = 5;
                }
            }
        }
        else if(alegere == 4) {
            if(rand() % 2 == 0) {
                if(ghiozdan->esteGol()) {
                    std::cout << "\n[!] Ghiozdanul tau este gol! Nu ai ce folosi!\n";
                    continue;
                }
                std::cout << "[!] Hai ca te lasa. Ce item doresti sa folosesti? \n";
                ghiozdan->afiseazaElemente();
                std::cout << "Alegerea ta: ";
                int index_item;
                std::cin >> index_item;
                try {
                    Item* it = ghiozdan->getElement(index_item);
                    it->foloseste(student, dificultate);
                    delete it;
                } catch (const std::out_of_range& e) {
                    std::cout << "Index invalid! Pierzi timpul!\n";
                }
            }
            else {
                std::cout << "\n[FAIL] Profesorul nu te lasa sa folosesti niciun item! Trebuie sa te descurci singur!\n";
            }
            
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
        student->adaugaCredite(getCredite());
        std::cout << "Total de credite curent: " << student->getCredite() << "\n";
    }
};


//EXAMEN GRILA
ExamenGrila::ExamenGrila(std::string materie, Profesor* p) : Examen(materie, 40, 20, 3, p) {}
void ExamenGrila::sustineExamen(Student* student, Ghiozdan<Item>* ghiozdan) {
    std::cout << "==========================================================================\n";
    std::cout << "INCEPE EXAMENUL GRILA LA " << getNume() << "!\n";
    std::cout << "Dificultate: " << getDificultate() << "\n";
    std::cout << "Nu te stresa foarte tare, examenul grila e examen grila.\n";
    std::cout << "Acest examen este mai simplu decat unul scris, dar nu lasa garda jos, are si el un nr cinstit de credite\n";
    std::cout << "Acest tip de examen are corectura la final, dar vei vedea in timp real cate raspunsuri corecte ai.\n";
    std::cout << "Iti trebuie mai mult de 3 grile corecte pentru a lua creditele!\n";
    std::cout << "\nApasa ENTER pentru a continua...";
    std::cin.ignore(10000, '\n'); 
    std::cin.get(); 
    std::cout << "Tocmai ai primit foaia de examen cu grile! Timpul se scurge...\n";

    int dificultate = getDificultate();
    int grile = 0;
    while (dificultate > 0 && student->getEnergie() > 0) {
        std::cout << "-> Dificultate ramasa: " << dificultate << "\n";
        std::cout << "-> Energia ramasa: " << student->getEnergie() << "\n";
        std::cout << "-> Grile corecte: " << grile << "\n";
        std::cout << "Alege o actiune: \n";
        std::cout << "1. Rezolvi corect o grila (umpli o ciorna si afli rezultatul bun) (-10 dificultate, -10 energie, +1 grila corecta) \n";
        std::cout << "2. Ghicesti la intamplare (-10 dificultate, -5 energie, 50 la suta sanse de corectitudine)\n";
        std::cout << "3. Folosesti bonus de pregatire din ce ai studiat acasa (-5 bonus, -10 dificultate, +1 grila corecta)\n";
        std::cout << "4. Folosesti un item de ajutor? \n";

        int alegere;
        std::cin >> alegere;
        if(alegere == 1) {
            std::cout << "\n[!] Ti-a dat bine intr-un final, pune raspunsul in caseta!!\n";
            dificultate -= 10;
            student->modificaEnergie(-10);
            grile++;
        }
        else if(alegere == 2) {
            if(rand() % 2 == 0) {
                std::cout << "\n[SUCCESS] Se pare ca in final acest raspuns a fost corect!\n";
                dificultate -= 10;
                student->modificaEnergie(-5);
                grile++;
            }
            else {
                std::cout << "\n[FAIL] Womp womp...aceasta grila a fost corectata ca fiind gresita!\n";
                dificultate -= 10;
                student->modificaEnergie(-5);

            }
        }
        else if(alegere == 3) {
            int bonus = student->getBonus();
            if(bonus <= 4) {
                std::cout << "Nu te-ai pregatit suficient acasa. Nu ai destul bonus. loser loser\n";
                continue;
            }
            else {
                dificultate -= 10;
                student->reseteazaBonus(5);
                grile++;
            }
        }
        else if(alegere == 4) {
            if(ghiozdan->esteGol()) {
                std::cout << "\n[!] Ghiozdanul tau este gol! Nu ai ce folosi!\n";
                continue;
            }
            std::cout << "[!] Hai ca te lasa. Ce item doresti sa folosesti? \n";
            ghiozdan->afiseazaElemente();
            std::cout << "Alegerea ta: ";
            int index_item;
            std::cin >> index_item;
            try {
                Item* it = ghiozdan->getElement(index_item);
                it->foloseste(student, dificultate);
                delete it;
            } catch (const std::out_of_range& e) {
                std::cout << "Index invalid! Pierzi timpul!\n";
            }
            
        }
        else {
            std::cout << "Alegere invalida. Pierzi timpul!\n";
        }
        profesor->reactioneaza(student, dificultate);
    }
    if (student->getEnergie() <= 0) {
        std::cout << "\n[GAME OVER] Ai cedat nervos la " << getNume() << "...\n";
    } else if (dificultate <= 0 ) {
        if(grile >= 3) {
            std::cout << "\n[VICTORIE] Ai luat examenul la " << getNume() << "! Castigi " << getCredite() << " credite!\n";
            student->adaugaCredite(getCredite());
            std::cout << "Total de credite curent: " << student->getCredite() << "\n";
        }
        else {
            std::cout << "\n[FAIL] Nu ai destule grile corecte, nu iei creditele, dar continui jocul";
        }
    }

};