/* Projet Ordonancement : Machines dédiées */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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
int nbIterations;

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


//fonction qui affecte les ti en fonction du tableau de tâches et qui retourne la somme des ci (pi+ti)
int sommeCi(tache tab[], int size){

	int i=0;

	tab[0].ti = tab[0].ri;
	for(i=1; i<size; i++){
		int finPrecedent =  tab[i-1].ti + tab[i-1].pi;
		if(tab[i].ri <= finPrecedent){
			tab[i].ti = finPrecedent;
		}else{
			tab[i].ti = tab[i].ri;
		}
	}

	int somme = 0;
	int j=0;
	for(j=0;j<size;j++){
		somme += tab[j].ti + tab[j].pi;
	}
	return somme;
}


//retourne le tableau de tâches avec une solution réalisable (ti affectés)
tache *realisable(tache tab[], int size){

	//pi = le temps
	//ri = date de debut min
	//ti = date de debut effective
	//famille = machines sur lesquelles s'execute la tâche

	//1. on trie par ri
	//2. on affecte les ti dans l'ordre

	//exemple avec 7 tâches
	//___---___________------------___________
	//---________------------______------_____
	//___--------______------______------_____

	// sort du tableau par ri
	int i = 0;
	int j = 0;
	tache tmp;
	for(i; i<size; i++){
		for(j=i+1; j<size; j++){
			if(tab[i].ri > tab[j].ri){
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
		}
	}

	//affectation des ti
	tab[0].ti = tab[0].ri;
	for(i=1; i<size; i++){
		int finPrecedent =  tab[i-1].ti + tab[i-1].pi;
		if(tab[i].ri <= finPrecedent){
			tab[i].ti = finPrecedent;
		}else{
			tab[i].ti = tab[i].ri;
		}
	}
	return tab;
}




// pour pouvoir générer deux solutions réalisables
// (on fait la meme chose (sort + affectation) sauf que l'on met la tâche avec le plus petit ri à la fin)
tache *realisable2(tache tab[], int size){

	// sort du tableau par ri
	int i = 0;
	int j = 0;
	tache tmp;
	for(i=0; i<size; i++){
		for(j=i+1; j<size; j++){
			if(tab[i].ri > tab[j].ri){
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
		}
	}

	//affectation des ti
	tab[1].ti = tab[1].ri;
	for(i=2; i<size; i++){
		int finPrecedent =  tab[i-1].ti + tab[i-1].pi;
		if(tab[i].ri <= finPrecedent){
			tab[i].ti = finPrecedent;
		}else{
			tab[i].ti = tab[i].ri;
		}
	}
	tab[0].ti = tab[size-1].ti + tab[size-1].pi;
	return tab;
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

void croisement(tache tab1[], tache tab2[], int tailleTab1, int tailleTab2){
  //  int tailleTab1 = sizeof(*tab1);
   // int tailleTab2 = sizeof(*tab2);
    if(tailleTab1 != tailleTab2){
        printf("Les deux tableaux doivent etre de meme taille !\n");
        return EXIT_FAILURE;
    }
    else{
        int coupure = 3*tailleTab1/4;
        int i;
        for(i = coupure-1; i < tailleTab1; i++){
            tache tmp = tab1[i];
            tab1[i] = tab2[i];
            tab2[i] = tmp;
        }
    }
}

void afficherTabTache(tache tableau[], int nombretache){
    int i;
    printf("\n");
  //  printf("Taille du tab : %d"+sizeof(tableau)/sizeof(tache));
    for(i = 0; i < nombretache; i++){
        tache t = tableau[i];
        printf("id : %i",t.id);
        printf("| pi : %i",t.pi);
        printf("| ri : %i",t.ri);
        printf("| ti : %i",t.ti);
        printf("| famille : %i\n",t.famille);
    }
}

int algoGenetique(int heuristique, tache tab[]){
  /* Heuristique 1 : croisement
                 2 : mutation
                 3 : aleatoire*/
  /*  switch(heuristique){
        int i;
    case 1:
        for(i = 0; i < nbIterations; i++){
            //croisement(tab);
        }
    case 2:
        for(i = 0; i < nbIterations; i++){
            mutation(tab);
        }
    case 3:
        srand(time(NULL));
        for(i = 0; i < nbIterations; i++){
            float r;
            r = round((float)(rand()) / (float) RAND_MAX);
            int res = (int)r;
            if(res == 1){
                croisement(tab);
            }
            else{
                mutation(tab);
            }
        }
    }*/
}

int algoBranchAndBound(int heuristique, llist taches){
  return 10;
}

int main(int argc, char **argv){

    int nbTache;
   /* printf("Saisissez le nombre de tache : ");
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

    int iteration;
    printf("Saisissez un nombre d'iteration : ");
    scanf("%d",&iteration);
    nbIterations = iteration;

    printf("\n****************Affiche tab : ****************\n");
    afficherTabTache(tableau, nombreDeTache);

    printf("Mutation");
    mutation(tableau);
    afficherTabTache(tableau, nombreDeTache);*/

    //algoGenetique(3,tableau);

    printf("\n****************Exemple pour croisement : ****************\n");
  /* llist ma_liste1 = NULL;
  element *ma_liste = NULL;
  struct element *ma_liste3 = NULL;

  famille : 1 sur la machine 1 uniquement
               2 sur la 2
               3 sur la 3
               4 sur 1 et 2
               5 sur 2 et 3
               6 sur 1 et 3
               7 sur les 3
  */

  tache t1 = { .id = 1, .pi = 5, .ri = 5, .ti = 0, .famille = 7 };
  tache t2 = { .id = 2, .pi = 3, .ri = 0, .ti = 0, .famille = 1 };
  tache t3 = { .id = 3, .pi = 7, .ri = 2, .ti = 0, .famille = 5 };
  tache t4 = { .id = 4, .pi = 1, .ri = 0, .ti = 0, .famille = 4 };
  tache t5 = { .id = 5, .pi = 2, .ri = 3, .ti = 0, .famille = 3 };
  tache t6 = { .id = 6, .pi = 4, .ri = 0, .ti = 0, .famille = 6 };
  tache t7 = { .id = 10, .pi = 40, .ri = 50, .ti = 1, .famille = 70 };
  tache t8 = { .id = 20, .pi = 20, .ri = 0, .ti = 1, .famille = 10 };
  tache t9 = { .id = 30, .pi = 10, .ri = 20, .ti = 1, .famille = 50 };
  tache t10 = { .id = 40, .pi = 80, .ri = 0, .ti = 1, .famille = 40 };
  tache t11 = { .id = 50, .pi = 30, .ri = 30, .ti = 1, .famille = 30 };
  tache t12 = { .id = 60, .pi = 50, .ri = 0, .ti = 1, .famille = 60 };

  tache tab1[6] = {t1,t2,t3,t4,t5,t6};
  tache tab2[6] = {t7,t8,t9,t10,t11,t12};

  afficherTabTache(tab1,6);
  afficherTabTache(tab2,6);

  croisement(tab1,tab2, 6 , 6);

  afficherTabTache(tab1,6);
  afficherTabTache(tab2,6);

  int algo = 1; // 1= genetique 2= b&b
  int heuristique = 1;


    printf("\n****************Exemple pour solution réalisable : ****************\n");

  tache *tab3 = realisable(tab2,6);
  afficherTabTache(tab3,6);

  int somme = sommeCi(tab3,6);
  printf("Somme des ci : %i\n", somme);

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
