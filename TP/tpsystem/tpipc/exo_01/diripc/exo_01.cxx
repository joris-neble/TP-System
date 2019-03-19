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

using namespace nsSysteme;
using namespace std;

int main(int argc, char * argv [])
{
  try {
    int pidFils;
    int dFic[2];
    int taille;
    nsSysteme::Pipe(dFic);
    if ((pidFils = nsSysteme::Fork()) > 0){
      Close(dFic[0]);
      for (int i = 1 ; i < argc ; ++i ){
        taille = strlen(argv[i]);
        nsSysteme::Write (dFic[1], &taille, sizeof (int));
        nsSysteme::Write(dFic[1], argv[i], sizeof (int));
      }
      int tailleFin = 1;
      char Msg = '#';
      nsSysteme::Write (dFic[1], &tailleFin, sizeof (int));
      nsSysteme::Write(dFic[1], &Msg, sizeof(char));
    }
    else if(pidFils == 0){
      nsSysteme::Close(dFic[1]);
      bool isEnd = true;
      while(isEnd){
        int OctetsLus = nsSysteme::Read (dFic[0], &taille, sizeof (int));
				char Message [taille + 1];
        if(OctetsLus) {
				    int TailleMessageReelle = nsSysteme::Read (dFic[0], &Message, taille);
				    Message[TailleMessageReelle] = '\0';
				    if((1 == taille) && ('#' == Message[0])) {
					isEnd = false;
					cout << "Fin de communication annoncee par '#'" << endl;
				    }
				    else {
					cout << "Le Consommateur fils id : " << ::getpid() << " a lu : "
					     << Message << endl;
				    }
				}
				else {
          isEnd = false;
					cout << "Fin de communication imprevue. "     << endl;
					cout << "Le pere producteur a ferme son pipe" << endl;
				}
			}
			return 0;
      }
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
