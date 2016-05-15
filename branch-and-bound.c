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
typedef struct element element;
struct element
{
  tache t;
  int taille;
  struct element *next;
};

typedef element* llist;
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
  element* nouvelElement = malloc(sizeof(element));
  element *tmp = liste;
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
    element* nouvelElement = malloc(sizeof(element));
    element *tmp = liste;
    if(tmp == NULL){
        nouvelElement->taille = 1;
        nouvelElement->t = tache1;
        nouvelElement->next = liste;

    }else{
        while(tmp != NULL){
            tmp = tmp->next;
        }
        nouvelElement->taille = (tmp->taille)+1;
        nouvelElement->t = tache1;

    }
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

    element *tmp = listeTaches;
    while(tmp != NULL){

        TachesRestantes = ajouterEnTete(TachesRestantes, tmp->t);
        tmp = tmp->next;
    }



while (ListArbre != NULL)
   if(ListArbre->chemin->taille != listeTaches->taille){

        noeud* tmp = ListArbre;
       /*  if(TachesRestantes = NULL){
            tachesrestantes = lsitetaches - tmp.chemin;
        }*/
        ListArbre = ListArbre->next;
        element *temp = TachesRestantes;
        while(temp != NULL){
            noeud* nt;
            nt->id = temp->id;
            nt->BI = BI;
            nt->chemin = tmp.chemin + nt.id
            Listenoeud ListeArbretmp.ajoutertete(nt);


        }
        for chaque n dans ListeArbretmp{
            ListArbre.ajoutertete(n);

        }
        Tachesrestantes.supprimer(ListArbre.tete.id);

   }else{

    res = sommeCiFamilles(ListArbre.tete);
    if(res < BS){
        BS = res;
        Resultat = ListArbre.tete.chemin;
    }

    ListArbre.supprtete();

   }

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

int main(int argc, char **argv){
    printf("****** Projet d'ordonnancement ******\n\n");
    int BI;
    int BS;
    return 0;
}
