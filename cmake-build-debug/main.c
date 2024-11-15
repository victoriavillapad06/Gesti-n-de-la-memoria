#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define SIZE 4096

int main() {
    // Crear un archivo de mapeo de memoria compartida
    HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, SIZE, NULL);
    if (hMapFile == NULL) {
        perror("CreateFileMapping");
        exit(EXIT_FAILURE);
    }

    // Mapeo de la memoria compartida
    char *shared_memory = (char *) MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, SIZE);
    if (shared_memory == NULL) {
        perror("MapViewOfFile");
        CloseHandle(hMapFile);
        exit(EXIT_FAILURE);
    }

    // Escribir en la memoria compartida
    strcpy(shared_memory, "¡Hola, proceso hijo!");

    // Aquí, puedes agregar lógica para crear procesos hijos si es necesario.
    // Recuerda que puedes usar funciones como CreateProcess para crear un hijo si es necesario.

    // Limpiar
    UnmapViewOfFile(shared_memory);
    CloseHandle(hMapFile);

    return 0;
}