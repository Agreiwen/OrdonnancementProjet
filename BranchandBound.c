/* Projet Ordonnancement : Machines dédiées - branch and bound */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <time.h>


struct tachebnb {
  int id;
  int pi;
  int ri;
  int ti;
  int famille;
};
typedef struct tachebnb tachebnb;
typedef struct elementbnb elementbnb;
struct elementbnb
{
  tachebnb t;
  int taille;
  struct elementbnb *next;
};

typedef elementbnb* llistbnb;
struct noeudbnb
{
    tachebnb id;
    int BI;
    llistbnb chemin;
    struct noeudbnb *next;
};
typedef struct noeudbnb noeudbnb;
typedef noeudbnb* listenoeud;


listenoeud ajouterTeteNoeud(listenoeud liste, noeudbnb *tache1){
  noeudbnb* nouvelElement = malloc(sizeof(noeudbnb));
  nouvelElement->BI = tache1->BI;
  nouvelElement->id = tache1->id;
  nouvelElement->chemin = tache1->chemin;
  nouvelElement->next = liste;


 // nouvelElement->next = liste;
  return nouvelElement;
}


llistbnb ajouterEnTetebnb(llistbnb liste, tachebnb tache1){
  elementbnb* nouvelElement = malloc(sizeof(elementbnb));
  elementbnb* tmp = liste;
  if(tmp==NULL){
        nouvelElement->taille = 1;
  }else{
      nouvelElement->taille = (tmp->taille)+1;
  }
  nouvelElement->t = tache1;
  nouvelElement->next = liste;
  return nouvelElement;
}


llistbnb copie(llistbnb liste){

    elementbnb* listed = liste;
    elementbnb* nouvelliste = NULL;
    while(listed != NULL){

        elementbnb* nouvelElement = malloc(sizeof(elementbnb));
        elementbnb* tmp = nouvelliste;
        if(tmp==NULL){
            nouvelElement->taille = 1;
        }else{
            nouvelElement->taille = (tmp->taille)+1;
        }
        nouvelElement->t = listed->t;
        nouvelElement->next = nouvelliste;

        nouvelliste = nouvelElement;
        listed = listed -> next;


    }

    return nouvelliste;
}


