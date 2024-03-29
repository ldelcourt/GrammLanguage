#include "etat.h"
#include "automate.h"
#include <iostream>

void Etat::print() const {
    cout << name << " ";
}

bool Etat0::transition(Automate &automate, Symbole * s) {
    switch(*s) {
        case INT:
            automate.decalage(s, new Etat3);
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
            break;
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
            break;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool Etat3::transition(Automate &automate, Symbole * s) {
    switch(*s) {
        case PLUS:
            automate.reduction(5, s);
            break;
        case MULT:  
            automate.reduction(5, s);
            break;
        case CLOSEPAR:
            automate.reduction(5, s);
            break;
        case FIN:
            automate.reduction(5, s);
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
            break;
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
            break;
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
            break;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool Etat7::transition(Automate &automate, Symbole * s) {
    switch(*s) {
        case PLUS:
            automate.reduction(2, s);
            break;
        case CLOSEPAR:
            automate.reduction(2, s);
            break;
        case FIN:
            automate.reduction(2, s);
            break;
        case MULT:
            automate.decalage(s, new Etat5);
            break;
        default:
            cout << "ERREUR Etat 7" << endl;
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}

bool Etat8::transition(Automate &automate, Symbole * s) {
    switch(*s) {
        case PLUS:
            automate.reduction(3, s);
            break;
        case MULT:
            automate.reduction(3, s);
            break;
        case CLOSEPAR:
            automate.reduction(3, s);
            break;
        case FIN:
            automate.reduction(3, s);
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
            automate.reduction(4, s);
            break;
        case MULT:
            automate.reduction(4, s);
            break;
        case CLOSEPAR:
            automate.reduction(4, s);
            break;
        case FIN:
            automate.reduction(4, s);
            break;
        default:
            automate.decalage(new Symbole(ERREUR), NULL);
            return false;
    }
    return true;
}