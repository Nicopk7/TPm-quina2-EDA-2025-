#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#define separador printf("____________________________________________________________________________________________ \n")
#define borrador system("cls")
#define pausa system("pause")
#include <string.h>
#include <stdlib.h>
#include "Alumno.h"
#define MAX 130

typedef struct nodo
{
    Alumno arb;
    struct nodo *hi;
    struct nodo *hd;
} nodo;

typedef struct
{
    nodo *raiz;
    int Nodos;
} ABB;

void init_ABB(ABB *a)
{
    (*a).raiz=NULL;
    (*a).Nodos=0;
}

void borrar_arbol(nodo **x)
{
    if (*x!=NULL)
    {
        borrar_arbol(&(*x)->hi);
        borrar_arbol(&(*x)->hd);
        free(*x);
        (*x) = NULL;
    }
}

int LocalizarABB(ABB *a, const char *id, nodo **x, nodo **y, int *exito, float *costo)
{
    *x = a->raiz;
    *y = NULL;

    *costo = 0.0;
    while (*x != NULL && strcmp((*x)->arb.codigo, id) != 0)
    {
        *costo += 1.0;
        *y = *x;
        if (strcmp((*x)->arb.codigo, id) < 0)
            *x = (*x)->hd;
        else
            *x = (*x)->hi;
    }
    if (*x != NULL)
    {
        *costo += 1.0;
        *exito = 1;
        return 1; // Encontrado
    }
    else
    {
        *exito = 0;
        return 0; // No encontrado
    }
}



int AltaABB(ABB *a, Alumno l, int *exito, float *costo)
{
    nodo *x, *y;
    float c = 0;

    LocalizarABB(a, l.codigo, &x, &y, exito, &c);
    if (*exito == 1)
    {
        return 0; // Ya existe
    }

    x = (nodo*)malloc(sizeof(nodo));
    if (x == NULL) {
        *exito = -1;
        return -1; // Error de memoria
    }

    x->arb = l;
    x->hi = x->hd = NULL;

    if (a->Nodos == 0)
    {
        a->raiz = x;
        *costo = c + 0.5;
    }
    else
    {
        if (strcmp(l.codigo, y->arb.codigo) < 0)
        {
            y->hi = x;
            *costo = c + 0.5;
        }
        else
        {
            y->hd = x;
            *costo = c + 0.5;
        }
    }

    a->Nodos++;
    *exito = 1;
    return 1;
}


Alumno evocar_alumno_ABB(ABB *a, const char *id, int *exito, float *costo)
{
    nodo *x, *y;
    Alumno aux;
    float c = 0;

    LocalizarABB(a, id, &x, &y, exito, &c);

    if (*exito == 1 && x != NULL)
    {
        aux = x->arb;   // copia del Alumno encontrado
        *costo = c;
        *exito = 1;
        return aux;
    }
    else
    {
        *exito = 0;
        *costo = c;
        Alumno vacio;
        strcpy(vacio.codigo, "");
        strcpy(vacio.nombreapellido, "");
        strcpy(vacio.correo, "");
        vacio.nota = -1;
        strcpy(vacio.condicionFinal, "");
        return vacio;
    }
}


int muestra_abb(nodo *x)
{
    if (x == NULL) return 0;

    int i = 0, top = 0, capacidad = 10;
    nodo **pila = (nodo**) malloc(capacidad * sizeof(nodo*));
    if (!pila)
    {
        fprintf(stderr, "Error al reservar memoria.\n");
        return -1;
    }

    pila[top++] = x;

    while (top > 0)
    {
        nodo *aux = pila[--top];

        // Mostrar info del nodo actual
        printf("Alumno %d\n", i);
        printf("Codigo: %s\n", aux->arb.codigo);
        printf("Nombre y Apellido: %s\n", aux->arb.nombreapellido);
        printf("Correo: %s\n", aux->arb.correo);
        printf("Nota: %d\n", aux->arb.nota);
        printf("Condicion Final: %s\n", aux->arb.condicionFinal);

        // Mostrar codigos de los hijos si existen
        if (aux->hi != NULL)
            printf(" → Hijo izquierdo: %s\n", aux->hi->arb.codigo);
        if (aux->hd != NULL)
            printf(" → Hijo derecho: %s\n", aux->hd->arb.codigo);
        if (aux->hi == NULL && aux->hd == NULL)
            printf(" → Sin hijos.\n");

        printf("******************************************\n");

        i++;
        if(i % 5 == 0)
        {
            printf("Presione ENTER para la pagina siguiente...\n");
            getchar();
        }

        // Preorden: apilar primero derecho, luego izquierdo
        if (aux->hd)
        {
            if (top >= capacidad)
            {
                capacidad *= 2;
                pila = (nodo**) realloc(pila, capacidad * sizeof(nodo*));
                if (!pila)
                {
                    fprintf(stderr, "Error al redimensionar la pila.\n");
                    exit(1);
                }
            }
            pila[top++] = aux->hd;
        }

        if (aux->hi)
        {
            if (top >= capacidad)
            {
                capacidad *= 2;
                pila = (nodo**) realloc(pila, capacidad * sizeof(nodo*));
                if (!pila)
                {
                    fprintf(stderr, "Error al redimensionar la pila.\n");
                    exit(1);
                }
            }
            pila[top++] = aux->hi;
        }
    }

    system("pause");
    free(pila);
    return 1;
}

