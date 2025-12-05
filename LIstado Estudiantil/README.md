# 📘 Listado Estudiantil en C++

Este proyecto implementa un sistema de gestión de estudiantes utilizando **listas enlazadas simples** en C++.  
El programa permite agregar, eliminar, buscar, imprimir e invertir la lista de estudiantes mediante un menú interactivo.

---

## 📌 Funcionalidades principales

El programa ofrece las siguientes operaciones:

### ✔️ Agregar estudiante  
Registra un estudiante solicitando por teclado:
- Nombre completo  
- Año de nacimiento  
- Identificación  
- Promedio académico  
- Email  

Los datos se almacenan en un nodo agregado al final de la lista.

### ✔️ Eliminar estudiante por ID  
Busca el estudiante cuyo campo `identificacion` coincida con el ingresado y elimina su nodo de la lista.

### ✔️ Buscar estudiante por ID  
Recorre la lista y devuelve la posición del estudiante.  
Si no existe, retorna -1.

### ✔️ Mostrar lista completa  
Imprime en pantalla todos los estudiantes almacenados.

### ✔️ Guardar lista en archivo  
Escribe la información de todos los estudiantes en el archivo:

estudiantes.txt

### ✔️ Invertir la lista  
Invierte el orden de los nodos, modificando los punteros de la lista enlazada.

### ✔️ Acceder a un estudiante por índice  
Mediante el operador `[]`, se puede acceder directamente a un estudiante indicando su posición.

---

## 🧱 Estructuras utilizadas

### **struct Estudiante**
Guarda la información básica del estudiante:
- nombreCompleto  
- anioNacimiento  
- identificacion  
- promedioAcademico  
- email  

### **struct Nodo**
Representa cada nodo de la lista enlazada:
- `Estudiante data`  
- `Nodo* next`  

### **ListadoEstudiantil**
Clase que contiene:
- Puntero `head` al inicio de la lista  
- Entero `size` con la cantidad de nodos  
- Funciones para gestionar la lista

---

## ▶️ Ejecución del programa

### Compilar:
```bash
g++ main.cpp -o estudiantes
````
Ejecutar:
./estudiantes       # Linux/Mac
estudiantes.exe     # Windows

📂 Archivo generado

El programa crea un archivo:

estudiantes.txt


con la información completa de los estudiantes registrados.
🧩 Menú del programa
===== MENU LISTADO ESTUDIANTIL =====
1. Agregar estudiante
2. Eliminar estudiante por ID
3. Buscar estudiante por ID
4. Imprimir lista en pantalla
5. Guardar lista en archivo
6. Invertir lista
7. Mostrar estudiante por índice
0. Salir

✔️ Conclusión

Este proyecto permite practicar:

Uso de listas enlazadas simples

Manejo de archivos

Sobrecarga de operadores

Manipulación dinámica de memoria

Menús interactivos en C++
