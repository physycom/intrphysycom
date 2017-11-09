#pragma once

#define Nmax 12    // il dominio � 12 * 12  di cui 10*10 caselle libere
#define NCANS 50   // numero lattine
#define NROBBY 100 // numero robby che compone una generazione
#define NSTEP                                                                  \
  100 // numero di passi per test  -- per raccogliere una lattina gli servono 2
      // passi
#define NTEST 5   // numero di volte che viene ripetuto il test
#define NGEN 8000 // numero di generazioni

//------------------------------------------------------------------------
struct Robby {
  int dna[243]; // Robby valuta i primi vicini ossia 5 celle ognana con 3
                // possibili valori (-1,0,+1) abbiamo 3^5= 243 stati
  int value;    // ad ogni stato associa un'azione fra 6 (
                // random,destra,sinistra,su,giu,raccogli )=(0,1,2,3,4,5)
  Robby() { value = 0; }
};
//------------------------------------------------------------------------
