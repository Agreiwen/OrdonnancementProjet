/* Projet Ordonancement : Machines dédiées */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

/* Definition structure de tache */

struct tache {
  int id;
  int pi;
  int ri;
  int ti;
  int famille;
};
typedef struct tache tache;


/* Definition de la structure d'une liste chainee de taches pour le branch and bounds */

typedef struct element element;
struct element
{
  tache t;
  struct element *next;
};

typedef element* llist;

struct elementhisto
{
    int taille;
    tache *sol;
    struct elementhisto *nxt;
};
// Erreur : Soit tu créer une structure histo et tu l'utilise soit tu défini histo en tant que liste d'element mais pas les deux
//typedef struct histo histo;
typedef struct elementhisto elementhisto;
typedef elementhisto* histo;

int sommeFinTache = INT_MAX;
int nombreDeTache;
int nbIterations = 1000;

histo ajouterTete(histo taches, tache sol[]){
    //printf("j'ajoute un element : \n");
  elementhisto* nouvelElmt = malloc(sizeof(elementhisto));
  elementhisto *tmp = taches;
  nouvelElmt->sol = sol;
  nouvelElmt->nxt = taches;
  if(tmp==NULL){
        nouvelElmt->taille = 1;
        //printf("C'est le premier element de la liste donc ma taille est de %d \n",nouvelElmt->taille);
       // nouvelElmt->taille = 1;
  }else{
      nouvelElmt->taille = (tmp->taille)+1;
      //printf("C'est pas le premier element de la liste, la taille c'est %d + 1 = %d \n",tmp->taille,nouvelElmt->taille);

  }

  return nouvelElmt;
}


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

void afficherTailleListeTabs(histo taches){
  elementhisto *tmp = taches;
  printf("Liste des taches :\n");
  printf("Taille de la liste de tab : %d",tmp->taille);
  /*while(tmp != NULL){
    printf("id : %i",tmp->t.id);
    printf("| pi : %i",tmp->t.pi);
    printf("| ri : %i",tmp->t.ri);
    printf("| ti : %i",tmp->t.ti);
    printf("| famille : %i\n",tmp->t.famille);
    tmp = tmp->next;
  }*/
}
/* Definition d'une structure de liste de tableaux (solutions) pour avoir un historique des solutions */





/* Definition des méthodes equals sur les taches et les tableaux de taches pour remplir l'historique */

bool equalsTache(tache t1, tache t2){
	return (t1.id == t2.id);/* && (t1.pi == t2.pi) && (t1.ri == t2.ri) && (t1.ti = t2.ti) && (t1.famille == t2.famille))*/
}


bool equalsTab(tache tab1[], tache tab2[], int size){
	int i=0;
	for(i;i<size;i++){
		if(equalsTache(tab1[i], tab2[i])==false){
            return false;
		}
	}
	return true;
}




int max2(int a, int b){
    if(a <= b){
        return b;
    }
    else{
        return a;
    }
}

int max3(int a, int b, int c){
    return max2(max2(a,b),c);
}

int sommeCiFamilles(tache tab[], int size){

	int i=0;
	int tM1 = 0;
	int tM2 = 0;
	int tM3 = 0;
    int max = 0;
	//attribution des pi
	for(i=0; i<size; i++){
		//int finPrecedent =  tab[i-1].ti + tab[i-1].pi;

		switch(tab[i].famille){
			case 1 : //M1
				if(tab[i].ri <= tM1){
					tab[i].ti = tM1;
				}else{
					tab[i].ti = tab[i].ri;
				}
				tM1 = tab[i].ti + tab[i].pi;
				break;
			case 2 : //M2
				if(tab[i].ri <= tM2){
					tab[i].ti = tM2;
				}else{
					tab[i].ti = tab[i].ri;
				}
				tM2 = tab[i].ti + tab[i].pi;
				break;
			case 3 : //M3
				if(tab[i].ri <= tM3){
					tab[i].ti = tM3;
				}else{
					tab[i].ti = tab[i].ri;
				}
				tM3 = tab[i].ti + tab[i].pi;
				break;
			case 4: //M1 et M2
				if(tM1 <= tM2){
					if(tab[i].ri <= tM2){
						tab[i].ti = tM2;
					}else{
						tab[i].ti = tab[i].ri;
					}

				}else{
					if(tab[i].ri <= tM1){
						tab[i].ti = tM1;
					}else{
						tab[i].ti = tab[i].ri;
					}
				}
				tM1 = tab[i].ti +tab[i].pi;
				tM2 = tab[i].ti +tab[i].pi;
				break;
			case 5 : // M2 et M3
				if(tM2 <= tM3){
					if(tab[i].ri <= tM3){
						tab[i].ti = tM3;
					}else{
						tab[i].ti = tab[i].ri;
					}

				}else{
					if(tab[i].ri <= tM2){
						tab[i].ti = tM2;
					}else{
						tab[i].ti = tab[i].ri;
					}
				}
				tM2 = tab[i].ti +tab[i].pi;
				tM3 = tab[i].ti +tab[i].pi;
				break;
			case 6 : // M1 et M3
				if(tM1 <= tM3){
					if(tab[i].ri <= tM3){
						tab[i].ti = tM3;
					}else{
						tab[i].ti = tab[i].ri;
					}

				}else{
					if(tab[i].ri <= tM1){
						tab[i].ti = tM1;
					}else{
						tab[i].ti = tab[i].ri;
					}
				}
				tM1 = tab[i].ti +tab[i].pi;
				tM3 = tab[i].ti +tab[i].pi;
				break;
			case 7 : // M1 M2 et M3

                max = max3(tM1,tM2,tM3);
				if(tab[i].ri <= max){
					tab[i].ti = max;
				}else{
					tab[i].ti = tab[i].ri;
				}
				tM1 = tab[i].ti +tab[i].pi;
				tM2 = tab[i].ti +tab[i].pi;
				tM3 = tab[i].ti +tab[i].pi;
				break;
		}
	}

	//somme des ci
	int somme = 0;
	int j=0;
	for(j=0;j<size;j++){
		somme += tab[j].ti + tab[j].pi;
	}
	return somme;
}

