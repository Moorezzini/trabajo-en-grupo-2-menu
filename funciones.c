#include <stdio.h>
#include <string.h>
#include "funciones.h"

void ingresarProducto(Producto productos[], int *numProductos) {
    if (*numProductos >= MAX_PRODUCTS) {
        printf("No se pueden agregar más productos.\n    ");
        return;
    }

    printf("Ingresar nombre del producto: ");
    fgets(productos[*numProductos].nombre, NAME_LENGTH, stdin);
    productos[*numProductos].nombre[strcspn(productos[*numProductos].nombre, "\n")] = 0; // Eliminar el salto de línea
    printf("Ingresar cantidad del producto: ");
    scanf("%d", &productos[*numProductos].cantidad);
    printf("Ingresar precio del producto: ");
    scanf("%f", &productos[*numProductos].precio);
    getchar(); // Limpiar el buffer de entrada

    (*numProductos)++;
}

void editarProducto(Producto productos[], int numProductos) {
    char nombre[NAME_LENGTH];
    printf("Ingresar nombre del producto a editar: ");
    fgets(nombre, NAME_LENGTH, stdin);
    nombre[strcspn(nombre, "\n")] = 0; // Eliminar el salto de línea

    for (int i = 0; i < numProductos; i++) {
        if (strcmp(productos[i].nombre, nombre) == 0) {
            printf("Ingresar nueva cantidad del producto: ");
            scanf("%d", &productos[i].cantidad);
            printf("Ingresar nuevo precio del producto: ");
            scanf("%f", &productos[i].precio);
            getchar(); // Limpiar el buffer de entrada
            return;
        }
    }

    printf("Producto no encontrado.\n");
}

void eliminarProducto(Producto productos[], int *numProductos) {
    char nombre[NAME_LENGTH];
    printf("Ingresar nombre del producto a eliminar: ");
    fgets(nombre, NAME_LENGTH, stdin);
    nombre[strcspn(nombre, "\n")] = 0; // Eliminar el salto de línea

    for (int i = 0; i < *numProductos; i++) {
        if (strcmp(productos[i].nombre, nombre) == 0) {
            for (int j = i; j < *numProductos - 1; j++) {
                productos[j] = productos[j + 1];
            }
            (*numProductos)--;
            printf("Producto eliminado.\n");
            return;
        }
    }

    printf("Producto no encontrado.\n");
}

void listarProductos(Producto productos[], int numProductos) {
    if (numProductos == 0) {
        printf("No hay productos para listar.\n");
        return;
    }

    printf("Listado de productos:\n");
    for (int i = 0; i < numProductos; i++) {
        printf("Nombre: %s, Cantidad: %d, Precio: %.2f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
    }
}

void comprarProductos(Producto productos[], int numProductos) {
    char nombre[NAME_LENGTH];
    int cantidad;
    int totalProductosComprados = 0;
    float totalPrecio = 0.0;
    char esEstudianteUDLA[4];  // Para la respuesta de si es estudiante de la UDLA

    while (1) {
        printf("Ingresar nombre del producto a comprar (o 'fin' para terminar): ");
        fgets(nombre, NAME_LENGTH, stdin);
        nombre[strcspn(nombre, "\n")] = 0; // Eliminar el salto de línea

        if (strcmp(nombre, "fin") == 0) break;

        int productoEncontrado = 0;
        for (int i = 0; i < numProductos; i++) {
            if (strcmp(productos[i].nombre, nombre) == 0) {
                productoEncontrado = 1;
                printf("Ingresar cantidad a comprar: ");
                scanf("%d", &cantidad);
                getchar(); // Limpiar el buffer de entrada

                if (productos[i].cantidad < cantidad) {
                    printf("No hay suficiente stock del producto.\n");
                    break;
                }

                productos[i].cantidad -= cantidad;
                totalProductosComprados += cantidad;
                totalPrecio += productos[i].precio * cantidad;

                break;
            }
        }

        if (!productoEncontrado) {
            printf("Producto no encontrado.\n");
        }
    }

    if (totalProductosComprados > 6) {
        totalPrecio *= 0.8;  // Aplicar descuento del 20%
    }

    printf("¿Eres estudiante de la UDLA? (sí/no): ");
    fgets(esEstudianteUDLA, 4, stdin);
    esEstudianteUDLA[strcspn(esEstudianteUDLA, "\n")] = 0; 

    if (strcmp(esEstudianteUDLA, "sí") == 0 || strcmp(esEstudianteUDLA, "si") == 0) {
        totalPrecio *= 0.9;  // Aplicar descuento del 10%
    }

    printf("Total de productos comprados: %d\n", totalProductosComprados);
    printf("Precio total: $%.2f\n", totalPrecio);
}

void chequeoDeInventario(Producto productos[], int numProductos) {
    int totalVapes = 0;
    printf("Chequeo de inventario:\n");
    for (int i = 0; i < numProductos; i++) {
        printf("Nombre: %s, Cantidad restante: %d\n", productos[i].nombre, productos[i].cantidad);
        totalVapes += productos[i].cantidad;
    }
    printf("Número total de vapes restantes: %d\n", totalVapes);
}

void agregarProductosMensuales(Producto productos[], int numProductos) {
    for (int i = 0; i < numProductos; i++) {
        productos[i].cantidad += 10;  // Agregar 10 unidades de cada producto
    }
    printf("El producto mensual se ha agregado.\n");
}

void controlDeInventario(Producto productos[], int numProductos) {
    int password;
    printf("Digite la contraseña: ");
    scanf("%d", &password);
    getchar(); // Limpiar el buffer de entrada

    if (password == 1234) {
        int opcion;
        do {
            printf("Control de Inventario\n");
            printf("1. Chequeo de inventario\n");
            printf("2. Agregar productos mensuales\n");
            printf("3. Salir\n");
            printf("Seleccionar una opción: ");
            scanf("%d", &opcion);
            getchar();  // Limpiar el buffer de entrada

            switch (opcion) {
                case 1:
                    chequeoDeInventario(productos, numProductos);
                    break;
                case 2:
                    agregarProductosMensuales(productos, numProductos);
                    break;
                case 3:
                    printf("Saliendo del control de inventario...\n");
                    break;
                default:
                    printf("Opción no válida.\n");
            }
        } while (opcion != 3);
    } else {
        printf("Contraseña incorrecta.\n");
    }
}
