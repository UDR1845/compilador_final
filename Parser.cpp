#include "Parser.h"
#include <iostream>

using namespace std;

Parser::Parser(vector<Token> tokens){
    this -> tokens = tokens;
    posicion = 0;
}

bool Parser::esFinal(){ return posicion >= tokens.size(); }

Token Parser::actual(){ return tokens[posicion]; }

bool Parser::coincidir(TipoToken tipoEsperado) {
    if (!esFinal() && actual().tipo == tipoEsperado){
        posicion++;
        return true;
    }
    return false;
}

bool Parser::tipo() {
    if (esFinal()){ return false; }
    if (actual().tipo == TipoToken::PALABRA_RESERVADA){
        if (actual().lexema == "int" || actual().lexema == "float" || actual().lexema == "string") {
            posicion++;
            return true;
        }
    }
    return false;
}

bool Parser::valor() {
    if (esFinal()) { return false; }
    if (coincidir(TipoToken::LITERAL_INT)) { return true; }
    if (coincidir(TipoToken::LITERAL_FLOAT)) { return true; }
    if (coincidir(TipoToken::LITERAL_STRING)) { return true; }
    if (coincidir(TipoToken::IDENTIFICADOR)) { return true; }
    return false;
}

bool Parser::declaracion() {
    // Tipo
    if (!tipo()) {
        error("int, float o string");
        return false;
    }
    // ID
    if (!coincidir(TipoToken::IDENTIFICADOR)) {
        error("IDENTIFICADOR");
        return false;
    }
    // =
    if (!coincidir(TipoToken::ASIGNACION)) {
        error("'='");
        return false;
    }

    if (!esFinal() && actual().tipo == TipoToken::LITERAL_STRING) { posicion++; }
    else if (!expresion()) {
        error("valor o expresion valida");
        return false;
    }

    // ;
    if (esFinal() || actual().lexema != ";") {
        error("';'");
        return false;
    }
    posicion++;
    return true;
}


bool Parser::factor() {
    if (!esFinal() && (actual().tipo == TipoToken::LITERAL_INT || 
                       actual().tipo == TipoToken::LITERAL_FLOAT || 
                       actual().tipo == TipoToken::IDENTIFICADOR)) {
        posicion++;
        return true;
    }
    if (!esFinal() && actual().lexema == "(") {
        posicion++;
        if (!expresion()) { return false; }
        if (!esFinal() && actual().lexema == ")") {
            posicion++;
            return true;
        }
    }
    return false;
}

bool Parser::termino() {
    if (!factor()) { return false; }
    while (!esFinal() && (actual().lexema == "*" || actual().lexema == "/")) {
        posicion++;
        if (!factor()) { return false; }
    }
    return true;
}

bool Parser::expresion() {
    if (!termino()) { return false; }
    while (!esFinal() && (actual().lexema == "+" || actual().lexema == "-")) {
        posicion++;
        if (!termino()) { return false; }
    }
    return true;
}

bool Parser::analizar(){
    if (esFinal()) {
        error("una declaracion");
        return false;
    }
    while (!esFinal()) {
        if (!declaracion()) { return false; }
    }
    return true;
}

void Parser::error(string esperado) {
    if (!esFinal()) {
        cout << "Error sintactico en linea " << actual().linea << ", columna " << actual().columna << ": se esperaba " << esperado << ", pero se encontro '" << actual().lexema << "'." << endl;
    }
    else {
        cout << "Error sintactico: " << "se esperaba " << esperado << ", pero se llego al final de la entrada." << endl;
    }
}