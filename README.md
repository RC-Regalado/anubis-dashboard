# Anubis Dashboard

Este proyecto consiste en la implementación de un servidor HTTP construido en C++ que soporta múltiples hilos para manejar conexiones concurrentes, implementa los métodos HTTP más comunes (GET, POST, DELETE) y utiliza una base de datos mínima en SQLite para almacenamiento persistente.

## Características

- **Servidor HTTP**:
  - Manejo de conexiones concurrentes utilizando un `thread pool`.
  - Soporte para los métodos HTTP comunes: `GET`, `POST` y `DELETE`.
  - Capacidad para procesar y responder a solicitudes HTTP con cabeceras.

- **Base de Datos**:
  - Uso de SQLite como base de datos embebida para almacenamiento mínimo.
  - Soporte para operaciones básicas de CRUD.

- **Diseño Extensible**:
  - Clases para representar diferentes métodos HTTP (`GET`, `POST`, `DELETE`) con capacidad para expandir y manejar otros métodos en el futuro.
  - Arquitectura basada en clases que separa la lógica del servidor, la gestión de hilos y las solicitudes HTTP.

## Requisitos del Sistema

- **Lenguaje**: C++17 o superior.
- **Librerías requeridas**:
  - [SQLite](https://www.sqlite.org/index.html)
  - Librerías estándar de C++ (`<thread>`, `<mutex>`, `<condition_variable>`, `<queue>`, `<iostream>`, etc.).
- **CMake**: Utilizado para gestionar la construcción del proyecto.
