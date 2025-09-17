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

typedef struct{
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
}Costos;

void init_costos(Costos *x){
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

void menu_admin_est(){
    printf("1.Ingresar alumno\n");
    printf("2.Eliminar alumno\n");
    printf("3.Modificar alumno\n");
    printf("4.Consultar alumno\n");
    printf("5.Memorizacion Previa\n");//posible cambio de cartel por "Cargar Estructura"
    printf("6.Mostrar Estructura\n");
    printf("7.Volver\n");
    printf("Elija una opcion:\n");
}

int main(){
    char codigoAbuscar[8];
    int exitoLI = 0, opcion, opcion2, opcion3, resultalta, exito_aux, red, contadorLI = 0, contadorLSO = 0, contadorABB = 0, exitoABB, costo;
    int modo;
    float costoaux = 0;
    Costos c_lvo;
    Costos c_libb;
    Costos c_abb;
    init_costos(&c_lvo);
    init_costos(&c_libb);
    init_costos(&c_abb);
    Alumno nuevo, aux;
    Alumno *evocativo;
    ABB arbol;
    init_ABB(&arbol);
    inicializarLI();
    do{
        printf("******* Menu Principal ******\n");
        printf("1.Administracion de Estructuras\n");
        printf("2. Comparar Estructurar\n");
        printf("3. Salir\n");
        separador;
        printf("Elija una opcion:\n");
        fflush(stdin);
        scanf("%d", &opcion);
        switch (opcion){
            case 1:{
                do{
                    modo=0;
                    borrador;
                    separador;
                    printf("\tElija la Estructura a administrar\n");
                    printf("1.Lista Secuencial Ordenada\n");
                    printf("2.Lista Invertida con Busqueda Binaria (triseccion)\n");
                    printf("3.Arbol Binario de Busqueda\n");
                    printf("4.Volver\n");
                    separador;
                    fflush(stdin);
                    scanf("%d", &opcion2);
                    borrador;
                    switch (opcion2){
                        case 1:{
                            do{
                                borrador;
                                separador;
                                opcion3=0;
                                printf("\tLista Secuencial Ordenada\n");
                                menu_admin_est();
                                separador;
                                fflush(stdin);
                                scanf("%d", &opcion3);
                                borrador;
                                switch(opcion3){
                                    case 1:{
                                        borrador;
                                        printf("CODIGO: ");
                                        red = scanf("%[^\n]s", nuevo.codigo);
                                        fflush(stdin);
                                        while (red !=1 ){
                                            printf("Ingrese una opción valida\n");
                                            red = scanf("%[^\n]s", nuevo.codigo);
                                            fflush(stdin);
                                        }
                                        printf("Nombre y Apellido: ");
                                        //getchar();
                                        scanf("%[^\n]", nuevo.nombreapellido);
                                        printf("Correo: ");
                                        scanf("%s", nuevo.correo);
                                        printf("Nota: ");
                                        scanf("%d", nuevo.nota);
                                        printf("Condicion Final: ");
                                        scanf("%s", nuevo.condicionFinal);
                                        getchar();
                                        fflush(stdin);
                                        resultalta=alta(nuevo,contadorLSO, &costoaux);
                                        if(resultalta==2){
                                            printf("Alta fallida. No hay mas espacio\n");
                                        }
                                        if(resultalta==0){
                                            printf("Alta fallida. Elemento con codigo repetido\n");
                                        }
                                        if(resultalta==1){
                                            printf("Alta exitosa!!\n");
                                            contadorLSO++;
                                        }
                                        pausa;
                                        system("cls");
                                        break;
                                    }//alta LSO

                                    case 2:{
                                        borrador;
                                        printf("CODIGO: ");
                                        red = scanf("%[^\n]s", nuevo.codigo);
                                        fflush(stdin);
                                        while (red !=1 ){
                                            printf("Ingrese una opción valida\n");
                                            red = scanf("%[^\n]s", nuevo.codigo);
                                            fflush(stdin);
                                        }
                                        printf("Nombre y Apellido: ");
                                        //getchar();
                                        scanf("%[^\n]", nuevo.nombreapellido);
                                        printf("Correo: ");
                                        scanf("%s", nuevo.correo);
                                        printf("Nota: ");
                                        scanf("%d", nuevo.nota);
                                        printf("Condicion Final: ");
                                        scanf("%s", nuevo.condicionFinal);
                                        getchar();
                                        fflush(stdin);
                                        int resbaja = baja(nuevo, contadorLSO, &costoaux, modo);
                                        if(resbaja)
                                            printf("Baja Exitosa\n");
                                            contadorLSO--;
                                        if(resbaja==0)
                                            printf("Baja Fallida\n");
                                        if(resbaja==2)
                                            printf("Baja Cancelada\n");
                                        pausa;
                                        break;
                                    }//baja LSO

                                    case 3:{
                                        borrador;
                                        printf("Ingrese el CODIGO: ");
                                        red = scanf("%[^\n]s", nuevo.codigo);
                                        fflush(stdin);
                                        while (red!=1){
                                            printf("Ingrese una opción valida\n");
                                            red = scanf("%[^\n]s",nuevo.codigo);
                                            fflush(stdin);
                                        }
                                        int resmodi=modificarAlumno(nuevo.codigo, contadorLSO);
                                        if(resmodi==0)
                                            printf("El alumno no se encuentra en la lista\n");
                                        if(resmodi==1)
                                            printf("Modificacion Exitosa\n");
                                        pausa;
                                        break;
                                    }//modificar LSO

                                    case 4:{
                                        borrador;
                                        printf("Ingrese el CODIGO:\n");
                                        scanf("%[^\n]s", codigoAbuscar);
                                        aux=evocar(codigoAbuscar, contadorLSO, &exito_aux, &costoaux);
                                        if(exito_aux==1){
                                            printf("Codigo: %s \n", aux.codigo);
                                            printf("Nombre y Apellido: %s \n", aux.nombreapellido);
                                            printf("Correo electrónico: %s \n", aux.correo);
                                            printf("Nota: %d \n", aux.nota);
                                            printf("Condicion Final: %s \n", aux.condicionFinal);
                                        }
                                        if(exito_aux==0)
                                            printf("El prestador no se encuentra en la Lista\n");
                                        pausa;
                                        break;
                                    }//evocar LSO

                                    case 5:{
                                        memorizacionprevia(&contadorLSO);
                                        break;
                                    }//memorizacion previa LSO

                                    case 6:{
                                        mostrarLSO(contadorLSO);
                                        break;
                                    }// mostrar LSO

                                    case 7: break;

                                    default:{
                                        printf("\tIngrese una opcion valida\n");
                                        pausa;
                                        break;
                                    }
                                }//fin switch operaciones LSO
                            }while(opcion3!=7);//fin do admin LSO

                            break;
                        }//fin case menu LSO

                        //menu LIBT
                        case 2:{
                            do{
                                borrador;
                                separador;
                                opcion3=0;
                                printf("\tLista Invertida\n");
                                menu_admin_est();
                                separador;
                                fflush(stdin);
                                scanf("%d", &opcion3);
                                borrador;
                                switch(opcion3){
                                    case 1:{
                                        borrador;
                                        if(contadorLI == MAXALUMNOS){
                                            printf("No hay espacio suficiente para cargar un alumno\n");
                                        }
                                        else{
                                            printf("Ingrese los datos del alumno a cargar: \n");
                                            printf("CODIGO: ");
                                            red = scanf("%[^\n]s", nuevo.codigo);
                                            while (getchar() != '\n');
                                            while (red != 1) {
                                                printf("Ingrese una opción válida\n");
                                                red = scanf("%[^\n]s", nuevo.codigo);
                                                while (getchar() != '\n');
                                            }
                                            printf("Nombre y Apellido: ");
                                            fgets(nuevo.nombreapellido, sizeof(nuevo.nombreapellido), stdin);
                                            nuevo.nombreapellido[strcspn(nuevo.nombreapellido, "\n")] = '\0';
                                            printf("Correo: ");
                                            scanf("%s", nuevo.correo);
                                            while (getchar() != '\n');
                                            printf("Nota: ");
                                            scanf("%d", nuevo.nota);
                                            printf("Condicion Final: ");
                                            fgets(nuevo.condicionFinal, sizeof(nuevo.condicionFinal), stdin);
                                            nuevo.condicionFinal[strcspn(nuevo.condicionFinal, "\n")] = '\0';
                                            while (getchar() != '\n');
                                            int resultadoaltaLI = altaLI(nuevo, &contadorLI, &costoaux);
                                            switch (resultadoaltaLI){
                                                case 0:
                                                    printf("Alumno cargado con exito.\n");
                                                    break;
                                                case 1:
                                                    printf("Ya existe un alumno con CODIGO: %d\n", nuevo.codigo);
                                                    break;
                                                case 2:
                                                    printf("No se pudo cargar el alumno por error de memoria.\n");
                                                    break;
                                            }
                                            pausa;
                                            break;
                                        }
                                    }//alta LIBT

                                    case 2:{
                                        borrador;
                                        printf("Ingrese el codigo del alumno que desea eliminar: \n");
                                        scanf("%[^\n]s", nuevo.codigo);
                                        fflush(stdin);
                                        int resultadoBajaLI = BajaLI(nuevo, &contadorLI, &costoaux, modo);
                                        if (resultadoBajaLI == 1) printf("Baja exitosa\n");
                                        else if (resultadoBajaLI == 0) printf("Alumno no encontrado\n");
                                        pausa;
                                        break;
                                    }//baja LIBT

                                    case 3:{
                                        borrador;
                                        printf("Ingrese el nuevo nombre y apellido: ");
                                        fgets(aux.nombreapellido, 81, stdin);
                                        aux.nombreapellido[strcspn(aux.nombreapellido, "\n")] = '\0';
                                        printf("Ingrese el nuevo correo: ");
                                        scanf("%s", aux.correo);
                                        printf("Ingrese la nueva nota: ");
                                        scanf("%d", aux.nota);
                                        int resultadoModificarLI = modificarLI(aux, contadorLI);
                                        if (resultadoModificarLI == 1) printf("Modificacion exitosa\n");
                                        else printf("No se encontro al alumno\n");
                                        pausa;
                                        break;
                                    }//modificar LIBT

                                    case 4:{
                                        borrador;
                                        printf("Ingrese el CODIGO del alumno que desea evocar: ");
                                        scanf("%[^\n]s", codigoAbuscar);
                                        evocativo = evocarLI(codigoAbuscar, contadorLI, &exitoLI,  &costoaux);
                                        if (evocativo != NULL) {
                                            mostrarAlumno(*evocativo);
                                        }
                                        else{
                                            printf("Alumno no encontrado.\n");
                                        }
                                        pausa;
                                        break;
                                    }//evocar/mostrar LIBT

                                    case 5:{
                                        memorizacionPreviaLI(&contadorLI, &costoaux);
                                        break;
                                    }//memorizacion previa LIBT

                                    case 6:{
                                        mostrarListaInvertida(contadorLI);
                                        break;
                                    }// mostrar LIBT

                                    case 7: break;

                                    default:{
                                        printf("\tIngrese una opcion valida\n");
                                        pausa;
                                        break;
                                    }
                                }//fin switch operaciones LIBT
                            }while(opcion3!=7);//fin do admin LIBT

                            break;
                        }//fin case menu LIBT

                        case 3:{
                            do{
                                borrador;
                                separador;
                                opcion3=0;
                                printf("\tArbol Binario de Busqueda\n");
                                menu_admin_est();
                                separador;
                                fflush(stdin);
                                scanf("%d", &opcion3);
                                pausa;
                                switch(opcion3){
                                    case 1:{
                                        borrador;
                                            printf("Ingrese los datos del alumno a cargar: \n");
                                            printf("CODIGO: ");
                                            red = scanf("%[^\n]s", nuevo.codigo);
                                            while (getchar() != '\n');
                                            while (red != 1) {
                                                printf("Ingrese una opción valida\n");
                                                red = scanf("%[^\n]s", nuevo.codigo);
                                                while (getchar() != '\n');
                                            }
                                            printf("Nombre y Apellido: ");
                                            fgets(nuevo.nombreapellido, sizeof(nuevo.nombreapellido), stdin);
                                            nuevo.nombreapellido[strcspn(nuevo.nombreapellido, "\n")] = '\0';
                                            printf("Correo: ");
                                            scanf("%s", nuevo.correo);
                                            while (getchar() != '\n');
                                            printf("Nota: ");
                                            scanf("%d", nuevo.nota);
                                            printf("Condicion Final: ");
                                            scanf("%s", nuevo.condicionFinal);
                                            while (getchar() != '\n');
                                            int resultadoaltaABB = AltaABB(&arbol, nuevo, &exitoABB, &costo);
                                            if (resultadoaltaABB == 1) {
                                                printf("Alumno agregado con exito\n", costo);
                                                contadorABB++;
                                            } else if (resultadoaltaABB == 0) {
                                                printf("Ya existe un Alumno con ese codigo.\n");
                                            } else{
                                                printf("Error de memoria al insertar el alumno.\n");
                                            }
                                        pausa;
                                        break;
                                    }//alta ABB

                                    case 2:{
                                        borrador;
                                        printf("Ingrese el CODIGO: ");
                                        red = scanf("%[^\n]s", nuevo.codigo);
                                        fflush(stdin);
                                        while (red!=1){
                                            printf("Ingrese una opción valida\n");
                                            red = scanf("%[^\n]s",nuevo.codigo);
                                            fflush(stdin);
                                        }
                                        int resbaja=bajaABB(&arbol,nuevo,&costoaux,modo);
                                        if(resbaja==1)
                                            printf("Baja exitosa\n");
                                        if(resbaja==2)
                                            printf("Baja cancelada\n");
                                        if(resbaja==0)
                                            printf("Baja fallida. No se encontro al Alumno\n");

                                        pausa;
                                        break;
                                    }//baja ABB

                                    case 3:{
                                        borrador;
                                        printf("Ingrese el CODIGO del alumno que desea modificar: ");
                                        scanf("%[^\n]s", aux.codigo);
                                        getchar();
                                        printf("Ingrese el nuevo nombre y apellido: ");
                                        fgets(aux.nombreapellido, 81, stdin);
                                        aux.nombreapellido[strcspn(aux.nombreapellido, "\n")] = '\0';
                                        printf("Ingrese el nuevo correo: ");
                                        scanf("%s", aux.correo);
                                        printf("Ingrese la nueva nota: ");
                                        scanf("%d", aux.nota);
                                        printf("Ingrese la nueva condicion final: ");
                                        scanf("%s", aux.condicionFinal);
                                        modificar_abb(&arbol,aux);
                                        break;
                                    }//modificar ABB

                                    case 4:{
                                        borrador;
                                        printf("Ingrese CODIGO del alumno que desea mostrar: \n");
                                        scanf("%[^\n]s", codigoAbuscar);
                                        aux=evocar_alumno_ABB(&arbol,codigoAbuscar,&exito_aux,&costoaux);
                                        if(exito_aux)
                                            mostrarAlumno(aux);
                                        else
                                            printf("El alumno no se encuentra en la estructura\n");
                                        pausa;
                                    break;
                                    }//evocar/mostrar ABB

                                    case 5:{
                                        memorizacion_ABB(&arbol,&costo);
                                    break;
                                    }//memorizacion previa ABB

                                    case 6:{
                                        if(arbol.Nodos==0){
                                            printf("El arbol esta vacio\n");
                                            system("pause");}
                                        else
                                            muestra_abb(arbol.raiz);
                                        break;
                                    }// mostrar ABB

                                    case 7: break;

                                    default:{
                                        printf("\tIngrese una opcion valida\n");
                                        pausa;
                                        break;
                                    }

                                }//fin switch operaciones ABB
                            }while(opcion3!=7);//fin do admin ABB
                            break;
                        }//fin case menu ABB
                        case 4: break;
                        default:{
                                printf("\tIngrese una opcion valida\n");
                                pausa;
                                break;
                        }
                    }//fin switch menu admin
                }while (opcion2 != 4);//fin de menu admin
            break;}//fin case administracion estructura


            case 2:{
                modo=1;
                borrador;                                                     /// INICIO DE COMPARACION DE ESTRUCTURA
                FILE *fp;
                borrar_arbol(&arbol);
                liberarLista(&Lista);
                limpiarLI(&contadorLI);
                init_LVO(&Lista);
                init_ABB(&arbol);
                inicializarLI();
                if((fp = fopen("Operaciones-Prestadores.txt","r"))==NULL){
                    printf("\tNo se pudo abrir el archivo\n");
                }
                else{

                    while(!(feof(fp))){
                        fflush(stdin);
                        fscanf(fp,"%d\n",&operacion);
                        fscanf(fp,"%ld\n",&aux.dni);
                        switch(operacion){
                            case 1:{
                                fflush(stdin);
                                fscanf(fp, "%80[^\n]", aux.nombreapellido);
                                fgetc(fp);
                                fscanf(fp, "%120[^\n]", aux.servicios);
                                fgetc(fp);
                                fscanf(fp, "%120[^\n]", aux.domicilio);
                                fgetc(fp);
                                fscanf(fp, "%50s", aux.correo);
                                fgetc(fp);
                                fscanf(fp, "%s", aux.telefono);
                                costoaux=0;
                                resalta=altaLVO(&Lista,aux,&costoaux);
                                if(resalta){
                                    c_lvo.cant_altas++;
                                    c_lvo.medio_alta=c_lvo.medio_alta+costoaux;
                                    if (costoaux>c_lvo.maximo_alta)
                                        c_lvo.maximo_alta = costoaux;
                                }
                                costoaux=0;
                                resalta=AltaABB(&arbol,aux,&exito_aux,&costoaux);
                                if(resalta){
                                    c_abb.cant_altas++;
                                    c_abb.medio_alta=c_abb.medio_alta+costoaux;
                                    if (costoaux>c_abb.maximo_alta)
                                        c_abb.maximo_alta = costoaux;
                                }
                                costoaux=0;
                                if(contadorLI<MAX){
                                resalta=altaLI(aux,&contadorLI,&costoaux);
                                if(resalta==0){
                                    c_libb.cant_altas++;
                                    c_libb.medio_alta=c_libb.medio_alta+costoaux;
                                    if (costoaux>c_libb.maximo_alta)
                                        c_libb.maximo_alta = costoaux;
                                }}
                                break;
                            }//fin case 1 alta
                            case 2:{
                                fscanf(fp, "%80[^\n]", aux.nombreapellido);
                                fgetc(fp);
                                fscanf(fp, "%120[^\n]", aux.servicios);
                                fgetc(fp);
                                fscanf(fp, "%120[^\n]", aux.domicilio);
                                fgetc(fp);
                                fscanf(fp, "%50s", aux.correo);
                                fgetc(fp);
                                fscanf(fp, "%s", aux.telefono);
                                fgetc(fp);

                                costoaux=0;
                                if(Lista.tam>0){
                                resbaja=bajaLVO(&Lista,aux,&costoaux,modo);
                                if(resbaja){
                                    c_lvo.cant_bajas++;
                                    c_lvo.medio_baja=c_lvo.medio_baja+costoaux;
                                    if (costoaux>c_lvo.maximo_baja)
                                        c_lvo.maximo_baja = costoaux;
                                }}

                                costoaux=0;
                                if(arbol.Nodos>0){
                                resbaja=bajaABB(&arbol,aux,&costoaux,modo);
                                if(resbaja==1){
                                    c_abb.cant_bajas++;
                                    c_abb.medio_baja=c_abb.medio_baja+costoaux;
                                    if (costoaux>c_abb.maximo_baja){
                                        c_abb.maximo_baja = costoaux;
                                    }

                                }}

                                costoaux=0;
                                if(contadorLI>0){
                                resbaja= BajaLI(aux, &contadorLI, &costoaux, modo);
                                if(resbaja==1){
                                    c_libb.cant_bajas++;
                                    c_libb.medio_baja=c_libb.medio_baja+costoaux;
                                    if (costoaux>c_libb.maximo_baja){
                                        c_libb.maximo_baja = costoaux;
                                    }

                                }}

                                break;
                            }//fin case 2 baja
                            case 3:{
                                exito_aux = 0;
                                costoaux=0;
                                if(Lista.tam>0){
                                evocarLVO(Lista,aux.dni,&exito_aux,&costoaux);
                                if(exito_aux==1){
                                    c_lvo.cant_evos_succ = c_lvo.cant_evos_succ +1;
                                    c_lvo.med_evo_succ = c_lvo.med_evo_succ+costoaux;
                                    if (costoaux>c_lvo.max_evo_succ)
                                        c_lvo.max_evo_succ = costoaux;
                                    }
                                    if(exito_aux==0){
                                        c_lvo.cant_evos_fail = c_lvo.cant_evos_fail+1;
                                        c_lvo.med_evo_fail = c_lvo.med_evo_fail + costoaux;
                                        if (costoaux>c_lvo.max_evo_fail)
                                            c_lvo.max_evo_fail = costoaux;
                                    }
                                }
                                exito_aux = 0;
                                costoaux=0;
                                if(arbol.Nodos>0){
                                evocar_prestador_ABB(&arbol,aux.dni,&exito_aux,&costoaux);
                                if(exito_aux==1){
                                    c_abb.cant_evos_succ = c_abb.cant_evos_succ +1;
                                    c_abb.med_evo_succ = c_abb.med_evo_succ+costoaux;
                                    if (costoaux>c_abb.max_evo_succ)
                                        c_abb.max_evo_succ = costoaux;
                                    }else{
                                        c_abb.cant_evos_fail = c_abb.cant_evos_fail+1;
                                        c_abb.med_evo_fail = c_abb.med_evo_fail + costoaux;
                                        if (costoaux>c_abb.max_evo_fail)
                                            c_abb.max_evo_fail = costoaux;
                                    }
                                }

                                exito_aux = 0;
                                costoaux=0;
                                if(contadorLI>0){
                                evocarLI(aux.dni, contadorLI, &exito_aux, &costoaux);
                                if(exito_aux){
                                    c_libb.cant_evos_succ = c_libb.cant_evos_succ +1;
                                    c_libb.med_evo_succ = c_libb.med_evo_succ+costoaux;
                                    if (costoaux>c_libb.max_evo_succ)
                                        c_libb.max_evo_succ = costoaux;
                                    }else{
                                        c_libb.cant_evos_fail = c_libb.cant_evos_fail+1;
                                        c_libb.med_evo_fail = c_libb.med_evo_fail + costoaux;
                                        if (costoaux>c_libb.max_evo_fail)
                                            c_libb.max_evo_fail = costoaux;
                                    }
                                }
                            break;
                            }//fin case 3 evocacion

                        }//fin switch operaciones

                    }//fin while
                    fclose(fp);
                        printf("LVO: %d Prestadores\n",Lista.tam);
                        printf("LI: %d Prestadores\n",contadorLI);
                        printf("ABB: %d Prestadores\n",arbol.Nodos);
                        printf("\t COMPARACION DE ESTRUCTURAS\n\n");
                        printf("COSTOS\t\tLVO\tLIBB\tABB\n");
                        sep;
                        printf("MAX.ALTA\t%.2f\t%.2f\t%.2f\n",c_lvo.maximo_alta,c_libb.maximo_alta,c_abb.maximo_alta);
                        printf("MED.ALTA\t%.2f\t%.2f\t%.2f\n",c_lvo.medio_alta/c_lvo.cant_altas,c_libb.medio_alta/c_libb.cant_altas,c_abb.medio_alta/c_abb.cant_altas);
                        printf("MAX.BAJA\t%.2f\t%.2f\t%.2f\n",c_lvo.maximo_baja,c_libb.maximo_baja,c_abb.maximo_baja);
                        printf("MED.BAJA\t%.2f\t%.2f\t%.2f\n",c_lvo.medio_baja/c_lvo.cant_bajas,c_libb.medio_baja/c_libb.cant_bajas,c_abb.medio_baja/c_abb.cant_bajas);
                        printf("MAX.EVOEX\t%.2f\t%.2f\t%.2f\n",c_lvo.max_evo_succ,c_libb.max_evo_succ,c_abb.max_evo_succ);
                        printf("MED.EVOEX\t%.2f\t%.2f\t%.2f\n",c_lvo.med_evo_succ/c_lvo.cant_evos_succ,c_libb.med_evo_succ/c_libb.cant_evos_succ,c_abb.med_evo_succ/c_abb.cant_evos_succ);
                        printf("MAX.EVONOEX\t%.2f\t%.2f\t%.2f\n",c_lvo.max_evo_fail,c_libb.max_evo_fail,c_abb.max_evo_fail);
                        printf("MED.EVONOEX\t%.2f\t%.2f\t%.2f\n",c_lvo.med_evo_fail/c_lvo.cant_evos_fail,c_libb.med_evo_fail/c_libb.cant_evos_fail,c_abb.med_evo_fail/c_abb.cant_evos_fail);
                    }//fin else
                break;}//fin case comparacion estructura
            case 3:{
                printf("Saliendo...\n");
            break;}
            default:{
                    printf("\tIngrese una Opcion Valida\n\n");
                    pausa;
                    break;
            }
        }//fin switch menu


    }while (opcion!=3);//fin do menu principal
    return 0;
}
