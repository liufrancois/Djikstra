#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h> 

typedef struct chemin_t{
    char D[100];//depart
    char A[100];//arriver
    int num;//cout
}chemin;

typedef struct liste_t{
    chemin* L[1000];//liste chemin
    int nb_L;//nombre de chemins
    char* LS[1000];//liste sommets
    int nb_LS;//nb_sommets
    
}liste;

typedef struct l_t{
    chemin* L;//liste chemin
    int nb_L;//nombre de chemins
    int cout;//cout total
    struct l_t* prec;//precedant
}l;

void afficher(l* C,int premier){
    if(C->nb_L!=1){
        afficher(C->prec,1);
        printf("%s-",C->L->D);
    }
    else{
        printf("%s-",C->L->D);
    }
    if(premier==0){
        printf("%s ",C->L->A);
    }
}

int nb_ligne(){
    FILE* f = fopen("liste_chemin.txt","r");
    char ligne[999];
    int nb=0;
    while (fgets(ligne,999,f)!=NULL){
        nb++;
    }
    fclose(f);
    return nb;
}
liste* cree_liste(liste* LC){
    FILE* f = fopen("liste_chemin.txt","r");
    char depart[100];
    char arriver[100];
    int cout;
    int nb=nb_ligne();
    for (int i=0;i!=nb;i++){
        chemin* C=(chemin*)malloc(sizeof *C);
        fscanf(f, "%s %s %d", &depart, &arriver, &cout);
        strcpy(C->D,depart);
        strcpy(C->A,arriver);
        C->num=cout;
        LC->L[i]=C;
        LC->nb_L++;
    }
    fclose(f);
    return LC;
}

liste* nb_sommet(liste* LC){
    for(int i=0;i!=LC->nb_L;i++){//pour chaque chemin
        bool DE=false;
        bool AR=false;

        for(int k=0;k!=LC->nb_LS;k++){//pour le sommet depart
            if (strcmp(LC->LS[k],LC->L[i]->D)==0){
                DE=true;
            }
        }
        if (!DE){//si il n'y est pas
            LC->LS[LC->nb_LS]=LC->L[i]->D;
            LC->nb_LS++;
        }
        for(int k=0;k!=LC->nb_LS;k++){//pour le sommet arriver
            if (strcmp(LC->LS[k],LC->L[i]->A)==0){//verifier si il est deja
                AR=true;
            }
        }
        if (!AR){//si il n'y est pas
            LC->LS[LC->nb_LS]=LC->L[i]->A;
            LC->nb_LS++;
        }
    }
    return LC;
}

int est_dans(char* Liste[100],int nb, char elem[100]){
    for (int i=0;i!=nb;i++){
        if(strcmp(Liste[i],elem)==0){
            return 1;
        }
    }
    return 0;
}

l* Dijkstra(liste* LC, char DE[100], char AR[100]){
    l* l1[100];
    int nb_chemin=0;
    char* point_finis[LC->nb_LS];
    int nb_finis=0;
    for (int i=0;i!=LC->nb_L;i++){
        if (strcmp(LC->L[i]->D,DE)==0){
            l* l2=(l*)malloc(sizeof *l2);
            l2->L=LC->L[i];
            l2->nb_L=1;
            l2->cout=LC->L[i]->num;
            l1[nb_chemin]=l2;
            nb_chemin++;
        }
    }
    for (int j=0;j!=LC->nb_L;j++){
        int min=99999999;
        int indice=9999999;
        for (int i=0;i!=nb_chemin;i++){
            if (l1[i]->cout<min && l1[i]->cout!=-1 && !est_dans(point_finis, nb_finis, l1[i]->L->A)){
                min=l1[i]->cout;
                indice=i;
            }
        }
        /*
        for (int p=0;p!=nb_chemin;p++){
            afficher(l1[p],0);
            printf("=%d\n",l1[p]->cout);
        }
        printf("\n");
        */
        if (strcmp(l1[indice]->L->A,AR)==0){
            return l1[indice];
        }
        if(!est_dans(point_finis,nb_finis, l1[indice]->L->D)){
            point_finis[nb_finis]=l1[indice]->L->D;
            nb_finis++;
        }
        for (int k=0;k!=LC->nb_L;k++){
            if (strcmp(LC->L[k]->D, l1[indice]->L->A)==0 && !est_dans(point_finis,nb_finis,LC->L[k]->A)){
                l1[nb_chemin]=(l*)malloc(sizeof *l1[nb_chemin]);
                l1[nb_chemin]->nb_L=l1[indice]->nb_L+1;
                l1[nb_chemin]->prec=(l1[indice]);
                l1[nb_chemin]->L=LC->L[k];
                l1[nb_chemin]->cout=l1[indice]->cout;
                l1[nb_chemin]->cout+=LC->L[k]->num;
                nb_chemin++;
            }
        }
        l1[indice]->cout=-1;
    }
}

int main(void){
    liste* LC=(liste*)malloc(sizeof *LC);
    l* dj=(l*)malloc(sizeof *dj);
    LC=cree_liste(LC);
    LC=nb_sommet(LC);
    char d[100];
    char a[100];
    printf("les point possible sont:\n");
    for(int i=0;i!=LC->nb_LS;i++){
        printf("%s ",LC->LS[i]);
    }
    printf("\n");
    printf("choisisez un point de depart\n");
    scanf("%s",&d);
    printf("choisisez un point d'ariver\n");
    scanf("%s",&a);
    dj=Dijkstra(LC,d,a);
    printf("plus petit chemin entre %s et %s:\n",d,a);
    afficher(dj,0);
    printf("et coute: %d\n",dj->cout);
    return 0;
}