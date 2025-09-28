#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED
#include "Alumno.h"
#define MAXALUMNOS 130
#define separador printf("____________________________________________________________________________________________ \n")
#define borrador system("cls")
#define pausa system("pause")

typedef struct{
    float costoLocalizar;
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
}costosLSO;

Alumno LSO[MAXALUMNOS];

//PROTOTIPOS
void localizar(char codigo[], int *exito, int *posicion, int contador, float *costo);
int alta(Alumno a, int *contador, float *costo);
int baja(Alumno a, int *contador, float *costo, int flag);
Alumno evocar(char codigo[], int contador,int *exito_aux, float *costo);
int modificarAlumno(char codigo[], int contador);
int memorizacionprevia(int *contador);
void mostrarLSO(int contador);
int strcmp_insensitive(const char *s1, const char *s2);

void localizar(char codigo[], int *exito, int *posicion, int contador, float *costo){
    int i = 0;
    *costo = 0;
    *exito = 0;
    while (i < contador && strcmp_insensitive(LSO[i].codigo, codigo) < 0){
        i++;
        *costo += 1;
    }
    if (i < contador ){
        *costo+=1;
        if(strcmp_insensitive(LSO[i].codigo, codigo) == 0){
            *exito = 1;
            *posicion = i;
        }
    }
    *posicion = i;

}


int alta(Alumno a, int *contador, float *costo){
    int exito = 0, posicion = 0, j = 0;
    float costoaux;
    localizar(a.codigo, &exito, &posicion, *contador, &costoaux);
    if (exito == 1){
        return 0; // ya existe, alta NO exitosa
    }
    if (*contador >= MAXALUMNOS){
        return 2; // lista llena, no se puede insertar
    }
    for (j = *contador; j > posicion; j--){
        LSO[j] = LSO[j - 1];
        *costo += 1;
    }
    LSO[posicion] = a;
    *contador += 1;
    //SUMAR 1 al asignar la tupla o no? (Esto arregla el medio)
    return 1; // alta EXITOSA
}

int baja(Alumno a, int *contador, float *costo, int flag){
    int exito = 0, posicion = 0, opcion = 0;
    float costoaux;
    localizar(a.codigo, &exito, &posicion, *contador, &costoaux);
    if (exito == 0){
        return 0; // no encontrado
    }
    else{
        if(flag == 1){
                if(!(0 == strcmpi(LSO[posicion].codigo, a.codigo) &&
                    0 == strcmpi(LSO[posicion].nombreapellido, a.nombreapellido) &&
                    0 == strcmpi(LSO[posicion].correo, a.correo) &&
                    LSO[posicion].nota == a.nota &&
                    0 == strcmpi(LSO[posicion].condicionFinal, a.condicionFinal))){
                    return exito = 0;
                }
        }
        if(flag==0){
            // Alumno encontrado
            printf("Alumno encontrado\n");
            separador;
            printf("Confirmacion Baja de:\n");
            printf("Codigo: %s\n", LSO[posicion].codigo);
            printf("Nombre completo: %s\n", LSO[posicion].nombreapellido);
            printf("Nota: %d\n", LSO[posicion].nota);
            printf("Correo: %s\n", LSO[posicion].correo);
            printf("Condicion final: %s\n", LSO[posicion].condicionFinal);
            separador;

            printf("Dar de Baja?\n");
            printf("1.Si\n2.No\n");
            scanf("%d",&opcion);
            fflush(stdin);
            while(opcion!=1 && opcion!=2){
                printf("Ingrese una opcion valida\n");
                scanf("%d",&opcion);
                fflush(stdin);
            }
            if(opcion==2)
                return 2;//baja cancelada
        }
    for (int j = posicion; j < *contador - 1; j++){
        LSO[j] = LSO[j + 1];
        *costo += 1;
        }
        *contador -= 1;
        return 1; // baja exitosa
        }
}

Alumno evocar(char codigo[], int contador,int *exito_aux, float *costo){
    int exito = 0, posicion = 0;
    Alumno aux;
    localizar(codigo, &exito, &posicion, contador, costo);
    if (exito == 1){ // encontrado
        *exito_aux = 1;
        return LSO[posicion];
    }
    else{
        strcpy(aux.codigo, "-1");
        strcpy(aux.nombreapellido, "");
        strcpy(aux.correo, "");
        strncpy(aux.condicionFinal, "NULL", sizeof(aux.condicionFinal) - 1);
        aux.condicionFinal[sizeof(aux.condicionFinal)-1] = '\0';
        aux.nota = 0;
        *exito_aux = 0;
        return aux;
    }
}

