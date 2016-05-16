/* Projet Ordonnancement : Machines dédiées - branch and bound */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <time.h>

struct tache {
  int id;
  int pi;
  int ri;
  int ti;
  int famille;
};
typedef struct tache tache;
typedef struct elementbnb elementbnb;
struct elementbnb
{
  tache t;
  int taille;
  struct elementbnb *next;
};

typedef elementbnb* llist;
struct noeud
{
    tache id;
    int BI;
    llist chemin;
    struct noeud *next;
};
typedef struct noeud noeud;
typedef noeud* listenoeud;


listenoeud ajouterTeteNoeud(listenoeud liste, noeud *tache1){
 // noeud* nouvelElement = malloc(sizeof(noeud));
  tache1->next = liste;
 // nouvelElement->next = liste;
  return tache1;
}


llist ajouterEnTete(llist liste, tache tache1){
  elementbnb* nouvelElement = malloc(sizeof(elementbnb));
  elementbnb *tmp = liste;
  if(tmp==NULL){
        nouvelElement->taille = 1;
  }else{
      nouvelElement->taille = (tmp->taille)+1;
  }
  nouvelElement->t = tache1;
  nouvelElement->next = liste;
  return nouvelElement;
}

llist ajouterQueue(llist liste, tache tache1){
    elementbnb* nouvelElement = malloc(sizeof(elementbnb));
    elementbnb *tmp = liste;
    if(liste == NULL){
        nouvelElement->taille = 1;
        nouvelElement->t = tache1;
        nouvelElement->next = liste;

    }else{
        while(liste != NULL){
            liste->taille = (liste->taille)+1;
            liste = liste->next;
        }
        nouvelElement->taille = (tmp->taille)+1;
        nouvelElement->t = tache1;
        liste = nouvelElement;

    }
    return tmp;
}

llist supprimerElement(llist liste, tache tache1){
    elementbnb* previous = malloc(sizeof(elementbnb));
    elementbnb* tmp = malloc(sizeof(elementbnb));

    if(liste != NULL){

        previous = liste;
        if(previous->t.id == tache1.id){
                liste = previous->next;
                free(previous);
                return liste;
        }
        tmp = previous->next;

        while(tmp != NULL){
            if(tmp->t.id == tache1.id){
                previous->next = tmp->next;
                free(tmp);
                return liste;
            }
            previous = tmp;
            tmp = tmp->next;


        }
        return liste;
    }else{
        return liste;
    }
}
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
llist soustractionListes(llist taches, llist chemin){
    elementbnb* res = taches;

    elementbnb* tmp1 = taches;
    elementbnb* tmp2 = chemin;
    while(tmp2 != NULL){
        while(tmp1 != NULL){
           // printf("id tmp1 : %i id tmp2 : %i\n",tmp1->t.id, tmp2->t.id);
            if(tmp1->t.id == tmp2->t.id){

                res = supprimerElement(res, tmp1->t);
            }
            tmp1 = tmp1->next;
        }
        tmp2 = tmp2->next;
    }

    return res;
}


