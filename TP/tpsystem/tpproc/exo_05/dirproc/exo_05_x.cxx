/**
 *
 * @File : exo_05-x.cxx
 *
 * @Authors : A.B. Dragut
 *
 * @Date : 2011
 *
 * @Synopsis :  Prog_test_executable pour exo_05
 *              Heritage des descripteurs de fichiers ouverts
 *              en execution, drapeau O_CLOEXEC
 *              Linux kernel ?2.6.23 et glibc ?2.7, open a le drapeau
 *              O_CLOEXEC
 *
 **/
#include <exception>
#include <iostream>
#include <unistd.h>          // execl()
#include <fcntl.h>           // O_RDONLY


#include "CExc.h"
#include "nsSysteme.h"       // Fork(), Signal()

using namespace std;
using namespace nsSysteme;   // Fork(), Signal()
using namespace nsFctShell;  //TestFdOuverts();

int main(int argc, char * argv [])
{
  try {

    cout << "Nombre d'arguments : " << argc << endl;
    cout << "Arguments de la commande : " << endl;

    for(int i=0;i<argc; i++) cout << argv [i] << ' ';
    cout << endl;

    TestFdOuverts ();

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


}  //  main()
