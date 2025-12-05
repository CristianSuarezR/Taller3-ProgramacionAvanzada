#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// ========================
// ESTRUCTURA DE LISTA
// ========================
struct Nodo {
    double tiempo;
    double amplitud;
    Nodo* sig;
    Nodo(double t, double a) : tiempo(t), amplitud(a), sig(nullptr) {}
};

// ========================
// CLASE ECG
// ========================
class ECG {
private:
    Nodo* head;
    Nodo* tail;

public:
    ECG() : head(nullptr), tail(nullptr) {}

    ~ECG() {
        while (head) {
            Nodo* temp = head;
            head = head->sig;
            delete temp;
        }
    }

    // ----------------------------
    // Cargar archivo .txt
    // ----------------------------
    void cargarArchivo(const string& nombre) {
        ifstream archivo(nombre);

        if (!archivo.is_open()) {
            cout << "Error al abrir archivo." << endl;
            return;
        }

        double t, a;
        while (archivo >> t >> a) {
            insertarOrdenado(t, a);
        }

        archivo.close();
    }

    // ----------------------------
    // Insertar en lista enlazada
    // ----------------------------
    void insertarOrdenado(double tiempo, double amplitud) {
        Nodo* nuevo = new Nodo(tiempo, amplitud);

        if (!head) {
            head = tail = nuevo;
            return;
        }

        Nodo* actual = head;
        Nodo* previo = nullptr;

        while (actual && actual->tiempo < tiempo) {
            previo = actual;
            actual = actual->sig;
        }

        if (!previo) { // insertar al inicio
            nuevo->sig = head;
            head = nuevo;
        }
        else {
            previo->sig = nuevo;
            nuevo->sig = actual;
            if (!actual) tail = nuevo; // insertar al final
        }
    }

    // ----------------------------
    // FILTRO PROMEDIO 5 MUESTRAS
    // ----------------------------
    void filtrarSenal() {
        Nodo* n1 = head;
        if (!n1 || !n1->sig) return;

        Nodo* n2 = n1->sig;
        Nodo* n3 = n2->sig;
        if (!n3) return;

        Nodo* n4 = n3->sig;
        if (!n4) return;

        Nodo* n5 = n4->sig;
        if (!n5) return;

        Nodo* actual = n3;

        while (n1 && n2 && n3 && n4 && n5) {
            n3->amplitud = (n1->amplitud + n2->amplitud + n3->amplitud + n4->amplitud + n5->amplitud) / 5.0;

            n1 = n2;
            n2 = n3;
            n3 = n4;
            n4 = n5;
            n5 = n5->sig;
        }
    }

    // ----------------------------
    // DURACIÓN TOTAL DEL ECG
    // ----------------------------
    double obtenerDuracion() {
        if (!head || !tail) return 0.0;
        return tail->tiempo - head->tiempo;
    }

    // ----------------------------
    // DETECCIÓN DE PICOS
    // ----------------------------
    int detectarPicos(double umbral = 0.30) {
        int picos = 0;
        Nodo* prev = head;
        Nodo* curr = (prev ? prev->sig : nullptr);
        Nodo* next = (curr ? curr->sig : nullptr);

        while (prev && curr && next) {
            if (curr->amplitud > umbral && 
                curr->amplitud > prev->amplitud &&
                curr->amplitud > next->amplitud) 
            {
                picos++;
            }

            prev = curr;
            curr = next;
            next = next->sig;
        }

        return picos;
    }
};

int main() {

    ECG ecg;

    ecg.cargarArchivo("ECG.txt");  
    ecg.filtrarSenal();

    int picos = ecg.detectarPicos(0.30); // UMBRAL OPTIMO PARA TU ARCHIVO
    double duracion = ecg.obtenerDuracion();

    double bpm = (duracion > 0) ? (picos * 60.0 / duracion) : 0;

    cout << "Procesamiento completado." << endl;
    cout << "Picos detectados: " << picos << endl;
    cout << "Frecuencia cardiaca (BPM): " << bpm << endl;

    return 0;
}
