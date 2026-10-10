# Compilador en C++

## Descripción

Proyecto educativo que implementa análisis léxico, sintáctico y semántico, generación de código intermedio y optimización básica.

## Requisitos

- Compilador C++ compatible con C++11 o superior.
- g++ instalado y disponible desde la terminal.

## Archivos principales

- `main.cpp`: punto de entrada.
- `Token.h`: definición de tokens y errores.
- `Lexer.cpp` y `Lexer.h`: análisis léxico.
- `Parser.cpp` y `Parser.h`: análisis sintáctico.
- `Semantico.cpp` y `Semantico.h`: análisis semántico.
- `CodigoIntermedio.cpp` y `CodigoIntermedio.h`: generación de código intermedio.
- `Optimizador.cpp` y `Optimizador.h`: optimización.

## Compilación

Desde la carpeta del proyecto, ejecutar:

```bash
g++ -std=c++11 main.cpp Lexer.cpp Parser.cpp Semantico.cpp CodigoIntermedio.cpp Optimizador.cpp -o main.exe
```

## Ejecución

En Windows:

```bash
main.exe
```

Introduce el código fuente línea por línea. Para finalizar la entrada en la terminal de Windows, presiona Ctrl+Z y después Enter.

## Ejemplo

```cpp
int resultado = 2 + 3 * 4;
int edad = 20;
```

El programa muestra los resultados de las etapas implementadas según las validaciones y la integración del código.