int bajaABB(ABB *a, Alumno aux, float *costo, int flag)
{
    nodo *x, *y, *u, *u1;
    int exito = 0;
    int confirmacion, reslocalizar;

    reslocalizar = LocalizarABB(a, aux.codigo, &x, &y, &exito, costo);
    if (reslocalizar == 0)
        return 0; // Alumno no encontrado

    // Verificación estricta de todos los campos (flag == 1)
    if (flag == 1)
    {
        if (!(strcmp(x->arb.codigo, aux.codigo) == 0 &&
              strcmp(x->arb.nombreapellido, aux.nombreapellido) == 0 &&
              strcmp(x->arb.correo, aux.correo) == 0 &&
              x->arb.nota == aux.nota &&
              strcmp(x->arb.condicionFinal, aux.condicionFinal) == 0))
        {
            return 0; // no coincide el alumno
        }
    }

    // Confirmación (flag == 0 → preguntar al usuario)
    if (flag == 0)
    {
        printf("\n--- ALUMNO ENCONTRADO ---\n");
        printf("Codigo: %s\n", x->arb.codigo);
        printf("Nombre y Apellido: %s\n", x->arb.nombreapellido);
        printf("Correo: %s\n", x->arb.correo);
        printf("Nota: %d\n", x->arb.nota);
        printf("Condicion Final: %s\n", x->arb.condicionFinal);
        printf("----------------------------\n");
        printf("\nDesea eliminar este alumno?\n");
        printf("1. SI\n");
        printf("2. NO\n");
        printf("Opcion: ");
        scanf("%d", &confirmacion);

        while (confirmacion != 1 && confirmacion != 2)
        {
            printf("Ingrese una opcion valida\n");
            scanf("%d", &confirmacion);
            fflush(stdin);
        }
        if (confirmacion == 2)
            return 2; // baja cancelada
    }

    // Reducir el contador de nodos
    a->Nodos--;

    // Caso 1: nodo hoja
    if (x->hi == NULL && x->hd == NULL)
    {
        if (x == a->raiz)
            a->raiz = NULL;
        else if (y->hd == x)
            y->hd = NULL;
        else
            y->hi = NULL;

        *costo += 0.5;
    }
    // Caso 2: solo hijo derecho
    else if (x->hi == NULL && x->hd != NULL)
    {
        if (x == a->raiz)
            a->raiz = x->hd;
        else if (y->hd == x)
            y->hd = x->hd;
        else
            y->hi = x->hd;

        *costo += 0.5;
    }
    // Caso 3: solo hijo izquierdo
    else if (x->hd == NULL && x->hi != NULL)
    {
        if (x == a->raiz)
            a->raiz = x->hi;
        else if (y->hd == x)
            y->hd = x->hi;
        else
            y->hi = x->hi;

        *costo += 0.5;
    }
    // Caso 4: dos hijos → reemplazo con el mayor de los menores
    else
    {
        u = x->hi;   // bajar al subárbol izquierdo
        u1 = x;

        while (u->hd != NULL) // buscar el mayor de los menores
        {
            u1 = u;
            u = u->hd;
        }

        // Copiar datos del reemplazante
        x->arb = u->arb;

        // Ajustar punteros
        if (u1 == x) // el reemplazante es hijo directo
            u1->hi = u->hi;
        else
            u1->hd = u->hi;

        free(u);
        *costo += 1.5;
        return 1;
    }

    free(x);
    return 1;
}

void modificar_abb(ABB *a, Alumno aux)
{
    nodo *x, *y;
    int exito;
    float costo;
    // Buscar el prestador por DNI (el único campo que no se modifica)
    LocalizarABB(a, aux.codigo, &x, &y, &exito, &costo);
    if (exito == 1 && x != NULL)
    {
        strcpy(x->arb.nombreapellido, aux.nombreapellido);
        strcpy(x->arb.correo, aux.correo);
        x->arb.nota = aux.nota;
        strcpy(x->arb.condicionFinal, aux.condicionFinal);
        printf("Alumno con codigo %s modificado exitosamente.\n", aux.codigo);
        system("pause");
    }
    else
    {
        printf("Alumno con codigo %s no encontrado. No se realizaron modificaciones.\n", aux.codigo);
        system("pause");
    }
}

int memorizacion_ABB(ABB *a, int *cont)
{
    int elemrepe = 0, resalta, flag,exito;
    float c=0;
    Alumno nuevo;
    flag = 0;

    FILE *fp = fopen("Alumno.txt", "r");
    if (fp == NULL)
    {
        printf("No se encontró el archivo\n");
        return 0;
    }

    while (!feof(fp) && flag != 1)
    {
        fscanf(fp, "%8[^\n]", nuevo.codigo);
        fgetc(fp);
        fscanf(fp, "%80[^\n]", nuevo.nombreapellido);
        fgetc(fp);
        fscanf(fp, "%23s", nuevo.correo);
        fgetc(fp);
        fscanf(fp, "%d", nuevo.nota);
        fgetc(fp);
        fscanf(fp, "%11s", nuevo.condicionFinal);
        fgetc(fp);
        resalta = AltaABB(a,nuevo,&exito,&c);
        if (resalta == 1)
        {
            (*cont)++;  // solo si se insertó correctamente
        }
        else if (resalta == 0)
        {
            elemrepe++;
        }
        else if (resalta == -1)
        {
            flag = 1;
            printf("La lista se llenó\n");
            break;
        }
    }

    fclose(fp);
    printf("Cantidad de Prestadores repetidos (No cargados en la lista): %d\n", elemrepe);
    system("pause");
    return 1;
}

#endif // ABB_H_INCLUDED
