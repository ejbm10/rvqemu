# Proyecto I: Encriptación y decriptación con TEA en un entorno QEMU
## Arquitectura de Computadores I
### Profesor: Dr. Ing. Jeferson Gonzalez
### Estudiante: Eduardo Bolívar Minguet 2020158103

Este proyecto presenta un ambiente de desarrollo de Qemu dentro de un contenedor Docker que provee el toolchain necesario para la compilación. El proyecto está dividido en tres programas: encriptación, decriptación, y manejo de cadenas de caractéres. A continuación se presentan los detalles de arquitectura y funcionalidad. 

---

## 1. Arquitectura del Software

### Programa en C

El programa principal se encuentra escrito en el lenguaje de programación C e implementa funciones para el manejo de caracteres y llamado de las funciones de encriptación y decriptación. Las funciones de encriptación y decriptación son declaradas como externas, es decir, el compilador no relaciona la definición de estas funciones dentro del código fuente, sino que deben ser buscadas por el enlazador.

### Ensamblador RV32

En lenguaje ensamblador RV32 se encuentran definidas las funciones de encriptación y decriptación propiamente. En un archivo (tea_encrypt.s) se encuentra el código fuente para la encriptación de una cadena de carácteres dada una dirección de memoria; en otro archivo (tea_decrypt.s) se encuentra el código fuente para la decriptación. Estas funciones son invocadas por el programa de C, y enlazadas de forma externa. 

### Entorno de compilación

Se trata de un entorno QEMU para la simulación de ejecución sin sistema operativo (bare-metal). El toolchain para generar el binario se encuentra contenido en Docker, lo que facilita la compilación sin necesidad de instalar todas las herramientas.

### Decisiones de diseño

Al tratarse de una programación bare-metal, se decidió establecer de forma fija un arreglo de cadenas de carácteres en memoria, así como una clave de encriptación también fija en memoria. El programador debe recompilar para elegir otra cadena de caracteres y/u otra clave. 

![Arquitectura](images/arquitectura.jpeg)

---

## 2. Funcionalidades implementadas


---

## 3. Resultados

---

## 4. Instrucciones de uso de la aplicación

- [`examples/README.md`](examples/README.md) - Información general

