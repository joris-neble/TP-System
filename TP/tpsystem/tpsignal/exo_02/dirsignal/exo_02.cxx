/**
 * @File : exo_01.cxx
 *
 * @Authors : A. B. Dragut
 *
 * @Version : V1.1
 *
 * @Synopsis : affichage de la liste de tous les signaux avec
 *             leur explication (sauf temps reel), et deroutement
 *             conditionne par un argument de la ligne de commande
 *             soit vers un traitant particulier, soit ignore, soit
 *             vers le traitant par defaut
 *
 **/
#include <string>
#include <exception>
#include <csignal>      // _sys_siglist

#include <iostream>
#include <iomanip>      // setw()
#include <sstream>

#include "CExc.h"
#include "nsSysteme.h"

using namespace nsSysteme;  // Signal()
using namespace std;

namespace{
  void Derout(int numSig){
    std::cout << "Signal :" << _sys_siglist[numSig] << "Chiffre :" << numSig << std::endl;
  }
}

int main(int argc, char * argv []) {
  try {
    struct sigaction Act;
    Act.sa_flags = SA_RESETHAND;
    Act.sa_mask

    return 0;
  }
  catch (const CExc & Exc) {
        cerr <<Exc<< endl;
        return errno;
  }
  catch (const exception & Exc) {
        cerr << "Exception : " << Exc.what () << endl;
        return 1;
  }
  catch (...) {
        cerr << "Exception inconnue recue dans la fonction main()"
             << endl;
        return 1;
  }

}  // main()
