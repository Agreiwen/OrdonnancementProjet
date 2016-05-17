/* Projet Ordonnancement : Machines d�di�es - branch and bound */

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
  noeud* nouvelElement = malloc(sizeof(noeud));
  nouvelElement->BI = tache1->BI;
  nouvelElement->id = tache1->id;
  nouvelElement->chemin = tache1->chemin;
  nouvelElement->next = liste;


 // nouvelElement->next = liste;
  return nouvelElement;
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

llist copie(llist liste){
    elementbnb* nouvelliste = malloc(sizeof(elementbnb));
    elementbnb* oldliste = liste;
    while(oldliste != NULL){


    }
}
llist ajouterQueue(llist liste, tache tache1){
    elementbnb* nouvelElement = malloc(sizeof(elementbnb));
    elementbnb* debut = liste;

    if(nouvelElement != NULL){
        nouvelElement->t = tache1;
        //nouvelElement->next = NULL;
        if(liste == NULL){
            //printf("Liste est nul");
            nouvelElement->taille = 1;
            nouvelElement->next = NULL;
            liste = nouvelElement;



        }else{
            elementbnb *tmp = liste;
          //  int i = tmp->taille;
         //   int i = 0;
            if(tmp->next == NULL){
                 //   printf("Je rentre la");
         //       ;
                tmp->taille = (tmp->taille)+1;
            }
            while(tmp->next != NULL){
                tmp->taille = (tmp->taille)+1;
              //  i = (tmp->taille)-1;
                // printf(" mon i %d : ",i);

                tmp = tmp->next;
            }

            nouvelElement->taille = 1;
            nouvelElement->next = NULL;
            tmp->next = nouvelElement;

        }
    }
    return debut;
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


void branchAndBound(int BI, int BS, llist listeTaches, int nbtaches){

    listenoeud ListArbre;

    listenoeud Resultat = NULL;
    llist tachesRestantes = NULL;
    noeud* n0 = malloc(sizeof(noeud));
    tache t0 = { .id = -1, .pi = 5, .ri = 0, .ti = 0, .famille = 7 };
    n0->id = t0;
    n0->BI = BI;
    elementbnb* ntmp = malloc(sizeof(elementbnb));
    ntmp->taille = 1;
    ntmp->t = t0;
  //  ntmp->chemin->taille = 0;
    n0->chemin = ntmp;
    n0->next = NULL;

    ListArbre = ajouterTeteNoeud(ListArbre, n0);
  //  printf("Liste de noeuds dans l'arbres \n");
  //  afficherListeNoeud(ListArbre);

    elementbnb* tachesRestantes2 = NULL;


    elementbnb *tmp = listeTaches;
    while(tmp != NULL){
        //printf("yo");
        tachesRestantes2 = ajouterEnTete(tachesRestantes2, tmp->t);
        tmp = tmp->next;
      //  printf("yo");
    }

    elementbnb *tmp2 = tachesRestantes2;
     while(tmp2 != NULL){
        //printf("yo");
        tachesRestantes = ajouterEnTete(tachesRestantes, tmp2->t);
        tmp2 = tmp2->next;
      //  printf("yo");
    }

   // printf("\nTaches Restantes \n");
    afficherListeTaches(tachesRestantes);

    int cmpt = 0;
    while (ListArbre != NULL){
            cmpt++;
        printf("\n<<<<<<<<<<<<<<<<<<Je rentre dans mon grand While<<<<<<<<<<<<<<<<<<<<<<<<< \n");

    /*    elementbnb* elemt = ListArbre->chemin;
        int i = 0;
        while (elemt != NULL){
            i++;
            elemt = elemt->next;
        }*/
    //    printf("%d",i);
      //  afficherListeNoeud(ListArbre);
     //   afficherListeTaches(ListArbre->chemin);
        printf("\nJe test si %d est different de %d \n",ListArbre->chemin->taille,(listeTaches->taille)+1);
        if(ListArbre->chemin->taille != (listeTaches->taille)+1){
            printf("Oui c'est different\n");
            noeud* tmp = ListArbre;
            printf("je definis un pointeur sur ma Listarbre tmp\n");
            printf("Contenu de tmp : \n");
            afficherListeNoeud(ListArbre);

            if(tachesRestantes == NULL){

               tachesRestantes = soustractionListes(listeTaches, tmp->chemin);
            }
            printf("\n je definis un pointeur sur mes tachesRestantes :\n");

            elementbnb *temp = tachesRestantes;
            afficherListeTaches(temp);

            printf("Je dis a ListAbre d'avance\n");
            ListArbre = ListArbre->next;
            afficherListeNoeud(ListArbre);

            printf("Je creer une listeArbretmp\n");
            listenoeud ListeArbretmp = NULL;
           // printf("taille de temp %d",temp->taille);
            printf("--------Je parcours mes taches dans temp : ---------\n\n");
            while(temp != NULL){
                printf("Tache courante %d \n",temp->t.id);

                printf("J'affiche le chemin contenu dans tmp : tmp->chemin \n");
               afficherListeTaches(tmp->chemin);

                noeud* nt = malloc(sizeof(noeud));
             //   printf("\n%d tache du noeud : ",temp->t.id);
                nt->id = temp->t;
                nt->BI = BI;
                elementbnb* tmp2 = malloc(sizeof(elementbnb));
                printf(" Adresse de tmp2 %a\n",&tmp2);
                tmp2 = copie(tmp->chemin);
             //   memmove(tmp2,tmp->chemin,(tmp->chemin->taille)*sizeof(elementbnb));
               // tmp->chemin = NULL;
                printf(" Adresse de tmp2 %a\n",&tmp2);
                printf("Je creer un noeud qui a pour chemin tmp->chemin + la tache %d\n",nt->id.id);
                nt->chemin = ajouterQueue(tmp2,nt->id);

                printf("Voici donc le chemin dans le noeud\n : ");
                afficherListeTaches(nt->chemin);

                printf("J'ajoute ce noeud dans ListeArbretmp\n");
                ListeArbretmp = ajouterTeteNoeud(ListeArbretmp, nt);

                printf("Je passe a la tache suivante\n");
                temp = temp->next;

            }
           // break;

            printf("\n-------Fin du parcours des taches---------\n");
            noeud* tmpn = malloc(sizeof(noeud));
            tmpn = ListeArbretmp;
            printf("Je remplit maintenant ListArbre avec les noeuds de ListeArbretmp\n");
            printf("Le contenu actuel de ma ListArbre est : \n");
            afficherListeNoeud(ListArbre);
            while(tmpn != NULL){
               printf("Noeud courant : %d\n",tmpn->id.id);


               // tmp3 = ListArbre;

                //printf("%i\n",tmp3->id.id);
               // printf("\nJe remplit ListArbre\n");
              //  afficherListeTaches(tmpn->chemin);
                ListArbre = ajouterTeteNoeud(ListArbre, tmpn);
                printf("Contenu de ma ListArbre apr�s ajout \n");
                afficherListeNoeud(ListArbre);
              //  printf("\nJ'ai ca dedans ListArbre\n");
              //  afficherListeTaches(ListArbre->chemin);
                tmpn = tmpn->next;
                printf("Je passe au noeud suivant \n");

            }
            printf("Fin du remplissage de ListAbre\n");
            printf("Contenu de ListArbre\n");
            afficherListeNoeud(ListArbre);
        //    printf(" taille du chemin %d \n: ",ListArbre->chemin->taille);

            //printf("je suis lahhhhhhhhhhhhhhhhhhhhhhh\n");
           // afficherListeTaches(ListArbre->chemin);
           printf("\nFin du grand While\n");
            if(cmpt==2)break;
            printf("Je retire le premier element de Taches restantes\n");

            tachesRestantes = supprimerElement(tachesRestantes, ListArbre->id);
            afficherListeTaches(tachesRestantes);

        }else{
           //  printf("je suis laaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
           break;
// break;
      //      afficherListeTaches(ListArbre->chemin);

            elementbnb* tachetmp = ListArbre->chemin;
            int j = 0;
            while(tachetmp != NULL){
                j++;
                tachetmp = tachetmp->next;

            }
        //    printf(" Mon j : %d",j);
            j--;
            tache tableau[j];
            int i = 0;
            elementbnb *tachetmp2 = ListArbre->chemin;
            tachetmp2 = tachetmp2->next;
            while(tachetmp2 != NULL){
                tableau[i] = tachetmp2->t;
                tachetmp2 = tachetmp2->next;
                i++;
            }
        //    printf("Tab fini %d ",i);
            //afficherTabTache(tableau,j);
          //  break;
            int res = sommeCiFamilles(tableau, j);
          //  afficherTabTache(tableau,j);
            printf(" Mon res %i",res);
            //break;
            if(res < BS){
                //    printf("Toyo");

                BS = res;
                //printf("%d",res);
                elementbnb* tmpel = ListArbre->chemin;
                tmpel = tmpel->next;

                while(tmpel != NULL){
                    noeud *ntmp = malloc(sizeof(noeud));
                    ntmp->id = tmpel->t;
                    ntmp->BI = BI;
                    ntmp->chemin = NULL;
                    Resultat = ajouterTeteNoeud(Resultat, ntmp);
                    tmpel = tmpel->next;
                }

            }

            ListArbre = ListArbre->next;

        }
      //  afficherListeTachesNoeud(Resultat);

    //ListArbre = ListArbre->next;
    }
    //afficherListeTachesNoeud(Resultat);

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
void afficherListeTaches(llist taches){
  elementbnb *tmp = taches;
  printf("Liste des taches :\n");
  while(tmp != NULL){
    printf("id : %i",tmp->t.id);
    printf("| pi : %i",tmp->t.pi);
    printf("| ri : %i",tmp->t.ri);
    printf("| ti : %i",tmp->t.ti);
    printf("| famille : %i",tmp->t.famille);
     printf("| TAILLE %i\n",tmp->taille);
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
void afficherListeNoeud(listenoeud nodes){
  //element *tmp2 = malloc(sizeof(element));
  printf("Liste des taches :\n");
  noeud *tmp = nodes;
  while(tmp != NULL){
    printf("id tache : %i",tmp->id.id);
    printf("| BI : %i\n",tmp->BI);
    //printf("| chemin : %i",tmp->chemin);
    //printf("| noeud : %i",tmp->next->id);

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
    tache tableau[3] = {t1,t2,t3};
    /* FIN TEST */
    int BI = 0;
    int BS = sommeCi(tableau,3);
    llist listesol = NULL;
    int i;
  //  for(i = 5; i>=0; i--){
       // listesol = ajouterEnTete(listesol, tableau[5]);
       // listesol = ajouterEnTete(listesol, tableau[4]);
      //  listesol = ajouterEnTete(listesol, tableau[3]);
        listesol = ajouterEnTete(listesol, tableau[2]);
        listesol = ajouterEnTete(listesol, tableau[1]);
        listesol = ajouterEnTete(listesol, tableau[0]);
  //  }
     printf("Tab1 \n");
    afficherListeTaches(listesol);
    //listesol = ajouterQueue(listesol, t2);
   // printf("\nTab2\n");
    //afficherListeTaches(listesol);
     /* noeud* n0 = malloc(sizeof(noeud));
      tache t0 = { .id = 1, .pi = 5, .ri = 0, .ti = 0, .famille = 7 };
      n0->id = t0;
      n0->BI = BI;
      elementbnb* ntmp = malloc(sizeof(elementbnb));
      ntmp->taille = 0;
      ntmp->t = t0;
      n0->chemin = ntmp;
      n0->next = NULL;


      listenoeud l1 = NULL;
      l1 = ajouterTeteNoeud(l1,n0);
      l1 = ajouterTeteNoeud(l1,n0);
      l1 = ajouterTeteNoeud(l1,n0);l1 = ajouterTeteNoeud(l1,n0);
      printf("TEST TETE\n");
      afficherListeNoeud(l1);*/

      //afficherListeTaches(nt->chemin);

    branchAndBound(BI, BS, listesol, 3);
    return 0;
}
