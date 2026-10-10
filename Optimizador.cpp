#include "Optimizador.h"
#include <sstream>
#include <cstdlib>

vector<string> Optimizador::optimizar(vector<string> codigo) {
    vector<string> resultado;
    for (const string& linea : codigo) {
        string variable, igual, izquierda, operador, derecha;
        stringstream ss(linea);
        ss >> variable >> igual >> izquierda;
        if (ss >> operador >> derecha) {
            char* fin1;
            char* fin2;
            double a = strtod(izquierda.c_str(), &fin1);
            double b = strtod(derecha.c_str(), &fin2);
            if (*fin1 == '\0' && *fin2 == '\0') {
                double valor = 0;
                bool valido = true;
                if (operador == "+") { valor = a + b; }
                else if (operador == "-") { valor = a - b; }
                else if (operador == "*") { valor = a * b; }
                else if (operador == "/" && b != 0) { valor = a / b; }
                else { valido = false; }
                if (valido) {
                    stringstream salida;
                    salida << variable << " = " << valor;
                    resultado.push_back(salida.str());
                    continue;
                }
            }
        }
        resultado.push_back(linea);
    }
    return resultado;
}