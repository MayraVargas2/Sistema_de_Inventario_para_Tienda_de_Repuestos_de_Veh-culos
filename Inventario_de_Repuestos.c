#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *archivo;
    int opcion;

    // Apertura del archivo en modo texto (lectura y escritura)
    archivo = fopen("inventario_repuestos.txt", "a+");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    while (opcion != 5){
        printf("\n1. Agregar Repuesto\n2. Editar Repuesto\n3. Eliminar Repuesto\n4. Listar Repuestos\n5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarRepuesto(archivo);
                break;
            case 2:
                editarRepuesto(archivo);
                break;
            case 3:
                eliminarRepuesto(archivo);
                break;
            case 4:
                listarRepuestos(archivo);
                break;
            case 5:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    }

    // Cierre del archivo al salir del programa
    fclose(archivo);

    return 0;
}

void agregarRepuesto(FILE *archivo) {
    char nombre[50];
    int cantidad;
    float precio;

    // Ingreso de datos del nuevo repuesto
    printf("Ingrese el nombre del repuesto (Para espacios utilize \"_\"): ");
    scanf("%s", nombre);
    printf("Ingrese la cantidad: ");
    scanf("%d", &cantidad);
    printf("Ingrese el precio: ");
    scanf("%f", &precio);

    // Escritura de los datos del nuevo repuesto en el archivo
    fprintf(archivo, "%s %d %.2f\n", nombre, cantidad, precio);

    printf("Repuesto agregado con exito.\n");
}

void editarRepuesto(FILE *archivo) {
    char nombre[50];
    int nuevaCantidad;
    float nuevoPrecio;

    // Edición de datos del repuesto existente
    printf("Ingrese el nombre del repuesto a editar (Para espacios utilize \"_\"): ");
    scanf("%s", nombre);
    printf("Ingrese la nueva cantidad: ");
    scanf("%d", &nuevaCantidad);
    printf("Ingrese el nuevo precio: ");
    scanf("%f", &nuevoPrecio);

    FILE *temporal;
    char tempNombre[50];
    int tempCantidad;
    float tempPrecio;
    int encontrado = 0;

    // Creación de un archivo temporal para almacenar datos editados
    temporal = fopen("temporal.txt", "w");
    // Volver al principio del archivo principal
    rewind(archivo);

    // Copiar los datos al archivo temporal, realizando la edición si se encuentra el repuesto
    while (fscanf(archivo, "%s %d %f", tempNombre, &tempCantidad, &tempPrecio) == 3) {
        if (strcmp(tempNombre, nombre) == 0) {
            fprintf(temporal, "%s %d %.2f\n", tempNombre, nuevaCantidad, nuevoPrecio);
            printf("Repuesto editado con exito.\n");
            encontrado = 1;
        } else {
            fprintf(temporal, "%s %d %.2f\n", tempNombre, tempCantidad, tempPrecio);
        }
    }

    // Si no se encuentra el repuesto, mostrar un mensaje
    if (!encontrado) {
        printf("No se encontro el repuesto con ese nombre.\n");
    }

    // Cierre de archivos
    fclose(archivo);
    fclose(temporal);
    // Eliminación del archivo original
    remove("inventario_repuestos.txt");
    // Renombrar el archivo temporal al original
    rename("temporal.txt", "inventario_repuestos.txt");
    // Reabrir el archivo principal en modo texto (lectura y escritura)
    archivo = fopen("inventario_repuestos.txt", "a+");
}

void eliminarRepuesto(FILE *archivo) {
    char nombre[50];

    // Eliminación de un repuesto
    printf("Ingrese el nombre del repuesto a eliminar: ");
    scanf("%s", nombre);

    FILE *temporal;
    char tempNombre[50];
    int tempCantidad;
    float tempPrecio;
    int encontrado = 0;

    // Creación de un archivo temporal para almacenar datos sin el repuesto eliminado
    temporal = fopen("temporal.txt", "w");

    // Volver al principio del archivo principal
    rewind(archivo);

    // Copiar los datos al archivo temporal, excluyendo el repuesto a eliminar
    while (fscanf(archivo, "%s %d %f", tempNombre, &tempCantidad, &tempPrecio) == 3) {
        if (strcmp(tempNombre, nombre) == 0) {
            printf("Repuesto eliminado con exito.\n");
            encontrado = 1;
        } else {
            fprintf(temporal, "%s %d %.2f\n", tempNombre, tempCantidad, tempPrecio);
        }
    }

    // Si no se encuentra el repuesto, mostrar un mensaje
    if (!encontrado) {
        printf("No se encontro el repuesto con ese nombre.\n");
    }

    // Cierre de archivos
    fclose(archivo);
    fclose(temporal);
    // Eliminación del archivo original
    remove("inventario_repuestos.txt");
    // Renombrar el archivo temporal al original
    rename("temporal.txt", "inventario_repuestos.txt");

    // Reabrir el archivo principal en modo texto (lectura y escritura)
    archivo = fopen("inventario_repuestos.txt", "a+");
}

void listarRepuestos(FILE *archivo) {
    char tempNombre[50];
    int tempCantidad;
    float tempPrecio;

    // Lectura y visualización de todos los repuestos en el archivo
    rewind(archivo); // Volver al principio del archivo

    printf("\n=== Lista de Repuestos ===\n");

    // Mientras haya datos, mostrar la información de cada repuesto
    while (fscanf(archivo, "%s %d %f", tempNombre, &tempCantidad, &tempPrecio) == 3) {
        printf("Nombre: %s\nCantidad: %d\nPrecio: %.2f\n\n", tempNombre, tempCantidad, tempPrecio);
    }
}
