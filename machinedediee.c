/* Projet Ordonancement : Machines dédiées */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

/* Definition structure de tache */
typedef struct noeud noeud;
typedef struct listnoeud listnoeud;

struct noeud
{
    int val;
    listnoeud *enfants;
};

struct listnoeud
{
    noeud *node;
    listnoeud *next;
};


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

/* Definition de la structure d'une liste de tableau solution, pour l'algo genetique */

struct elementhisto
{
    int taille;
    tache *sol;
    struct elementhisto *nxt;
};

typedef struct elementhisto elementhisto;
typedef elementhisto* histo;

/* Les variables globales */

int sommeFinTache = INT_MAX;
int nombreDeTache = 6;
int nbIterations = 1000;

/* Les methodes pour ajouter des elements dans les structures */

histo ajouterTete(histo taches, tache sol[]){
  elementhisto* nouvelElmt = malloc(sizeof(elementhisto));
  elementhisto *tmp = taches;
  nouvelElmt->sol = sol;
  nouvelElmt->nxt = taches;
  if(tmp==NULL){
        nouvelElmt->taille = 1;
  }else{
      nouvelElmt->taille = (tmp->taille)+1;
  }
  return nouvelElmt;
}

llist ajouterEnTete(llist liste, tache tache1){
  element* nouvelElement = malloc(sizeof(element));
  nouvelElement->t = tache1;
  nouvelElement->next = liste;
  return nouvelElement;
}

/* Methode qui permet d'acceder à un element de l'historique (une solution) */

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

/* Methode pour afficher la liste des taches */

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

/* Methode qui permet d'afficher les taches d'une solution */

void afficherTabTache(tache tableau[], int nombretache){
    int i;
    printf("\n");
    for(i = 0; i < nombretache; i++){
        tache t = tableau[i];
        printf("id : %i",t.id);
        printf("| pi : %i",t.pi);
        printf("| ri : %i",t.ri);
        printf("| ti : %i",t.ti);
        printf("| famille : %i\n",t.famille);
    }
}

/* Methode pour afficher la taille de la liste des solutions */

void afficherTailleListeTabs(histo taches){
  elementhisto *tmp = taches;
  printf("Taille de la liste de tab : %d",tmp->taille);
}

/* Definition des méthodes equals sur les taches et les tableaux de taches pour remplir l'historique sans doublon */

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

/* Methode qui donne le max pour organiser les taches correctement et obtenir le bon sommeCi */

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

/* Methode qui gere l'ordonnancement des taches pour minimiser Ci et qui retourne Ci dans le cas de 3 machines */

