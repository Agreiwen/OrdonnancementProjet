/* Projet Ordonnancement : Machines dédiées - branch and bound */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <time.h>

struct noeud
{
    tache id;
    int BI;
    tache[] chemin;
};
typedef noeud* listenoeud;

listenoeud ListArbre;
//Listetache ListChemin;
listetaches listeTaches;
//Listetache Tachesrestantes;
Listenoeud Resultat;
noeud n0;
n0.id = null;
no.BI = BI;
no.chemin = null;

ListArbre.ajouter(t0);
Tachesrestantes.ajouter(Taches);
while ListArbre != NULL
   if(ListArbre.tete.chemin.length != listeTaches.length){

        noeud tmp = ListArbre.tete;
         if(tacheREstantes = null){
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

int main(int argc, char **argv){
    printf("****** Projet d'ordonnancement ******\n\n");
    return 0;
}
