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

// CONSTANTES
const int rows=5;
const int cols=3;
const char archivoHabitaciones[]="Habitaciones.txt";
const char archivoClientes[]="Clientes.txt";
const char archivoClientesAUX[]="ClientesAuxiliares.txt";
const char archivoUsuarios[]="Usuarios.txt";

// PROTOTIPADO DE ESTRUCTURAS
typedef struct
{
    char nombre[20];
    char contrasena[50];
} Usuario;

typedef struct
{
    int numero;
    char categoria[20];
    int precio;
    char estado[20];
    int camas;
    int personas;
} Habitacion;

typedef struct
{
    Habitacion habitacion;
    char nombre[50];
    char nacionalidad[40];
    int edad;
    int codigo;
} Cliente;

typedef struct
{
    char user[30];
    char password[40];
} Administrador;

// PROTOTIPADO DE FUNCIONES
void setHabitacionesStatus(int M[rows][cols]);
Cliente cargarCliente(int dato, int H);
void altaDeClientes();
void mostrarEdificio(int M[rows][cols]);
void mostrarClientes();
void mostrarUnCliente();
int bajaDeCliente();
Cliente consultaCliente();
int bajaDeCliente();

int main()
{
    Habitacion habitaciones[rows*cols];
    srand(time(NULL));
    int matrizEdificio[rows][cols];
    int op=0;
    setHabitacionesStatus(matrizEdificio);

}




void login()
{
    int opcion, i=0;
    char nombre[30];
    char clave[30];
    char caracter;

    printf("\t----| Bienvenido a ... Sistema de Software Hotelero |----\n\n");

    sleep(3);

    printf("- Seleccione una opcion:\n\n");
    printf("\t1. Iniciar sesion\n\n");
    printf("\t2. Registrarse\n\n");
    scanf("%d", &opcion);
    system("cls");

    if (opcion == 1)
    {
        printf("\t----| Inicio de sesión en el software |----\n");
        printf("\n- USERNAME: ");
        scanf("%s", nombre);
        printf("\n- PASSWORD: ");
        while(caracter=getch())
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
        system("cls");

        if(verificarUsuario(nombre,clave))
        {
            printf("Inicio de sesion exitoso. Bienvenido %s!\n", nombre);
        }
        else
        {
            printf("Nombre de usuario o contrasena incorrectos.\n");
        }

    }
    else if (opcion == 2)
    {
        registrarUsuario();
    }
    else
    {
        printf("Opcion invalida.\n");
    }
}

void registrarUsuario()
{
    Usuario A;
    int i=0;
    char caracter;
    char clave[30];
    FILE *usuario = fopen(archivoUsuarios, "ab");

    printf("\t----| Formulario de Registro |----\n");
    printf("\n- USUARIO: ");
    scanf("%s", A.nombre);
    printf("\n- CLAVE: ");
    while(caracter=getch())
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

    if(usuario)
    {
        fwrite(&A, sizeof(Usuario), 1, usuario);
        fclose(usuario);
    }

    printf("Usuario registrado correctamente!\n");
}

int verificarUsuario(char nombre[], char contrasena[])
{
    Usuario A;

    FILE *usuario = fopen(archivoUsuarios, "rb");
    if(usuario)
    {
        while((fread(&A, sizeof(Usuario), 1, usuario)) > 0)
        {
            if((strcmp(nombre, A.nombre)) == 0 && (strcmp(contrasena, A.contrasena)) == 0)
            {
                fclose(usuario);
                return 1;
            }
        }
        fclose(usuario);
    }
    return 0;
}

