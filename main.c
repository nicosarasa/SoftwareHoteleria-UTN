#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <string.h>
#include <ctype.h>
#include <time.h>

#define RESET_COLOR    "\x1b[0m"
#define ROJO_T     "\x1b[31m"
#define ROJO_F     "\x1b[41m"
#define AMARILLO_T "\x1b[33m"
#define AMARILLO_F  "\x1b[43m"
#define AZUL_T     "\x1b[34m"
#define AZUL_F      "\x1b[44m"
#define MAGENTA_T  "\x1b[35m"
#define MAGENTA_F  "\x1b[45m"
#define CYAN_T     "\x1b[36m"
#define CYAN_F     "\x1b[46m"
#define BLANCO_T   "\x1b[37m"
#define BLANCO_F   "\x1b[47m"

// CONSTANTES
const int rows=5;
const int cols=3;

// PROTOTIPADO DE ESTRUCTURAS
typedef struct
{
    char nombre[20];
    char contrasena[50];
} Usuario;

typedef struct
{
    int numero;
    int categoria;
    int precio;
    char estado[20];
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



int main()
{
    Habitacion habitaciones[rows*cols];
    setHabitacionesStatus(habitaciones, rows*cols);

    char listaDeUsuarios[30] = "usuarios.txt";

}

Cliente cargarCliente(char nombre[])
{
    FILE * hab = fopen(nombre, "r+b");
    Cliente A;
    Habitacion B;
    int flag = 0;
    if(hab)
    {
        printf("\nNOMBRE: ");
        fflush(stdin);
        gets(A.nombre);

        printf("\nNACIONALIDAD: ");
        fflush(stdin);
        gets(A.nacionalidad);

        printf("\nEDAD: ");
        do
        {
            scanf("%i", &A.edad);
            if(A.edad < 1 || A.edad > 130)
            {
                printf("\nSe ingreso una edad invalida, intente nuevamente.");
                system("pause");
            }
        }while(A.edad < 1 || A.edad > 130);

    printf("\nHABITACIONES DISPONIBLES ");
    while((fread(&B, sizeof(Cliente), 1, hab))>0)
    {
        if((strcmpi(B.estado, "Disponible"))==0)
        {
            printf("| %i ", B.numero);
        }
    }
    fseek(hab, 0, SEEK_SET);
    do
    {
        printf("\nNRO. HABITACION: %i");
        scanf("%i", &A.habitacion.numero);
        while((fread(&B,sizeof(Habitacion), 1, hab))>0)
        {
            if(B.numero==A.habitacion.numero)
            {
                if((strcmpi(B.estado, "Ocupada"))==0)
                {
                    printf("\nLa habitacion elegida esta ocupada. Ingrese otra habitacion por favor.");
                    system("pause");
                    flag=1;
                }
                else
                {
                    flag=0;
                    break;
                }
            }
        }
        fseek(hab, 0, SEEK_SET);
    }while(flag==1);
        fclose(hab);
    }
    return A;
}

void mostrarEdificio(int M[rows][cols], char nombre[])
{
    int i,j;
    Habitacion A;
    FILE * hab=fopen(nombre, "rb");
    if(hab)
    {
        for(i=rows-1; i>=0; i--)
        {
            for(j=0; i<cols; i++)
            {
                while(fread(&A, sizeof(Habitacion), 1, hab))
                {
                    if((strcmpi(A.estado,"Ocupado"))==0 && (strcmpi(A.categoria,"Normal"))==0)
                    {
                        printf("[ " ROJO_F "%i" RESET_COLOR" ]");
                    }
                    else if((strcmpi(A.estado,"Ocupado"))==0 && (strcmpi(A.categoria, "VIP"))==0)
                    {
                        printf(AMARILLO_F "[ " ROJO_F "%i" AMARILLO_F" ]");

                    }
                }
            }
        }
        fclose(hab);
    }

}

void setHabitacionesStatus(char nombre[])
{
    int r, j;
    Habitacion A;
    FILE * hab;
    if((hab=fopen(nombre, "rb"))==NULL)
    {
        hab=fopen(nombre, "wb");
        if(hab)
        {
            for(r=1; r<=rows; r++)
            {
                for(j=1; j<=cols; j++)
                {
                    strcpy(A.estado,"Disponible");
                    A.numero= (r*100) + j;
                    A.precio= (j *4600) + (r*2150) + 1300;
                    if(j!=3)
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

}


void registrarUsuario(char usuarios[]){
    Usuario usuario;
    FILE *archivo = fopen(usuarios, "ab");

    printf("----| Formulario de Registro |----");
    printf("Nombre de usuario: ");
    scanf("%s", usuario.nombre);
    printf("Contrasena: ");
    scanf("%s", usuario.contrasena);

    if(archivo){
        fwrite(&usuario, sizeof(Usuario), 1, archivo);
        fclose(archivo);
    }

    printf("Usuario registrado correctamente!\n");
}

int verificarUsuario(char usuarios[], char nombre, char contrasena){
    Usuario usuario;

    FILE *archivo = fopen(usuarios, "rb");
    if(archivo){
        while(fread(&usuario, sizeof(Usuario), 1, archivo) > 0){
            if(strcmp(nombre, usuario.nombre) == 0 && strcmp(contrasena, usuario.contrasena) == 0){
                fclose(archivo);
                return 1;
            }
        }
        fclose(archivo);
    }
    return 0;
}

void login(char usuarios[]){
    FILE *archivo = fopen(usuarios, "rb");

    printf("----| Bienvenido a ... Sistema de Software Hotelero |----");

    system("pause");
    

    printf("¿Estas registrado?");
    printf("1. Si\n");
    printf("2. No\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    if (opcion == 1)
    {
        printf("Nombre de usuario: ");
        scanf("%s", nombre);
        printf("Contrasena: ");
        scanf("%s", contrasena);

        if(verificarUsuario(usuarios,nombre,contrasena)){
            printf("Inicio de sesion exitoso. Bienvenido %s!\n", nombre);
        }else{
            printf("Nombre de usuario o contrasena incorrectos.\n");
        }

    }else if (opcion == 2){
        registrarUsuario(usuarios);
    }else{
        printf("Opcion invalida.\n");
    }
}