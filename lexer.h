#pragma once

#include <string>
#include "symbole.h"
using namespace std;

class Lexer {

   public:
      Lexer(string s) : flux(s), tete(0), tampon(nullptr) { }
      ~Lexer() { }

      Symbole * Consulter();
      void Avancer();
      void putSymboleBack(Symbole * s) { tampon = s; };

   protected:
      string flux;
      int tete;
      Symbole * tampon;
};
