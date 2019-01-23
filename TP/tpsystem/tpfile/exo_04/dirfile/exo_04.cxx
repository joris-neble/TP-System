#include <string>
#include <exception>
#include <fcntl.h>

#include "CExc.h"
#include "nsSysteme.h"


using namespace std;
using namespace nsSysteme;


int main (int argc, char * argv []) {
  try {
  if (2 != argc)throw CExc ("main()",string ("Usage : ") +
      argv [0] + " <fichier> ");

  char c;
  int fD;
  fD = Open(argv[1],O_RDONLY | O_CREAT, 0700);
  Read(fD,&c,sizeof(char));
  cout << "Lecture caractere:  '" << c << "' " << endl;
  int n;
  Read(fD,&n,sizeof(int));
  cout << "Lecture entier:  " << n <<flush;
  cout << " et lecture d'autant de caracteres: "<<endl <<"' " << flush;
  const int AReserver= 512;
	   char Tab[AReserver+1];
	   size_t NbLus;

	   while (n>AReserver)
	   {
		   n-=AReserver;
		   NbLus=Read(fD, Tab, AReserver);
		   Tab[NbLus]='\0';
		   cout << Tab;

	   }
	   NbLus=Read(fD, Tab, n);
	   Tab[NbLus]='\0';
	   cout << Tab;
	   cout<< "  '"<<endl;
	   cout << "lecture du reste: '" << flush;


	   while((NbLus=Read(fD, Tab, AReserver))>0)
	   {
		   Tab[NbLus]='\0';
		   cout << Tab;
	   }
	   cout << flush;
     cout << "' "<< endl<<"et le traitement est fini, au revoir.\n";
     Close(fD);
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
        cerr << "Exception inconnue recue dans la fonction main()" << endl;
        return 1;
   }
}
