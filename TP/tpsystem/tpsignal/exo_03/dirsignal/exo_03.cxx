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
  struct sigaction OldAction;

    void Derout1 (int NumSig)
    {
        cout << "Debut fonction Derout1()" << endl;
        ::sleep (5);
        cout << "Fin fonction Derout1()" << endl;

    } // Derout1()

    void Derout2 (int NumSig)
    {
        cout << "Debut fonction Derout2()" << endl;
        ::sleep (5);
        Sigaction (NumSig, &OldAction, 0);
        cout << "Fin fonction Derout2()" << endl;

    } // Derout2()
}

int main(int argc, char * argv []) {
  try {
   if (argc != 1)
       throw CExc ("main()",string ("Usage : ") + argv [0]);

   struct sigaction Action;

   Action.sa_flags   = 0;
   Action.sa_handler = Derout1;
   sigemptyset (&Action.sa_mask);
   sigaddset   (&Action.sa_mask, SIGTSTP);

   Sigaction (SIGINT, &Action, 0);
   ::pause ();

   Action.sa_handler = Derout2;
   sigemptyset (&Action.sa_mask);

   Sigaction (SIGINT, &Action, &OldAction);

   for (;;);

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
