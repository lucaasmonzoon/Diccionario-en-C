#include <stdio.h>
#include <locale.h>
#include <string.h>

void carga (char espaniol[10000][21],char ingles[10000][21],int cont[10000],int *contp){

    /// var

    int cont2,c,f,i;
    char esp[21],ing[21];
    FILE*archi;

    /// inicio

    setlocale(LC_ALL,"");
    i = -1;
    archi=fopen("espaingl.dat","r");
    fscanf(archi,"%s\t%s\t%d",esp,ing,&cont2);
    while(!feof(archi)){
        *contp = *contp+1;
        i = i+1;
        strcpy(espaniol[i],esp);
        strcpy(ingles[i],ing);
        cont[i] = cont2;
        fscanf(archi,"%s\t%s\t%d",esp,ing,&cont2);

    }
    fclose(archi);
} ///fin

void ordenar(char espaniol[10000][21], char ingles[10000][21], int cont[10000],int contp){

    /// var
        int j,i,lugar,aux2;
        char aux[21],min[21];

    /// inicio
        for(i=0;i<=contp-1;i++){
            strcpy(min,espaniol[i]);
            lugar=i;
            for(j=i+1;j<=contp;j++){
            if(strcoll(espaniol[j],min)<0){
                strcpy(min,espaniol[j]);
                lugar=j;


            }
            }
            strcpy(espaniol[lugar],espaniol[i]);
            strcpy(espaniol[i],min);
            strcpy(aux,ingles[lugar]);
            strcpy(ingles[lugar],ingles[i]);
            strcpy(ingles[i],aux);
            aux2=cont[lugar];
            cont[lugar]=cont[i];
            cont[i]=aux2;
        }
}///fin

void agregar_palabra(char ingles[10000][21],char espaniol[10000][21],int cont[10000],int *contp, char *opc, char palabra[21], char traduc[21], FILE*archi){

    /// var

    int i;

    /// inicio

        if(*contp==10000){
            printf("El diccionario esta lleno");

        }
        else if (*opc=='1'){
            strcpy(ingles[*contp],palabra);
            strcpy(espaniol[*contp],traduc);
            (*contp)++;
        }
        else if(*opc=='2') {
                printf("AVER");
                strcpy(espaniol[*contp],palabra);
                strcpy(ingles[*contp],traduc);
                *contp = *contp+1;
        }
        ordenar(espaniol, ingles, cont, *contp);
        archi = fopen("espaingl.dat", "w");
        for (i=0; i<*contp; i++) {
            fprintf(archi, "%s\t %s\t %d\n", espaniol[i+1], ingles[i+1], cont[i+1]);
        }
        fclose(archi);
        printf("La palabra fue agregada con exito\n");
} ///fin

void tradu (char espaniol[10000][21],char ingles[10000][21],int cont[10000], char *opc, int *contp, char palabra[21]){

    ///var

    char traduc[21],A;
    int max, medio, min, cont2, c;

    /// inicio

    switch (*opc){
        case '1':
            cont2 = 0;
            while(cont2<*contp && strcoll(ingles[cont2],palabra)!=0){
                cont2=cont2+1;
            }
            if(strcoll(ingles[cont2],palabra) == 0){
                printf("\nLa traduccion de %s es %s\n\n", palabra, espaniol[cont2]);
                cont[cont2] = cont[cont2]+1;
            }
            else{
                printf("La palabra no se encuentra en el diccionario\n");
                printf("Presione A si desea agregarla al diccionario\n");
            }
        break;
        case '2':
            min = 0;
            max = *contp;
            medio = (min+max)/2;
            while(strcoll(espaniol[medio],palabra)!= 0 && min<=max){
                if((c = strcoll(palabra,espaniol[medio])) < 0){
                    max = medio-1;
                }
                else if(c>0){
                    min = medio+1;
                }

                medio = (min+max)/2;
            }
            if(strcoll(espaniol[medio],palabra) == 0){
                printf("\nLa traduccion de %s es %s\n\n", palabra, ingles[medio]);
                cont[medio] = cont[medio]+1;
            }
            else{
                printf("\nLa palabra no se encuentra en el diccionario\n");
                printf("\nPresione A si desea agregarla al diccionario\n");

            }
        break;
    }
} ///fin

