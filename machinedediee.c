/* Projet */

#include <stdlib.h>
#include <stdio.h>

typedef struct element element;
struct element
{
  int val;
  struct element *next;
};

typedef element* llist;


struct tache {
  int pi;
  int ri;
  int ti;
  int machine;
  int famille;
};

typedef struct tache tache;



int main(int argc, char **argv){

  /* llist ma_liste1 = NULL;
  element *ma_liste = NULL;
  struct element *ma_liste3 = NULL;
  */

  tache t1 = { .pi = 5, .ri = 5, .ti = 0, .machine = 1, .famille = 7 };
  tache t2 = { .pi = 3, .ri = 0, .ti = 0, .machine = 3, .famille = 1 };
  tache t3 = { .pi = 7, .ri = 2, .ti = 0, .machine = 2, .famille = 5 };
  tache t4 = { .pi = 1, .ri = 0, .ti = 0, .machine = 2, .famille = 4 };
  tache t5 = { .pi = 2, .ri = 3, .ti = 0, .machine = 3, .famille = 3 };
  tache t6 = { .pi = 4, .ri = 0, .ti = 0, .machine = 1, .famille = 6 };

  // 1. definir heuristique 
  // choix de l'utilisateur (tapez 1 pour h1, 2 pour h2, etc.)
  //    --> un entier pour l'heuristique et un switch pour savoir quelle action réaliser dans l'algo
  
  // 2. appeler l'algo avec h en paramètre et la liste de taches 
  //    --> une fonction par algo : int algoGenetique(int h,llist taches) et int algoBranchAndBound(int h, llist tahces) 
  //        qui renvoie une durée totale d'execution des taches

  return 0;
}  
