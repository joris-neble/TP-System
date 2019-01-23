#include <string>
#include <exception>
#include "string.h"

#include <sys/stat.h>       // struct stat
#include <fcntl.h>          //O_RDONLY
#include <stdlib.h>         // system()

#include "CExc.h"
#include "nsSysteme.h"

using namespace std;
using namespace nsSysteme;

int main (int argc, char * argv []) {
  try {
    if (2 != argc)
        throw CExc ("main()",string ("Usage : ") +
                          argv [0] + "  <source> ");

    string Commande ("ls -l ");
	Commande += argv[1];

	char c;
  cout << "Avant unlink() : " << flush;
	system(Commande.c_str());
	cout << "Appuyez sur return pour continuer";
	cin.get (c);


	const int fdSource = Open (argv[1], O_RDONLY);

	struct stat buf;
	try { Stat (argv [1], &buf); }
	catch (const CExc & Exc) {
		   cerr <<Exc<< endl;
		   if (errno != ENOENT) throw;
		   cerr << "Le fichier source n'existe plus.\n";
	}

	Unlink (argv[1]);
	cout << "Apres unlink() : " << flush;
	system(Commande.c_str());
	cout << "Appuyez sur return pour continuer";
	cin.get (c);


  cout << "Les premiers 10 characteres du fichier Source " << "\n";
	const int NoCharac=10;
	char Tampon [NoCharac+1];

	Read (fdSource, Tampon, NoCharac);
	Tampon[NoCharac]='\0';

	Write (1, Tampon, NoCharac+1);

	Close (fdSource);

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
}