void mas_buscada(char espaniol[10000][21], char ingles[10000][21], char *opc, int cont[10000],int *contp){

    /// var

    char palmax[10][21];
    int max[10]={0};
    int i,c,lugar,j;

    ///inicio

        switch(*opc){
            case '1':
                for(c=0;c<10;c++){
                    for(i=0;i<*contp;i++){
                    if(c==0){
                        for(i=0;i<*contp;i++){
                            if(cont[i]>max[c]){
                           max[c]=cont[i];
                           strcpy(palmax[c],espaniol[i]);
                    }
                    }
                    }

                    else if(cont[i]>max[c] && cont[i]<max[c-1]){
                           max[c]=cont[i];
                           strcpy(palmax[c],espaniol[i]);
                    }

                    }
                }
                printf("\nLas palabras mas buscadas son:\n");
                for(j=0;j<10;j++){
                    printf("\n%s\t consultadas %d veces\n",palmax[j],max[j]);
                }

            break;
            case '2':
                for(c=0;c<10;c++){
                    for(i=0;i<*contp;i++){
                    if(c==0){
                        for(i=0;i<*contp;i++){
                            if(cont[i]>max[c]){
                           max[c]=cont[i];
                           strcpy(palmax[c],ingles[i]);
                    }
                    }
                    }

                    else if(cont[i]>max[c] && cont[i]<max[c-1]){
                           max[c]=cont[i];
                           strcpy(palmax[c],ingles[i]);
                    }

                    }
                }
                printf("\nLas palabras mas buscadas son:\n");
                for(j=0;j<10;j++){
                    printf("\n%s\t consultadas %d veces\n",palmax[j],max[j]);
                }


            break;
        }
} ///fin

void menu1 (char espaniol[10000][21], char ingles[10000][21], int cont[10000], char *opc, int *contp, FILE *archi){

    ///var

    char opc2, palabra[21], traduc[21];

    ///inicio

        do {
            printf("\n\tT - Traducir al espanol\n");
            printf("\tA - Agregar una palabra\n");
            printf("\tM - Mas buscadas\n");
            printf("\tV - Volver\n\n");
            printf("\nIngrese una opcion: ");
            scanf(" %c", &opc2);
            while ((opc2!='T') && (opc2!='A') && (opc2!='M') && (opc2!='V')){
                printf("Error. Ingrese una opcion valida: ");
                scanf(" %c", &opc2);
            }
            switch (opc2) {
                case 'T':
                        printf("\nIngrese una palabra para traducir: ");
                        scanf("%s", palabra);
                        tradu(espaniol, ingles, cont, *&opc, *&contp, palabra);
                break;
                case 'A':
                        printf("Ingrese la palabra que desea agregar junto a su traduccion\n\n");
                        scanf("%s %s", palabra, traduc);
                        agregar_palabra(ingles, espaniol, cont, *&contp, *&opc, palabra, traduc, archi);
                break;
                case 'M':
                        mas_buscada(espaniol, ingles, *&opc, cont, contp);
                break;
            }
        } while (opc2!='V');
} ///fin

void menu2 (char espaniol[10000][21],char ingles[10000][21],int cont[10000], char *opc, int *contp, FILE *archi){

    ///var

    char opc2, palabra [21], traduc [21];

    ///inicio

        do {
            printf("\n\tT - Traducir al ingles\n");
            printf("\tA - Agregar una palabra\n");
            printf("\tM - Mas buscadas\n");
            printf("\tV - Volver\n\n");
            printf("\nIngrese una opcion: ");
            scanf(" %c", &opc2);
            while ((opc2!='T') && (opc2!='A') && (opc2!='M') && (opc2!='V')){
                printf("Error. Ingrese una opcion valida: ");
                scanf(" %c", &opc2);
            }
            switch (opc2) {
                case 'T':
                        printf("\nIngrese una palabra para traducir: ");
                        scanf("%s", palabra);
                        tradu(espaniol, ingles, cont, *&opc, *&contp, palabra);
                 break;
                case 'A':
                        printf("\nIngrese la palabra que desea agregar junto a su traduccion: ");
                        scanf("%s %s", palabra, traduc);
                        agregar_palabra(ingles, espaniol, cont, *&contp, *&opc, palabra, traduc, archi);
                break;
                case 'M':
                        mas_buscada(espaniol, ingles, *&opc, cont, contp);
                break;
            }
        } while(opc2!='V');
} ///fin

void menu (char *opc, char espaniol[10000][21],char ingles[10000][21],int cont[10000],int contp, FILE *archi){

    /// var

    /// inicio

        printf("\n\t1. Ingles a espanol\n");
        printf("\t2. Espanol a ingles\n");
        printf("\t0. Cerrar\n\n");
        printf("\nIngrese una opcion: ");
        scanf(" %c",opc);
        while ((*opc!= '1') && (*opc!='2') && (*opc!='0')){
            printf("Error. Ingrese una opcion valida: ");
            scanf(" %c", opc);
        }
        switch (*opc) {
            case '1':
                menu1(espaniol, ingles, cont, *&opc, &contp, archi);
            break;
            case '2':
                menu2(espaniol, ingles, cont, *&opc, &contp, archi);
            break;
        }
} /// fin


int main () {

    /// var

    char espaniol [10000][21], ingles [10000][21], opc;
    int contp, cont [10000];
    FILE *archi;

    ///inicio

        contp = 0;
        carga(espaniol, ingles, cont, &contp);
        do {
            menu(&opc, espaniol, ingles, cont, contp, archi);
        } while (opc!='0');
        printf("Usted ha salido del programa");
    return (0);
}
