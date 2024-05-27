#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_PRODUCTS 100
#define NAME_LENGTH 50

typedef struct {
    char nombre[NAME_LENGTH];
    int cantidad;
    float precio;
} Producto;

void ingresarProducto(Producto productos[], int *numProductos);
void editarProducto(Producto productos[], int numProductos);
void eliminarProducto(Producto productos[], int *numProductos);
void listarProductos(Producto productos[], int numProductos);
void comprarProductos(Producto productos[], int numProductos);
void controlDeInventario(Producto productos[], int numProductos);
void chequeoDeInventario(Producto productos[], int numProductos);
void agregarProductosMensuales(Producto productos[], int numProductos);

#endif
