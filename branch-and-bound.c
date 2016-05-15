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
void branchAndBound(int BI, int BS, llist listeTaches){

    listenoeud ListArbre;
    //Listetache ListChemin;
    //llist listeTaches;
    //Listetache Tachesrestantes;
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
         if(TachesRestantes = null){
            tachesrestantes = lsitetaches - tmp.chemin;
        }
        ListArbre.supprimertete();
        for chaque t dans taches restantes {
            nt.id = t;
            nt.BI = BI;
            nt.chemin[] = tmp.chemin + nt.id
            Listenoeud ListeArbretmp.ajoutertete(nt);


        }
        for chaque n dans ListeArbretmp{
            ListArbre.ajoutertete(n);

        }
        Tachesrestantes.supprimer(ListArbre.tete.id);
  // ListChemin.ajouter(ListArbre.tete);
  // Tachesrestantes.enlever(ListArbre.tete);
   }else{

    res = sommeCiFamilles(ListArbre.tete);
    if(res < BS){
        BS = res;
        Resultat = ListArbre.tete.chemin;
    }
   // ListChemin = suppr2dernierelement(ListChemin);

    ListArbre.supprtete();
   //  Tachesrestantes.ajouterqueue(Taches que je viens de suppr);
  //  ListChemin.ajouter(ListArbre.tete);
  //  ListChemin.ajouter(ListArbre.tete);
 //  Tachesrestantes.enlever(ListArbre.tete);
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
