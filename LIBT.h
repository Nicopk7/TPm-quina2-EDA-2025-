#ifndef LIBT_H_INCLUDED
#define LIBT_H_INCLUDED
#include "Alumno.h"
#include "LSO.h"
#define MAXALUMNOS 130

Alumno* ListaInvertida[MAXALUMNOS];


//PROTOTIPOS
void inicializarLI();
void localizarLI(const char *codigo_abuscar, int *posicion, int *exito, int n, float *costo);
int altaLI(Alumno nuevo, int *n, float *costo);
int BajaSinConfirmacionLI(Alumno aux, int *n, float *costo, int flag);
Alumno* evocarLI(const char *codigo, int n, int *exito, float *costo);
void mostrarListaInvertida(int n);
void limpiarLI(int *n);
void memorizacionPreviaLI(int *n, float *costos);

//FUNCIONES
void inicializarLI(){
    for (int i = 0; i < MAXALUMNOS; i++) {
        ListaInvertida[i] = NULL;
    }
}

void localizarLI(const char *codigo_abuscar, int *posicion, int *exito, int n, float *costo) {
    int LI = 0, LS = n - 1;
    int m;
    *exito = 0;

    if (n == 0){
        *exito = 0;
        *posicion = 0;
    }
    else{
        m = (LI + LS + 1) / 2;
        while (LI <= LS && strcmp_insensitive(ListaInvertida[m]->codigo, codigo_abuscar) != 0) {
            if (strcmp_insensitive(ListaInvertida[m]->codigo, codigo_abuscar) < 0) {
                LI = m + 1;
            } else {
                LS = m - 1;
            }
            m = (LI + LS + 1) / 2;
            *costo += 2;
        }
        *exito = (LI <= LS);
        *posicion = m;
        if (*exito){
            *costo += 2;
        }
    }
}


int altaLI(Alumno nuevo, int *n, float *costo) {
    int posicion = 0;
    int exito = 0;
    float costoaux = 0;
    localizarLI(nuevo.codigo, &posicion, &exito, *n, &costoaux);
    if (exito) {
        return 1; // Ya existe
    }else{

    Alumno* nuevoPtr = malloc(sizeof(Alumno));
    if (nuevoPtr == NULL) {
        return 2; // Error de memoria
    }

    *nuevoPtr = nuevo;

    for (int i = *n; i > posicion; i--) {
        ListaInvertida[i] = ListaInvertida[i - 1];
        *costo+= 0.5;
    }

    ListaInvertida[posicion] = nuevoPtr;
    *costo+=0.5;
    (*n)++;
    return 0;} //OK
}

void mostrarAlumno(Alumno a){
    printf("Codigo: %s\n", a.codigo);
    printf("Nombre y Apellido: %s\n", a.nombreapellido);
    printf("Correo: %s\n", a.correo);
    printf("Nota: %d\n", a.nota);
    printf("Condicion Final: %s\n", a.condicionFinal);
    printf("-------------------------------\n");
}

int BajaLI(Alumno aux, int *n, float *costo, int flag){
    int exito, pos, confirmacion;
    float costoaux = 0;
    localizarLI(aux.codigo, &pos, &exito, *n, &costoaux);
    if (exito==0){
        return 0;
    }
    else{
        if(flag == 1){
            if(!(0 == strcmp_insensitive(ListaInvertida[pos]->codigo, aux.codigo) &&
            0 == strcmp_insensitive(ListaInvertida[pos]->nombreapellido, aux.nombreapellido) &&
            0 == strcmp_insensitive(ListaInvertida[pos]->correo, aux.correo) &&
            ListaInvertida[pos]->nota == aux.nota &&
            0 == strcmp_insensitive(ListaInvertida[pos]->condicionFinal, aux.condicionFinal))){
            return exito = 0;
            }
        }
        if(flag == 0){
            printf("Confirmacion Baja de:\n");
            mostrarAlumno(*ListaInvertida[pos]);
            printf("Dar de Baja?\n");
            printf("1.Si\n2.No\n");
            scanf("%d",&confirmacion);
            fflush(stdin);
            while(confirmacion!=1 && confirmacion!=2){
                printf("Ingrese una opcion valida\n");
                scanf("%d",&confirmacion);
                fflush(stdin);
            }
            if(confirmacion==2)
                return 2;//baja cancelada
        }
        free(ListaInvertida[pos]);

        for (int i = pos; i < (*n) - 1; i++) {
            ListaInvertida[i] = ListaInvertida[i + 1];
            *costo+= 0.5;
        }
        *n=*n-1;
        return 1;
    }
}

int modificarLI(Alumno modificado, int n) {
    int pos, exito;
    float costoaux = 0;
    localizarLI(modificado.codigo, &pos, &exito, n, &costoaux);

    if (exito){
        strcpy(ListaInvertida[pos]->nombreapellido, modificado.nombreapellido);
        strcpy(ListaInvertida[pos]->correo, modificado.correo);
        ListaInvertida[pos]->nota = modificado.nota;
        strcpy(ListaInvertida[pos]->condicionFinal, modificado.condicionFinal);
        exito = 1;
        return exito;
    }
    else exito = 0;
    return exito;
}

Alumno* evocarLI(const char *codigo, int n, int *exito, float *costo) {
    int pos;
    localizarLI(codigo, &pos, exito, n, costo);

    if (*exito)
        return ListaInvertida[pos];
    else
        return NULL;
}


void mostrarListaInvertida(int n) {
    int contador = 0;

    for (int i = 0; i < n; i++) {
        Alumno* a = ListaInvertida[i];
        printf("Alumno #%d\n", i + 1);
        printf("codigo: %s\n", a->codigo);
        printf("Nombre y Apellido: %s\n", a->nombreapellido);
        printf("Correo: %s\n", a->correo);
        printf("Nota: %d\n", a->nota);
        printf("Condicion Final: %s\n", a->condicionFinal);
        printf("------------------------------\n");
        contador++;
        if (contador == 10 && i != n - 1) {
            printf("Presione ENTER para continuar...\n");
            getchar(); // Espera una tecla
            contador = 0;
        }
    }
    if (n == 0)
        printf("No hay Alumnos cargados.\n");
    system("pause");
}

void limpiarLI(int *n) {
    for (int i = 0; i < *n; i++) {
        if (ListaInvertida[i] != NULL) {
            free(ListaInvertida[i]);
            ListaInvertida[i] = NULL;
        }
    }
    *n = 0;
}

void memorizacionPreviaLI(int *n, float *costos) {
    FILE* archivo = fopen("Alumnos.txt", "r");
    Alumno nuevo;
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    else{
        printf("Archivo abierto con éxito.\n");
    }
    while (fscanf(archivo, "%[^\n]s\n", &nuevo.codigo) == 1 && *n < MAXALUMNOS) {
        fgets(nuevo.nombreapellido, sizeof(nuevo.nombreapellido), archivo);
        fgets(nuevo.correo, sizeof(nuevo.correo), archivo);
        fgets(nuevo.nota, sizeof(nuevo.nota), archivo);
        fgets(nuevo.condicionFinal, sizeof(nuevo.condicionFinal), archivo);

        nuevo.nombreapellido[strcspn(nuevo.nombreapellido, "\n")] = '\0';
        nuevo.correo[strcspn(nuevo.correo, "\n")] = '\0';
        nuevo.condicionFinal[strcspn(nuevo.condicionFinal, "\n")] = '\0';
        altaLI(nuevo, n, costos);
    }
    system("pause");
    fclose(archivo);
}





#endif // LIBT_H_INCLUDED
