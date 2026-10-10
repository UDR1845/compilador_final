#include "CodigoIntermedio.h"
#include <iostream>
#include <stack>
using namespace std;

int prioridad(string op) {
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

vector<string> CodigoIntermedio::generar(vector<Token> tokens) {
    vector<string> codigo;
    int temporal = 1;
    for (size_t i = 0; i + 2 < tokens.size();) {
        // Buscar una declaracion: tipo identificador =
        if (tokens[i + 1].tipo != TipoToken::IDENTIFICADOR || tokens[i + 2].tipo != TipoToken::ASIGNACION) {
            i++;
            continue;
        }
        string resultado = tokens[i + 1].lexema;
        size_t j = i + 3;
        // Obtener la expresion hasta el punto y coma
        vector<Token> expresion;
        while (j < tokens.size() && tokens[j].lexema != ";") {
            expresion.push_back(tokens[j]);
            j++;
        }
        // Convertir a notacion postfija
        vector<string> postfija;
        stack<string> operadores;
        for (const Token& token : expresion) {
            if (token.tipo == TipoToken::LITERAL_INT || token.tipo == TipoToken::LITERAL_FLOAT || token.tipo == TipoToken::IDENTIFICADOR || token.tipo == TipoToken::LITERAL_STRING) {
                postfija.push_back(token.lexema);
            }
            else if (token.lexema == "(") {
                operadores.push(token.lexema);
            }
            else if (token.lexema == ")") {
                while (!operadores.empty() && operadores.top() != "(") {
                    postfija.push_back(operadores.top());
                    operadores.pop();
                }
                if (!operadores.empty()) { operadores.pop(); }
            }
            else if (token.tipo == TipoToken::OPERADOR) {
                while (!operadores.empty() && operadores.top() != "(" && prioridad(operadores.top()) >= prioridad(token.lexema)) {
                    postfija.push_back(operadores.top());
                    operadores.pop();
                }
                operadores.push(token.lexema);
            }
        }
        while (!operadores.empty()) {
            postfija.push_back(operadores.top());
            operadores.pop();
        }
        cout << "\nNotacion postfija de " << resultado << ": ";
        for (const string& elemento : postfija) { cout << elemento << " "; }
        cout << endl;
        // Generar codigo de tres direcciones
        stack<string> pila;
        for (const string& elemento : postfija) {
            if (elemento == "+" || elemento == "-" || elemento == "*" || elemento == "/") {
                if (pila.size() < 2) { continue; }
                string derecha = pila.top();
                pila.pop();
                string izquierda = pila.top();
                pila.pop();
                string temp = "t" + to_string(temporal++);
                codigo.push_back(temp + " = " + izquierda + " " + elemento + " " + derecha);
                pila.push(temp);
            }
            else {
                pila.push(elemento);
            }
        }
        if (!pila.empty()) { codigo.push_back(resultado + " = " + pila.top()); }
        i = (j < tokens.size()) ? j + 1 : j;
    }
    return codigo;
}