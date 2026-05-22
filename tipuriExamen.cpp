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
    std::cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n";
    std::cout << "Dificultate: " << dificultate << "\n";
    profesor->afiseaza_status();
    std::cout << "Examenele scrise sunt foarte grele si mananca multa energie, dar valoreaza multe credite.\n";
    std::cout << "Ai grija cum iti gestionezi energia. Unoeri, nu se stie cand, stresul examenului iti va lua automat putin din energie.\n";
    std::cout << "Ai grija sa nu tragi mult de timp, cu cat mai multe ture trec cu atat nota iti scade\n";
    std::cout << "Sfat: Cand nu stai foarte bine cu energia, mai bine te concentrezi sa scapi de examen cu riscul de a nu lua creditele.\n";
    std::cout << "\nApasa ENTER pentru a continua...";
    std::cin.ignore(10000, '\n'); 
    std::cin.get(); 
    int cooldown_relaxare = 0;
    int cooldown_item = 0;
    int ture = 0;

    std::cout << "\nTocmai ai primit foaia de examen! Timpul se scurge...\n";
    while (dificultate > 0 && student->getEnergie() > 0) {
        std::cout << "-> Dificultate ramasa: " << dificultate << "\n";
        std::cout << "-> Ture parcurse: " << ture << "\n";
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
            std::cout << BLUE << "\n[!] Ai umplut o pagina de formule!\n" << RESET;
            dificultate -= 15;
            student->modificaEnergie(-20);
            cooldown_relaxare--;
            cooldown_item--;
        }
        else if (alegere == 2) {
            if(cooldown_relaxare > 0) {
                std::cout << YELLOW << "\n[?] Prea devreme! Profesorul se uita urat la tine daca mai iei o pauza acum. Ateapta o tura\n" << RESET;
            } else {
                std::cout << "\n[!] Te uiti pe pereti 5 minute sa te calmezi.\n";
                student->modificaEnergie(5);
                cooldown_relaxare = 2;
                
            }
        }
        else if(alegere == 3) {
            if(rand() % 2 == 0) {
                std::cout << "\n" << BLUE << "[SUCCESS] " << RESET << "Ai vazut raspunsul! Scazi 30 pct din examen!\n";
                dificultate -= 30;
            }
            else {
                std::cout << "\n" << YELLOW << "[FAIL] " << RESET <<  "Ai primit avertisment! Te-ai panicat maxim! (-20 energie, +10 dificultate, -15 rabdare profesor)\n";
                student->modificaEnergie(-20);
                profesor->scadeRabdare(15);
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
            if(cooldown_item > 0) {
                std::cout << YELLOW << "\nE prea devreme sa folosesti un item. Mai asteapta " << RESET << cooldown_item << YELLOW << " ture\n" << RESET;
            }
            if(ghiozdan->esteGol()) {
                std::cout << YELLOW << "\n[!] Ghiozdanul tau este gol! Nu ai ce folosi!\n" << RESET;
                continue;
            }
            std::cout << "\n[!] Ce item doresti sa folosesti? \n";
            ghiozdan->afiseazaElemente();
            std::cout << "Alegerea ta: ";
            int index_item;
            std::cin >> index_item;
            try {
                Item* it = ghiozdan->getElement(index_item);
                it->foloseste(student, dificultate);
                delete it;
            } catch (const std::out_of_range& e) {
                    std::cout << "\nIndex invalid! Pierzi timpul!\n";
            }
            cooldown_item = 3;
        }
        else {
            std::cout << "\nAlegere invalida. Pierzi timpul!\n";
        }
        profesor->reactioneaza(student, dificultate);
        if (cooldown_relaxare > 0 && alegere != 2) cooldown_relaxare--;
        if (cooldown_item > 0 && alegere != 2) cooldown_item--;
        ture++;
        if(rand() % 4) {
            std::cout << YELLOW << "\n[!] Stresul examenului iti mai mananca 5 energie" << RESET;
            student->modificaEnergie(-5);
        }

        std::cout << "\nApasa ENTER pentru a continua...";
        std::cin.ignore(10000, '\n'); 
        std::cin.get(); 
    }

    if (student->getEnergie() <= 0) {
        std::cout << RED << "\n[GAME OVER] Ai cedat nervos la " << getNume() << "...\n" << RESET;
    } else if (profesor->getRabdare() <=0){
        std::cout << RED << "\n[!!!!!!!!] Profesorul ti-a dat prea multe avertismente. Nu te mai poate ierta acum, esti exmatriculat hahaha.\n" << RESET;
        profesor->exmatriculeaza(student);
    } else if (dificultate <= 0) {
        std::cout << GREEN << "\n[VICTORIE] Ai luat examenul la " << getNume() << "! Castigi " << getCredite() << " credite!\n" << RESET;
        student->adaugaCredite(getCredite());
        std::cout << "Total de credite curent: " << student->getCredite() << "\n";
        int nota = profesor->puneNotaScris(ture);
        std::cout << YELLOW << "[CATALOG]" << RESET << "Profesorul " << profesor->getTitluComplet() << " ti-a trecut nota " << nota << " in carnet.\n";
        student->adaugaNota(nota);
        if(nota > 7) {
            std::cout << "[!] O nota ca asta iti asigura o bursa. Castigi 15 lei (nu te duce in Afi ca ramai fara ei)\n";
            student->modificaBani(15);
        }
    }
};

