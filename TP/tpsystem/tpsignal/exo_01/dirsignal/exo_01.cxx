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
    if (2 != argc || (argv[1][0] != 'D' && argv[1][0] != 'I' && argv[1][0] != 'P')) throw CExc ("main()",string ("Usage : ") + argv [0] + " {P|I|D} ");
    for (int numSig = 1; numSig < CstSigMax ; ++numSig)
    {
      if(numSig != SIGKILL && numSig != SIGSTOP){
        switch (argv[1][0]) {
          case 'P':
            Signal(numSig, Derout);
            break;
          case 'I':
            Signal(numSig, SIG_IGN);
            break;
          case 'D':
            Signal(numSig, SIG_DFL);
            break;
          default :
            std::cout<< argv[1][0] << " est inconnue" << '\n';
            break;
        }
      }
    }
    for ( ; ; );

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
