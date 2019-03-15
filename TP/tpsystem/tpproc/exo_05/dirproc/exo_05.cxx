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

int main(int argc, char * argv [])
{
	try {
		if (1 != argc)
			throw CExc ("main()",string ("Usage : ") + argv [0]);

    Open ("exo_05.txt", O_WRONLY|O_CREAT,0700);
    Open ("exo_05.txt", O_RDONLY);
    Open ("exo_05.txt", O_RDWR|O_CLOEXEC);

    TestFdOuverts();

   ::execl ("exo_05_x.run", "exo_05_x.run", "lance ", "par ", argv [0], static_cast <char*>(0));
   throw CExc("execl()","");

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
