#include <iostream>
#include "lexer.h"
#include "automate.h"


int main(void) {
   string chaine("(1+34)*123");
   string sp("1+2");

   Lexer l(sp);

   Symbole * s;
   while(*(s=l.Consulter())!=FIN) {
      s->Affiche();
      cout<<endl;
      l.Avancer();
   }
   Automate *a = new Automate(sp);
   a->run();
   return 0;
}

