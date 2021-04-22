#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h>
const char *tiposProductos[]={"Galletas","Snack","Cigarrillos","Caramelos","Bebidas"};

typedef struct Producto {
    int ProductoID; //Numerado en ciclo iterativo
    int Cantidad; // entre 1 y 10
    char *TipoProducto; // Algún valor del arreglo TiposProductos
    float PrecioUnitario; // entre 10 - 100
}producto;

typedef struct Cliente {
    int ClienteID; // Numerado en el ciclo iterativo
    char *NombreCliente; // Ingresado por usuario
    int CantidadProductosAPedir; // (alteatorio entre 1 y 5)
    Producto *Productos; //El tamaño de este arreglo depende de la variable “CantidadProductosAPedir”
}cliente;

float mostrarProductos(producto, int);
void mostrarRecibo(cliente);
float precioTotalProducto(producto);
producto crearProducto(int);
cliente agregarCliente(int);

int main(){
    srand((unsigned int) time(0));

    int cantidad, i;
    cliente *clientes;

    clientes = new cliente;

    std::cout << "Ingrese cantidad de clientes:" << std::endl;
    std::cin >> cantidad;

    for(i = 0; i < cantidad;i++ ){
        clientes[i] = agregarCliente(i+1);
    }

    for(i = 0; i < cantidad;i++ ){
        mostrarRecibo(clientes[i+1]);
    }

    delete(clientes);
    return 0;
}


cliente agregarCliente(int iteracion){
    cliente nuevo; 
    
    nuevo.ClienteID = iteracion;
    std::cout << "Ingrese nombre del cliente: ";    
    nuevo.NombreCliente= (char*)malloc(sizeof(char)*30);
    gets(nuevo.NombreCliente);
    nuevo.CantidadProductosAPedir = rand() % 5 + 1;

    nuevo.Productos = (producto *) malloc(sizeof(producto*) * nuevo.CantidadProductosAPedir);

    for(int x=0; x < nuevo.CantidadProductosAPedir; x++){
        nuevo.Productos[x] = crearProducto(x+1);
    }

    return nuevo;
}


producto crearProducto(int j){
    producto nuevo2;
    int posicion;

    nuevo2.ProductoID = j;
    nuevo2.Cantidad = rand() % 10 + 1;
    posicion = rand() % 5 + 1;
    nuevo2.TipoProducto = (char*) malloc(sizeof(char*) * strlen(tiposProductos[posicion]));
    strcpy(nuevo2.TipoProducto, tiposProductos[posicion]);
    nuevo2.PrecioUnitario = rand() % 91 + 10;

    return nuevo2;
}

float precioTotalProducto(producto prod){
    return prod.Cantidad * prod.PrecioUnitario;
}

void mostrarRecibo(cliente todo){
    float precioFinal = 0;

    std::cout << "Cliente N" << todo.ClienteID << std::endl;
    std::cout << "Nombre" << todo.NombreCliente << std::endl;
    std::cout << "Cantidad de productos" << todo.CantidadProductosAPedir << std::endl;
    std::cout << "Productos: " << std::endl;

    for(int x=0; x < todo.CantidadProductosAPedir; x++){
        precioFinal += mostrarProductos(todo.Productos[x], x);
    }

    std::cout << "Total a pagar: $" << precioFinal << std::endl;    
}

float mostrarProductos(producto prod, int x){
    float precio;

    std::cout << "Producto N" << x << std::endl;
    std::cout << "Cantidad" << prod.Cantidad << std::endl;
    std::cout << "Tipo" << prod.TipoProducto << std::endl;
    precio = precioTotalProducto(prod);
    std::cout << "Precio total: $" << precio << std::endl;

    return precio;
}