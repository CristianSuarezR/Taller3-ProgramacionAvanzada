#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <fstream>

using namespace std;

// =====================================================
// ESTRUCTURA DEL NODO DEL HISTORIAL (LISTA ENLAZADA)
// =====================================================
struct NodoHistorial {
    string jugador;
    string ficha;
    string estadoMesa;
    NodoHistorial* sig;

    NodoHistorial(string j, string f, string e)
        : jugador(j), ficha(f), estadoMesa(e), sig(nullptr) {}
};

// =====================================================
// Clase Ficha
// =====================================================
class Ficha {
public:
    int a, b;
    Ficha(int x = 0, int y = 0) : a(x), b(y) {}

    string str() const {
        return "[" + to_string(a) + "|" + to_string(b) + "]";
    }

    void imprimir() const {
        cout << "[" << a << "|" << b << "]";
    }
};

// =====================================================
// Clase Jugador
// =====================================================
class Jugador {
public:
    string nombre;
    vector<Ficha> fichas;
    int puntos = 0;

    Jugador(string n = "") : nombre(n) {}

    void mostrarFichas() const {
        cout << "Fichas de " << nombre << ": ";
        for (int i = 0; i < fichas.size(); i++) {
            cout << "(" << i << ")";
            fichas[i].imprimir();
            cout << " ";
        }
        cout << endl;
    }

    bool tieneMovimiento(int izquierda, int derecha) {
        for (auto &f : fichas)
            if (f.a == izquierda || f.b == izquierda ||
                f.a == derecha || f.b == derecha)
                return true;
        return false;
    }
};

// =====================================================
// Clase JuegoDomino
// =====================================================
class JuegoDomino {
private:
    vector<Ficha> mazo;
    vector<Jugador> jugadores;
    vector<Ficha> mesa;

    // Lista enlazada
    NodoHistorial* historial = nullptr;

public:

    // Insertar nodo al final del historial
    void agregarAlHistorial(string jugador, string ficha, string estadoMesa) {
        NodoHistorial* nuevo = new NodoHistorial(jugador, ficha, estadoMesa);
        if (!historial) {
            historial = nuevo;
        } else {
            NodoHistorial* temp = historial;
            while (temp->sig)
                temp = temp->sig;
            temp->sig = nuevo;
        }
    }

    // Convertir mesa a string
    string mesaToString() {
        string s = "";
        for (auto &f : mesa)
            s += f.str() + " ";
        return s;
    }

    // Guardar historial en archivo
    void guardarHistorial() {
        ofstream file("historial_domino.txt");
        if (!file) {
            cout << "Error creando historial_domino.txt\n";
            return;
        }

        NodoHistorial* temp = historial;
        while (temp) {
            file << "Jugador: " << temp->jugador << "\n";
            file << "Ficha: " << temp->ficha << "\n";
            file << "Mesa: " << temp->estadoMesa << "\n";
            file << "-------------------------------------\n";
            temp = temp->sig;
        }

        file.close();
        cout << "\nHistorial guardado en historial_domino.txt\n";
    }

    void iniciar() {
        int n;
        cout << "Cantidad de jugadores (2 - 4): ";
        cin >> n;

        jugadores.clear();
        for (int i = 0; i < n; i++) {
            cout << "Nombre del jugador " << i+1 << ": ";
            string nombre;
            cin >> nombre;
            jugadores.push_back(Jugador(nombre));
        }

        jugarRondas();
        guardarHistorial();
    }

    // Crear las 28 fichas
    void crearMazo() {
        mazo.clear();
        for (int i = 0; i <= 6; i++)
            for (int j = i; j <= 6; j++)
                mazo.push_back(Ficha(i, j));
    }

    // Barajar y repartir fichas
    void repartir() {
        shuffle(mazo.begin(), mazo.end(), default_random_engine(time(NULL)));

        int porJugador = (mazo.size() / jugadores.size());
        for (int i = 0; i < jugadores.size(); i++) {
            jugadores[i].fichas.clear();
            for (int j = 0; j < porJugador; j++)
                jugadores[i].fichas.push_back(mazo.back()), mazo.pop_back();
        }
    }

    // Mostrar mesa
    void mostrarMesa() {
        cout << "\nMesa: ";
        for (auto &f : mesa) {
            f.imprimir();
            cout << " ";
        }
        cout << "\nIzquierda: " << mesa.front().a
             << " | Derecha: " << mesa.back().b << "\n";
    }

    // Intentar colocar ficha
    bool colocarFicha(Jugador &jug, int idx) {
        if (idx < 0 || idx >= jug.fichas.size()) return false;

        Ficha f = jug.fichas[idx];
        int izq = mesa.front().a;
        int der = mesa.back().b;

        // izquierda
        if (f.b == izq) {
            mesa.insert(mesa.begin(), f);
        } else if (f.a == izq) {
            mesa.insert(mesa.begin(), Ficha(f.b, f.a));
        }
        // derecha
        else if (f.a == der) {
            mesa.push_back(f);
        } else if (f.b == der) {
            mesa.push_back(Ficha(f.b, f.a));
        } else {
            return false;
        }

        // guardar historial
        agregarAlHistorial(jug.nombre, f.str(), mesaToString());

        jug.fichas.erase(jug.fichas.begin() + idx);
        return true;
    }

    // Jugar ronda
    void jugarRondas() {
        bool continuar = true;

        while (continuar) {
            crearMazo();
            repartir();
            mesa.clear();

            // primera ficha
            mesa.push_back(jugadores[0].fichas.back());
            jugadores[0].fichas.pop_back();

            agregarAlHistorial(jugadores[0].nombre,
                               mesa.back().str(),
                               mesaToString());

            bool bloqueado = false;
            int turno = 0;

            while (true) {
                Jugador &j = jugadores[turno];

                cout << "\n-------------------------------------------\n";
                cout << "Turno de " << j.nombre << endl;
                mostrarMesa();
                j.mostrarFichas();

                if (!j.tieneMovimiento(mesa.front().a, mesa.back().b)) {
                    cout << j.nombre << " NO puede jugar.\n";

                    bool todosBloqueados = true;
                    for (auto &x : jugadores)
                        if (x.tieneMovimiento(mesa.front().a, mesa.back().b))
                            todosBloqueados = false;

                    if (todosBloqueados) {
                        cout << "Juego bloqueado!\n";
                        break;
                    }
                }
                else {
                    int sel;
                    cout << "Elige ficha (indice): ";
                    cin >> sel;

                    if (!colocarFicha(j, sel))
                        cout << "Movimiento invalido.\n";
                    else if (j.fichas.empty()) {
                        cout << "\n" << j.nombre << " HA GANADO LA RONDA!\n";
                        j.puntos++;
                        break;
                    }
                }

                turno = (turno + 1) % jugadores.size();
            }

            cout << "\nPUNTAJE GENERAL\n";
            for (auto &j : jugadores)
                cout << j.nombre << ": " << j.puntos << endl;

            cout << "\n¿Jugar otra ronda? (1=si, 0=no): ";
            cin >> continuar;
        }

        cout << "\nFIN DEL JUEGO\n";
    }
};

// =====================================================
// MAIN
// =====================================================
int main() {
    JuegoDomino domino;
    domino.iniciar();
    return 0;
}
