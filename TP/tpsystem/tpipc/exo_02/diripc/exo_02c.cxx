/**
 *
 * @File :
 *
 * @Author : A. B. Dragut
 *
 * @Synopsis : modelmain
 **/

#include <string>
#include <exception>
#include <iostream>

#include <unistd.h>     // getdtablesize()
#include <sys/time.h>   // fd_set

#include "nsSysteme.h"
#include "CExc.h"
#include <fcntl.h>

using namespace nsSysteme;
using namespace std;

int main(int argc, char * argv [])
{
  try {
    	const int fdFIFO = Open(argv[1], O_RDONLY);
      size_t TailleMessage;
      int VraieFinPasRecue = 1;
      while (VraieFinPasRecue) { //tant que on n'as pas recu  '#' on continue
		    int OctetsLus = Read (fdFIFO, &TailleMessage, sizeof (int));
		    char Message [TailleMessage + 1];
		    if(OctetsLus) {
			      int TailleMessageReelle = Read (fdFIFO, Message, TailleMessage);
			      Message[TailleMessageReelle] = '\0';
			      if((1 == TailleMessage) && ('#' == Message[0])) {
			          VraieFinPasRecue = 0;
			          cout << "Fin de communication annoncee par '#'" << endl;
			      }
			      else {
			          cout << "Le Consommateur fils id : " << ::getpid() << " a lu : "
				             << Message << endl;
			       }
		    }
		    else {
			    VraieFinPasRecue = 0;
			    cout << "Fin de communication imprevue. "     << endl;
			    cout << "Le pere producteur a ferme son pipe" << endl;
			}
		}
		Close (fdFIFO);
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
