#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define RESET_COLOR    "\x1b[0m"
#define ROJO_T     "\x1b[31m"
#define VERDE_T     "\x1b[32m"
#define AMARILLO_T "\x1b[33m"
#define AZUL_T     "\x1b[34m"
#define MAGENTA_T  "\x1b[35m"
#define CYAN_T     "\x1b[36m"
#define BLANCO_T   "\x1b[37m"
#define NARANJA_T   "\x1B[38;2;255;102;0m"

// CONSTANTES
const int rows=5; // pisos del edificio
const int cols=3; // habitaciones por piso

// NOMBRES DE LOS ARCHIVOS
const char archivoHabitaciones[]="Habitaciones.txt";
const char archivoClientes[]="Clientes.txt";
const char archivoClientesAUX[]="ClientesAuxiliares.txt";
const char archivoAdministrador[]="Administrador.txt";

// PROTOTIPADO DE ESTRUCTURAS
typedef struct
{
    int diaEntrada;
    int mesEntrada;
    int anioEntrada;
    int diaSalida;
    int mesSalida;
    int anioSalida;
} Fecha;
typedef struct
{
    int numero; //numero de la habitacion
    char categoria[20]; // vip o normal
    int precio;
    char estado[20]; // disponible u ocupada
    int camas;
    int personas; // personas que ocupan la habitacion
} Habitacion;

typedef struct
{
    char nombre[50];
    int dni;
    int edad;
    char nacionalidad[40];
    unsigned long telefono;
    char estado[20]; // activo o inactivo
    Habitacion habitacion;
    Fecha estadia;
    int codigo; //codigo unico de cliente
} Cliente;

typedef struct
{
    char user[30];
    char password[40];
} Administrador;

// PROTOTIPADO DE FUNCIONES

void menuPrincipal(int matrizEdificio[rows][cols]);
void subMenuReservaClientes();
void subMenuCheckInOut();
void subMenuHabitacionAct(int matrizEdificio[rows][cols]);
void subMenuListados();
void subMenuMasInformacion();
void login();
void registrarUsuario();
int verificarUsuario(char nombre[], char contrasena[]);
void mostrarInformes();
void checkIn(Cliente A);
Cliente cargarCliente(int);
void setHabitacionesStatus(int M[rows][cols]);
void mostrarEdificio(int M[rows][cols]);
void mostrarUnCliente(Cliente A);
void mostrarClientes();
Cliente consultaCliente();
void mostrarUnaHabitacion(Habitacion A);
void mostrarHabitaciones();
void ordenacionPilaDisponibles(Pila * dada);
void listadoInsercionPrecioHab();
void insertarPrecio(Habitacion A[], int i, Habitacion dato);
int modificacionDeClientes(Cliente A);
int verificarArchivoClientes();
void listadoInsercionNumeroHab();
void insertarNumero(Habitacion A[], int i, Habitacion dato);
int checkOut(Cliente A);
void listadoInsercionEdadCliente(int flag);
void insertarEdad(Cliente A[], int i, Cliente dato);
void listadoSeleccionNombreCliente(int flag);
int seleccionNombre(Cliente A[], int posicion, int validos);
void listadoInsercionHabitacionDeCliente(int flag);
void insertarNroHabitacionCliente(Cliente A[], int i, Cliente dato);
void listadoInsercionHabDisponible();
void editarHabitacion();
void subMenuConfiguracion();



int main()
{
    srand(time(NULL));
    int matrizEdificio[rows][cols];
    setHabitacionesStatus(matrizEdificio); // seteo de habitaciones disponibles si el archivo no esta creado
    menuPrincipal(matrizEdificio);
    return 0;
}

