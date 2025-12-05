# 📘 Procesamiento de Señal ECG – `SenialECG.cpp`

Este proyecto implementa un programa en C++ para cargar, filtrar y analizar una señal ECG (electrocardiograma) a partir de un archivo de texto. El sistema utiliza listas enlazadas para gestionar los datos y calcula la frecuencia cardíaca (BPM) a partir de la detección de picos.

---

## 📁 Archivos necesarios

El programa requiere **obligatoriamente** que el archivo:

ECG.txt

esté en **la misma carpeta** donde se encuentra:

SenialECG.cpp

De lo contrario, el programa no podrá abrir la señal y mostrará error al cargar el archivo.

---

## 🎯 Objetivo del Programa

El propósito del código es:

- Cargar muestras de ECG desde un archivo de texto.
- Almacenar la señal en una lista enlazada ordenada por tiempo.
- Filtrar la señal utilizando un promedio móvil de 5 muestras.
- Detectar picos (complejos QRS).
- Calcular la duración total de la señal.
- Estimar la frecuencia cardíaca en BPM.

---

# ⚙️ Metodología del Programa

El programa se fundamenta en los siguientes pasos:

---

## **1. Lectura de la señal desde archivo (ECG.txt)**

El archivo debe contener dos columnas:

tiempo amplitud

El método:

void cargarArchivo(const string& nombre)

abre el archivo y lee cada par (tiempo, amplitud).
Cada muestra se inserta ordenadamente en la lista enlazada según el tiempo.

2. Almacenamiento en una lista enlazada

Se usa una estructura:
struct Nodo {
    double tiempo;
    double amplitud;
    Nodo* sig;
};
Cada muestra es un nodo, permitiendo:

Recorrido secuencial.

Inserción ordenada.

Bajo uso de memoria.

Procesamiento directo sin necesidad de vectores.

3. Filtro de Promedio Móvil (5 puntos)

El método:
void filtrarSenal()
aplica un filtro suavizador usando:

Promedio = (n1 + n2 + n3 + n4 + n5) / 5


Este filtro reduce ruido y permite una detección de picos más limpia.

4. Obtención de la duración total de la señal

Usando:

double obtenerDuracion()


se calcula:

duración = tiempo_final - tiempo_inicial


Esto es esencial para convertir picos detectados a BPM.

5. Detección de picos (Complejos QRS)

El método:

int detectarPicos(double umbral)


compara cada muestra con sus vecinas:

Un punto curr se considera pico si:

Es mayor que el umbral.

Es mayor que la muestra anterior.

Es mayor que la muestra siguiente.

Esto permite identificar los picos R del ECG.

6. Cálculo de Frecuencia Cardíaca (BPM)

La fórmula usada:

BPM = (picos_detectados * 60) / duración_total


Si la señal es válida y el umbral correcto, el resultado debe aproximarse a la frecuencia cardíaca real.

▶️ Compilación y Ejecución
Compilar:
g++ SenialECG.cpp -o ECG

Ejecutar:
./ECG      # Linux / MacOS
ECG.exe    # Windows


📌 IMPORTANTE:
Debes ejecutar el programa desde la misma carpeta donde están:

SenialECG.cpp
ECG.txt

📌 Notas importantes

Si el archivo ECG.txt NO está en la misma carpeta, el programa mostrará:

Error al abrir archivo.


Puedes ajustar el umbral del detector:

ecg.detectarPicos(0.30);


según la amplitud de tu señal.

✅ Conclusión

Este programa implementa un procesamiento simple pero efectivo de señales ECG usando:

Listas enlazadas

Filtrado por promedio móvil

Detección de picos basada en vecinos

Cálculo directo de BPM

Es ideal para prácticas de estructuras de datos, lectura de archivos y análisis básico de señales biomédicas.

