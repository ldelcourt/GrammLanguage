#include <iostream>
#include "lexer.h"
#include "automate.h"


int main(void) {
   string chaine("(1+34)*123");
   //string sp("1+2");

   Lexer l(chaine);

   Symbole * s;
   while(*(s=l.Consulter())!=FIN) {
      s->Affiche();
      cout<<endl;
      l.Avancer();
   }
   cout << "Fin de lecture de la chaine, début Automate:" << endl << endl;
   Automate *a = new Automate(chaine);
   a->run();
   return 0;
}

