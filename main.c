#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>

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
        printf("\n- NOMBRE: ");
        fflush(stdin);
        gets(A.nombre);

        printf("\n- NACIONALIDAD: ");
        fflush(stdin);
        gets(A.nacionalidad);

        printf("\n- EDAD: ");
        do
        {
            scanf("%i", &A.edad);
            if(A.edad < 1 || A.edad > 130)
            {
                printf("\n[Se ingreso una edad invalida, intente nuevamente.]");
                system("pause");
            }
        }while(A.edad < 1 || A.edad > 130);

    printf("\n- HABITACIONES DISPONIBLES ");
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
                    printf("\n[La habitacion elegida esta ocupada. Ingrese otra habitacion por favor.]");
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



void login(char nombreArchivo[])
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

        if(verificarUsuario(nombreArchivo,nombre,clave))
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
        registrarUsuario(nombreArchivo);
    }
    else
    {
        printf("Opcion invalida.\n");
    }
}

void registrarUsuario(char usuarios[])
{
    Usuario A;
    int i=0;
    char caracter;
    char clave[30];
    FILE *usuario = fopen(usuarios, "ab");

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

int verificarUsuario(char nombreArchivo[], char nombre[], char contrasena[])
{
    Usuario A;

    FILE *usuario = fopen(nombreArchivo, "rb");
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