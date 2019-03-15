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
    void Derout (int) {
      cout << "Un fils est termine!" << endl;
    }

}


int main(int argc, char * argv [])
{
	try {
		if (2 != argc)
			throw CExc ("main()",string ("Usage : ") + argv [0]);

		const int NbFils = atoi(argv[1]);
		::pid_t tabFils[NbFils];
		Signal(SIGCHLD,::Derout);

		for (int i = 0; i; ++i){
			if (!(tabFils[i]=Fork()))     //fils i
      	{
        	cerr << "Le fils "<<::getpid() <<" dort  " << i << " secondes\n";
          ::sleep (i);
          return i;
        }
		}
		int status;
		::pid_t Fils;
		for (int i = NbFils; i ;--i ) {
            Fils=tabFils[i];
						::Waitpid(tabFils[i],&status,0);
	      		cout << "Le fils de pid " << Fils << " est termine "<<endl;

	      		if (WIFEXITED(status)){
							cout << "par un exit/return de " << WEXITSTATUS(status)<<endl;
						}
		}

    cout << "J'ai reussi a ne pas perdre de SIGCHLD" << endl;

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
