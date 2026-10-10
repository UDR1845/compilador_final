#include "Semantico.h"
#include <iostream>

using namespace std;


bool Semantico::analizar(vector<Token> tokens) {
    bool correcto = true;
    tablaSimbolos.clear();
    for (size_t i = 0; i < tokens.size();) {
        if (i + 2 >= tokens.size()) { break; }
        string tipo = tokens[i].lexema;
        string nombre = tokens[i + 1].lexema;
        // Verificar variable duplicada
        if (tablaSimbolos.count(nombre)) {
            cout << "Error semantico: variable duplicada '" << nombre << "'." << endl;
            correcto = false;
        }
        // Revisar los valores hasta el punto y coma
        size_t j = i + 3;
        string tipoValor = "";
        bool expresionNumerica = true;
        while (j < tokens.size() && tokens[j].lexema != ";") {
            Token token = tokens[j];
            if (token.tipo == TipoToken::LITERAL_INT) { if (tipoValor.empty()) { tipoValor = "int"; } }
            else if (token.tipo == TipoToken::LITERAL_FLOAT) { tipoValor = "float"; }
            else if (token.tipo == TipoToken::IDENTIFICADOR) {
                if (!tablaSimbolos.count(token.lexema)) {
                    cout << "Error semantico: variable '" << token.lexema << "' no declarada." << endl;
                    correcto = false;
                    expresionNumerica = false;
                }
                else if (tipoValor.empty()) { tipoValor = tablaSimbolos[token.lexema]; }
                else if (tablaSimbolos[token.lexema] == "float") { tipoValor = "float"; }
            }
            else if (token.tipo == TipoToken::LITERAL_STRING) { tipoValor = "string"; }
            j++;
        }
        if (tipo == "string") {
            if (j != i + 4 || tokens[i + 3].tipo != TipoToken::LITERAL_STRING) {
                cout << "Error semantico: valor incompatible para '" << nombre << "'." << endl;
                correcto = false;
            }
        }
        else if (!expresionNumerica || (tipo == "int" && tipoValor != "int") || 
                                       (tipo == "float" && tipoValor != "int" && tipoValor != "float")) {
            cout << "Error semantico: tipo incompatible en '" << nombre << "'." << endl;
            correcto = false;
        }
        if (!tablaSimbolos.count(nombre)) { tablaSimbolos[nombre] = tipo; }
        i = (j < tokens.size()) ? j + 1 : tokens.size();
    }
    return correcto;
}

void Semantico::mostrarTabla() {
    cout << "\n--- TABLA DE SIMBOLOS ---\n";
    for (const auto& simbolo : tablaSimbolos) { cout << simbolo.first << " -> " << simbolo.second << endl; }
}