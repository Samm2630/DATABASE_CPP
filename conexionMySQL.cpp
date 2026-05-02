#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;

//ALUMOS
void listarAlumnos(MYSQL* conn) {
    const char* consulta =
        "SELECT a.id, a.nombres, a.apellidos, a.carnet, "
        "COALESCE(GROUP_CONCAT(c.nombre), 'Sin cursos') AS cursos, "
        "COALESCE(MAX(s.nombre), 'Sin sección') AS seccion "
        "FROM alumnos a "
        "LEFT JOIN alumnos_cursos ac ON a.id = ac.alumno_id "
        "LEFT JOIN cursos c ON ac.curso_id = c.id "
        "LEFT JOIN alumnos_seccion ase ON a.id = ase.alumno_id "
        "LEFT JOIN secciones s ON ase.seccion_id = s.id "
        "GROUP BY a.id, a.nombres, a.apellidos, a.carnet;";
    if (mysql_query(conn, consulta)) {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }
    MYSQL_RES* result = mysql_store_result(conn);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        cout << "ID: " << row[0]
            << " | Nombre: " << row[1]
            << " | Apellido: " << row[2]
            << " | Carnet: " << row[3]
            << " | Cursos: " << (row[4] ? row[4] : "Sin cursos")
            << " | Seccion: " << (row[5] ? row[5] : "Sin sección")
            << endl;
    }
    mysql_free_result(result);
}

