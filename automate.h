#pragma once

#include <string>
#include <stack>
#include "etat.h"
#include "symbole.h"
#include "lexer.h"
using namespace std;

class Automate {
   public:
      Automate(string flux);
      virtual ~Automate() { }
      void decalage(Symbole* s, Etat* e);
      void reduction(int numeroRegle, Symbole* s);
      void run();
      void showSymbolStack();
      void showStateStack();
   protected:
      stack<Symbole *> symbolstack;
      stack<Etat *> statestack;
      Lexer* lexer;
};