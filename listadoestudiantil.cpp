#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// ---------------------------------------------------------------
// Estructura que almacena la información del estudiante
// ---------------------------------------------------------------
struct Estudiante {
    string nombreCompleto;
    int anioNacimiento;
    string identificacion;
    float promedioAcademico;
    string email;
};

// ---------------------------------------------------------------
// Nodo de la lista enlazada
// ---------------------------------------------------------------
struct Nodo {
    Estudiante data;
    Nodo* next;

    Nodo(const Estudiante& est) : data(est), next(nullptr) {}
};

// ---------------------------------------------------------------
// Clase ListadoEstudiantil
// ---------------------------------------------------------------
class ListadoEstudiantil {
private:
    Nodo* head;
    int size;

public:

    ListadoEstudiantil() : head(nullptr), size(0) {}

    // Insertar al final
    void insertarFinal(const Estudiante& est) {
        Nodo* nuevo = new Nodo(est);

        if (!head) {  
            head = nuevo;
        } else {
            Nodo* actual = head;
            while (actual->next != nullptr) {
                actual = actual->next;
            }
            actual->next = nuevo;
        }
        size++;
    }

    // Eliminar por identificación
    bool eliminarPorID(const string& id) {
        if (!head) return false;

        if (head->data.identificacion == id) {
            Nodo* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }

        Nodo* actual = head;
        while (actual->next && actual->next->data.identificacion != id) {
            actual = actual->next;
        }

        if (!actual->next) return false;

        Nodo* nodoEliminar = actual->next;
        actual->next = nodoEliminar->next;
        delete nodoEliminar;
        size--;
        return true;
    }

    // Buscar por ID
    int buscarPorID(const string& id) {
        Nodo* actual = head;
        int pos = 0;

        while (actual) {
            if (actual->data.identificacion == id)
                return pos;
            actual = actual->next;
            pos++;
        }
        return -1;
    }

    // Imprimir en archivo
    void imprimirEnArchivo(const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);

        if (!archivo.is_open()) {
            cout << "Error abriendo archivo.\n";
            return;
        }

        Nodo* actual = head;
        while (actual) {
            archivo << "Nombre: " << actual->data.nombreCompleto << "\n";
            archivo << "Año nacimiento: " << actual->data.anioNacimiento << "\n";
            archivo << "ID: " << actual->data.identificacion << "\n";
            archivo << "Promedio: " << actual->data.promedioAcademico << "\n";
            archivo << "Email: " << actual->data.email << "\n";
            archivo << "---------------------------------------\n";
            actual = actual->next;
        }

        archivo.close();
        cout << "Archivo generado correctamente.\n";
    }

    // Operador []
    Estudiante& operator[](int index) {
        if (index < 0 || index >= size)
            throw out_of_range("Indice fuera de rango.");

        Nodo* actual = head;
        for (int i = 0; i < index; i++)
            actual = actual->next;

        return actual->data;
    }

    // Invertir lista
    void invertir() {
        Nodo* prev = nullptr;
        Nodo* actual = head;
        Nodo* siguiente = nullptr;

        while (actual) {
            siguiente = actual->next;
            actual->next = prev;
            prev = actual;
            actual = siguiente;
        }
        head = prev;
    }

    // Imprimir en pantalla
    void imprimirLista() {
        Nodo* actual = head;
        while (actual) {
            cout << "Nombre: " << actual->data.nombreCompleto << endl;
            cout << "Año nacimiento: " << actual->data.anioNacimiento << endl;
            cout << "ID: " << actual->data.identificacion << endl;
            cout << "Promedio: " << actual->data.promedioAcademico << endl;
            cout << "Email: " << actual->data.email << endl;
            cout << "--------------------------------------\n";
            actual = actual->next;
        }
    }

    ~ListadoEstudiantil() {
        Nodo* actual = head;
        while (actual) {
            Nodo* temp = actual;
            actual = actual->next;
            delete temp;
        }
    }
};

// ---------------------------------------------------------------
// Función para ingresar un estudiante por teclado
// ---------------------------------------------------------------
Estudiante ingresarEstudiante() {
    Estudiante e;

    cout << "Ingrese nombre completo: ";
    getline(cin, e.nombreCompleto);

    cout << "Ingrese año de nacimiento: ";
    cin >> e.anioNacimiento;
    cin.ignore();

    cout << "Ingrese identificación: ";
    getline(cin, e.identificacion);

    cout << "Ingrese promedio académico: ";
    cin >> e.promedioAcademico;
    cin.ignore();

    cout << "Ingrese email: ";
    getline(cin, e.email);

    return e;
}

// ---------------------------------------------------------------
// MAIN CON MENÚ COMPLETO
// ---------------------------------------------------------------
int main() {
    ListadoEstudiantil lista;
    int opcion;

    do {
        cout << "\n===== MENU LISTADO ESTUDIANTIL =====\n";
        cout << "1. Agregar estudiante\n";
        cout << "2. Eliminar estudiante por ID\n";
        cout << "3. Buscar estudiante por ID\n";
        cout << "4. Imprimir lista en pantalla\n";
        cout << "5. Guardar lista en archivo\n";
        cout << "6. Invertir lista\n";
        cout << "7. Mostrar estudiante por índice\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            cout << "\n--- Ingresar estudiante ---\n";
            Estudiante e = ingresarEstudiante();
            lista.insertarFinal(e);
        }
        else if (opcion == 2) {
            string id;
            cout << "Ingrese ID a eliminar: ";
            getline(cin, id);
            if (lista.eliminarPorID(id))
                cout << "Eliminado correctamente.\n";
            else
                cout << "ID no encontrado.\n";
        }
        else if (opcion == 3) {
            string id;
            cout << "Ingrese ID a buscar: ";
            getline(cin, id);
            int pos = lista.buscarPorID(id);
            if (pos != -1)
                cout << "Encontrado en posición: " << pos << endl;
            else
                cout << "ID no encontrado.\n";
        }
        else if (opcion == 4) {
            cout << "\n--- LISTA DE ESTUDIANTES ---\n";
            lista.imprimirLista();
        }
        else if (opcion == 5) {
            lista.imprimirEnArchivo("estudiantes.txt");
        }
        else if (opcion == 6) {
            lista.invertir();
            cout << "Lista invertida.\n";
        }
        else if (opcion == 7) {
            int index;
            cout << "Ingrese índice: ";
            cin >> index;
            cin.ignore();

            try {
                Estudiante& e = lista[index];
                cout << "\n--- Estudiante en índice " << index << " ---\n";
                cout << "Nombre: " << e.nombreCompleto << endl;
                cout << "Año nacimiento: " << e.anioNacimiento << endl;
                cout << "ID: " << e.identificacion << endl;
                cout << "Promedio: " << e.promedioAcademico << endl;
                cout << "Email: " << e.email << endl;
            }
            catch (exception& ex) {
                cout << ex.what() << endl;
            }
        }

    } while (opcion != 0);

    cout << "Programa finalizado.\n";
    return 0;
}