llistbnb ajouterQueue(llistbnb liste, tachebnb tache1){
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
           // if(tmp->next == NULL){
                 //   printf("Je rentre la");
         //       ;
           //     tmp->taille = (tmp->taille)+1;
           // }
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

llistbnb supprimerElement(llistbnb liste, tachebnb tache1){
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
int sommeCiFamillesbnb(tachebnb tab[], int size){
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


/*int max2(int a, int b){
    if(a <= b){
        return b;
    }
    else{
        return a;
    }
}*/

/*int max3(int a, int b, int c){
    return max2(max2(a,b),c);
}*/
llistbnb soustractionListes(llistbnb taches, llistbnb chemin){
    elementbnb* res = copie(taches);




    elementbnb* tmp2 = chemin;
    while(tmp2 != NULL){
             elementbnb* tmp1 = taches;
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


int branchAndBound(int BI, int BS, llistbnb listeTaches, int nbtaches){

    listenoeud ListArbre;

    listenoeud Resultat = NULL;
    llistbnb tachesRestantes = NULL;
    noeudbnb* n0 = malloc(sizeof(noeudbnb));
    tachebnb t0 = { .id = -1, .pi = 5, .ri = 0, .ti = 0, .famille = 7 };
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
        tachesRestantes2 = ajouterEnTetebnb(tachesRestantes2, tmp->t);
        tmp = tmp->next;
      //  printf("yo");
    }

    elementbnb *tmp2 = tachesRestantes2;
     while(tmp2 != NULL){
        //printf("yo");
        tachesRestantes = ajouterEnTetebnb(tachesRestantes, tmp2->t);
        tmp2 = tmp2->next;
      //  printf("yo");
    }

    while (ListArbre != NULL){
        //    cmpt++;
       // printf("\n<<<<<<<<<<<<<<<<<<Je rentre dans mon grand While<<<<<<<<<<<<<<<<<<<<<<<<< \n");

    /*    elementbnb* elemt = ListArbre->chemin;
        int i = 0;
        while (elemt != NULL){
            i++;
            elemt = elemt->next;
        }*/

        if(ListArbre->chemin->taille != (listeTaches->taille)+1){
         //   printf("Oui c'est different\n");
            noeudbnb* tmp = ListArbre;
        //    printf("je definis un pointeur sur ma Listarbre tmp\n");
        //    printf("Contenu de tmp : \n");
        //    afficherListeNoeud(ListArbre);

            if(tachesRestantes == NULL){

               tachesRestantes = soustractionListes(listeTaches, tmp->chemin);

            }
         //   printf("\n je definis un pointeur sur mes tachesRestantes :\n");

            elementbnb *temp = tachesRestantes;
         //   afficherListeTachesbnb(temp);
//
        //    printf("Je dis a ListAbre d'avance\n");
            ListArbre = ListArbre->next;
         //   afficherListeNoeud(ListArbre);

         //   printf("Je creer une listeArbretmp\n");
            listenoeud ListeArbretmp = NULL;
           // printf("taille de temp %d",temp->taille);
          //  printf("--------Je parcours mes taches dans temp : ---------\n\n");
            while(temp != NULL){
             //   printf("Tache courante %d \n",temp->t.id);



                noeudbnb* nt = malloc(sizeof(noeudbnb));
             //   printf("\n%d tache du noeud : ",temp->t.id);
                nt->id = temp->t;
                nt->BI = BI;



                elementbnb* tmp22 = copie(tmp->chemin);
                elementbnb* copietmp22 = tmp22;
                elementbnb* tmp2 = NULL;
                while(copietmp22 != NULL){

                tmp2 = ajouterEnTetebnb(tmp2, copietmp22->t);
                copietmp22 = copietmp22->next;

                }








                nt->chemin = ajouterQueue(tmp2,nt->id);


                //afficherListeTachesbnb(nt->chemin);


                ListeArbretmp = ajouterTeteNoeud(ListeArbretmp, nt);

              //  printf("Je passe a la tache suivante\n");
                temp = temp->next;

            }
           // break;


            noeudbnb* tmpn = malloc(sizeof(noeudbnb));
            tmpn = ListeArbretmp;

         //   afficherListeNoeud(ListArbre);
            while(tmpn != NULL){




     /*           elementbnb* tacheduchemin = tmpn->chemin;
                int j = 0;
                printf("JE parcours mon chemin pour créer un tab\n");
                while(tacheduchemin!= NULL){
                    j++;
                    tacheduchemin = tacheduchemin->next;

                }
                j--;
                tachebnb tableautemp[j];
                int i = 0;
                elementbnb *tachetmp2duchemin = tmpn->chemin;
                tachetmp2duchemin = tachetmp2duchemin->next;
                while(tachetmp2duchemin != NULL){
                    tableautemp[i] = tachetmp2duchemin->t;
                    tachetmp2duchemin = tachetmp2duchemin->next;
                    i++;
                }

                int res = sommeCiFamillesbnb(tableautemp, j);
*/

                    ListArbre = ajouterTeteNoeud(ListArbre, tmpn);




                tmpn = tmpn->next;
          //      printf("Je passe au noeud suivant \n");

            }


            tachesRestantes = supprimerElement(tachesRestantes, ListArbre->id);
        //    afficherListeTachesbnb(tachesRestantes);

        }else{
           //  printf("je suis laaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

// break;
      //      afficherListeTaches(ListArbre->chemin);

            elementbnb* tachetmp = ListArbre->chemin;
            int j = 0;
         //   printf("JE parcours mon chemin pour créer un tab\n");
            while(tachetmp != NULL){
                j++;
                tachetmp = tachetmp->next;

            }

        //    printf(" Mon j : %d",j);
            j--;
            tachebnb tableau[j];

            int i = 0;
            elementbnb *tachetmp2 = ListArbre->chemin;
            tachetmp2 = tachetmp2->next;

            while(tachetmp2 != NULL){
                tableau[i] = tachetmp2->t;
                tachetmp2 = tachetmp2->next;
                i++;
            }


            int res = sommeCiFamillesbnb(tableau, j);

            if(res < BS){
           //     printf("oui c'est plus petit que la BS \n");

                BS = res;

                elementbnb* tmpel = ListArbre->chemin;
                tmpel = tmpel->next;

                Resultat = NULL;

                while(tmpel != NULL){

                    noeudbnb *ntmp = malloc(sizeof(noeudbnb));
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

    noeudbnb *copieres = Resultat;
    noeudbnb *Resultat2 = NULL;
    noeudbnb *tmp3 = malloc(sizeof(noeudbnb));
    while(copieres != NULL){
        tmp3->id = copieres->id;
        tmp3->BI = 0;
        Resultat2 = ajouterTeteNoeud(Resultat2,tmp3);
        copieres = copieres->next;

    }
    printf("Ma liste de tache dans l'ordre\n");
    afficherListeTachesNoeud(Resultat2);
    return BS;

}

int sommeCibnb(tachebnb tab[], int size){
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

void afficherListeTachesbnb(llistbnb taches){
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
  noeudbnb *tmp = nodes;
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
  noeudbnb *tmp = nodes;
  while(tmp != NULL){
    printf("id tache : %i",tmp->id.id);
    printf("| BI : %i\n",tmp->BI);
    //printf("| chemin : %i",tmp->chemin);
    //printf("| noeud : %i",tmp->next->id);

    tmp = tmp->next;
  }
}
int algorbnb(llistbnb* l, int nbtaches){
    printf("****** Projet d'ordonnancement ******\n\n");
/* POUR TEST */

    printf(" Mon nombre de taches que je recois : %d", nbtaches);
    tachebnb t1 = { .id = 1, .pi = 5, .ri = 0, .ti = 0, .famille = 7 };
    tachebnb t2 = { .id = 2, .pi = 3, .ri = 2, .ti = 0, .famille = 1 };
    tachebnb t3 = { .id = 3, .pi = 2, .ri = 5, .ti = 0, .famille = 5 };
    tachebnb t4 = { .id = 4, .pi = 5, .ri = 6, .ti = 0, .famille = 2 };
    tachebnb t5 = { .id = 5, .pi = 8, .ri = 3, .ti = 0, .famille = 3 };
    tachebnb t6 = { .id = 6, .pi = 1, .ri = 1, .ti = 0, .famille = 6 };

    tachebnb tableau[nbtaches];
    printf("Tableau cree");
   /* int i = 0;
    elementbnb *tachetmp2 = liste;
    while(tachetmp2 != NULL){
        tableau[i] = tachetmp2->t;
        tachetmp2 = tachetmp2->next;
        i++;
    }*/
  //  printf("Tableau rempli");
   // tachebnb test1 = { .id = 7, .pi = 10, .ri = 0, .ti = 0, .famille = 7 };
   // tachebnb test2 = { .id = 6, .pi = 10, .ri = 0, .ti = 0, .famille = 7 };
  //  tachebnb test = { .id = 8, .pi = 1, .ri = 50, .ti=0, .famille = 7};
    tableau[0] = t1;
    tableau[1] = t2;
    tableau[2] = t3;
    tableau[3] = t4;
    tableau[4] = t5;
    tableau[5] = t6;
    /* FIN TEST */
    int BI = 0;
    int BS = sommeCibnb(tableau,nbtaches);
    llistbnb listesol = NULL;


        listesol = ajouterEnTetebnb(listesol, tableau[5]);
        listesol = ajouterEnTetebnb(listesol, tableau[4]);
        listesol = ajouterEnTetebnb(listesol, tableau[3]);
        listesol = ajouterEnTetebnb(listesol, tableau[2]);
       listesol = ajouterEnTetebnb(listesol, tableau[1]);
        listesol = ajouterEnTetebnb(listesol, tableau[0]);

     printf("Tab1 \n");
 //   afficherListeTachesbnb(liste);






   int res = branchAndBound(BI, BS, *l, nbtaches);
 //  printf("Ma solution : %d\n",res);
    return res;
}