//EXAMEN ORAL
ExamenOral::ExamenOral(std::string materie, Profesor* p) : Examen(materie, 40, 3, 2, p) {}
void ExamenOral::sustineExamen(Student* student, Ghiozdan<Item>* ghiozdan) {
    std::cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n";
    std::cout << "Dificultate: " << getDificultate() << "\n";
    profesor->afiseaza_status();
    std::cout << "Acest tip de examen este destul de usor de trecut, in consecinta nu valoreaza prea multe credite.\n";
    std::cout << "Te poti folosi si de noroc, insa aici conteaza foarte mult si de profesorul la care pici sa dai examenul oral (vezi cata rabdare are).\n";
    std::cout << "Ai grija sa nu ramana fara rabdare!!\n";
    std::cout << "\nApasa ENTER pentru a continua...";
    std::cin.ignore(10000, '\n'); 
    std::cin.get(); 
    std::cout << "Tocmai ai intrat in sala de examen! Profesorul incepe sa iti adreseze intrebari...\n";
    int dificultate = getDificultate();
    int cooldown_item = 0;
    while (dificultate > 0 && student->getEnergie() > 0 && profesor->getRabdare() > 0) {
        std::cout << "-> Dificultate ramasa: " << dificultate << "\n";
        std::cout << "-> Energia ramasa: " << student->getEnergie() << "\n";
        profesor->afiseaza_status();
        std::cout << "Alege o actiune: \n";
        std::cout << "1. Raspunzi direct la o intrebare (-10 dificultate, -15 energie, -5 rabdare) \n";
        std::cout << "2. Zambesti carismatic sperand sa te ajute (-5 energie, -10 dificultate (dar cu 50 la suta sanse)) \n";
        std::cout << "3. Folosesti bonus de pregatire din ce ai studiat acasa (-5 bonus, -5 dificultate) \n";
        std::cout << "4. Ceri voie la un item de ajutor? (50 la suta sanse sa te lase) \n";
        int alegere;
        std::cin >> alegere;

        if(alegere == 1) {
            std::cout << BLUE << "\n[!] Profesorul pare impresionat. Tine-o tot asa daca poti!\n" << RESET;
            dificultate -= 10;
            student->modificaEnergie(-15);
        }
        else if(alegere == 2) {
            if(rand() % 2 == 0) {
                std::cout << BLUE << "\n[SUCCESS] Proful te vede emotionat, te iarta pentru intrebarea asta si trece la urmatoarea!\n" << RESET;
                dificultate -= 10;
                student->modificaEnergie(-5);
            }
            else {
                std::cout << YELLOW << "\n[FAIL] Nu-l poti fenta de data asta, proful isi cam pierde din rabdare!\n" << RESET;
                student->modificaEnergie(-5);
                profesor->scadeRabdare(10);
            }
        }
        else if(alegere == 3) {
            int bonus = student->getBonus();
            if(bonus <= 4) {
                std::cout << YELLOW << "\n[!] Nu te-ai pregatit suficient acasa. Nu ai destul bonus. loser loser\n" << RESET;
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
                    std::cout << YELLOW << "\n[!] Ghiozdanul tau este gol! Nu ai ce folosi!\n" << RESET;
                    continue;
                }
                std::cout << BLUE << "\n[!] Hai ca te lasa. Ce item doresti sa folosesti? \n" << RESET;
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
                std::cout << YELLOW << "\n[FAIL] Profesorul nu te lasa sa folosesti niciun item! Trebuie sa te descurci singur!\n" << RESET;
            }
            
        }
        else {
            std::cout << "\nAlegere invalida. Pierzi timpul!\n";
        }
        if(rand() % 2) {
            std::cout << "-> Se vede ca proful incepe sa oboseasca. Ii scade 3 rabdare.";
            profesor->scadeRabdare(3);
        }
        if(rand() % 4 == 1) {
            std::cout << "-> Stresul examenului iti mai consuma 5 energie.\n";
            student->modificaEnergie(-stres_provocat);
        }
    }
    if (student->getEnergie() <= 0) {
        std::cout << RED << "\n[GAME OVER] Ai cedat nervos la " << getNume() << "...\n" << RESET;
    } else if(profesor->getRabdare() <=0) {
        std::cout << "\n[!] Profesorul s-a plictisit sa piarda timpul cu tine. Dar ai luat examenul.\n";
        int nota = profesor->puneNotaOral(dificultate);
        std::cout << YELLOW << "\n[CATALOG]" << RESET << "Profesorul " << profesor->getTitluComplet() << " ti-a trecut nota " << nota << " in carnet.\n";
        std::cout << "! Castigi " << getCredite() << " credite!\n";
        student->adaugaCredite(getCredite());
        student->adaugaNota(nota);
        if(nota >= 7) {
            std::cout << "[!] O nota ca asta iti asigura o bursa. Castigi 15 lei (nu te duce in Afi ca ramai fara ei)\n";
            student->modificaBani(15);
        }
    } else if (dificultate <= 0) {
        std::cout << GREEN << "\n[VICTORIE] Ai luat examenul la " << getNume() << "! Castigi " << getCredite() << " credite si nota 10!\n" << RESET;
        student->adaugaCredite(getCredite());
        student->adaugaNota(10);
        std::cout << "Total de credite curent: " << student->getCredite() << "\n";
        std::cout << "[!] O nota ca asta iti asigura o bursa. Castigi 15 lei (nu te duce in Afi ca ramai fara ei)\n";
        student->modificaBani(15);
    }
};