void menuPrincipal(int matrizEdificio[rows][cols])
{
    int op;
    do
    {
        system("cls");
        printf(" - Bienvenido\n\n\t- - - - "CYAN_T"SISTEMA ADMINISTRATIVO HOTELERO "RESET_COLOR "- - - -\n\n");
        printf("\t[ 1 ] Iniciar sesion\n\n\t[ 2 ] Registrarse\n\n");
        printf("  -  ");
        scanf("%i", &op);
        system("cls");

        switch (op)
        {
        case 1:
            login();
            system("pause");
            do
            {
                system("cls");
                printf("\t- - - - "CYAN_T"MENU PRINCIPAL  "RESET_COLOR "- - - -\n\n");
                printf(" [ 1 ] Clientes\n\n [ 2 ] Check in/Check out\n\n [ 3 ] Instalaciones\n\n [ 4 ] Listados\n\n [ 5 ] Mas informacion\n\n [ 6 ] Configuracion\n\n [ 0 ] Salir del sistema \n\n  - ");
                scanf("%i", &op);
                system("cls");
                switch(op)
                {
                case 1:
                    subMenuReservaClientes();
                    break;
                case 2:
                    subMenuCheckInOut();
                    break;
                case 3:
                    mostrarEdificio(matrizEdificio);
                    system("pause");
                    system("cls");
                    break;
                case 4:
                    subMenuListados();
                    break;
                case 5:
                    subMenuMasInformacion();
                    break;
                case 6:
                    subMenuConfiguracion();
                    break;
                case 0:
                    system("cls");
                    exit(0);
                default:
                    break;
                }
            }
            while(op!=0);
            break;
        case 2:
            registrarUsuario();
            system("pause");
            system("cls");
            break;
        }
    }
    while(1);
}
void subMenuReservaClientes()
{
    int op, flag;
    Cliente A;
    do
    {

        system("cls");
        printf("\t- - - - "CYAN_T"MENU CLIENTES  "RESET_COLOR "- - - -\n\n");
        printf(" [ 1 ] Registrar cliente\n\n [ 2 ] Consulta de clientes\n\n [ 0 ] Volver\n\n  - ");
        scanf("%i", &op);
        system("cls");
        switch(op)
        {
        case 1:
            printf(AMARILLO_T"\t- - MENU DE RESERVAS - -\n\n"RESET_COLOR);
            cargarCliente(0);
            printf("\n\tVolviendo al menu principal.");
            Sleep(700);
            printf(" .");
            Sleep(700);
            system("cls");
            break;
        case 2:
            flag=verificarArchivoClientes();
            if(flag==0)
            {
                printf(ROJO_T" - ERROR: Todavia no se ha cargado ningun cliente. Ingrese uno e intente mas tarde\n\n"RESET_COLOR);
                system("pause");
                system("cls");
                break;
            }
            printf(AMARILLO_T"\t- - CONSULTA DE CLIENTE - -\n\n"RESET_COLOR);
            printf(" - Ingrese el codigo del cliente a consultar (presione 0 para cancelar) ");
            A=consultaCliente();
            if(A.codigo==0)
            {
                break;
            }
            mostrarUnCliente(A);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case 0:
            system("cls");
            break;
        default:
            break;
        }
    }
    while(op!=0);
}
void subMenuCheckInOut()
{
    int op, flag, dato;
    Cliente A;
    do
    {
        system("cls");
        printf("\t- - - - "CYAN_T"MENU CHECK IN/CHECK OUT  "RESET_COLOR "- - - -\n\n");
        printf(" [ 1 ] Check in\n\n [ 2 ] Check out\n\n [ 0 ] Volver\n\n  - ");
        scanf("%i", &op);
        system("cls");
        switch(op)
        {
        case 1:
            flag=verificarArchivoClientes();
            if(flag==0)
            {
                printf(ROJO_T" - ERROR: Todavia no se ha cargado ningun cliente. Ingrese uno e intente mas tarde\n\n"RESET_COLOR);
                system("pause");
                system("cls");
                break;
            }
            printf(AMARILLO_T"\t- - CHECK IN - -\n\n"RESET_COLOR);
            printf("\t- Ingrese el numero de cliente a realizar check in (presione 0 para cancelar) ");
            flag=0;

            A=consultaCliente();
            if(A.codigo==0)
            {
                break;
            }
            if((strcmpi(A.estado,"Activo"))==0)
            {
                printf(ROJO_T"\nERROR: El cliente ingresado ya esta dado de alta en el hotel.\n"RESET_COLOR);
                system("pause");
                break;
            }
            mostrarUnCliente(A);
            checkIn(A);
            system("cls");
            break;
        case 2:
            flag=verificarArchivoClientes();
            if(flag==0)
            {
                printf(ROJO_T" - ERROR: Todavia no se ha cargado ningun cliente. Ingrese uno e intente mas tarde\n\n"RESET_COLOR);
                system("pause");
                system("cls");
                break;
            }
            printf(AMARILLO_T"\t- - CHECK OUT - -\n\n"RESET_COLOR);
            printf("\t- Ingrese el numero de cliente a realizar check out (presiones 0 para cancelar) ");
            flag=0;

            A=consultaCliente();
            if(A.codigo==0)
            {
                break;
            }
            if((strcmpi(A.estado,"Inactivo"))==0)
            {
                printf(ROJO_T"\nERROR: El cliente ingresado no esta dado de alta en el hotel. Ingrese al menu de check in para ingresarlo\n"RESET_COLOR);
                system("pause");
                break;
            }

            mostrarUnCliente(A);
            printf("\n - Desea hacer el check out del cliente"AMARILLO_T" %s"RESET_COLOR"?\n [ 1 ] Si\n\n [ 2 ] No\n - ", A.nombre);
            scanf("%i", &dato);
            if(dato==2)
            {
                printf("\nVolviendo al menu principal...");
                Sleep(2600);
                system("cls");
                break;
            }
            checkOut(A);
            system("cls");
            break;
        case 0:
            system("cls");
            break;
        default:
            break;
        }
    }
    while(op!=0);
}

