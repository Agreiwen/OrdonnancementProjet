/* Projet Ordonancement : Machines dédiées */

#include <stdlib.h>
#include <stdio.h>

struct tache {
  int id;
  int pi;
  int ri;
  int ti;
  int famille;
};
typedef struct tache tache;

typedef struct element element;
struct element
{
  tache t;
  struct element *next;
};

typedef element* llist;
int sommeFinTache;
int nombreDeTache;

llist ajouterEnTete(llist liste, tache tache1){
  element* nouvelElement = malloc(sizeof(element));
  nouvelElement->t = tache1;
  nouvelElement->next = liste;
  return nouvelElement;
}

void afficherListeTaches(llist taches){
  element *tmp = taches;
  printf("Liste des taches :\n");
  while(tmp != NULL){
    printf("id : %i",tmp->t.id);
    printf("| pi : %i",tmp->t.pi);
    printf("| ri : %i",tmp->t.ri);
    printf("| ti : %i",tmp->t.ti);
    printf("| famille : %i\n",tmp->t.famille);
    tmp = tmp->next;
  }
}

void mutation(tache tab[]){
    int randy =  rand()%nombreDeTache;
    int randy2 =  rand()%nombreDeTache;
    while(randy == randy2){
        randy2 =  rand()%nombreDeTache;
    }
    tache tmp = tab[randy];
    tab[randy] = tab[randy2];
    tab[randy2] = tmp;
}

void croisement(tache tab1[], tache tab2[]){
    int tailleTab1 = sizeof(*tab1);
    int tailleTab2 = sizeof(*tab2);
    if(tailleTab1 != tailleTab2){
        printf("Les deux tableaux doivent etre de meme taille !\n");
        return EXIT_FAILURE;
    }
    else{
        int coupure = 3*tailleTab1/4;
        int i;
        for(i = coupure; i < tailleTab1; i++){
            tache tmp = tab1[i];
            tab1[i] = tab2[i];
            tab2[i] = tmp;
        }
    }
}

void afficherTabTache(tache tableau[]){
    int i;
    printf("\n");
    for(i = 0; i < 6; i++){
        tache t = tableau[i];
        printf("id : %i",t.id);
        printf("| pi : %i",t.pi);
        printf("| ri : %i",t.ri);
        printf("| ti : %i",t.ti);
        printf("| famille : %i\n",t.famille);
    }
}

int algoGenetique(int heuristique, llist taches, int nbIterations){
  return 20;

}

int algoBranchAndBound(int heuristique, llist taches){
  return 10;
}

int main(int argc, char **argv){

    /*int nbTache;
    printf("Saisissez le nombre de tache : ");
    scanf("%d", &nbTache);
    int pi, ri, ti, famille;
    int i;
    nombreDeTache = nbTache;
    tache tableau[nombreDeTache];
    for(i = 0; i < nombreDeTache; i++){
        printf("Definition de la tache %d : \n",i+1);
        printf("Pi : ");
        scanf("%d",&pi);
        printf("Ri : ");
        scanf("%d",&ri);
        printf("Ti : ");
        scanf("%d",&ti);
        printf("Famille : ");
        scanf("%d",&famille);
        tache tmp = { .id = i+1, .pi = pi, .ri = ri, .ti = ti, .famille = famille };
        tableau[i] = tmp;
    }
    printf("\n****************Affiche tab : ****************\n");
    afficherTabTache(tableau);

    printf("Mutation ");
    mutation(tableau);
    afficherTabTache(tableau);*/




    printf("\n****************Exemple pour croisement : ****************\n");
  /* llist ma_liste1 = NULL;
  element *ma_liste = NULL;
  struct element *ma_liste3 = NULL;
  */

  tache t1 = { .id = 1, .pi = 5, .ri = 5, .ti = 0, .famille = 7 };
  tache t2 = { .id = 2, .pi = 3, .ri = 0, .ti = 0, .famille = 1 };
  tache t3 = { .id = 3, .pi = 7, .ri = 2, .ti = 0, .famille = 5 };
  tache t4 = { .id = 4, .pi = 1, .ri = 0, .ti = 0, .famille = 4 };
  tache t5 = { .id = 5, .pi = 2, .ri = 3, .ti = 0, .famille = 3 };
  tache t6 = { .id = 6, .pi = 4, .ri = 0, .ti = 0, .famille = 6 };

  /* famille : 1 sur la machine 1 uniquement
               2 sur la 2
               3 sur la 3
               4 sur 1 et 2
               5 sur 2 et 3
               6 sur 1 et 3
               7 sur les 3
  */

  tache tab1[6] = {t1,t2,t3,t4,t5,t6};

  tache t7 = { .id = 10, .pi = 40, .ri = 50, .ti = 1, .famille = 70 };
  tache t8 = { .id = 20, .pi = 20, .ri = 0, .ti = 1, .famille = 10 };
  tache t9 = { .id = 30, .pi = 10, .ri = 20, .ti = 1, .famille = 50 };
  tache t10 = { .id = 40, .pi = 80, .ri = 0, .ti = 1, .famille = 40 };
  tache t11 = { .id = 50, .pi = 30, .ri = 30, .ti = 1, .famille = 30 };
  tache t12 = { .id = 60, .pi = 50, .ri = 0, .ti = 1, .famille = 60 };

  tache tab2[6] = {t7,t8,t9,t10,t11,t12};
  afficherTabTache(tab1);
  afficherTabTache(tab2);

  croisement(tab1,tab2);
  afficherTabTache(tab1);
  afficherTabTache(tab2);

  int algo = 1; // 1= genetique 2= b&b
  int heuristique = 1;
  int nbIterations = 50;


  /*int resultat = 0;
  switch(algo){
  case 1:
    resultat = algoGenetique(heuristique, taches, nbIterations);
    break;
  case 2:
    resultat = algoBranchAndBound(heuristique, taches);
    break;
  default:
    printf("l'algo n'exsite pas\n");
    break;
  }

 printf("RESULTAT de l'algorithme : %i\n",resultat);*/

  // 1. definir heuristique
  // choix de l'utilisateur (tapez 1 pour h1, 2 pour h2, etc.)
  //    --> un entier pour l'heuristique et un switch pour savoir quelle action réaliser dans l'algo

  // 2. appeler l'algo avec h en paramètre et la liste de taches
  //    --> une fonction par algo : int algoGenetique(int h,llist taches, int nbIterations) et
  //                                int algoBranchAndBound(int h, llist taches)
  //        qui renvoie une durée totale d'execution des taches





  /* Fonctionement interface terminal
     1. On demande le nombre de taches
     2. On demande les taches une par une
     3. On demande l'algo à appliquer
     4. On demande l'heuristique à utiliser
     5. Si c'est génétique : on demande le nombre d'itérations
     6. On lance l'algo
     7. On affiche le résultat
  */

  return 0;
}
