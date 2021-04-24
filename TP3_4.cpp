#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
const char *tiposProductos[]={"Galletas","Snack","Cigarrillos","Caramelos","Bebidas"};

typedef struct Producto 
{
    int ProductoID; //Numerado en ciclo iterativo
    int Cantidad; // entre 1 y 10
    char *TipoProducto; // Algún valor del arreglo TiposProductos
    float PrecioUnitario; // entre 10 - 100
}producto;

typedef struct Cliente 
{
    int ClienteID; // Numerado en el ciclo iterativo
    char *NombreCliente; // Ingresado por usuario
    int CantidadProductosAPedir; // (alteatorio entre 1 y 5)
    producto *Productos; //El tamaño de este arreglo depende de la variable “CantidadProductosAPedir”
}cliente;

void agregarCliente(cliente *, int);
void crearProducto(producto *, int);
void mostrarRecibo(cliente *, int);
void mostrarProductos(producto *, int);
float precioTotalProducto(producto *);

int main()
{
    srand((unsigned int) time(0));

    int cantidad;
    cliente *clientes;

    printf("Ingrese cantidad de clientes:\n");
    fflush(stdin);
    scanf("%d", &cantidad);
    getchar();
    fflush(stdin);

    clientes = (cliente*)(malloc(sizeof(cliente) * cantidad));
   
    agregarCliente(clientes, cantidad);

    mostrarRecibo(clientes, cantidad);

    free(clientes);
    getchar();

    return 0;
}


void agregarCliente(cliente * nuevo ,int cantidad)
{
    char buff[100];
    int i;

    for(i = 0; i < cantidad;i++ )
    {    
        (nuevo + i)->ClienteID = i + 1;
        printf("Ingrese nombre del cliente: \n");   
        fflush(stdin);

        //gets(buff);//error del gets?        
        scanf("%s", buff);
        getchar();
        fflush(stdin);

        (nuevo + i)->NombreCliente= (char*)malloc(sizeof(char) * strlen(buff));
        strcpy((nuevo + i)->NombreCliente, buff);
        fflush(stdin);

        (nuevo + i)->CantidadProductosAPedir = rand() % 5 + 1;

        (nuevo + i)->Productos = (producto *) malloc(sizeof(producto*) * (nuevo + i)->CantidadProductosAPedir);

        crearProducto((nuevo + i)->Productos, (nuevo + i)->CantidadProductosAPedir);
    }
}


void crearProducto(producto * nuevoProducto, int cantidad)
{
    int posicion, x;

    for(x=0; x < cantidad; x++)
    {
        (nuevoProducto + x)->ProductoID = x + 1;
        (nuevoProducto + x)->Cantidad = rand() % 10 + 1;
        posicion = rand() % 5;
        (nuevoProducto + x)->TipoProducto = (char*) malloc(sizeof(char*) * strlen(tiposProductos[posicion]));
        strcpy((nuevoProducto + x)->TipoProducto, tiposProductos[posicion]);
        (nuevoProducto + x)->PrecioUnitario = (float) (rand() % 910 + 1000) / 10;
    }
}

float precioTotalProducto(producto * prod)
{
    return prod->Cantidad * prod->PrecioUnitario;
}

void mostrarRecibo(cliente * clientes, int cantidad)
{
    int x;

    for(x=0; x < cantidad; x++)
    {
        printf("\n\nCliente N %d",(clientes + x)->ClienteID);
        printf("\nNombre: %s",(clientes + x)->NombreCliente);
        printf("\nCantidad de productos: %d",(clientes + x)->CantidadProductosAPedir);
        printf("\n\nProductos: ");
        mostrarProductos((clientes + x)->Productos, (clientes + x)->CantidadProductosAPedir);
    }        
}

void mostrarProductos(producto * prod, int cantidadProd)
{
    int x;
    float precio, precioFinal = 0;

    for(x=0; x < cantidadProd; x++)
    {
        printf("\nProducto N %d", x+1);
        printf("\nCantidad: %d", (prod + x)->Cantidad);
        printf("\nTipo: %s", (prod + x)->TipoProducto);
        printf("\nPrecio unitario: $ %.2f", (prod + x)->PrecioUnitario);
        precio = precioTotalProducto(prod + x);
        precioFinal += precio;
        printf("\nPrecio total: $ %.2f", precio);
        printf("\n");
    }
    printf("\nPrecio total final: $ %.2f",precioFinal);       
    
}