void realizarReserva() {
    Cliente cliente;
    int habitaciones;
    float total;
    
    printf("Bienvenido al sistema de reservas del hotel ... .\n");
    printf("Por favor, ingrese su nombre: ");
    fgets(cliente.nombre, sizeof(cliente.nombre), stdin);
    printf("Ingrese su nacionalidad: ");
    fgets(cliente.nacionalidad, sizeof(cliente.nacionalidad), stdin);
    printf("Ingrese su edad: ");
    scanf("%d", &cliente.edad);
    printf("Ingrese su código: ");
    scanf("%d", &cliente.codigo);
    printf("Ingrese la cantidad de habitaciones a reservar: ");
    scanf("%d", &habitaciones);
    
    total = habitaciones * cliente.habitacion.precio;
    
    printf("\nDetalles de la reserva:\n");
    printf("Nombre: %s", cliente.nombre);
    printf("Nacionalidad: %s", cliente.nacionalidad);
    printf("Edad: %d\n", cliente.edad);
    printf("Código: %d\n", cliente.codigo);
    printf("Cantidad de habitaciones: %d\n", habitaciones);
    printf("Total a pagar: $%.2f\n", total);
    
    printf("\nProcesando el pago...\n");
    sleep(2);
    printf("Pago realizado exitosamente. ¡Reserva confirmada!\n");
}

void mostrarHorarioActividades() {
    printf("Horario de Actividades\n");
    printf("----------------------\t");

    printf("Restaurante:\n");
    printf(" - Desayuno: 7:00 AM - 10:00 AM\n");
    printf(" - Almuerzo: 12:00 PM - 14:00 PM\n");
    printf(" - Cena: 20:00 PM - 23:00 PM\n\n");

    printf("Bar:\n");
    printf(" - Horario de apertura: 17:00 PM\n");
    printf(" - Horario de cierre: 01:00 AM\n\n");

    printf("Spa:\n");
    printf(" - Horario de apertura: 9:00 AM\n");
    printf(" - Horario de cierre: 20:00 PM\n\n");

    printf("Pileta:\n");
    printf(" - Horario de apertura: 10:00 AM\n");
    printf(" - Horario de cierre: 18:00 PM\n\n");

    printf("Recreación:\n");
    printf(" - Actividades disponibles durante todo el día\n\n");

    printf("Gimnasio:\n");
    printf(" - Horario de apertura: 7:00 AM\n");
    printf(" - Horario de cierre: 22:30 PM\n");
}

