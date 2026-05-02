CREATE TABLE alumnos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombres VARCHAR(100) NOT NULL,
    apellidos VARCHAR(100) NOT NULL,
    carnet VARCHAR(20) NOT NULL UNIQUE
);
CREATE TABLE cursos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100) NOT NULL,
    codigo VARCHAR(20) NOT NULL UNIQUE
);
CREATE TABLE secciones (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(50) NOT NULL,
    jornada VARCHAR(50) NOT NULL
);
CREATE TABLE alumnos_cursos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    alumno_id INT,
    curso_id INT,
    FOREIGN KEY (alumno_id) REFERENCES alumnos(id),
    FOREIGN KEY (curso_id) REFERENCES cursos(id)
);
CREATE TABLE alumnos_seccion (
    id INT AUTO_INCREMENT PRIMARY KEY,
    alumno_id INT,
    seccion_id INT,
    FOREIGN KEY (alumno_id) REFERENCES alumnos(id),
    FOREIGN KEY (seccion_id) REFERENCES secciones(id)
);
ALTER TABLE alumnos_cursos 
ADD UNIQUE (alumno_id, curso_id);

ALTER TABLE alumnos_seccion 
ADD UNIQUE (alumno_id, seccion_id);

INSERT INTO alumnos (nombres, apellidos, carnet) VALUES
('Juan', 'Pérez', '2024001'),
('María', 'López', '2024002');

INSERT INTO cursos (nombre, codigo) VALUES
('Programación I', 'PROG101'),
('Base de Datos', 'BD101');

INSERT INTO secciones (nombre, jornada) VALUES
('A', 'Matutina'),
('B', 'Nocturna');

SELECT * FROM alumnos;

UPDATE alumnos SET nombres = 'Carlos' WHERE id = 1;

DELETE FROM alumnos WHERE id = 2;

INSERT INTO alumnos_cursos (alumno_id, curso_id)
VALUES (1, 1);

select * from alumnos_cursos;

SHOW TABLE STATUS WHERE Name = 'alumnos_seccion';