void insertarAlumno(MYSQL* conn) {
    string nombres, apellidos, carnet;
    cin.ignore();
    cout << "Nombres: ";
    getline(cin, nombres);
    cout << "Apellidos: ";
    getline(cin, apellidos);
    cout << "Carnet: ";
    getline(cin, carnet);
    string consulta = "INSERT INTO alumnos (nombres, apellidos, carnet) VALUES ('" +
        nombres + "', '" + apellidos + "', '" + carnet + "')";
    if (mysql_query(conn, consulta.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Alumno agregado correctamente" << endl;
    }
}

void modificarAlumno(MYSQL* conn) {
    int id;
    string nombres, apellidos;
    cout << "ID del alumno: ";
    cin >> id;
    cin.ignore();
    cout << "Nuevo nombre: ";
    getline(cin, nombres);
    cout << "Nuevo apellido: ";
    getline(cin, apellidos);
    string consulta = "UPDATE alumnos SET nombres='" + nombres +
        "', apellidos='" + apellidos +
        "' WHERE id=" + to_string(id);
    if (mysql_query(conn, consulta.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Alumno actualizado correctamente" << endl;
    }
}

void eliminarAlumno(MYSQL* conn) {
    int id;
    cout << "ID del alumno a eliminar: ";
    cin >> id;
    string consulta = "DELETE FROM alumnos WHERE id=" + to_string(id);
    if (mysql_query(conn, consulta.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Alumno eliminado correctamente" << endl;
    }
}

//CURSOS
void listarCursos(MYSQL* conn) {
    const char* consulta = "SELECT id, nombre, codigo FROM cursos";
    if (mysql_query(conn, consulta)) {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }
    MYSQL_RES* result = mysql_store_result(conn);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        cout << "ID: " << row[0]
            << " | Nombre: " << row[1]
            << " | Codigo: " << row[2]
            << endl;
    }
    mysql_free_result(result);
}

void insertarCurso(MYSQL* conn) {
    string nombre, codigo;
    cin.ignore();
    cout << "Nombre del curso: ";
    getline(cin, nombre);
    cout << "Codigo: ";
    getline(cin, codigo);
    string consulta = "INSERT INTO cursos (nombre, codigo) VALUES ('" +
        nombre + "', '" + codigo + "')";
    if (mysql_query(conn, consulta.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Curso agregado correctamente" << endl;
    }
}

void modificarCurso(MYSQL* conn) {
    int id;
    string nombre, codigo;
    cout << "ID del curso: ";
    cin >> id;
    cin.ignore();
    cout << "Nuevo nombre: ";
    getline(cin, nombre);
    cout << "Nuevo codigo: ";
    getline(cin, codigo);
    string consulta = "UPDATE cursos SET nombre='" + nombre +
        "', codigo='" + codigo +
        "' WHERE id=" + to_string(id);
    if (mysql_query(conn, consulta.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Curso actualizado correctamente" << endl;
    }
}

void eliminarCurso(MYSQL* conn) {
    int id;
    cout << "ID del curso a eliminar: ";
    cin >> id;
    string validar = "SELECT * FROM alumnos_cursos WHERE curso_id=" + to_string(id);
    if (mysql_query(conn, validar.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }
    MYSQL_RES* result = mysql_store_result(conn);
    if (mysql_num_rows(result) > 0) {
        cout << "No se puede eliminar, curso asignado a alumnos" << endl;
        mysql_free_result(result);
        return;
    }
    mysql_free_result(result);
    string eliminar = "DELETE FROM cursos WHERE id=" + to_string(id);
    if (mysql_query(conn, eliminar.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Curso eliminado correctamente" << endl;
    }
}

//SECCIONES
void listarSecciones(MYSQL* conn) {
    const char* consulta = "SELECT id, nombre, jornada FROM secciones";
    if (mysql_query(conn, consulta)) {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }
    MYSQL_RES* result = mysql_store_result(conn);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        cout << "ID: " << row[0]
            << " | Nombre: " << row[1]
            << " | Jornada: " << row[2]
            << endl;
    }
    mysql_free_result(result);
}

void insertarSeccion(MYSQL* conn) {
    string nombre, jornada;
    cin.ignore();
    cout << "Nombre de la seccion: ";
    getline(cin, nombre);
    cout << "Jornada: ";
    getline(cin, jornada);
    string consulta = "INSERT INTO secciones (nombre, jornada) VALUES ('" +
        nombre + "', '" + jornada + "')";
    if (mysql_query(conn, consulta.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Seccion agregada correctamente" << endl;
    }
}

void modificarSeccion(MYSQL* conn) {
    int id;
    string nombre, jornada;
    cout << "ID de la seccion: ";
    cin >> id;
    cin.ignore();
    cout << "Nuevo nombre: ";
    getline(cin, nombre);
    cout << "Nueva jornada: ";
    getline(cin, jornada);
    string consulta = "UPDATE secciones SET nombre='" + nombre +
        "', jornada='" + jornada +
        "' WHERE id=" + to_string(id);
    if (mysql_query(conn, consulta.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Seccion actualizada correctamente" << endl;
    }
}

void eliminarSeccion(MYSQL* conn) {
    int id;
    cout << "ID de la seccion a eliminar: ";
    cin >> id;
    string validar = "SELECT * FROM alumnos_seccion WHERE seccion_id=" + to_string(id);

    if (mysql_query(conn, validar.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }
    MYSQL_RES* result = mysql_store_result(conn);
    if (mysql_num_rows(result) > 0) {
        cout << "No se puede eliminar, la seccion tiene alumnos asignados" << endl;
        mysql_free_result(result);
        return;
    }
    mysql_free_result(result);
    string eliminar = "DELETE FROM secciones WHERE id=" + to_string(id);
    if (mysql_query(conn, eliminar.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Seccion eliminada correctamente" << endl;
    }
}

//ALUMNOS-CURSOS
void listarAlumnosCursos(MYSQL* conn) {
    const char* consulta =
        "SELECT a.nombres, a.apellidos, c.nombre "
        "FROM alumnos_cursos ac "
        "JOIN alumnos a ON ac.alumno_id = a.id "
        "JOIN cursos c ON ac.curso_id = c.id";
    if (mysql_query(conn, consulta)) {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }
    MYSQL_RES* result = mysql_store_result(conn);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        cout << "Alumno: " << row[0] << " " << row[1]
            << " | Curso: " << row[2] << endl;
    }
    mysql_free_result(result);
}

void asignarCurso(MYSQL* conn) {
    int alumno_id, curso_id;
    cout << "ID del alumno: ";
    cin >> alumno_id;
    cout << "ID del curso: ";
    cin >> curso_id;
    string consulta = "INSERT INTO alumnos_cursos (alumno_id, curso_id) VALUES (" +
        to_string(alumno_id) + ", " + to_string(curso_id) + ")";
    if (mysql_query(conn, consulta.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Curso asignado correctamente" << endl;
    }
}

void eliminarAsignacionCurso(MYSQL* conn) {
    int alumno_id, curso_id;
    cout << "ID del alumno: ";
    cin >> alumno_id;
    cout << "ID del curso a quitar: ";
    cin >> curso_id;
    string consulta = "DELETE FROM alumnos_cursos WHERE alumno_id=" +
        to_string(alumno_id) + " AND curso_id=" + to_string(curso_id);
    if (mysql_query(conn, consulta.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Asignacion eliminada correctamente" << endl;
    }
}

//ALUMNOS-SECCION
void listarAlumnosSeccion(MYSQL* conn) {
    const char* consulta =
        "SELECT a.nombres, a.apellidos, s.nombre, s.jornada "
        "FROM alumnos_seccion ase "
        "JOIN alumnos a ON ase.alumno_id = a.id "
        "JOIN secciones s ON ase.seccion_id = s.id";
    if (mysql_query(conn, consulta)) {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }
    MYSQL_RES* result = mysql_store_result(conn);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        cout << "Alumno: " << row[0] << " " << row[1]
            << " | Seccion: " << row[2]
            << " | Jornada: " << row[3] << endl;
    }
    mysql_free_result(result);
}

void asignarSeccion(MYSQL* conn) {
    int alumno_id, seccion_id;
    cout << "ID del alumno: ";
    cin >> alumno_id;
    cout << "ID de la seccion: ";
    cin >> seccion_id;
    string validar = "SELECT * FROM alumnos_seccion WHERE alumno_id=" + to_string(alumno_id);
    if (mysql_query(conn, validar.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
        return;
    }
    MYSQL_RES* result = mysql_store_result(conn);
    if (mysql_num_rows(result) > 0) {
        cout << "El alumno ya tiene una seccion asignada" << endl;
        mysql_free_result(result);
        return;
    }
    mysql_free_result(result);
    string consulta = "INSERT INTO alumnos_seccion (alumno_id, seccion_id) VALUES (" +
        to_string(alumno_id) + ", " + to_string(seccion_id) + ")";
    if (mysql_query(conn, consulta.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Seccion asignada correctamente" << endl;
    }
}

void modificarSeccionAlumno(MYSQL* conn) {
    int alumno_id, nueva_seccion;
    cout << "ID del alumno: ";
    cin >> alumno_id;
    cout << "Nueva seccion ID: ";
    cin >> nueva_seccion;
    string consulta = "UPDATE alumnos_seccion SET seccion_id=" +
        to_string(nueva_seccion) +
        " WHERE alumno_id=" + to_string(alumno_id);
    if (mysql_query(conn, consulta.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Seccion actualizada correctamente" << endl;
    }
}

void eliminarSeccionAlumno(MYSQL* conn) {
    int alumno_id;
    cout << "ID del alumno: ";
    cin >> alumno_id;
    string consulta = "DELETE FROM alumnos_seccion WHERE alumno_id=" +
        to_string(alumno_id);
    if (mysql_query(conn, consulta.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Seccion eliminada correctamente" << endl;
    }
}

//MENUS
void menuAlumnos(MYSQL* conn) {
    int opcion;
    do {
        cout << "\n===== MENU ALUMNOS =====\n";
        cout << "1. Listar\n";
        cout << "2. Grabar\n";
        cout << "3. Modificar\n";
        cout << "4. Eliminar\n";
        cout << "5. Regresar\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
        case 1: listarAlumnos(conn); break;
        case 2: insertarAlumno(conn); break;
        case 3: modificarAlumno(conn); break;
        case 4: eliminarAlumno(conn); break;
        }
    } while (opcion != 5);
}

void menuCursos(MYSQL* conn) {
    int opcion;
    do {
        cout << "\n===== MENU CURSOS =====\n";
        cout << "1. Listar\n";
        cout << "2. Grabar\n";
        cout << "3. Modificar\n";
        cout << "4. Eliminar\n";
        cout << "5. Regresar\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
        case 1: listarCursos(conn); break;
        case 2: insertarCurso(conn); break;
        case 3: modificarCurso(conn); break;
        case 4: eliminarCurso(conn); break;
        }
    } while (opcion != 5);
}

void menuSecciones(MYSQL* conn) {
    int opcion;
    do {
        cout << "\n===== MENU SECCIONES =====\n";
        cout << "1. Listar\n";
        cout << "2. Grabar\n";
        cout << "3. Modificar\n";
        cout << "4. Eliminar\n";
        cout << "5. Regresar\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
        case 1: listarSecciones(conn); break;
        case 2: insertarSeccion(conn); break;
        case 3: modificarSeccion(conn); break;
        case 4: eliminarSeccion(conn); break;
        }
    } while (opcion != 5);
}

void menuAlumnosCursos(MYSQL* conn) {
    int opcion;
    do {
        cout << "\n===== MENU ALUMNOS-CURSOS =====\n";
        cout << "1. Listar\n";
        cout << "2. Asignar curso\n";
        cout << "3. Eliminar asignacion\n";
        cout << "4. Regresar\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
        case 1: listarAlumnosCursos(conn); break;
        case 2: asignarCurso(conn); break;
        case 3: eliminarAsignacionCurso(conn); break;
        }

    } while (opcion != 4);
}

void menuAlumnosSeccion(MYSQL* conn) {
    int opcion;
    do {
        cout << "\n===== MENU ALUMNOS-SECCION =====\n";
        cout << "1. Listar\n";
        cout << "2. Asignar\n";
        cout << "3. Modificar\n";
        cout << "4. Eliminar\n";
        cout << "5. Regresar\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
        case 1: listarAlumnosSeccion(conn); break;
        case 2: asignarSeccion(conn); break;
        case 3: modificarSeccionAlumno(conn); break;
        case 4: eliminarSeccionAlumno(conn); break;
        }
    } while (opcion != 5);
}

//MENU PRINCIPAL
void menuPrincipal(MYSQL* conn) {
    int opcion;
    do {
        cout << "\n===== BASE DE DATOS UNIVERSIDAD =====\n";
        cout << "1. Alumnos\n";
        cout << "2. Cursos\n";
        cout << "3. Secciones\n";
        cout << "4. Alumnos - Cursos\n";
        cout << "5. Alumnos - Seccion\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
        case 1: menuAlumnos(conn); break;
        case 2: menuCursos(conn); break;
        case 3: menuSecciones(conn); break;
        case 4: menuAlumnosCursos(conn); break;
        case 5: menuAlumnosSeccion(conn); break;
        case 6: cout << "Saliendo..." << endl; break;
        default: cout << "Opcion invalida\n";
        }
    } while (opcion != 6);
}

//MAIN
int main() {
    MYSQL* conn;
    conn = mysql_init(0);
    if (conn == NULL) {
        cout << "Error al inicializar MySQL" << endl;
        return 1;
    }
    conn = mysql_real_connect(conn, "localhost", "root", "EWE/2630mz", "universidad", 3306, NULL, 0);
    if (conn) {
        cout << "Conexion exitosa!" << endl;
        // 👉 AQUÍ LLAMAS TU SISTEMA
        menuPrincipal(conn);
    } else {
        cout << "Error: " << mysql_error(conn) << endl;
    }

    mysql_close(conn);
    system("pause");
    return 0;
}