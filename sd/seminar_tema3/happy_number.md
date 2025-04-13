# Solutie 1:
Folosim un hash set pentru a stoca numerele generate. Începem cu numărul n. Pentru fiecare iterație, calculăm suma pătratelor cifrelor. Dacă suma este 1, atunci returnăm true (este număr fericit), iar dacă suma există deja în hash set, atunci avem un ciclu și returnăm false (nu este număr fericit). Dacă nu suntem în unul dintre aceste cazuri, adăugăm suma la hash set și repetăm procesul cu noua sumă.

# Solutie 2:
Folosim 2 variabile, x și y, care la început sunt egale cu n. Variabila x calculează suma pătratelor o singură dată, iar variabila y calculează suma pătratelor de două ori. Dacă y ajunge la 1, atunci numărul este fericit. Dacă x și y devin egale și sunt diferite de 1, atunci avem un ciclu și numărul nu este fericit. Procesul continuă până când una dintre aceste condiții este îndeplinită.
