#include <string>
#include <exception>
#include "string.h"
#include "CExc.h"
#include "nsSysteme.h"

using namespace std;
using namespace nsSysteme;

size_t donneTailleMorceau(const string &comment, const string &nomFichier){
    if(comment == "char")return 1;
    if(comment == "all"){
        struct stat S;
        Stat(nomFichier.c_str(), & S);
        return S.st_size;
    }
    if(comment == "block"){
        struct stat S;
        Stat(nomFichier.c_str(), & S);
        return S.st_blksize;
    }
    return 0;
}

int main (int argc, char * argv []) {
  char* comment = argv[1];
  char* Source  = argv[2];
  char* Destination =  argv[3];
  size_t Bytes = donneTailleMorceau(comment, Source);
  std::cout << Bytes << '\n';
  nsFctShell::FileCopy(Destination, Source, Bytes);
}
