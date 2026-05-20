# Joc Simulator - Sesiune de examene
Proiect pentru laboratorul de Programare Orientata pe Obiecte, Anul 1, Semestrul 2, FMI

Acesta este un mini-joc text-based RPG care implementează cerințele de Programare Orientată pe Obiecte învățate. Tematica jocului este o sesiune de examene a unui student (player), care trebuie să simuleze anumite activități și chiar examene pentru a obține credite (20) și pentru a promova anul (și jocul).

Acesta se folosește de mecanici tipice ale jocurilor de genul. Jucătorul are un nivel de energie (150 initial) pe care nu trebuie să-l piardă complet și se poate folosi de bani pentru a achiziționa item-uri ajutătoare sau pentru a se relaxa. Jucătorul este pus în fața unor decizii tipice RPG-urilor, cum ar fi învățatul acasă în schimbul energiei și creșterii stresului (care nu trebuie să depăsească pragul de 25), mersul la examene și decizii legate de acestea, etc.

## Obiectivul jocului
- Condiție de victorie: Acumularea a 20 de credite prin susținerea și promovarea cu succes a examenelor.
- Condiții de End Game:
    - Nivelul de `energie` scade la 0 sau mai jos de 0.
    - Nivelul de `stres` atinge pragul critic de 25 (Burnout)
 
## Functionalități și mecanici de joc (Gameplay)

1. Sistem de gestionare a resurselor:
     - Energia: Se consumă prin învățat și prin susținerea examenelor. Este specificat câtă energie necesită fiecare acțiune, astfel încât jucătorul își va putea crea strategia posibilă prin care să folosească și să obțină energie.
     - Stresul: Acest mecanism crește în timpul sesiunilor individuale de studiu, astfel încât acestea să nu poată fi folosite continuu fără consecințe. Un nivel apropiat de cel de Burnout va declanșa avertismente jucătorului
     - Banii: Economia jocului, banii sunt câștigați prin obținerea unei note mari la un examen și pot fi cheltuiți la Magazin sau pentru momente de Relaxare care să scadă stresul și să permită continuarea studiului individual.
2. Inventar(Ghiozdan): Jucătorul poate cumpăra iteme (ex: Cafea, Sticlă de Apă, Copiuțe), care oferă avantaje în timpul examenului.
3. Sistem de luptă (examenele): Examenele sunt generate random, jucătorul nu știe dacă va primi un examen Scris, Oral sau Grilă. Acestea sunt interactive și au metode diferite de notare și promovare, specificate la începutul examenului. Examenul se încheie atunci când jucătorul reușesște să aducă la 0 nivelul de `Dificultate` al acestuia. Dacă reușește acest lucru, obține creditele aferente tipului de examen, dar asta nu garantează neapărat o notă mare. Dacă rămâne fără energie ăn timpul examenului, jocul s-a încheiat. Deci trebuie să fie atent cum își gestionează energia și itemele înainte să intre la examen.
4. Evenimente Alleatorii: Pe parcursul sesiunii pot apărea evenimente neprevăzute (ex: găsește bani pe jos, i-a mâncat iepurele tema de laborator, profesorul întârzie, etc.), care adaugă imprevizibilitate.
5. Gestionarea datelor: Sistem complet de Save/Load a progresului, menținând inventarul și statisticile intacte între sesiuni de joc
  
## Arhitectură și concepte avansate de POO
1. Clase template
     - Ghiozdanul: Ghiozdan<T> - O structură de date generică ce gestionează o colecție de pointeri către elemente. Include gestionarea excepțiilor și curățarea corectă a memoriei prin destructor pentru a preveni memory leaks.
2. Design pattern
     - Singleton Pattern (GameManager): Asigura existenta unei singure instante de manager de joc pentru loop-ul principal, Meniul de Boot și instanțierea jucătorului și accesul la fișiere de salvare.
     - Factory Pattern: ExamenFactory, metoda statică din fabrică generează examene complet randomizate (materie, format) ascunzând complexitatea alocării de memorie de clasa GameManager
3. Librarie JSON
     -Am utilizat libraria `nlohmann/json`. Modul de salvare extrage datele primitive, dar include și pointerii din clasa abstractă Item, care sunt transformați într-un array JSON, iar la metoda de Load, fconstrucția se reia reconstruind derivatele corecte (produsele)