void branchAndBound(int BI, int BS, llist listeTaches){

    listenoeud ListArbre;

    listenoeud Resultat;
    llist TachesRestantes;
    noeud* n0 = malloc(sizeof(noeud));
    tache t0;
    n0->id = t0;
    n0->BI = BI;
    n0->chemin = NULL;

    ListArbre = ajouterTeteNoeud(ListArbre, n0);

    elementbnb *tmp = listeTaches;
    while(tmp != NULL){

        TachesRestantes = ajouterEnTete(TachesRestantes, tmp->t);
        tmp = tmp->next;
    }



    while (ListArbre != NULL){
        if(ListArbre->chemin->taille != listeTaches->taille){

            noeud* tmp = ListArbre;
            if(TachesRestantes = NULL){
               TachesRestantes = soustractionListes(listeTaches, tmp->chemin);
            }
            ListArbre = ListArbre->next;
            elementbnb *temp = TachesRestantes;
            listenoeud ListeArbretmp;
            while(temp != NULL){
                noeud* nt;
                nt->id = temp->t;
                nt->BI = BI;
                nt->chemin = ajouterQueue(tmp->chemin,nt->id);

                ListeArbretmp = ajouterTeteNoeud(ListeArbretmp, nt);
                temp = temp->next;
            }
            noeud* tmpn = ListeArbretmp;
            while(tmpn != NULL){

                ListArbre = ajouterTeteNoeud(ListArbre, tmpn);
                tmpn = tmpn->next;

            }

        TachesRestantes = supprimerElement(TachesRestantes, ListArbre->id);

   }else{

    noeud *noeudtmp = ListArbre;
    int j = 0;
    while(noeudtmp != NULL){
        j++;
        noeudtmp = noeudtmp->next;

    }
    tache tableau[j];
    int i = 0;
    noeud *noeudtmp2 = ListArbre;
    while(noeudtmp2 != NULL){
        tableau[i] = noeudtmp2->id;
        noeudtmp2 = noeudtmp2->next;
    }
    int res = sommeCiFamilles(tableau, j);

    if(res < BS){
        BS = res;
        elementbnb* tmpel = ListArbre->chemin;
        while(tmpel != NULL){
            noeud *ntmp;
            ntmp->id = tmpel->t;
            ntmp->BI = BI;
            ntmp->chemin = NULL;
            Resultat = ajouterTeteNoeud(Resultat, ntmp);
            tmpel = tmpel->next;
        }
    }

    ListArbre = ListArbre->next;

   }

    }
    afficherListeTachesNoeud(Resultat);

}

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

/* Definition structure de tache */
/*typedef struct noeud noeud;
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
};*/

void afficherListeTaches(llist taches){
  elementbnb *tmp = taches;
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

void afficherListeTachesNoeud(listenoeud nodes){
  //element *tmp2 = malloc(sizeof(element));
  printf("Liste des taches :\n");
  noeud *tmp = nodes;
  while(tmp != NULL){
    printf("id : %i",tmp->id.id);
    printf("| pi : %i",tmp->id.pi);
    printf("| ri : %i",tmp->id.ri);
    printf("| ti : %i",tmp->id.ti);
    printf("| famille : %i\n",tmp->id.famille);
    tmp = tmp->next;
  }
}
int main(int argc, char **argv){
    printf("****** Projet d'ordonnancement ******\n\n");
/* POUR TEST */
    tache t1 = { .id = 1, .pi = 5, .ri = 0, .ti = 0, .famille = 7 };
    tache t2 = { .id = 2, .pi = 3, .ri = 2, .ti = 0, .famille = 1 };
    tache t3 = { .id = 3, .pi = 2, .ri = 5, .ti = 0, .famille = 5 };
    tache t4 = { .id = 4, .pi = 5, .ri = 6, .ti = 0, .famille = 2 };
    tache t5 = { .id = 5, .pi = 8, .ri = 3, .ti = 0, .famille = 3 };
    tache t6 = { .id = 6, .pi = 1, .ri = 1, .ti = 0, .famille = 6 };
    tache tableau[6] = {t1,t2,t3,t4,t5,t6};
    /* FIN TEST */
    int BI = 0;
    int BS = sommeCi(tableau,6);
    llist listesol = NULL;
    int i;
  //  for(i = 5; i>=0; i--){
        listesol = ajouterEnTete(listesol, tableau[5]);
        listesol = ajouterEnTete(listesol, tableau[4]);
        listesol = ajouterEnTete(listesol, tableau[3]);
        listesol = ajouterEnTete(listesol, tableau[2]);
        listesol = ajouterEnTete(listesol, tableau[1]);
        listesol = ajouterEnTete(listesol, tableau[0]);
  //  }
     printf("Tab1 \n");
    afficherListeTaches(listesol);
    listesol = ajouterQueue(listesol, t2);
    printf("\nTab2\n");
    afficherListeTaches(listesol);
  //  branchAndBound(BI, BS, listesol);
    return 0;
}
