#include "EqLaplace.h"
#include "dati.h"
#include <iostream>

using namespace std;
// ********************************************************************************************************
int main(int argc, char **argv) {
  int k;
  Start();
  for (k = 0; k < 100; k++)
    Next2();
  cout << " k= " << k << " Err%= " << Err() << endl;
  cout << "Press a key...";
  cin.get();
  return 0;
}
// ********************************************************************************************************
