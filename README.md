# GPS-tracker
A small project with trees and Bellman-Ford algorithm


Sistemul Global de Poziționare (sau GPS) este o rețea de aproximativ 30 de sateliți care orbitează în jurul Pământului,
la o altitudine de 20.000km. Acesta a fost dezvoltat de guvernul Statelor Unite în scop militar, 
dar oricine folosește acum un dispozitiv GPS poate recepționa semnalele radio pe care sateliții le fac broadcast.

Oriunde te afli pe planetă, cel puțin 3 sateliți sunt 'vizibili' la un moment dat. 
Fiecare transmite informații despre poziția sa și timpul curent la anumite intervale.
Aceste semnale sunt interceptate de dispozitivul GPS care calculează cât de departe e satelitul,
în funcție de cât de mult îi ia mesajului să ajungă.

Odată ce acesta are informații despre cât de departe cei trei sateliți sunt,
receiver-ul GPS poate indica locația folosind un proces numit trilaterație .
Trilaterația (măsurarea distanțelor, nu a unghiurilor)

Imaginează-ți că stai undeva pe Pământ cu 3 sateliți deasupra ta. 
Dacă știi cât de departe ești de satelitul A, atunci trebuie să te afli undeva în cercul roșu.
Dacă consideri la fel pentru sateliții B și C, poți afla locația ta precisă calculând intersecția celor 3 cercuri.
Asta este ceea ce receiver-ul GPS-ul tău face, deși acesta consideră sfere suprapuse. 


Vom considera ca fișier de intrare coordonate.in, în care pe prima linie vom avea un număr N care va reprezenta câte locații depistează sateliții noștri.

Pe următoarele linii vom avea pentru fiecare locație:

    nume locație
    coordonate (x1, y1) satelit1
    raza R satelit1
    coordonate (x2, y2) satelit2
    raza R satelit2
    coordonate (x3, y3) satelit3
    raza R satelit3


    Coordonatele și raza se consideră date de fiecare satelit pentru fiecare dintre cele N locații.
    Datorită distanței mult mai mari de la Pământ la sateliți, față de diferența de înălțime între sateliți, ei se pot considera în același plan (z1 = z2 = z3 = z). 
    Între cele 3 sfere există așadar cel mult 2 puncte de intersecție, obținându-le prin găsirea triadelor (x,y,z) care să satisfacă ecuațiile sferei.
    
    
    
    
    

Executabilul obținut în urma compilării va avea numele gps, iar regula de execuție va fi:
./gps coordonate.in avarii.in nume_destinatie coord_finale.out rezultat.out

unde numele destinației reprezintă locația unde vrem să ajungem pornind din nodul pe care am zis că-l vom considera nod de plecare.

În fișierul coord_finale.out se vor scrie numele și perechea (x,y) de coordonate calculate pentru fiecare locație, în ordinea citirii lor din fișierul de intrare coordonate.in

Având toate aceste date, vrem să calculăm costul celui mai scurt drum de la nodul de plecare, la cel destinație, pe care îl vom scrie în fișierul rezultat.out .