void subMenuListados()
{
    int op, flag;
    do
    {
        system("cls");
        printf("\t- - - - "CYAN_T"MENU LISTADOS  "RESET_COLOR "- - - -\n\n");
        printf(" [ 1 ] Listado de clientes\n\n [ 2 ] Listado de habitaciones\n\n [ 0 ] Volver\n\n  - ");
        scanf("%i", &op);
        system("cls");
        switch(op)
        {
        case 1:

            do
            {
                printf(CYAN_T"\n\n\t- - LISTADO DE CLIENTES - -\n\n"RESET_COLOR);
                printf(" [ 1 ] Listado Activos\n\n [ 2 ] Listado Totales\n\n [ 0 ] Volver\n\n - ");
                scanf("%i", &op);
                system("cls");
                switch(op)
                {
                case 1:
                    do
                    {
                        flag=1;
                        printf(CYAN_T"\n\n\t- - LISTADO DE CLIENTES ACTIVOS - -\n\n"RESET_COLOR);
                        printf(" [ 1 ] Listado por nombre\n\n [ 2 ] Listado por edad\n\n [ 3 ] Listado por numero de habitacion\n\n [ 0 ] Volver\n\n - ");
                        scanf("%i", &op);
                        system("cls");

                        switch(op)
                        {
                        case 1:
                            listadoSeleccionNombreCliente(flag);
                            system("pause");
                            system("cls");
                            break;
                        case 2:
                            listadoInsercionEdadCliente(flag);
                            system("pause");
                            system("cls");
                            break;
                        case 3:
                            listadoInsercionHabitacionDeCliente(flag);
                            system("pause");
                            system("cls");
                            break;
                        case 0:
                            system("cls");
                            break;
                        default:
                            break;
                        }
                    }
                    while(op!=0);
                    system("cls");
                    break;
                case 2:

                    do
                    {
                        flag=0;
                        printf(CYAN_T"\n\n\t- - LISTADO DE CLIENTES TOTALES - -\n\n"RESET_COLOR);
                        printf(" [ 1 ] Listado por nombre\n\n [ 2 ] Listado por edad\n\n [ 0 ] Volver\n\n - ");
                        scanf("%i", &op);
                        system("cls");
                        switch(op)
                        {
                        case 1:
                            listadoSeleccionNombreCliente(flag);
                            system("pause");
                            system("cls");
                            break;
                        case 2:
                            listadoInsercionEdadCliente(flag);
                            system("pause");
                            system("cls");
                            break;
                        case 0:
                            system("cls");
                            break;
                        default:
                            break;
                        }
                    }
                    while(op!=0);
                    break;
                case 0:
                    system("cls");
                    break;
                default:
                    break;
                }
            }
            while(op!=0);
            system("cls");
            break;
        case 2:
            do
            {
                printf(CYAN_T"\n\n\t- - LISTADO DE HABITACIONES - -\n\n"RESET_COLOR);
                printf(" [ 1 ] Listado por precio\n\n [ 2 ] Listado por nro. de habitacion\n\n [ 3 ] Habitaciones Disponibles\n\n [ 0 ] Volver\n\n- ");
                scanf("%i", &op);
                system("cls");
                switch(op)
                {
                case 1:
                    listadoInsercionPrecioHab();
                    system("pause");
                    system("cls");
                    break;
                case 2:
                    listadoInsercionNumeroHab();
                    system("pause");
                    system("cls");
                    break;
                case 3:
                    listadoInsercionHabDisponible();
                    system("pause");
                    system("cls");
                    break;
                case 0:
                    system("cls");
                    break;
                default:
                    break;
                }
            }
            while(op!=0);
            system("cls");
            break;
        case 0:
            system("cls");
            break;
        default:
            break;
        }
    }
    while(op!=0);
}
void subMenuMasInformacion()
{
    int op;
    do
    {
        system("cls");
        printf("\t- - - - "CYAN_T"MAS INFORMACION  "RESET_COLOR "- - - -\n\n");
        printf(" [ 1 ] Mostrar estadistica e informe\n\n [ 0 ] Volver\n\n  - ");
        scanf("%i", &op);
        system("cls");
        switch(op)
        {
        case 1:
            mostrarInformes();
            system("pause");
            system("cls");
            break;
        case 0:
            system("cls");
            break;
        }
    }
    while(op!=0);
}
void subMenuConfiguracion()
{
    int op, flag, dato;
    Cliente A;
    do
    {
        system("cls");
        printf("\t- - - - "CYAN_T"MENU CONFIGURACION  "RESET_COLOR "- - - -\n\n");
        printf(" [ 1 ] Editar habitacion\n\n [ 2 ] Editar clientes\n\n [ 0 ] Volver\n\n  - ");
        scanf("%i", &op);
        system("cls");
        switch(op)
        {
        case 1:
            editarHabitacion();
            system("pause");
            system("cls");
            break;
          case 2:
            flag=verificarArchivoClientes();
            if(flag==0)
            {
                printf(ROJO_T" - ERROR: Todavia no se ha cargado ningun cliente. Ingrese uno e intente mas tarde\n\n"RESET_COLOR);
                system("pause");
                system("cls");
                break;
            }
            printf(AMARILLO_T"\t- - MODIFICACION DE CLIENTE - -\n\n"RESET_COLOR);
            printf("\t- Ingrese el numero de cliente a modificar (presiones 0 para cancelar) ");
            A=consultaCliente();
            if(A.codigo==0)
            {
                break;
            }

            mostrarUnCliente(A);
            printf("\n - Desea modificar ese cliente?\n [ 1 ] Si\n\n [ 2 ] No\n - ");
            scanf("%i", &dato);
            if(dato==2)
            {
                printf("\nVolviendo al menu principal...");
                Sleep(2600);
                system("cls");
                break;
            }
            modificacionDeClientes(A);
            system("cls");
            break;
        case 0:
            system("cls");
            break;
        default:
            break;
        }
    }
    while(op!=0);
}
void login()
{
    int i=0;
    int flag=1;
    char nombre[30];
    char clave[30];
    char caracter;
    do
    {
        memset(clave, 0, 30);
        i=0;
        printf(CYAN_T"\n\t- - INICIO DE SESION - -\n\n"RESET_COLOR);
        printf(" - USUARIO: ");
        fflush(stdin);
        gets(nombre);
        printf(" - CLAVE: ");

        while((caracter=getch()))
        {
            if(caracter==13)
            {
                clave[i]= '\0';
                break;
            }
            else if (caracter==8)
            {
                if(i>0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else
            {
                printf("*");
                clave[i]=caracter;
                i++;
            }
        }
        if(verificarUsuario(nombre,clave))
        {
            printf(VERDE_T"\n\n- Inicio de sesion exitoso. Bienvenido" AMARILLO_T" %s"VERDE_T"! -\n\n" RESET_COLOR, nombre);
            flag=0;
        }
        else
        {
            printf(ROJO_T"\n\nERROR: Nombre de usuario o clave incorrecta. Intente nuevamente.\n"RESET_COLOR);
            system("pause");
            system("cls");
        }
    }
    while(flag!=0);
}
void registrarUsuario()
{
    Administrador A;
    int i=0;
    char caracter;
    char clave[30];
    FILE *admin = fopen(archivoAdministrador, "ab");

    printf(CYAN_T"\n\t- - REGISTRO DE USUARIO - -\n"RESET_COLOR);
    printf("\n- USUARIO: ");
    fflush(stdin);
    gets(A.user);
    printf("\n- CLAVE: ");
    while((caracter=getch()))
    {
        if(caracter==13)
        {
            clave[i]= '\0';
            break;
        }
        else if (caracter==8)
        {
            if(i>0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            printf("*");
            clave[i]=caracter;
            i++;
        }
    }
    strcpy(A.password, clave);
    if(admin)
    {
        fwrite(&A, sizeof(Administrador), 1, admin);
        fclose(admin);
    }
    printf(VERDE_T"\n\n\t- USUARIO REGISTRADO CORRECTAMENTE -\n"RESET_COLOR);
}
int verificarUsuario(char nombre[], char contrasena[])
{
    Administrador A;

    FILE *admin = fopen(archivoAdministrador, "rb");
    if(admin)
    {
        while((fread(&A, sizeof(Administrador), 1, admin)) > 0)
        {
            if((strcmp(nombre, A.user)) == 0 && (strcmp(contrasena, A.password)) == 0)
            {
                fclose(admin);
                return 1;
            }
        }
        rewind(admin);
        fclose(admin);
    }
    return 0;
}
void mostrarInformes()
{
    Habitacion A;
    Cliente B;
    int Pasajeros = 0;
    int Ocupadas = 0;
    int Disponibles = 0;
    int Facturado=0;
    int TotalPasajeros=0;
    FILE * hab=fopen(archivoHabitaciones, "rb");
    FILE * clientes=fopen(archivoClientes, "rb");
    if(hab)
    {
        while((fread(&A, sizeof(Habitacion),1, hab))>0)
        {
            if (strcmp(A.estado, "Ocupada") == 0)
            {
                Pasajeros=Pasajeros + A.personas;
                Ocupadas++;
            }
            else if (strcmp(A.estado, "Disponible") == 0)
            {
                Disponibles++;
            }
            Facturado=Facturado + (A.personas*A.precio);
        }
        fclose(hab);
    }
    if(clientes)
    {
        while((fread(&B, sizeof(Cliente), 1, clientes))>0)
        {
            TotalPasajeros++;
        }
        fclose(clientes);
    }
    printf("\t- -  INFORMES DEL HOTEL - - \n\n\n");
    printf(" - Numero total de habitaciones: %i\n\n", rows*cols);
    printf(" - Numero total de clientes activo: %i\n\n", Pasajeros);
    printf(" - Numero total de clientes historicos: %i\n\n", TotalPasajeros);
    printf(" - Habitaciones ocupadas: %i\n\n", Ocupadas);
    printf(" - Habitaciones disponibles: %i\n\n", Disponibles);
    printf(" - Total facturado: $ %i\n\n", Facturado);
}
void checkIn(Cliente A)
{
    FILE * clientes = fopen(archivoClientes, "r+b");
    FILE * hab = fopen(archivoHabitaciones, "r+b");
    Cliente C;
    Habitacion B;
    Pila disponibles;
    inicpila(&disponibles);
    int dato, flag=0, H, maxCamas=0, opcion, resultadoE=0, resultadoS=0;
    if(hab &&  clientes)
    {
        while((fread(&B, sizeof(Habitacion),1, hab))>0)
        {
            if(B.camas>maxCamas)
            {
                maxCamas=B.camas;
            }
        }
        rewind(hab);
        printf(CYAN_T"\t\t- - - SISTEMA DE CHECK IN- - -\n"RESET_COLOR);

        do
        {
            printf("\n\n- Ingrese la cantidad de personas que van a ocupar la habitacion. Hay habitaciones de hasta %i personas: ", maxCamas);
            scanf("%i", &dato);
            if(dato<1 || dato>maxCamas)
            {
                printf(ROJO_T"\nERROR: El numero ingresado no es entre 1 y %i. Intente nuevamente.\n"RESET_COLOR, maxCamas);
                system("pause");
            }
        }
        while(dato<1 || dato>maxCamas);

        printf("\n- HABITACIONES DISPONIBLES: ");

        while((fread(&B, sizeof(Habitacion), 1, hab))>0)
        {
            if((strcmpi(B.estado,"Disponible"))==0 && B.camas>=dato)
            {
                apilar(&disponibles, B.numero);
            }
        }

        rewind(hab);
        ordenacionPilaDisponibles(&disponibles);
        mostrar(&disponibles);

        do
        {
            flag=0;
            printf("\n- NRO. HABITACION: ");
            fflush(stdin);
            scanf("%i", &H);
            while((fread(&B,sizeof(Habitacion), 1, hab))>0 && flag==0)
            {
                if(B.numero==H)
                {
                    flag=1;
                    if((strcmpi(B.estado,"Ocupada"))==0 || B.camas<dato)
                    {
                        printf(ROJO_T"\nERROR: La habitacion elegida no esta disponible. Ingrese otra habitacion por favor.\n"RESET_COLOR);
                        system("pause");
                        flag=2;
                    }
                }
            }
            if(flag==0)
            {
                printf(ROJO_T "\nERROR: La habitacion elegida no se encontro o no esta disponible. Intente con otra por favor.\n" RESET_COLOR);
                system("pause");
            }
            rewind(hab);
        }
        while(flag!=1);

        do
        {
            printf("\n- FECHA DE ENTRADA: ");
            scanf("%i %i %i", &A.estadia.diaEntrada, &A.estadia.mesEntrada, &A.estadia.anioEntrada);

            if(A.estadia.diaEntrada < 1 || A.estadia.diaEntrada > 31 || A.estadia.mesEntrada < 1 || A.estadia.mesEntrada > 12)
            {
                printf(ROJO_T "\nERROR: Fecha de entrada invalida. Intente nuevamente.\n" RESET_COLOR);
                system("pause");
            }
            else
            {
                resultadoE = 1;
            }
        }
        while(!resultadoE);

        do
        {
            printf("\n- FECHA DE EGRESO: ");
            scanf("%i %i %i", &A.estadia.diaSalida, &A.estadia.mesSalida, &A.estadia.anioSalida);

            if(A.estadia.diaSalida < 1 || A.estadia.diaSalida > 31 || A.estadia.mesSalida < 1 || A.estadia.mesSalida > 12)
            {
                printf(ROJO_T "\nERROR: Fecha de salida invalida. Intente nuevamente.\n" RESET_COLOR);
            }
            else
            {
                resultadoS = 1;
            }
        }
        while(!resultadoS);

        printf("\n\n- TOTAL A PAGAR: $ %i -\n\n [ 1 ] - Efectivo\n [ 2 ] - Tarjeta de debito o credito\n - ", B.precio*dato);
        scanf("%i", &opcion);
        printf("\nProcesando pago. ");
        Sleep(1000);
        printf(".");
        Sleep(1000);
        printf(" .\n");
        Sleep(1000);

        printf(VERDE_T"\n\t\t- - - CHECK IN REALIZADO CON EXITO! BIENVENIDO AL HOTEL"AMARILLO_T" %s"VERDE_T" - - - \n\n"RESET_COLOR, A.nombre);
        system("pause");

        while((fread(&C, sizeof(Cliente),1, clientes))>0)
        {
            if(C.codigo==A.codigo)
            {
                A.habitacion.numero=H;
                strcpy(A.estado,"Activo");
                fseek(clientes,(int) sizeof(Cliente) * (-1), SEEK_CUR);
                fwrite(&A, sizeof(Cliente), 1, clientes);
                break;
            }
        }
        while((fread(&B, sizeof(Habitacion), 1, hab))>0)
        {
            if(H==B.numero)
            {
                strcpy(B.estado,"Ocupada");
                B.personas=dato;
                fseek(hab, (int) sizeof(Habitacion) * (-1), SEEK_CUR);
                fwrite(&B, sizeof(Habitacion), 1, hab);
                break;
            }
        }
        rewind(hab);
        fclose(hab);
        fclose(clientes);
    }
}
Cliente cargarCliente(int flaggy)
{
    FILE * clientes = fopen(archivoClientes, "a+b");
    Cliente A, C;
    int flag = 0;

    if(clientes)
    {
        // NOMBRE
        do
        {
            printf("\n- NOMBRE Y APELLIDO: ");
            fflush(stdin);
            gets(A.nombre);
            strupr(A.nombre);
            flag=0;
            while((fread(&C, sizeof(Cliente),1, clientes))>0 && flag==0)
            {
                if((strcmpi(C.nombre, A.nombre))==0)
                {
                    printf(ROJO_T"\nERROR: El nombre introducido ya esta registrado. Intente nuevamente.\n" RESET_COLOR);
                    system("pause");
                    flag=1;
                }
            }
            rewind(clientes);
        }
        while(flag==1);

        // NACIONALIDAD
        printf("\n- NACIONALIDAD: ");
        fflush(stdin);
        gets(A.nacionalidad);
        strupr(A.nacionalidad);

        // EDAD
        do
        {
            printf("\n- EDAD: ");
            fflush(stdin);
            scanf("%i", &A.edad);
            if(A.edad < 1 || A.edad > 130)
            {
                printf(ROJO_T"\nERROR: Se ingreso una edad invalida, intente nuevamente.\n"RESET_COLOR);
                system("pause");
            }
        }
        while(A.edad < 1 || A.edad > 130);

        // DNI
        printf("\n- DNI: ");
        scanf("%i", &A.dni);

        // TELEFONO
        printf("\n- TELEFONO DE CONTACTO: ");
        scanf("%lu", &A.telefono);

        if(flaggy!=1)
        {
            strcpy(A.estado,"Inactivo");
            do
            {
                flag=0;
                A.codigo=rand() % 8999+1000;
                while((fread(&C, sizeof(Cliente), 1, clientes))>0)
                {
                    if((C.codigo==A.codigo))
                    {
                        flag=1;
                    }
                }
                rewind(clientes);
            }
            while(flag==1);

            printf(VERDE_T"\t--- CLIENTE REGISTRADO CORRECTAMENTE!  ---\n" RESET_COLOR"\t-- TU CODIGO DE CLIENTE ES" AMARILLO_T" %i" RESET_COLOR" --\n\n", A.codigo);
            fseek(clientes, 0, SEEK_END);
            fwrite(&A, sizeof(Cliente), 1, clientes);
            system("pause");
        }

        fclose(clientes);
    }
    return A;
}
void setHabitacionesStatus(int M[rows][cols])
{
    int r, c;
    Habitacion A;
    FILE * hab;
    if((hab=fopen(archivoHabitaciones, "rb"))==NULL)
    {
        hab=fopen(archivoHabitaciones, "wb");
        if(hab)
        {
            for(r=0; r<rows; r++)
            {
                for(c=0; c<cols; c++)
                {
                    strcpy(A.estado,"Disponible");
                    A.camas=3+c;
                    A.numero= ((rows-r)*100) + (c+1);
                    M[r][c]=A.numero;
                    A.precio= ((c+1) *3900) + ((rows-r)*3150) + 1300; // declaracion de precio de habitaciones
                    if(c!=(cols-1))
                    {
                        strcpy(A.categoria, "Normal");
                    }
                    else
                    {
                        strcpy(A.categoria, "VIP");
                    }
                    fwrite(&A, sizeof(Habitacion), 1, hab);
                }
            }
            fclose(hab);
        }
    }
    else
    {
        hab=fopen(archivoHabitaciones, "rb");
        if(hab)
        {
            for(r=0; r<rows; r++)
            {
                for(c=0; c<cols; c++)
                {
                    M[r][c]=((rows-r)*100) + (c+1);
                }
            }

            fclose(hab);
        }
    }
}
void mostrarEdificio(int M[rows][cols])
{
    int i,j;
    Habitacion A;
    FILE * hab=fopen(archivoHabitaciones, "rb");
    if(hab)
    {
        printf("\t        -------------------------\n");
        printf("\t            MAPA DEL EDIFICIO\n");
        printf("\t        -------------------------\n");
        printf("\n\n\n");
        for(i=0; i<rows; i++)
        {
            for(j=0; j<cols; j++)
            {
                printf("\t");
                fread(&A, sizeof(Habitacion), 1, hab);
                {
                    if((strcmpi(A.estado,"Ocupada"))==0 && (strcmpi(A.categoria,"Normal"))==0)
                    {
                        printf("[ " ROJO_T "%i" RESET_COLOR" ] ", M[i][j]);
                    }
                    else if((strcmpi(A.estado,"Ocupada"))==0 && (strcmpi(A.categoria, "VIP"))==0)
                    {
                        printf(AMARILLO_T "[ " ROJO_T "%i" AMARILLO_T" ] ", M[i][j]);

                    }
                    else if((strcmpi(A.estado, "Disponible"))==0 && (strcmpi(A.categoria, "VIP"))==0)
                    {
                        printf(AMARILLO_T "[ " RESET_COLOR "%i" AMARILLO_T" ] ", M[i][j]);
                    }
                    else
                    {
                        printf(RESET_COLOR "[ " RESET_COLOR "%i" RESET_COLOR " ] ", M[i][j]);
                    }
                }
            }
            printf(RESET_COLOR"\n\n\n");
        }
        fclose(hab);
    }
}
void mostrarUnCliente(Cliente A)
{
    printf(CYAN_T"----------------------------------------------------------\n\n"RESET_COLOR);
    printf("- NOMBRE: %s\t", A.nombre);
    printf("- DNI: %i\n", A.dni);
    printf("- EDAD: %i\t", A.edad);
    printf("- NACIONALIDAD: %s\n", A.nacionalidad);
    printf("- TELEFONO: %lu\n", A.telefono);
    if((strcmpi(A.estado, "Inactivo"))==0)
    {
        printf("- ESTADO DEL CLIENTE: "NARANJA_T "%s"RESET_COLOR "\n", A.estado);
    }
    else
    {
        printf("- ESTADO DEL CLIENTE: "VERDE_T"%s"RESET_COLOR"\n", A.estado);
        printf("- NRO. HABITACION: %i\n", A.habitacion.numero);
        printf("- FECHA DE ENTRADA: %i/%i/%i \t", A.estadia.diaEntrada, A.estadia.mesEntrada, A.estadia.anioEntrada);
        printf("- FECHA DE SALIDA: %i/%i/%i \n", A.estadia.diaSalida, A.estadia.mesSalida, A.estadia.anioSalida);
    }
    printf("- CODIGO: "AMARILLO_T"%i\n"RESET_COLOR, A.codigo);
}
void mostrarClientes()
{
    Cliente A;
    FILE * clientes=fopen(archivoClientes, "rb");
    if(clientes)
    {
        while((fread(&A, sizeof(Cliente),1, clientes))>0)
        {
            mostrarUnCliente(A);
        }
        fclose(clientes);
    }
}
Cliente consultaCliente()
{
    Cliente A;
    int flag=0, dato, i;
    FILE * clientes=fopen(archivoClientes, "rb");
    if(clientes)
    {
        for(i =0; i<3; i++)
        {
            printf("- ");
            scanf("%i", &dato);
            if(dato==0)
            {
                A.codigo=0;
                return A;
            }
            while((fread(&A, sizeof(Cliente), 1, clientes))>0 && flag==0)
            {
                if(dato==A.codigo)
                {
                    fclose(clientes);
                    return A;
                }
            }
            if(i==2)
            {
                flag=1;
            }
            if(flag==0)
            {
                printf(ROJO_T"\n ERROR: El codigo ingresado no se encontro en la base de datos de los clientes. Intente con un codigo valido.\n\tINTENTO NRO. %i\n" RESET_COLOR, i+1);
                system("pause");
            }
            rewind(clientes);
        }

        printf("\n\n- NUMERO DE INTENTOS PERMITIDOS EXCEDIDOS. SALIENDO DEL SISTEMA -\n");
        Sleep(1500);
        fclose(clientes);
        exit(0);
    }

    return A;
}
void mostrarUnaHabitacion(Habitacion A)
{
    printf(CYAN_T"----------------------------------\n\n"RESET_COLOR);
    printf("- NRO. DE HABITACION: %i\n", A.numero);
    printf("- CATEGORIA: %s\n", A.categoria);
    printf("- CAMAS: %i\n", A.camas);
    printf("- PRECIO: $ %i\n", A.precio);
    if((strcmpi(A.estado, "Ocupada"))==0)
    {
        printf("- ESTADO: "ROJO_T"%s\n"RESET_COLOR, A.estado);
        printf("- NRO. DE PERSONAS EN LA HABITACION: %i\n", A.personas);
    }
    else
    {
        printf("- ESTADO: "VERDE_T"%s\n"RESET_COLOR, A.estado);
    }
    printf("\n");
}
void mostrarHabitaciones()
{
    Habitacion A;
    FILE * hab=fopen(archivoHabitaciones, "rb");
    if(hab)
    {
        while((fread(&A, sizeof(Habitacion),1, hab))>0)
        {
            mostrarUnaHabitacion(A);
        }
        fclose(hab);
    }
}
void ordenacionPilaDisponibles(Pila * dada)
{
    ///SE ORDENA LA PILA DE MENOR A MAYOR PARA MOSTRAR LAS HABITACIONES EN ORDEN ASCENDENTE
    Pila aux, basura, ordenada;
    inicpila(&aux);
    inicpila(&basura);
    inicpila(&ordenada);
    apilar(&aux, desapilar(dada));
    while(!pilavacia(dada))
    {
        while(!pilavacia(dada))
        {
            if(tope(dada)<tope(&aux))
            {
                apilar(&basura, desapilar(&aux));
                apilar(&aux, desapilar(dada));
            }
            else
            {
                apilar(&basura, desapilar(dada));
            }
        }
        while(!pilavacia(&basura))
        {
            apilar(dada, desapilar(&basura));
        }
        apilar(&ordenada, desapilar(&aux));
        if(!pilavacia(dada))
        {
            apilar(&aux, desapilar(dada));
        }
    }
    if(!pilavacia(&aux))
    {
        apilar(&ordenada, desapilar(&aux));
    }
    while(!pilavacia(&ordenada))
    {
        apilar(&basura, desapilar(&ordenada));
    }
    while(!pilavacia(&basura))
    {
        apilar(dada, desapilar(&basura));
    }
}
void listadoInsercionPrecioHab()
{
    FILE * hab=fopen(archivoHabitaciones, "rb");
    Habitacion A[20];
    Habitacion B;
    int validos=0;
    if(hab)
    {
        while((fread(&B, sizeof(Habitacion),1, hab))>0)
        {
            A[validos]=B;
            validos++;
        }
        for(int i=0; i<validos-1; i++)
        {
            insertarPrecio(A, i, A[i+1]);
        }
        for(int i=0; i<validos; i++)
        {
            mostrarUnaHabitacion(A[i]);
        }
        fclose(hab);
    }
}
void insertarPrecio(Habitacion A[], int i, Habitacion dato)
{
    while(i>=0 && dato.precio<A[i].precio)
    {
        A[i+1]=A[i];
        i--;
    }
    A[i+1]=dato;
}
int modificacionDeClientes(Cliente A)
{
    FILE * clientes=fopen(archivoClientes, "r+b");
    Cliente B;
    if(clientes)
    {
        while((fread(&B, sizeof(Cliente),1, clientes))>0)
        {
            if(B.codigo==A.codigo)
            {
                B=cargarCliente(1);
                B.codigo=A.codigo;
                strcpy(B.estado, A.estado);
                if((strcmpi(A.estado,"Activo"))==0)
                {
                    B.habitacion.numero=A.habitacion.numero;
                    B.estadia=A.estadia;
                }
                fseek(clientes, (int) sizeof(Cliente) * (-1), SEEK_CUR);
                fwrite(&B, sizeof(Cliente), 1, clientes);
                break;
            }
        }
        printf(VERDE_T"\n\t- Cliente modificado correctamente -\n"RESET_COLOR);
        system("pause");
        fclose(clientes);
    }
    return 0;
}
int verificarArchivoClientes()
{
    ///VERIFICACION MEDIANTE UN RETURN 1 O 0 SI EL ARCHIVO ESTA CREADO O NO
    FILE * clientes;
    if((fopen(archivoClientes, "rb"))== NULL)
    {
        return 0;
    }
    return 1;
}
void listadoInsercionNumeroHab()
{
    FILE * hab=fopen(archivoHabitaciones, "rb");
    Habitacion A[20];
    Habitacion B;
    int validos=0;
    if(hab)
    {
        while((fread(&B, sizeof(Habitacion),1, hab))>0)
        {
            A[validos]=B;
            validos++;
        }
        for(int i=0; i<validos-1; i++)
        {
            insertarNumero(A, i, A[i+1]);
        }
        for(int i=0; i<validos; i++)
        {
            mostrarUnaHabitacion(A[i]);
        }
        fclose(hab);
    }
}
void insertarNumero(Habitacion A[], int i, Habitacion dato)
{
    while(i>=0 && dato.numero<A[i].numero)
    {
        A[i+1]=A[i];
        i--;
    }
    A[i+1]=dato;
}
int checkOut(Cliente A)
{
    if(A.codigo==0)
    {
        return 0;
    }
    // SE CAMBIA EL ESTADO DE LA HABITACION A DISPONIBLE Y CON NINGUNA PERSONA DENTRO
    FILE *clientes;
    Cliente B;
    clientes=fopen(archivoClientes,"r+b");


    if(clientes)
    {
        while((fread(&B, sizeof(Cliente),1, clientes))>0)
        {
            if(A.habitacion.numero==B.habitacion.numero)
            {
                strcpy(B.estado, "Inactivo");
                B.habitacion.numero=0;
                fseek(clientes, (int)sizeof(Cliente) * (-1), SEEK_CUR);
                fwrite(&B, sizeof(Cliente), 1, clientes);
                break;
            }
        }
        FILE * hab=fopen(archivoHabitaciones,"r+b");
        Habitacion C;
        if(hab)
        {
            while((fread(&C, sizeof(Habitacion),1,hab))>0)
            {
                if(A.habitacion.numero==C.numero)
                {
                    strcpy(C.estado, "Disponible");
                    C.personas = 0; // vaciado de la habitacion
                    fseek(hab, (int)sizeof(Habitacion) * (-1), SEEK_CUR);
                    fwrite(&C, sizeof(Habitacion), 1, hab);
                    break;

                }
            }
            fclose(hab);
        }
        fclose(clientes);
    }

    printf(VERDE_T"\n\t- CHECKOUT REALIZADO CON EXITO! GRACIAS POR SU ESTADIA. -\n"RESET_COLOR);
    system("pause");
    return 0;
}
void listadoInsercionEdadCliente(int flag)
{
    FILE * clientes=fopen(archivoClientes, "rb");
    Cliente A[20];
    Cliente B;
    int validos=0;
    if(clientes)
    {
        while((fread(&B, sizeof(Cliente),1, clientes))>0)
        {
            if(flag)
            {
                if((strcmpi(B.estado, "Activo"))==0)
                {
                    A[validos]=B;
                    validos++;
                }
            }
            else
            {
                A[validos]=B;
                validos++;
            }
        }
        for(int i=0; i<validos-1; i++)
        {
            insertarEdad(A, i, A[i+1]);
        }
        for(int i=0; i<validos; i++)
        {
            mostrarUnCliente(A[i]);
        }
        fclose(clientes);
    }
}
void insertarEdad(Cliente A[], int i, Cliente dato)
{
    while(i>=0 && dato.edad<A[i].edad)
    {
        A[i+1]=A[i];
        i--;
    }
    A[i+1]=dato;
}
void listadoSeleccionNombreCliente(int flag)
{
    FILE * clientes = fopen(archivoClientes, "rb");
    Cliente A[20];
    Cliente B;
    Cliente aux;
    int validos=0, posMenor;
    if(clientes)
    {
        while((fread(&B, sizeof(Cliente),1,clientes))>0)
        {
            if(flag)
            {
                if((strcmpi(B.estado, "Activo"))==0)
                {
                    A[validos]=B;
                    validos++;
                }
            }
            else
            {
                A[validos]=B;
                validos++;
            }
        }
        for(int i=0; i<(validos-1); i++)
        {
            posMenor=seleccionNombre(A, i, validos);
            aux=A[i];
            A[i]=A[posMenor];
            A[posMenor]=aux;

        }
        for(int i=0; i<validos; i++)
        {
            mostrarUnCliente(A[i]);
        }
        fclose(clientes);
    }
}
int seleccionNombre(Cliente A[], int posicion, int validos)
{
    int posMenor=posicion;
    char menor[50];
    strcpy(menor, A[posicion].nombre);
    for(int i=posicion+1; i<validos; i++)
    {
        if((strcmpi(menor, A[i].nombre))>0)
        {
            posMenor=i;
            strcpy(menor, A[i].nombre);
        }
    }
    return posMenor;
}
void listadoInsercionHabitacionDeCliente(int flag)
{
    FILE * clientes=fopen(archivoClientes, "rb");
    Cliente A[20];
    Cliente B;
    int validos=0;
    if(clientes)
    {
        while((fread(&B, sizeof(Cliente), 1, clientes))>0)
        {
            if(flag)
            {
                if((strcmpi(B.estado,"Activo"))==0)
                {
                    A[validos]=B;
                    validos++;
                }
            }
        }
        for(int i=0; i<validos-1; i++)
        {
            insertarNroHabitacionCliente(A, i, A[i+1]);
        }
        for (int i = 0; i < validos; i++)
        {
            mostrarUnCliente(A[i]);
        }
        fclose(clientes);
    }
}
void insertarNroHabitacionCliente(Cliente A[], int i, Cliente dato)
{
    while (i>= 0 && dato.habitacion.numero < A[i].habitacion.numero)
    {
        A[i+1] = A[i];
        i--;
    }
    A[i+1] = dato;
}
void listadoInsercionHabDisponible()
{
    FILE * hab=fopen(archivoHabitaciones, "rb");
    Habitacion A[20];
    Habitacion B;
    int validos=0;
    if(hab)
    {
        while((fread(&B, sizeof(Habitacion),1, hab))>0)
        {
            if((strcmpi(B.estado,"Disponible"))==0)
            {
                A[validos]=B;
                validos++;
            }
        }
        for(int i=0; i<validos-1; i++)
        {
            insertarNumero(A, i, A[i+1]);
        }
        for(int i=0; i<validos; i++)
        {
            mostrarUnaHabitacion(A[i]);
        }
        fclose(hab);
    }
}
void editarHabitacion()
{
    FILE * hab=fopen(archivoHabitaciones, "r+b");
    Habitacion A;
    int numHab;

    if(hab)
    {
        printf("\n\nIngrese la habitacion que desea editar: ");
        scanf("%i", &numHab);


        while(fread(&A, sizeof(Habitacion), 1, hab)>0)
        {
            if(numHab==A.numero)
            {
                mostrarUnaHabitacion(A);
                printf("\n\n- Ingrese el nuevo numero de camas: ");
                scanf("%i", &A.camas);
                printf("\n\n- Ingrese el nuevo precio: ");
                scanf("%i", &A.precio);

                fseek(hab, (int) sizeof(Habitacion)*(-1), SEEK_CUR);
                fwrite(&A, sizeof(Habitacion), 1, hab);
                printf(VERDE_T"\n\t- HABITACION ACTUALIZADA CON EXITO -\n\n"RESET_COLOR);
                system("pause");
                break;
            }
        }
        fclose(hab);
    }
}