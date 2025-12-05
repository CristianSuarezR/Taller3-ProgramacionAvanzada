# 📘 README – domino2.0.cpp

## 🎯 Descripción General  
Este programa implementa una versión básica del juego de dominó, permitiendo generar las fichas, mezclarlas, repartirlas a los jugadores y simular la mecánica principal del juego. El código fue desarrollado como ejercicio práctico para reforzar el uso de estructuras de datos, funciones, clases y control de flujo en C++.

---

## ⚙️ Metodología de Desarrollo

El programa sigue una metodología estructurada dividida en cuatro etapas:

### 1. Modelado de Datos (Diseño de la Ficha de Dominó)  
Se define una estructura o clase `Ficha` que representa cada pieza del dominó:

- Cada ficha tiene dos valores enteros: **lado izquierdo (a)** y **lado derecho (b)**.  
- Se incluyen funciones para:
  - Mostrar la ficha en formato `[a|b]`  
  - Comparar fichas  
  - Rotar una ficha si es necesario (para que coincida con la jugada)

Esta etapa permite trabajar con las fichas de forma ordenada y reutilizable.

---

### 2. Generación del Conjunto de Fichas  
Se construye el **juego completo de dominó doble-6**, generando todas las combinaciones posibles


El programa:  
- Crea un vector de fichas vacías  
- Añade 28 fichas sin repeticiones  
- Garantiza que el conjunto esté completo y en orden

---

### 3. Mezcla y Reparto de Fichas  
Una vez generado el mazo:

- Se mezcla usando funciones de aleatoriedad (`shuffle` o similar)  
- Se reparten fichas a cada jugador (por lo general 7 por jugador)  
- Las fichas restantes quedan como **pozo** o **bazar**

Este proceso simula el inicio real de una partida de dominó.

---

### 4. Lógica del Juego  
El programa implementa la mecánica principal del dominó:

#### a) Determinación de la ficha inicial  
- Usualmente la ficha doble más alta  
- O la primera del jugador 1  
- Según cómo esté diseñado el código

#### b) Ciclo de turnos  
Cada jugador intenta:  
1. Verificar si tiene una ficha jugable  
2. Comparar con los valores en los extremos de la mesa  
3. Colocar la ficha correspondiente  
4. Rotarla si es necesario para coincidir

Si un jugador no tiene jugada:  
- Toma del pozo  
- O pasa (según las reglas implementadas)

#### c) Condiciones de finalización  
El programa determina si:  
- Un jugador se queda sin fichas → **gana**  
- La mesa se tranca → **se cuentan puntos**  
- No hay más fichas en el pozo

---

## 🧪 Validaciones y Manejo de Errores  
El código incluye validaciones para:  
- Evitar jugadas ilegales  
- Detectar cuando un jugador no puede jugar  
- Manejar el pozo vacío  
- Asegurar que la ficha colocada coincida con los valores en los extremos

---

## 🖥️ Compilación y Ejecución

### Compilación (Windows – MinGW):
g++ domino2.0.cpp -o domino2.0.exe

### Ejecución:

domino2.exe



