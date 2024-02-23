#include "automate.h"
#include "etat.h"
#include <iostream>



Automate::Automate(string flux) {
    lexer = new Lexer(flux);
    //On commence à l'état 0
    statestack.push(new Etat0());
}

void Automate::run() {
  bool continuer = true;
  int i = 0;
  while(continuer) { 
    Symbole *s = lexer->Consulter();
    continuer = statestack.top()->transition(*this, s);
    lexer->Avancer();
    i++;
  }

  if(*symbolstack.top() == ERREUR) {
    cout << "Syntaxe non reconnue ou programme cassé" << endl;
    return;
  }
  cout << "Syntaxe correcte, le résultat est : " << ((Expression*)symbolstack.top())->getValue() << endl;
}

void Automate::decalage(Symbole* s, Etat* e) {
    statestack.push(e);
    symbolstack.push(s);
}


void Automate::reduction(int numeroRegle) {
  Expression *e1, *e2;
  Entier *en;
  switch (numeroRegle)
  {
  case 2: //E -> E + E
    e2 = (Expression*) symbolstack.top(); symbolstack.pop(); 
    symbolstack.pop();
    e1 = (Expression*) symbolstack.top(); symbolstack.pop();
    for(int i = 0; i < 3; i++) {
      statestack.pop();
    }
    statestack.top()->transition(*this, new Expression(e1->getValue() + e2->getValue()));
    break;
  case 3: // E -> E * E
    e2 = (Expression*) symbolstack.top(); symbolstack.pop(); 
    symbolstack.pop();
    e1 = (Expression*) symbolstack.top(); symbolstack.pop();
    for(int i = 0; i < 3; i++) {
      statestack.pop();
    }
    statestack.top()->transition(*this, new Expression(e1->getValue() * e2->getValue()));
    break;
  case 4: // E -> ( E )
    symbolstack.pop();
    e1 = (Expression*) symbolstack.top(); symbolstack.pop();
    symbolstack.pop();
    for(int i = 0; i < 3; i++) {
      statestack.pop();
    }
    statestack.top()->transition(*this, e1);

  case 5:
    en = (Entier*) symbolstack.top(); symbolstack.pop();
    statestack.pop();
    statestack.top()->transition(*this, new Expression(en->getValue()));

  }

}