tache* getTab(histo histo, int a){
    elementhisto *tab = histo;
    int i=0;
    while(tab!=NULL){
        if(i==a){
            return tab->sol;
        }
        tab=tab->nxt;
        i++;
    }
   printf("\ERREUR IMPOSSIBLE DE TROUVER UN TABLEAU A L'INDICE %i\n",a);
   return EXIT_FAILURE;
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






void mutation(tache tab[], int size){


    int randy =  rand()%size;
    int randy2 =  rand()%size;
    while(randy == randy2){
        randy2 =  rand()%size;
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

tache* algoGenetique(int heuristique, histo histo, int nbIterations){
    tache *tabFinal = malloc(6*sizeof(tache));

    tache *tab1;
    tache *tab2;
  /* Heuristique 1 : croisement
                 2 : mutation
                 3 : aleatoire*/
    //printf("HEURISTIQUE %i\n",heuristique);
   switch(heuristique){
        int i;
    case 1:
        for(i = 0; i < nbIterations; i++){
            //croisement(tab);
        }
        break;
    case 2:
        for(i = 0; i < nbIterations; i++){
            srand(time(NULL));
            int rnd = rand()%(histo->taille-1)+1;
            tache *tab = getTab(histo,rnd);
             int size = sizeof(tab)/sizeof(tab[0]);
            mutation(tab, size);
        }
        break;
    case 3:

        srand(time(NULL));
        int rnd1 = rand()%(histo->taille-1)+1;
        int rnd2 = rand()%(histo->taille-1)+1;
        tab1 = getTab(histo,rnd1);
        tab2 = getTab(histo,rnd2);
        for(i = 0; i < nbIterations; i++){

            float r;
            r = round((float)(rand()) / (float) RAND_MAX);
            int res = (int)r;

            if(res == 1){
                //int sizeT1 = sizeof(tab1)/sizeof(tab1[0]);
                //int sizeT2 = sizeof(tab2)/sizeof(tab2[0]);
                croisement(tab1,tab2,6,6);
                int somme1 = sommeCiFamilles(tab1,6);
                int somme2 = sommeCiFamilles(tab2,6);
                if(somme1 < sommeFinTache) {
                    sommeFinTache = somme1;
                    //printf("SOMME FIN TACHES%i\n",sommeFinTache);
                    memcpy(tabFinal,tab1,6*sizeof(tache));
                    //tabFinal = tab1;
                    //afficherTabTache(tabFinal,6);
                }
                if(somme2 < sommeFinTache){
                    sommeFinTache = somme2;
                    //printf("SOMME FIN TACHES%i\n",sommeFinTache);
                    memcpy(tabFinal,tab2,6*sizeof(tache));
                    //tabFinal = tab2;
                    //afficherTabTache(tabFinal,6);
                }
                histo = ajouterTete(histo,tab1);
                histo = ajouterTete(histo,tab2);
            }
            else{
                //int size = sizeof(tab1)/sizeof(tab1[0]);
                mutation(tab1, 6);
                int somme = sommeCiFamilles(tab1,6);
                if(somme < sommeFinTache){
                    sommeFinTache = somme;
                    //printf("SOMME FIN TACHES%i\n",sommeFinTache);
                     memcpy(tabFinal,tab1,6*sizeof(tache));
                    //tabFinal = tab1;
                    //afficherTabTache(tabFinal,6);
                }
                histo = ajouterTete(histo, tab1);
            }
        }
        break;
    }
   afficherTabTache(tabFinal,6);
   int s = sommeCiFamilles(tabFinal,6);
   //printf("FDP : %i\n",s);
   //printf("RESULTAT DE L'ALGORITHME %i\n",sommeFinTache);
   return 0;
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

  tache t1 = { .id = 1, .pi = 5, .ri = 0, .ti = 0, .famille = 7 };
  tache t2 = { .id = 2, .pi = 3, .ri = 2, .ti = 0, .famille = 1 };
  tache t3 = { .id = 3, .pi = 2, .ri = 5, .ti = 0, .famille = 5 };
  tache t4 = { .id = 4, .pi = 5, .ri = 6, .ti = 0, .famille = 2 };
  tache t5 = { .id = 5, .pi = 8, .ri = 3, .ti = 0, .famille = 3 };
  tache t6 = { .id = 6, .pi = 1, .ri = 1, .ti = 0, .famille = 6 };
  tache t7 = { .id = 10, .pi = 40, .ri = 50, .ti = 1, .famille = 1 };
  tache t8 = { .id = 20, .pi = 20, .ri = 0, .ti = 1, .famille = 1 };
  tache t9 = { .id = 30, .pi = 10, .ri = 20, .ti = 1, .famille = 5 };
  tache t10 = { .id = 40, .pi = 80, .ri = 0, .ti = 1, .famille = 4 };
  tache t11 = { .id = 50, .pi = 30, .ri = 30, .ti = 1, .famille = 3 };
  tache t12 = { .id = 60, .pi = 50, .ri = 0, .ti = 1, .famille = 6 };

  tache tab1[6] = {t1,t2,t3,t4,t5,t6};
  tache tab2[6] = {t7,t8,t9,t10,t11,t12};
  tache tab4[6] = {t2,t4,t5,t6,t1,t2};

 /* histo test = NULL;
  test = ajouterTete(test,tab1);
  test = ajouterTete(test,tab2);
*/

/*  afficherTabTache(tab1,6);
  afficherTabTache(tab2,6);

  croisement(tab1,tab2, 6 , 6);

  afficherTabTache(tab1,6);
  afficherTabTache(tab2,6);*/

  int algo = 1; // 1= genetique 2= b&b
  int heuristique = 3;

  /* Test genetique full croisement */

    histo listeSol = NULL;
    listeSol = ajouterTete(listeSol, tab1);
    listeSol = ajouterTete(listeSol, tab4);
    //listeSol = ajouterTete(listeSol, tab2);
    //listeSol = ajouterTete(listeSol, tab2);
    afficherTailleListeTabs(listeSol);
    tache tab1Aux[6];
    tache tab2Aux[6];
    int i;
   /* for(i = 0; i < 50; i++){
        printf("%d",listeSol->taille);
    }*/

    printf("\n****************Exemple pour solution realisable : ****************\n");

  tache *tab3 = realisable(tab2,6);
  afficherTabTache(tab3,6);


  int sommeSansFamille = sommeCi(tab3,6);
  int somme = sommeCiFamilles(tab3,6);
  printf("\nSomme des ci sans familles (1 machine) : %i\n",sommeSansFamille);
  printf("Somme des ci avec familles (3 machines): %i\n\n", somme);

  llist taches = NULL;
  taches = ajouterEnTete(taches, t1);
  taches = ajouterEnTete(taches, t2);
  taches = ajouterEnTete(taches, t3);
  taches = ajouterEnTete(taches, t4);
  taches = ajouterEnTete(taches, t5);
  taches = ajouterEnTete(taches, t6);

  afficherListeTaches(taches);



    /* tests fonctions equals */
    bool testEqualsFalse = equalsTache(t1,t2);
    bool testEqualsTrue = equalsTache(t1,t1);


    int size = sizeof(tab1)/sizeof(tab1[0]); //taille du tableau
    bool testEqualsTabFalse = equalsTab(tab1,tab2,size);
    bool testEqualsTabTrue = equalsTab(tab1,tab1,size);

    printf("t1 == t2 ? %s\n", testEqualsFalse?"true":"false");
    printf("t1 == t1 ? %s\n", testEqualsTrue?"true":"false");
    printf("tab1 == tab2 ? %s\n", testEqualsTabFalse?"true":"false");
    printf("tab1 == tab1 ? %s\n", testEqualsTabTrue?"true":"false");

    printf("\n\nEXECUTION DE L'ALGORITHME\n\n");

  int resultat = 0;
  algo = 1;
  tache *finalTAB;
  switch(algo){
  case 1:
    resultat = algoGenetique(heuristique, listeSol, nbIterations);
    break;
  case 2:
    resultat = algoBranchAndBound(heuristique, taches);
    break;
  default:
    printf("l'algo n'exsite pas\n");
    break;
  }

printf("RESULTAT de l'algorithme : %i\n",sommeFinTache);
//afficherTabTache(finalTAB,6);
//int s = sommeCiFamilles(finalTAB,6);
//printf("%i\n",s);


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