void mostrarInformes(Habitacion habitaciones[], int numHabitaciones)
{
    int contadorHabitaciones = 0;
    int contadorPasajeros = 0;
    int contadorOcupadas = 0;
    int contadorDisponibles = 0;
    int contadorMantenimiento = 0;

    for (int i = 0; i < numHabitaciones; i++) {
        contadorHabitaciones++;
        if (strcmp(habitaciones[i].estado, "Ocupada") == 0) {
            contadorPasajeros++;
            contadorOcupadas++;
        } else if (strcmp(habitaciones[i].estado, "Disponible") == 0) {
            contadorDisponibles++;
        } else if (strcmp(habitaciones[i].estado, "Mantenimiento") == 0) {
            contadorMantenimiento++;
        }
    }

    printf("---- Informes del Hotel ----\n");
    printf("Numero total de habitaciones: %i\n", contadorHabitaciones);
    printf("Numero total de pasajeros: %i\n", contadorPasajeros);
    printf("Habitaciones ocupadas: %i\n", contadorOcupadas);
    printf("Habitaciones disponibles: %i\n", contadorDisponibles);
    printf("Habitaciones en mantenimiento: %i\n", contadorMantenimiento);
}
void altaDeClientes()
{
    FILE * clientes = fopen(archivoClientes, "a+b");
    FILE * hab = fopen(archivoHabitaciones, "r+b");
    Cliente A;
    int dato, flag=0, H;
    Habitacion B;
    if(hab &&  clientes)
    {
        printf("\t\t\t\t- - - BIENVENIDO A LA ALTA DE CLIENTES! - - -\n");
        do
        {
            printf("\n- Ingrese la cantidad de personas que van a ocupar la habitacion. Hay habitaciones de hasta 5 personas: ");
            scanf("%i", &dato);
            if(dato<1 || dato>5)
            {
                printf(ROJO_T"\nERROR: El numero ingresado no es entre 1 y 5. Intente nuevamente.\n"RESET_COLOR);
                system("pause");
            }
        }
        while(dato<1 || dato>5);

        printf("\n- HABITACIONES DISPONIBLES: ");

        while((fread(&B, sizeof(Habitacion), 1, hab))>0)
        {
            if((strcmpi(B.estado,"Disponible"))==0 && B.camas>=dato)
            {
                printf("| %i ", B.numero);
            }
        }
        rewind(hab);

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
                    if((strcmpi(B.estado, "Ocupada"))==0 || B.camas<dato)
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

        for(int i=1; i<=dato; i++)
        {
            printf(AMARILLO_T"\n\t- CLIENTE %i -\n" RESET_COLOR, i);
            A=cargarCliente(dato, H);
            fwrite(&A, sizeof(Cliente), 1, clientes);
        }


        while((fread(&B, sizeof(Habitacion), 1, hab))>0)
        {
            if(H==B.numero)
            {
                strcpy(B.estado, "Ocupada");
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
Cliente cargarCliente(int dato, int H)
{
    FILE * clientes = fopen(archivoClientes, "rb");
    Cliente A, C;
    int flag = 0;
    if(clientes)
    {
        A.habitacion.numero=H;
        do
        {
            printf("\n- NOMBRE: ");
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

        printf("\n- NACIONALIDAD: ");
        fflush(stdin);
        gets(A.nacionalidad);
        strupr(A.nacionalidad);

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
        system("pause");
        system("cls");

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
                    A.precio= ((c+1) *4600) + ((r+1)*2150) + 1300;
                    if(c!=2)
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
    printf(CYAN_T"----------------------------------\n\n"RESET_COLOR);
    printf("- NOMBRE: %s\n", A.nombre);
    printf("- EDAD: %i\n", A.edad);
    printf("- NRO. HABITACION: %i\n", A.habitacion.numero);
    printf("- NACIONALIDAD: %s\n", A.nacionalidad);
    printf("- CODIGO: %i\n\n", A.codigo);
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
int bajaDeCliente()
{
    FILE *clientes, *clientesAUX;
    Cliente A;
    int dato;
    clientesAUX=fopen(archivoClientesAUX,"wb");
    clientes=fopen(archivoClientes,"rb");

    if(clientes && clientesAUX)
    {

        A=consultaCliente();
        dato=A.codigo;
        mostrarUnCliente(A);
        printf("\n\tEsta seguro de eliminar este registro?\n1 - Si\n2 - No\n");
        int op;
        scanf("%i", &op);
        if(op==2)
        {
            printf("\n- Proceso cancelado -\n");
            system("pause");
            system("cls");
            return 1;
        }
        while((fread(&A, sizeof(Cliente),1, clientes))>0)
        {
            if (A.codigo!=dato)
            {
                fwrite(&A, sizeof(Cliente),1, clientesAUX);
            }
        }
        fclose(clientes);
        fclose(clientesAUX);
    }
    clientesAUX=fopen(archivoClientesAUX,"rb");
    clientes=fopen(archivoClientes,"wb");

    if(clientes && clientesAUX)
    {
        while(fread(&A, sizeof(Cliente),1, clientesAUX))
        {
            fwrite(&A, sizeof(Cliente),1, clientes);
        }
        fclose(clientes);
        fclose(clientesAUX);
    }
    remove(archivoClientesAUX);
    printf(VERDE_T"\n\t- Cliente dado de baja con exito -\n"RESET_COLOR);
    return 0;
}
void mostrarUnaHabitacion(Habitacion A)
{
    printf(CYAN_T"----------------------------------\n\n"RESET_COLOR);
    printf("- NRO. DE HABITACION: %i\n", A.numero);
    printf("- CATEGORIA: %s\n", A.categoria);
    printf("- CAMAS: %i\n", A.camas);
    printf("- PRECIO: %i\n", A.precio);
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