int sommeCiFamilles(tache tab[], int size){
	int i=0;
	int tM1 = 0;
	int tM2 = 0;
	int tM3 = 0;
    int max = 0;
	//attribution des pi
	for(i=0; i<size; i++){
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

/* Methode qui gere l'ordonnancement des taches pour minimiser Ci et qui retourne Ci dans le cas d'une seule machine */

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

/* Methode qui permet d'inverser un tableau de tache pour generer une deuxieme solution et lancer l'algo */

void inverseTableau(tache tableau[], int tailleTableau)
{
    int i = 0;
    tache tmp;
    for (i = 0 ; i < tailleTableau/2 ; i++)
    {
        tmp = tableau[i];
        tableau[i] = tableau[tailleTableau - i - 1];
        tableau[tailleTableau - i - 1] = tmp;
    }
}

/* Methode qui permet de realiser une mutation entre deux solutions */

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

/* Methode qui permet de realiser un croisement entre deux solutions */

void croisement(tache **tab1, tache **tab2, int tailleTab1, int tailleTab2){
    if(tailleTab1 != tailleTab2){
        printf("Les deux tableaux doivent etre de meme taille !\n");
        return EXIT_FAILURE;
    }
    else{
        int coupure = 3*tailleTab1/4;
        int i;
        for(i = coupure-1; i < tailleTab1; i++){
            tache *tmp = tab1[i];
            tab1[i] = tab2[i];
            tab2[i] = tmp;
        }
    }
}

/* Methode qui permet de lancer l'algorithme genetique */

void algoGenetique(int heuristique, histo histo, int nbIterations){
    tache *tabFinal = malloc(nombreDeTache*sizeof(tache));
    tache *tab1;
    tache *tab2;
    tache *tab;
    /* Heuristique 1 : croisement
                   2 : mutation
                   3 : aleatoire*/
    switch(heuristique){
        int i;
    case 1:
        srand(time(NULL));
        for(i = 0; i < nbIterations; i++){
            int rnd1 = rand()%(histo->taille-1)+1;
            int rnd2 = rand()%(histo->taille-1)+1;
            tab1 = getTab(histo,rnd1);
            tab2 = getTab(histo,rnd2);
            croisement(&tab1,&tab2,nombreDeTache,nombreDeTache);
            int somme1 = sommeCiFamilles(tab1,nombreDeTache);
            int somme2 = sommeCiFamilles(tab2,nombreDeTache);
            if(somme1 < sommeFinTache) {
                sommeFinTache = somme1;
                memcpy(tabFinal,tab1,nombreDeTache*sizeof(tache));
            }
            if(somme2 < sommeFinTache){
                sommeFinTache = somme2;
                memcpy(tabFinal,tab2,nombreDeTache*sizeof(tache));
            }
            histo = ajouterTete(histo,tab1);
            histo = ajouterTete(histo,tab2);
        }
        break;
    case 2:
        srand(time(NULL));
        for(i = 0; i < nbIterations; i++){
            int rnd = rand()%(histo->taille);
            tab = getTab(histo,rnd);
            mutation(tab, nombreDeTache);
            int somme = sommeCiFamilles(tab,nombreDeTache);
            if(somme < sommeFinTache){
                sommeFinTache = somme;
                memcpy(tabFinal,tab,nombreDeTache*sizeof(tache));
            }
            histo = ajouterTete(histo, tab);
        }
        break;
    case 3:
        srand(time(NULL));
        for(i = 0; i < nbIterations; i++){
            int rnd1 = rand()%(histo->taille-1)+1;
            int rnd2 = rand()%(histo->taille-1)+1;
            tab1 = getTab(histo,rnd1);
            tab2 = getTab(histo,rnd2);
            //printf("iteration %i\n",rnd1);
            float r;
            r = round((float)(rand()) / (float) RAND_MAX);
            int res = (int)r;
            if(res == 1){
                croisement(&tab1,&tab2,nombreDeTache,nombreDeTache);
                int somme1 = sommeCiFamilles(tab1,nombreDeTache);
                int somme2 = sommeCiFamilles(tab2,nombreDeTache);
                if(somme1 < sommeFinTache) {
                    sommeFinTache = somme1;
                    memcpy(tabFinal,tab1,nombreDeTache*sizeof(tache));

                }
                if(somme2 < sommeFinTache){
                    sommeFinTache = somme2;
                    memcpy(tabFinal,tab2,nombreDeTache*sizeof(tache));

                }
               histo = ajouterTete(histo,tab1);
               histo = ajouterTete(histo,tab2);
            }
            else{
                mutation(tab1,nombreDeTache);
                int somme = sommeCiFamilles(tab1,nombreDeTache);
                if(somme < sommeFinTache){
                    sommeFinTache = somme;
                     memcpy(tabFinal,tab1,nombreDeTache*sizeof(tache));

                }
                histo = ajouterTete(histo, tab1);
            }
        }
        break;
    }
    afficherTabTache(tabFinal,nombreDeTache);
    int s = sommeCiFamilles(tabFinal,nombreDeTache);
}

int algoBranchAndBound(int heuristique, llist taches){
    return 10;
}

int main(int argc, char **argv){
    printf("****** Projet d'ordonnancement ******\n\n");
    int algo = 1;
    int heuristique = 3;
    int i, pi, ri, ti, famille;
    printf("Saisissez le nombre de taches : >> ");
    scanf("%d", &nombreDeTache);
    tache tableau[nombreDeTache];
    for(i = 0; i < nombreDeTache; i++){
        printf("\nDefinition de la tache %d : \n",i+1);
        printf("Pi : >> ");
        scanf("%i",&pi);
        printf("Ri : >> ");
        scanf("%i",&ri);
        printf("Famille : >> ");
        scanf("%i",&famille);
        tache tmp = { .id = i+1, .pi = pi, .ri = ri, .ti = 0, .famille = famille };
        tableau[i] = tmp;
    }

    printf("\nChoisissez l'algorithme :\n1. Genetique\n2. Branch and bound\n>> ");
    scanf("%i",&algo);

    if(algo == 1){
        printf("\nChoisissez une heuristique\n1. Que des croisements\n2. Que des mutations\n3. Aleatoire\n>> ");
        scanf("%i",&heuristique);
    }
    else{
        printf("\nOn l'a pas encore codé, noob !");
        return 0;
    }

    /* POUR TEST */
    /*tache t1 = { .id = 1, .pi = 5, .ri = 0, .ti = 0, .famille = 7 };
    tache t2 = { .id = 2, .pi = 3, .ri = 2, .ti = 0, .famille = 1 };
    tache t3 = { .id = 3, .pi = 2, .ri = 5, .ti = 0, .famille = 5 };
    tache t4 = { .id = 4, .pi = 5, .ri = 6, .ti = 0, .famille = 2 };
    tache t5 = { .id = 5, .pi = 8, .ri = 3, .ti = 0, .famille = 3 };
    tache t6 = { .id = 6, .pi = 1, .ri = 1, .ti = 0, .famille = 6 };
    tache tableau[6] = {t1,t2,t3,t4,t5,t6};*/
    /* FIN TEST */

    printf("\nSaisissez un nombre d'iteration : >> ");
    scanf("%i",&nbIterations);

    afficherTabTache(tableau,nombreDeTache);
    tache *tab1 = malloc(nombreDeTache*sizeof(tache));
    memcpy(tab1,tableau,nombreDeTache*sizeof(tache));
    tache *tab2 = malloc(nombreDeTache*sizeof(tache));
    memcpy(tab2,tableau,nombreDeTache*sizeof(tache));
    inverseTableau(tab2,nombreDeTache);

    histo listeSol = NULL;
    listeSol = ajouterTete(listeSol, tab1);
    listeSol = ajouterTete(listeSol, tab2);

    switch(algo){
    case 1:
        algoGenetique(heuristique, listeSol, nbIterations);
        break;
    case 2:
        //algoBranchAndBound(heuristique, taches);
        break;
    default:
        printf("l'algo n'exsite pas\n");
        break;
    }
    printf("RESULTAT de l'algorithme : %i\n",sommeFinTache);
    return 0;
}
