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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "nsSysteme.h"
#include "CExc.h"

using namespace nsSysteme;
using namespace std;

int main(int argc, char * argv [])
{
  try {
      const int fdFIFO = Open(argv[1], O_WRONLY);
      size_t TailleMessage;
      for (int i = 2; i < argc; ++i)
		  {
			     TailleMessage = strlen (argv [i]);

		       Write (fdFIFO, &TailleMessage, sizeof (int));
			     Write (fdFIFO, argv [i], TailleMessage);
		  }
      TailleMessage = 1;
		  char Fin='#';
		  Write (fdFIFO, &TailleMessage, sizeof (int));
		  Write (fdFIFO, &Fin, TailleMessage);
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