/*int modificarAlumno(char codigo[], int contador){
    int exito = 0, posicion = 0, opcion = 0;
    float costo;
    localizar(codigo, &exito, &posicion, contador, &costo);

    if (exito == 1){
        printf("Que dato desea modificar?\n");
        printf("1. Nombre y apellido\n2. Correo\n3. Nota\n4. Condicion Final\n");
        scanf("%d", &opcion);
        getchar();

        switch (opcion){
            case 1:
                printf("Ingrese el nuevo nombre y apellido: ");
                fgets(LSO[posicion].nombreapellido, sizeof(LSO[posicion].nombreapellido), stdin);
                LSO[posicion].nombreapellido[strcspn(LSO[posicion].nombreapellido, "\n")] = '\0';
                break;

            case 2:
                printf("Ingrese el nuevo correo: ");
                fgets(LSO[posicion].correo, sizeof(LSO[posicion].correo), stdin);
                LSO[posicion].correo[strcspn(LSO[posicion].correo, "\n")] = '\0';
                break;

            case 3: {
                int nuevaNota;
                do {
                    printf("Ingrese la nueva nota (1 a 10): ");
                    if (scanf("%d", &nuevaNota) != 1) {
                        printf("Entrada invalida.\n");
                        while (getchar() != '\n');
                        nuevaNota = 0;
                    }
                } while (nuevaNota < 1 || nuevaNota > 10);
                LSO[posicion].nota = nuevaNota;
                break;
            }

            case 4: {
                char nuevaCond[20];

                printf("Ingrese la nueva condicion final (Promociona / Regular / Libre / Ausente): ");
                fgets(nuevaCond, sizeof(nuevaCond), stdin);
                nuevaCond[strcspn(nuevaCond, "\n")] = '\0';

                pasarAMayusculas(nuevaCond);
                strncpy(LSO[posicion].condicionFinal, nuevaCond, sizeof(LSO[posicion].condicionFinal));
                LSO[posicion].condicionFinal[sizeof(LSO[posicion].condicionFinal) - 1] = '\0';
                break;
            }

            default:
                printf("Opcion invalida.\n");
                return 0;
        }
        return 1; // modificación exitosa
    }
    else{
        return 0; // alumno no encontrado
    }
}

int memorizacionprevia(int *contador){
    FILE *fp = fopen("Alumnos.txt", "r");
    Alumno aux;
    char buffer[100];
    float costo;

    if (fp == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 0;
    }

    while (!feof(fp) && *contador < MAXALUMNOS){

        // Leer código
        if (fgets(buffer, sizeof(buffer), fp) == NULL) break;
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(aux.codigo, buffer, sizeof(aux.codigo));
        aux.codigo[sizeof(aux.codigo) - 1] = '\0';
        pasarAMayusculas(aux.codigo);

        // Leer nombre y apellido
        if (fgets(buffer, sizeof(buffer), fp) == NULL) break;
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(aux.nombreapellido, buffer, sizeof(aux.nombreapellido));
        aux.nombreapellido[sizeof(aux.nombreapellido) - 1] = '\0';

        // Leer correo
        if (fgets(buffer, sizeof(buffer), fp) == NULL) break;
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(aux.correo, buffer, sizeof(aux.correo));
        aux.correo[sizeof(aux.correo) - 1] = '\0';

        // Leer nota
        if (fgets(buffer, sizeof(buffer), fp) == NULL) break;
        aux.nota = atoi(buffer);

        // Leer condicionFinal
        if (fgets(buffer, sizeof(buffer), fp) == NULL) break;
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(aux.condicionFinal, buffer, sizeof(aux.condicionFinal));
        aux.condicionFinal[sizeof(aux.condicionFinal) - 1] = '\0';
        pasarAMayusculas(aux.condicionFinal);

        // Alta
        if (!alta(aux, contador, &costo)) {
            printf("No se pudo cargar el alumno con código %s (duplicado o lista llena)\n", aux.codigo);
        }
        else *contador++;
    }

    fclose(fp);

    if (*contador == MAXALUMNOS){
        return 3; // lista llena
    }
    return 1; // carga exitosa
}*/

void mostrarLSO(int contador){
    int mostrados = 0;
    if (contador == 0){
        separador;
        printf("\nLSO VACÍA\n");
        separador;
        return;
    }
    printf("Alumnos cargados: %d\n", contador);
    for (int i = 0; i < contador; i++) {
        separador;
        printf("\nAlumno #%d\n", mostrados + 1);
        printf("Codigo: %s\n", LSO[i].codigo);
        printf("Nombre completo: %s\n", LSO[i].nombreapellido);
        printf("Nota: %d\n", LSO[i].nota);
        printf("Correo: %s\n", LSO[i].correo);


        if (strcmp(LSO[i].condicionFinal, "PROMOCIONA") == 0) {
            printf("Condicion final: Promociona\n");
        }
        else if (strcmp(LSO[i].condicionFinal, "REGULAR") == 0) {
            printf("Condicion final: Regular\n");
        }
        else if (strcmp(LSO[i].condicionFinal, "LIBRE") == 0) {
            printf("Condicion final: Libre\n");
        }
        else if (strcmp(LSO[i].condicionFinal, "AUSENTE") == 0) {
            printf("Condicion final: Ausente\n");
        }
        else {
            printf("Condicion final: Desconocida\n");
        }
        separador;
        mostrados++;

        // paginación de a 3
        if (mostrados % 3 == 0){
            printf("\nPresione cualquier tecla para continuar...\n");
            system("pause");
            borrador;
        }
    }
    if (mostrados % 3 != 0){

    }
}

int strcmp_insensitive(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (toupper((unsigned char)*s1) != toupper((unsigned char)*s2))
            return toupper((unsigned char)*s1) - toupper((unsigned char)*s2);
        s1++;
        s2++;
    }
    return toupper((unsigned char)*s1) - toupper((unsigned char)*s2);
}
#endif // LSO_H_INCLUDED
