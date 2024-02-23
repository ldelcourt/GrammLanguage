#include "etat.h"
#include "automate.h"
#include <iostream>

bool Etat0::transition(Automate &automate, Symbole * s) {
    switch(*s) {
        case INT:
            automate.decalage(s, new Etat3);
            cout << "INT Transition vers Etat 3" << endl;
            break;
        case OPENPAR:
            automate.decalage(s, new Etat2);
            break;
        case EXPR:
            automate.decalage(s, new Etat1);
            break;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;  
}

bool Etat1::transition(Automate &automate, Symbole * s) {
    switch(*s) {
        case PLUS:
            automate.decalage(s, new Etat4);
            break;
        case MULT:
            automate.decalage(s, new Etat5);
            break;
        case FIN:
            return false;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool Etat2::transition(Automate &automate, Symbole * s) {
    switch(*s) {
        case INT:
            automate.decalage(s, new Etat3);
            break;
        case OPENPAR:
            automate.decalage(s, new Etat2);
            break;
        case EXPR:
            automate.decalage(s, new Etat6);

        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool Etat3::transition(Automate &automate, Symbole * s) {
    switch(*s) {
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN:
            automate.reduction(5);
            cout << "Symbole:";
            s->Affiche();
            cout << "Réduction 5" << endl;
            break;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool Etat4::transition(Automate &automate, Symbole * s) {
    switch(*s) {
        case INT:
            automate.decalage(s, new Etat3);
            break;
        case OPENPAR:
            automate.decalage(s, new Etat2);
            break;
        case EXPR:
            automate.decalage(s, new Etat7);

        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool Etat5::transition(Automate &automate, Symbole * s) {
    switch(*s) {
        case INT:
            automate.decalage(s, new Etat3);
            break;
        case OPENPAR:
            automate.decalage(s, new Etat2);
            break;
        case EXPR:
            automate.decalage(s, new Etat8);

        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool Etat6::transition(Automate &automate, Symbole * s) {
    switch(*s) {
        case PLUS:
            automate.decalage(s, new Etat4);
            break;
        case MULT:
            automate.decalage(s, new Etat5);
            break;
        case CLOSEPAR:
            automate.decalage(s, new Etat9);

        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool Etat7::transition(Automate &automate, Symbole * s) {
    switch(*s) {
        case PLUS:
        case CLOSEPAR:
        case FIN:
            automate.reduction(2);
            break;
        
        case MULT:
            automate.decalage(s, new Etat5);
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool Etat8::transition(Automate &automate, Symbole * s) {
    switch(*s) {
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN:
            automate.reduction(3);
            break;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool Etat9::transition(Automate &automate, Symbole * s) {
    switch(*s) {
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN:
            automate.reduction(4);
            break;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}