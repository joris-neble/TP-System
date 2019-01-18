#include <string>
#include <exception>
#include "string.h"
#include "CExc.h"
#include "nsSysteme.h"

using namespace std;
using namespace nsSysteme;

int main (int argc, char * argv []) {
  try {	
     struct stat S;  
     stat(argv[1], &S);
     cout << "Liens dur : " << S.st_nlink << endl;
     cout << "Taille : " << S.st_size << endl;
     cout << "Last Modification date : " << ctime(&(S.st_mtime)) << endl;
  }
  catch (const CExc & Exc){
    cerr << Exc << endl;
    return 1;
  }
  catch (const exception & Exc) {
    cerr << "Exception : " << Exc.what () << endl;
    return 1;
  }
  catch (...){
    cerr << "Exception inconnue recue dans la fonction main()" << endl;
    return 1;
  }
}  
