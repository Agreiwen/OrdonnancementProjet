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

    int randy =  rand()%(nombreDeTache-1) +1;
    int randy2 =  rand()%(nombreDeTache-1) +1;
    while(randy == randy2){
        randy2 =  rand()%(nombreDeTache-1) +1;
    }
    tache tmp = tab[randy];
    tab[randy] = tab[randy2];
    tab[randy2] = tmp;

}

int algoGenetique(int heuristique, llist taches, int nbIterations){
  return 20;

}


int algoBranchAndBound(int heuristique, llist taches){
  return 10;
}


int main(int argc, char **argv){

    int nbTache;
    printf("Saisissez le nombre de tache : ");
    scanf("%d", &nbTache);
    int pi, ri, ti, famille;
    int i;
    nombreDeTache = nbTache;
    tache tableau[nbTache];
    for(i = 0; i < nbTache; i++){
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
    for(i = 0; i < nbTache; i++){
        tache t = tableau[i];
        printf("id : %i",t.id);
        printf("| pi : %i",t.pi);
        printf("| ri : %i",t.ri);
        printf("| ti : %i",t.ti);
        printf("| famille : %i\n",t.famille);
    }

    printf("Mutation ");
    mutation(tableau);




    printf("\n****************Exemple Thibault : ****************\n");
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

  llist taches = NULL;
  taches = ajouterEnTete(taches, t1);
  taches = ajouterEnTete(taches, t2);
  taches = ajouterEnTete(taches, t3);
  taches = ajouterEnTete(taches, t4);
  taches = ajouterEnTete(taches, t5);
  taches = ajouterEnTete(taches, t6);

  afficherListeTaches(taches);

  int algo = 1; // 1= genetique 2= b&b
  int heuristique = 1;
  int nbIterations = 50;


  int resultat = 0;
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

 printf("RESULTAT de l'algorithme : %i\n",resultat);

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