//EXAMEN GRILA
ExamenGrila::ExamenGrila(std::string materie, Profesor* p) : Examen(materie, 40, 20, 3, p) {}
void ExamenGrila::sustineExamen(Student* student, Ghiozdan<Item>* ghiozdan) {
    std::cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n";
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
    int cooldown_item = 0;
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
            std::cout << BLUE << "\n[!] Ti-a dat bine intr-un final, pune raspunsul in caseta!!\n" << RESET;
            dificultate -= 10;
            student->modificaEnergie(-10);
            grile++;
        }
        else if(alegere == 2) {
            if(rand() % 2 == 0) {
                std::cout << BLUE << "\n[SUCCESS] Se pare ca in final acest raspuns a fost corect!\n" << RESET;
                dificultate -= 10;
                student->modificaEnergie(-5);
                grile++;
            }
            else {
                std::cout << YELLOW << "\n[FAIL] Womp womp...aceasta grila a fost corectata ca fiind gresita!\n" << RESET;
                dificultate -= 10;
                student->modificaEnergie(-5);

            }
        }
        else if(alegere == 3) {
            int bonus = student->getBonus();
            if(bonus <= 4) {
                std::cout << YELLOW << "\n[!] Nu te-ai pregatit suficient acasa. Nu ai destul bonus. loser loser\n" << RESET;
                continue;
            }
            else {
                dificultate -= 10;
                student->reseteazaBonus(5);
                grile++;
            }
        }
        else if(alegere == 4) {
            if(cooldown_item > 0) {
                std::cout << YELLOW << "\nE prea devreme sa folosesti un item. Mai asteapta " << RESET << cooldown_item << YELLOW << " ture\n" << RESET;
            }
            if(ghiozdan->esteGol()) {
                std::cout << YELLOW << "\n[!] Ghiozdanul tau este gol! Nu ai ce folosi!\n" << RESET;
                continue;
            }
            std::cout << BLUE << "\n[!] Hai ca te lasa. Ce item doresti sa folosesti? \n" << RESET;
            ghiozdan->afiseazaElemente();
            std::cout << "Alegerea ta: ";
            int index_item;
            std::cin >> index_item;
            try {
                Item* it = ghiozdan->getElement(index_item);
                it->foloseste(student, dificultate);
                delete it;
            } catch (const std::out_of_range& e) {
                std::cout << "\nIndex invalid! Pierzi timpul!\n";
            }
            cooldown_item = 2;
            
        }
        else {
            std::cout << "\nAlegere invalida. Pierzi timpul!\n";
        }
        profesor->reactioneaza(student, dificultate);
        if(cooldown_item > 0) cooldown_item--;
    }
    
    if (student->getEnergie() <= 0) {
        std::cout << RED << "\n[GAME OVER] Ai cedat nervos la " << getNume() << "...\n" << RESET;
    } else if (dificultate <= 0 ) {
        if(grile >= 3) {
            std::cout << GREEN << "\n[VICTORIE] Ai luat examenul la " << getNume() << "! Castigi " << getCredite() << " credite!\n" << RESET;
            student->adaugaCredite(getCredite());
            std::cout << "Total de credite curent: " << student->getCredite() << "\n";

        }
        else {
            std::cout << RED << "\n[FAIL] Nu ai destule grile corecte, nu iei creditele, dar continui jocul" << RESET;
        }
        int nota = profesor->puneNotaGrila(dificultate);
        std::cout << YELLOW << "\n[CATALOG]" << RESET << "Profesorul " << profesor->getTitluComplet() << " ti-a trecut nota " << nota << " in carnet.\n";
        if(nota >= 7) {
            std::cout << "[!] O nota ca asta iti asigura o bursa. Castigi 15 lei (nu te duce in Afi ca ramai fara ei)\n";
            student->modificaBani(15);
        }
    }

};