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

#include <fcntl.h>      // O_RDONLY

using namespace nsSysteme;
using namespace std;

int main(int argc, char * argv [])
{
  try {
    pid_t pidFils;

    cout<<"Le pere ouvre trois fichiers"<<endl;
    Open ("test.txt", O_RDONLY);
    Open ("test.txt", O_RDONLY);
    Open ("test.txt", O_RDONLY);
    cout<< "le pere ferme les fichiers"<<endl;
    Close (2);
    if((pidFils = Fork())){
      cout<<"je suis le pere de pid "<<::getpid()
		      <<"et j'ai un fils de pid "<<pidFils<<endl;
    }
    else{
      cout<<" fils de pid  "<< ::getpid()
          <<" mon pere est "<<::getppid()<<endl;
		  cout<< "ferme le stdin "<<endl;
   	  Close (0);


		nsFctShell::TestFdOuverts ();
    }
    for(;;);


///code
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
