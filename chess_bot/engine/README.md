# Rulare
`make xboard` -- compileaza sursele si deschide engine-ul in xboard (comanda suficienta)  
`make build` -- compileaza sursele  
`make clean` -- curata folderul de fisierele create in urma compilarii  

# Structura proiectului
__main.cpp__ contine consola prin intermediul caruia programul comunica cu protocolul xboard  
__functions.cpp__ contine functii utile pentru reprezentarea in intermediul programului a tablei de sah, generarea tuturor miscarilor
__functions.h__ contine definitiile functiilor anterior descrise  
__variables.cpp__ contine variabile globale ce vor fi folosite in restul surselor si (reprezentarea tablei de sahsub forma de vector, culoarea curenta si culoarea cu care joaca engine-ul)
__variables.h__ contine definitiile variabilelor anterior descrise  
__definitions.h__ contine definitii pentru reprezentarea culorilor, pieselor si a tablei de sah  

# Abordarea algoritmica
Aproximativ "greedy": la fiecare pas, engine-ul genereaza toate mutarile posibile pentru fiecare piesa de pe tabla de sah a culorii curente. Acestea se 
sorteaza dupa o functie care calculeaza un "scor" pentru fiecare mutare, in functie de cat de buna pare la momentul in care se genereaza. Se alege cea 
mai buna mutare (sau daca sunt mai multe mutari cu acelasi scor maxim, se alege una aleatoare din cele mai bune, dar aceste cazuri sunt rare si se 
intampla doar daca mutarile sunt foarte asemanatoare) si apoi se executa.

La generarea mutarilor, mai intai se genereaza rocadele, apoi mutarile pionilor, intrucat acestea sunt cazuri speciale (rocadele au multe conditii,
iar pionii se comporta complet diferit daca nu au fost mutati inainte sau sunt intr-o pozitie de en passant). Celelalte mutari sunt generate cu ajutorul
unor offset-uri prestabilite, avand grija ca la dame, nebuni si turnuri sa se genereze toate mutarile posibile (pana se ajunge intr-o margina a tablei 
sau se ajunge la o alta piesa)

Generarea miscarilor se face in O(n), n = marimea totala a tablei de sah (8x8).
Aceste miscari se sorteaza apoi in O(m * log m), m = numarul de miscari pseudo-legale pentru o anumita stare a unei tabele de sah.
Alegerea unei miscari din cele generate se face in O(m) in cel mai rau caz.

Complexitatea totala: O(n * log n), intrucat aceasta este complexitatea sortarii miscarilor in functie de scor, iar generarea mutarilor se genereaza
in aproximativ aceeasi complexitate, intrucat se trece prin toata tabla de sah, iar pentru dame, nebuni si turnuri se mai genereaza cateva mutari in plus
(de exemplu, pentru dama, numarul maxim posibil de mutari generate este 27, dar acest  lucru este posibil doar daca tabla este aproape complet goala; in
plus, exista doar 2 dame, acestea fiind echilibrate de restul pieselor cand vine vorba de complexitate temporala).

# Surse de inspiratie
Playlist YT: https://www.youtube.com/playlist?list=PLZ1QII7yudbc-Ky058TEaOstZHVbT-2hg  
-- generarea mutarilor pseudo-legale
-- detectarea miscarilor ce se vor situa in afara tabelei de sah

# Responsabilitati membrii
Toti membrii echipei au contribuit fie la generarea tuturor miscrilor pseudo-legale, verificarea legalitatii miscarilor, formatarea codului, fixarea bug-urilor scrise de ceilalti membrii ai echipei 
