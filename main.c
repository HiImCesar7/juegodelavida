#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//deficiones de alias de tipo de variable
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;


//medidas del tablero
#define alto (30U) //alto del tablero
#define ancho (30U) //ancho del tablero 

//condiciones de celulas
#define celula_viva (1U) //celula viva
#define celula_muerta (0U) //celula muerta
#define sobrevive_min (2U) //valor minimo de vecinos para que sobreviva la celula
#define sobrevive_max (3U) //valor maximo de vecinos para que sobreviva la celula
#define reproduccion (3U) //valor necesario para que una celula muerta reviva

//modelos de prueba
#define modelo_prueba (4U) //cambiar valor de la macro para probar diferentes algoritmos

//prototipos de funcion
void imprimir_vtablero(uint8 tablero[alto][ancho]);
void siguiente_vgeneracion(uint8 u8tablero_actual[alto][ancho], uint8 u8tablero_siguiente[alto][ancho]);
void copiar_vtablero(uint8 u8tablero_actual[alto][ancho], uint8 u8tablero_destino[alto][ancho]);

int main() {

    uint8 u8tablero_actual[alto][ancho] = {0};
    uint8 u8tablero_siguiente[alto][ancho] = {0};

    switch (modelo_prueba)
    {
    case 1:
            //glider
             u8tablero_actual[1][2] = (uint8)celula_viva;
             u8tablero_actual[2][3] = (uint8)celula_viva; 
             u8tablero_actual[3][1] = (uint8)celula_viva;
             u8tablero_actual[3][2] = (uint8)celula_viva;
             u8tablero_actual[3][3] = (uint8)celula_viva;
        break;
    case 2:
            //oscilador
             u8tablero_actual[10][9] = (uint8)celula_viva;
             u8tablero_actual[10][10] = (uint8)celula_viva;
             u8tablero_actual[10][11] = (uint8)celula_viva;

        break;
    case 3:
            //nave espacial
             u8tablero_actual[1][2] = (uint8)celula_viva;
             u8tablero_actual[1][5] = (uint8)celula_viva;
             u8tablero_actual[2][1] = (uint8)celula_viva;
             u8tablero_actual[2][5] = (uint8)celula_viva;
             u8tablero_actual[3][5] = (uint8)celula_viva;
             u8tablero_actual[3][1] = (uint8)celula_viva;
             u8tablero_actual[4][3] = (uint8)celula_viva;
             u8tablero_actual[4][4] = (uint8)celula_viva;
             u8tablero_actual[4][5] = (uint8)celula_viva;
        break;
    case 4:
            //inicializacion aleatoria de todas las celdas
            for (uint8 u8i = 0; u8i < (uint8)alto; u8i++) {
                for (uint8 u8j = 0; u8j < (uint8)ancho; u8j++) {
                u8tablero_actual[u8i][u8j] = rand() % 2; 
                }
            }
    default:
            //Do nothing
        break;
    }

    while(1)
    {
        imprimir_vtablero(u8tablero_actual); // se imprime el tablero actual en la pantalla 

        siguiente_vgeneracion(u8tablero_actual,u8tablero_siguiente); // se genera la nueva generacion de celulas

        copiar_vtablero(u8tablero_siguiente,u8tablero_actual); //se actualiza el tablero despues de las reglas del ciclo de la vida

        usleep(200000); // Pausa de 200 milisegundos para poder ver el comportamiento del programa

        system("cls"); // comando de consola para poder visualizar el comportamiento del pograma
    }



    return 0;
}

void copiar_vtablero(uint8 u8tablero_actual[alto][ancho], uint8 u8tablero_destino[alto][ancho])
{
    for(uint8 altura = 0; altura < alto ; altura++)
    {
        for(uint8 anchura = 0; anchura < ancho ; anchura++)
        {
            u8tablero_destino[altura][anchura] = u8tablero_actual[altura][anchura];
        }
    }

}

void imprimir_vtablero(uint8 tablero[alto][ancho])
{
    for(uint8 altura = 0; altura < alto ; altura++)
    {
        for(uint8 anchura = 0; anchura < ancho; anchura++)
        {
            if(tablero[altura][anchura] == (uint8)celula_viva)
            {
                printf("O");
            }
            else
            {
                printf(".");
            }
        }

        printf("\n");
    }

}

void siguiente_vgeneracion(uint8 u8tablero_actual[alto][ancho], uint8 u8tablero_siguiente[alto][ancho])
{
    for (uint8 u8altura = 0; u8altura < alto; u8altura++) {
        for (uint8 u8anchura = 0; u8anchura < ancho; u8anchura++) {

            uint16 u16vecinos_vivos = 0;

            for(sint8 s8y = -1 ; s8y <= 1 ; s8y++)
            {
                for(sint8 s8x = -1; s8x <= 1 ; s8x++)
                {
                    if (!(s8x == (sint8)0 && s8y == (sint8)0)) {

                            sint8 s8plano_x = s8x + u8anchura;
                            sint8 s8plano_y = s8y + u8altura;


                    if (s8plano_x >= 0 && s8plano_x < (uint8)ancho && s8plano_y >= 0 && s8plano_y < (uint8)alto) {
                            u16vecinos_vivos += (uint8)u8tablero_actual[s8plano_y][s8plano_x];
                    }

                }
            }
        }


         if (u8tablero_actual[u8altura][u8anchura] == (uint8)celula_viva) {

                if (u16vecinos_vivos == (uint16)sobrevive_min || u16vecinos_vivos == (uint16)sobrevive_max) {

                    u8tablero_siguiente[u8altura][u8anchura] = (uint8)celula_viva;

                } else {

                    u8tablero_siguiente[u8altura][u8anchura] = (uint8)celula_muerta;
                }
            } else {

                if (u16vecinos_vivos == (uint16)reproduccion) {

                    u8tablero_siguiente[u8altura][u8anchura] = (uint8)celula_viva;

                } else {

                    u8tablero_siguiente[u8altura][u8anchura] = (uint8)celula_muerta;
                }
            }
        }

    }

}
