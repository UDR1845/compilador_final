#include <iostream>
#include <string>
#include <cctype>
#include <ctype.h>
#include "Lexer.h"
#include "Parser.h"
#include "Semantico.h"
#include "CodigoIntermedio.h"
#include "Optimizador.h"
using namespace std;

string nombreToken(TipoToken tipo){
    switch(tipo){
        case TipoToken::LITERAL_INT:
            return "LITERAL_ENTERO";
        case TipoToken::LITERAL_FLOAT:
            return "LITERAL_REAL";
        case TipoToken::LITERAL_STRING:
            return "LITERAL_STRING";
        case TipoToken::IDENTIFICADOR:
            return "IDENTIFICADOR";
        case TipoToken::PALABRA_RESERVADA:
            return "PALABRA_RESERVADA";
        case TipoToken::OPERADOR:
            return "OPERADOR";
        case TipoToken::ASIGNACION:
            return "ASIGNACION";
        case TipoToken::DELIMITADOR:
            return "DELIMITADOR";
        case TipoToken::DESCONOCIDO:
            return "DESCONOCIDO";
    }
    return "";
}


int main(){
    string codigo, linea;
    cout << "Ingrese codigo: (Ctrl+Z y Enter para terminar):\n";
    while (getline(cin, linea)) { codigo += linea + '\n'; }

    Lexer lexer(codigo);
    vector<Token> tokens = lexer.analizar();
    cout << "--------TOKENS ENCONTRADOS---------\n";
    for(Token token : tokens){
        cout << "<" << nombreToken(token.tipo) << ", " << token.lexema << ">" << endl;
    }
    vector<ErrorLexico> errores = lexer.obtenerErrores();
    cout << "\n-------- ERRORES LEXICOS --------\n";
    if (errores.empty()){ cout << "No se encontraron errores lexicos." << endl; }
    else{
        for (ErrorLexico error : errores){
            cout << "Lexema: " << error.lexema << endl;
            cout << "Linea: " << error.linea << endl;
            cout << "Columna: " << error.columna << endl;
            cout << "Mensaje: " << error.mensaje << endl;
            cout << "----------------------" << endl;
        }
    }

    cout << "\n===============================" << endl;
    cout << "     ANALISIS SINTACTICO" << endl;
    cout << "===============================" << endl;

    Parser parser(tokens);
    if (parser.analizar()) { 
        cout << "\nResultado: " << "Instruccion sintacticamente correcta." << endl;

        Semantico semantico;
        bool correcto = semantico.analizar(tokens);
        semantico.mostrarTabla();
        if (correcto) { 
            cout << "Analisis semantico correcto." << endl; 
            
            CodigoIntermedio generador;
            vector<string> codigo = generador.generar(tokens);
            cout << "\n--- CODIGO INTERMEDIO ---\n";
            for (const string& linea : codigo) { cout << linea << endl; }

            Optimizador optimizador;
            vector<string> optimizado = optimizador.optimizar(codigo);
            cout << "\n--- CODIGO OPTIMIZADO ---\n";
            for (const string& instruccion : optimizado) { cout << instruccion << endl; }
        }
        else { cout << "Se encontraron errores semanticos." << endl; }
    }
    else { cout << "\nResultado: " << "Instruccion sintacticamente incorrecta." << endl; }

    return 0;
}

//COMPILACION
//g++ main.cpp Lexer.cpp Parser.cpp Semantico.cpp CodigoIntermedio.cpp Optimizador.cpp -o main
//main