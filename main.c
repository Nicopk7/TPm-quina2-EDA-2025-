//GRUPO 34
//PEREYRA NICOLAS - VOTTERO ELISEO
//ANALISIS

                                                        /*COMPARACION DE ESTRUCTURAS

                                                        COSTOS          LSO     LIBT    ABB
                                                        ______________________________________
                                                        MAX.ALTA        91.00   45.50   11.50
                                                        MED.ALTA        23.01   11.51   6.17
                                                        MAX.BAJA        91.00   45.50   8.50
                                                        MED.BAJA        22.38   11.19   5.36
                                                        MAX.EVOEX       100.00  14.00   12.00
                                                        MED.EVOEX       45.13   11.18   6.43
                                                        MAX.EVONOEX     71.00   14.00   11.00
                                                        MED.EVONOEX     24.57   10.49   5.95
                                                        */

/*
Si lo que se busca hacer son busquedas, tanto la Lista invertida como el Arbol binario de busqueda son buenos, pero el ABB
gana por menor costo promedio.
Si hay muchas altas y bajas, el ABB es el mas adecuado porque evita corrimientos.
La LSO queda totalmente descartada en escenarios grandes, solo sirve si el conjunto de elementos o datos es muy chico o fijo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Alumno.h"
#include "LSO.h"
#include "LIBT.h"
#include "ABB.h"
#define separador printf("____________________________________________________________________________________________ \n")
#define borrador system("cls")
#define pausa system("pause")
#define MAXALUMNOS 130

typedef struct {
    float maximo_alta;
    float medio_alta;
    float maximo_baja;
    float medio_baja;
    float max_evo_succ;
    float med_evo_succ;
    float max_evo_fail;
    float med_evo_fail;
    float cant_altas;
    float cant_bajas;
    float cant_evos_succ;
    float cant_evos_fail;
} Costos;

void init_costos(Costos *x) {
    (*x).maximo_alta=0;
    (*x).medio_alta=0;
    (*x).maximo_baja=0;
    (*x).medio_baja=0;
    (*x).max_evo_succ=0;
    (*x).med_evo_succ=0;
    (*x).max_evo_fail=0;
    (*x).med_evo_fail=0;
    (*x).cant_altas=0;
    (*x).cant_bajas=0;
    (*x).cant_evos_fail=0;
    (*x).cant_evos_succ=0;
}

void menu_admin_est() {
    printf("1.Ingresar alumno\n");
    printf("2.Eliminar alumno\n");
    printf("3.Modificar alumno\n");
    printf("4.Consultar alumno\n");
    printf("5.Memorizacion Previa\n"); //posible cambio de cartel por "Cargar Estructura"
    printf("6.Mostrar Estructura\n");
    printf("7.Volver\n");
    printf("Elija una opcion:\n");
}

int main() {
    char codigoAbuscar[8];
    int exitoLI = 0, opcion, opcion2, opcion3, resultalta, exito_aux, red, contadorLI = 0, contadorLSO = 0, contadorABB = 0, exitoABB, costo;
    int modo, operacion;
    float costoaux = 0;
    Costos c_lso;
    Costos c_libb;
    Costos c_abb;
    init_costos(&c_lso);
    init_costos(&c_libb);
    init_costos(&c_abb);
    Alumno nuevo, aux;
    Alumno *evocativo;
    ABB arbol;
    init_ABB(&arbol);
    inicializarLI();

    do {
        printf("******* Menu Principal ******\n");
        printf("1.Mostrar Estructuras\n");
        printf("2. Comparar Estructurar\n");
        printf("3. Salir\n");
        separador;
        printf("Elija una opcion:\n");
        fflush(stdin);
        scanf("%d", &opcion);
        switch (opcion) {
            case 1: {
                do {
                    modo=0;
                    borrador;
                    separador;
                    printf("\tElija la Estructura a mostrar\n");
                    printf("1.Lista Secuencial Ordenada\n");
                    printf("2.Lista Invertida con Busqueda Binaria (triseccion)\n");
                    printf("3.Arbol Binario de Busqueda\n");
                    printf("4.Volver\n");
                    separador;
                    fflush(stdin);
                    scanf("%d", &opcion2);
                    borrador;
                    switch (opcion2) {
                        case 1: {
                            printf("Lista Secuencial Ordenada\n");
                            mostrarLSO(contadorLSO);
                            pausa;
                            break;
                        }
                        case 2: {
                            printf("Lista Invertida con Busqueda Binaria (Triseccion)\n");
                            mostrarListaInvertida(contadorLI);
                            pausa;
                            break;
                        }
                        case 3: {
                            printf("Arbol Binario de Busqueda\n");
                            muestra_abb(arbol.raiz);
                            pausa;
                            break;
                        }
                    }
                } while (opcion2 != 4);
                break;
            } // fin case mostrar estructura

            case 2: { /// INICIO DE COMPARACION DE ESTRUCTURA
                borrador;
                costoaux = 0;
                modo = 1;
                borrar_arbol(&arbol);
                contadorLSO = 0;
                limpiarLI(&contadorLI);
                init_ABB(&arbol);
                inicializarLI();

                FILE *fp = fopen("Operaciones-Alumnos.txt", "r");
                if (fp == NULL) {
                    printf("\tNo se pudo abrir el archivo\n");
                } else {
                    while (fscanf(fp, "%d", &operacion) == 1) {
                        if (fscanf(fp, "%10s", aux.codigo) != 1) break;

                        switch (operacion) {
                            case 1: { // ALTA

                                // leer nombre y apellido
                                fscanf(fp, " %80[^\n]", aux.nombreapellido);
                                fgetc(fp);

                                // leer correo
                                fscanf(fp, " %23s", aux.correo);
                                fgetc(fp);

                                // leer nota
                                if (fscanf(fp, "%d", &aux.nota) == 1) {

                                }
                                fgetc(fp);

                                // leer condicion final
                                fscanf(fp, " %10s", aux.condicionFinal);
                                fgetc(fp);




                                // Alta en LSO
                                costoaux = 0;
                                resultalta = alta(aux, &contadorLSO, &costoaux);

                                if (resultalta) {
                                    c_lso.cant_altas++;
                                    c_lso.medio_alta += costoaux;
                                    if (costoaux > c_lso.maximo_alta)
                                        c_lso.maximo_alta = costoaux;
                                }

                                // Alta en ABB
                                costoaux = 0;
                                resultalta = AltaABB(&arbol, aux, &exito_aux, &costoaux);
                                if (resultalta) {
                                    c_abb.cant_altas++;
                                    c_abb.medio_alta += costoaux;
                                    if (costoaux > c_abb.maximo_alta)
                                        c_abb.maximo_alta = costoaux;
                                }

                                // Alta en LI
                                if (contadorLI < MAX) {
                                    costoaux = 0;
                                    resultalta = altaLI(aux, &contadorLI, &costoaux);
                                    if (resultalta == 0) {
                                        c_libb.cant_altas++;
                                        c_libb.medio_alta += costoaux;
                                        if (costoaux > c_libb.maximo_alta)
                                            c_libb.maximo_alta = costoaux;
                                    }
                                }
                                break;
                            }

                            case 2: { // BAJA

                                // leer nombre y apellido
                                fscanf(fp, " %80[^\n]", aux.nombreapellido);
                                fgetc(fp);

                                // leer correo
                                fscanf(fp, " %23s", aux.correo);
                                fgetc(fp);

                                // leer nota
                                if (fscanf(fp, "%d", &aux.nota) == 1) {
                                }
                                fgetc(fp);

                                // leer condicion final
                                fscanf(fp, " %10s", aux.condicionFinal);
                                fgetc(fp);

                                // Baja en LSO
                                costoaux = 0;
                                if (contadorLSO > 0) {
                                    int resbaja = baja(aux, &contadorLSO, &costoaux, modo);
                                    if (resbaja) {
                                        c_lso.cant_bajas++;
                                        c_lso.medio_baja += costoaux;
                                        if (costoaux > c_lso.maximo_baja)
                                            c_lso.maximo_baja = costoaux;
                                    }
                                }

                                // Baja en ABB
                                costoaux = 0;
                                if (arbol.Nodos > 0) {
                                    int resbaja = bajaABB(&arbol, aux, &costoaux, modo);
                                    if (resbaja == 1) {
                                        c_abb.cant_bajas++;
                                        c_abb.medio_baja += costoaux;
                                        if (costoaux > c_abb.maximo_baja)
                                            c_abb.maximo_baja = costoaux;
                                    }
                                }

                                // Baja en LI
                                costoaux = 0;
                                if (contadorLI > 0) {
                                    int resbaja = BajaLI(aux, &contadorLI, &costoaux, modo);
                                    if (resbaja == 1) {
                                        c_libb.cant_bajas++;
                                        c_libb.medio_baja += costoaux;
                                        if (costoaux > c_libb.maximo_baja)
                                            c_libb.maximo_baja = costoaux;
                                    }
                                }
                                break;
                            }

                            case 3: { // EVOCACION
                                exito_aux = 0;
                                costoaux = 0;
                                if (contadorLSO > 0) {
                                    evocar(aux.codigo, contadorLSO, &exito_aux, &costoaux);
                                    if (exito_aux) {
                                        c_lso.cant_evos_succ++;
                                        c_lso.med_evo_succ += costoaux;
                                        if (costoaux > c_lso.max_evo_succ)
                                            c_lso.max_evo_succ = costoaux;
                                    } else {
                                        c_lso.cant_evos_fail++;
                                        c_lso.med_evo_fail += costoaux;
                                        if (costoaux > c_lso.max_evo_fail)
                                            c_lso.max_evo_fail = costoaux;
                                    }
                                }

                                exito_aux = 0;
                                costoaux = 0;
                                if (arbol.Nodos > 0) {
                                    evocar_alumno_ABB(&arbol, aux.codigo, &exito_aux, &costoaux);
                                    if (exito_aux) {
                                        c_abb.cant_evos_succ++;
                                        c_abb.med_evo_succ += costoaux;
                                        if (costoaux > c_abb.max_evo_succ)
                                            c_abb.max_evo_succ = costoaux;
                                    } else {
                                        c_abb.cant_evos_fail++;
                                        c_abb.med_evo_fail += costoaux;
                                        if (costoaux > c_abb.max_evo_fail)
                                            c_abb.max_evo_fail = costoaux;
                                    }
                                }

                                exito_aux = 0;
                                costoaux = 0;
                                if (contadorLI > 0) {
                                    evocarLI(aux.codigo, contadorLI, &exito_aux, &costoaux);
                                    if (exito_aux) {
                                        c_libb.cant_evos_succ++;
                                        c_libb.med_evo_succ += costoaux;
                                        if (costoaux > c_libb.max_evo_succ)
                                            c_libb.max_evo_succ = costoaux;
                                    } else {
                                        c_libb.cant_evos_fail++;
                                        c_libb.med_evo_fail += costoaux;
                                        if (costoaux > c_libb.max_evo_fail)
                                            c_libb.max_evo_fail = costoaux;
                                    }
                                }
                                break;
                            }
                        } // fin switch
                    } // fin while
                    fclose(fp);

                    printf("LSO: %d Alumnos\n", contadorLSO);
                    printf("LI: %d Alumnos\n", contadorLI);
                    printf("ABB: %d Alumnos\n", arbol.Nodos);
                    printf("\t COMPARACION DE ESTRUCTURAS\n\n");
                    printf("COSTOS\t\tLSO\tLIBT\tABB\n");
                    separador;

                    float medAltaLSO = (c_lso.cant_altas > 0) ? (c_lso.medio_alta / c_lso.cant_altas) : 0.0;
                    float medAltaLI  = (c_libb.cant_altas > 0) ? (c_libb.medio_alta / c_libb.cant_altas) : 0.0;
                    float medAltaABB = (c_abb.cant_altas > 0) ? (c_abb.medio_alta / c_abb.cant_altas) : 0.0;

                    float medBajaLSO = (c_lso.cant_bajas > 0) ? (c_lso.medio_baja / c_lso.cant_bajas) : 0.0;
                    float medBajaLI  = (c_libb.cant_bajas > 0) ? (c_libb.medio_baja / c_libb.cant_bajas) : 0.0;
                    float medBajaABB = (c_abb.cant_bajas > 0) ? (c_abb.medio_baja / c_abb.cant_bajas) : 0.0;

                    float medEvoExLSO = (c_lso.cant_evos_succ > 0) ? (c_lso.med_evo_succ / c_lso.cant_evos_succ) : 0.0;
                    float medEvoExLI  = (c_libb.cant_evos_succ > 0) ? (c_libb.med_evo_succ / c_libb.cant_evos_succ) : 0.0;
                    float medEvoExABB = (c_abb.cant_evos_succ > 0) ? (c_abb.med_evo_succ / c_abb.cant_evos_succ) : 0.0;

                    float medEvoNoExLSO = (c_lso.cant_evos_fail > 0) ? (c_lso.med_evo_fail / c_lso.cant_evos_fail) : 0.0;
                    float medEvoNoExLI  = (c_libb.cant_evos_fail > 0) ? (c_libb.med_evo_fail / c_libb.cant_evos_fail) : 0.0;
                    float medEvoNoExABB = (c_abb.cant_evos_fail > 0) ? (c_abb.med_evo_fail / c_abb.cant_evos_fail) : 0.0;

                    printf("MAX.ALTA\t%.2f\t%.2f\t%.2f\n", c_lso.maximo_alta, c_libb.maximo_alta, c_abb.maximo_alta);
                    printf("MED.ALTA\t%.2f\t%.2f\t%.2f\n", medAltaLSO, medAltaLI, medAltaABB);
                    printf("MAX.BAJA\t%.2f\t%.2f\t%.2f\n", c_lso.maximo_baja, c_libb.maximo_baja, c_abb.maximo_baja);
                    printf("MED.BAJA\t%.2f\t%.2f\t%.2f\n", medBajaLSO, medBajaLI, medBajaABB);
                    printf("MAX.EVOEX\t%.2f\t%.2f\t%.2f\n", c_lso.max_evo_succ, c_libb.max_evo_succ, c_abb.max_evo_succ);
                    printf("MED.EVOEX\t%.2f\t%.2f\t%.2f\n", medEvoExLSO, medEvoExLI, medEvoExABB);
                    printf("MAX.EVONOEX\t%.2f\t%.2f\t%.2f\n", c_lso.max_evo_fail, c_libb.max_evo_fail, c_abb.max_evo_fail);
                    printf("MED.EVONOEX\t%.2f\t%.2f\t%.2f\n", medEvoNoExLSO, medEvoNoExLI, medEvoNoExABB);
                }
                break;
            }


            case 3: {
                printf("Saliendo...\n");
                break;
            }

            default: {
                printf("\tIngrese una Opcion Valida\n\n");
                pausa;
                break;
            }
        }//fin switch menu
    } while (opcion!=3);//fin menu principal

    return 0;
}

