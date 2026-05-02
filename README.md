# DATABASE_CPP
Segundo Parcial Programacion I

Desarrollo de un programa de consola en C++ que se conecta a una base de datos de MySQL llamada **universidad**, permitiendo realizar operaciones CRUD (Create, Read, Update and Delete) sobre usuarios académicas.

El sistema gestiona alumnos, cursos, secciones y sus relaciones utilizando consultas SQL y conexión mediante MySQL Connector.

## Objetivo General

Desarrollar una aplicación de consola en C++ que se conecte a una base de datos MySQL y permita realizar operaciones CRUD sobre tablas del dominio académico.

### Tablas principales:

* **alumnos**: id, nombres, apellidos, carnet
* **cursos**: id, nombre, codigo
* **secciones**: id, nombre, jornada

### Tablas intermedias:

* **alumnos_cursos**: relación entre alumnos y cursos
* **alumnos_seccion**: relación entre alumno y sección (máximo una por alumno)

### Módulo Alumnos

* Listar alumnos con cursos y sección (con JOIN)
* Registrar alumnos
* Modificar datos de alumnos
* Eliminar alumnos

### Módulo Cursos

* Listar cursos
* Registrar cursos
* Modificar cursos
* Eliminar cursos (validando si están asignados)

### Módulo Secciones

* Listar secciones
* Registrar secciones
* Modificar secciones
* Eliminar secciones (validando asignaciones)

### Módulo Alumnos - Cursos

* Asignar cursos a alumnos
* Listar asignaciones
* Eliminar asignaciones
* Evitar duplicados

### Módulo Alumnos - Sección

* Asignar sección a alumno
* Listar asignaciones
* Modificar sección
* Eliminar asignación
* Validar una sola sección por alumno

## Menú del Sistema
```
===== SISTEMA UNIVERSIDAD =====
1. Alumnos
2. Cursos
3. Secciones
4. Alumnos - Cursos
5. Alumnos - Sección
6. Salir
```

Cada módulo contara con su propio submenú CRUD.

## Requisitos

* C++
* MySQL Server
* MySQL Workbench (opcional)
* MySQL Connector/C++
* Visual Studio

## Ejecución

1. Compilar el proyecto en Visual Studio
2. Ejecutar el programa
3. Navegar por el menú
4. Realizar operaciones CRUD

## Autor

* Samuel :D

---

## 📅 Fecha

2026
