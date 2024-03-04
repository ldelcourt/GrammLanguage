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

  while(continuer) { 
    Symbole *s = lexer->Consulter();
    cout << "Lecture du symbole ";
    s->Affiche();
    cout << endl;
    lexer->Avancer();
    continuer = statestack.top()->transition(*this, s);
  }

  if(*symbolstack.top() == ERREUR) {
    symbolstack.top()->Affiche();
    cout << "Syntaxe non reconnue ou programme cassé" << endl;
    return;
  }
  cout << "Syntaxe correcte, le résultat est : " << ((Expression*)symbolstack.top())->getValue() << endl;
}

void Automate::decalage(Symbole* s, Etat* e) {
    cout << "Décalage " << endl;
    statestack.push(e);
    symbolstack.push(s);
    showStateStack();
    showSymbolStack();
}


void Automate::reduction(int numeroRegle, Symbole* s) {
  cout << "Réduction " << numeroRegle << endl;
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

  case 5: // E -> var
    en = (Entier*) symbolstack.top(); symbolstack.pop();
    statestack.pop();
    statestack.top()->transition(*this, new Expression(en->getValue()));
  }

  lexer->putSymboleBack(s);
}

void Automate::showStateStack() {
  cout << "State stack : ";
  stack<Etat*> temp = statestack;
  while(!temp.empty()) {
    temp.top()->print();
    cout << " ";
    temp.pop();
  }
  cout << endl;
}

void Automate::showSymbolStack() {
  cout << "Symbol stack : ";
  stack<Symbole*> temp = symbolstack;
  while(!temp.empty()) {
    temp.top()->Affiche();
    cout << " ";
    temp.pop();
  }
  cout << endl;
}