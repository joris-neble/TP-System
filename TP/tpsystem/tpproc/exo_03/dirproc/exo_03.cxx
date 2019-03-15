/**
 *  *
 *   *  @File : exo_01_c.cxx
 *    *
 *     *  @Authors  : A. Dragut
 *      *  @Synopsis : mise en evidence du partage de pointeur de fichier.
 *       *
 *        **/

#include <string>
#include <exception>
#include <iostream>
#include <sys/types.h>      // pid_t

#include <unistd.h>         // SEEK_SET
#include <fcntl.h>          // O_RDWR

#include "nsSysteme.h"
#include "CExc.h"

using namespace nsSysteme;
using namespace nsFctShell;
using namespace std;

namespace
{
    void Derout(int) {
      cout << "Fils arrete! Init recupere son status!" << endl;
    }

}


int main(int argc, char * argv [])
{
	try {
		if (2 != argc)
			throw CExc ("main()",string ("Usage : ") + argv [0]);

    const int CstNbreFils = atoi (argv [1]);

    struct sigaction Act;
    Act.sa_flags = SA_NOCLDWAIT;
    sigemptyset(&Act.sa_mask);
    Act.sa_handler = Derout;
    Sigaction(SIGCHLD, &Act, NULL);

    for (int i = CstNbreFils; i; --i ){
      if (!Fork()){
        cout << "Le fils "<<::getpid() <<" dormira  " << i << " secondes"<<endl;
        ::sleep (i);
        return i;
      }
   }
   sleep(CstNbreFils);
   cout << "Je ne recupere pas les status des fils mais je ne cree pas de zombies" << endl;
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
