#include <stdio.h>
#include <stdlib.h>

#include "arbre.h"
#include "pile.h"

void MAJPileDeNoeuds(pNoeud arbre){

    pNoeud tmp=arbre;

    if (tmp!=NULL)
    {
        empilerN(Pile_de_noeuds, tmp );
        MAJPileDeNoeuds(tmp->drt);
        MAJPileDeNoeuds(tmp->gch);
    }

}

void menu ()

{
printf ("Bonjour saississez l'operation que vous souhaitez realiser \n");
printf ("---------------------------------------------------------- \n");
printf(" 1* Ajouter un nouvel employe a partir du clavier\n");
printf(" 2* Lecture des donnees a partir d'un fichier \n");
printf(" 3* Afficher tous les employes \n");
printf(" 4* Modifier les informations d'un employe \n");
printf(" 5* Supprimer un employe de la base de donnees par le numero \n");
printf(" 6* Supprimer tous les employes \n");
printf(" 7* Supprimer l'arbre des salaires \n");
printf(" 8* Sauvegarder l'arbre dans un fichier \n");
printf(" 9* Quitter \n");
printf("-------------------------------------------------------------\n");

}



int main()
{
    char* f="data.txt";
    char* f2="data2.txt";
    pNoeud arbre = NULL;
    int num =0;
    char nom[50];
    char fonction[50];
    int age=0;
    int salaire=0;

    ltrie=malloc(sizeof(element));
    ltrie=NULL;


    int i=0;

while(i!=9)

{

system("cls");
menu();
printf("entrez votre choix : ");
scanf("%d",&i);


switch (i)
{
    case 1 :

            printf("Entrer le numero de l'employe\n");
            scanf("%d", &num );
            printf("Entrer le nom de l'employe\n");
            scanf("%s", nom );
            printf("Entrer la fonction de l'employe\n");
            scanf("%s", fonction );
            printf("Entrer l'age de l'employe\n");
            scanf("%d", &age);
            printf("Entrer le salaire de l'employe\n");
            scanf("%d", &salaire);
            pEmploye ne=nouveauEmploye(num, nom,fonction,age,salaire);
            arbre=insererEmploye(arbre, ne);
            system("pause");
            break;

    case 2 :
            arbre= lireFichier(arbre, f);
             printf ("Le fichier a bien ete lu\n");
             system("pause");
            break;

    case 3 :
            if (arbre==NULL)
            {
                printf("La liste des employes est vide\n");
            }
            else{
                ltrie=malloc(sizeof(element));
                ltrie=NULL;
            printf("------------------------------------------------------------------------------------------------------------------------");
            printf("\n");
            printf("|Identifiant \t| Nom                \t| Fonction                 \t| Age                 \t| Salaire              \t|");
            printf("\n");
            printf("------------------------------------------------------------------------------------------------------------------------");
            printf("\n");
            afficherEmployes(arbre);
            printf("------------------------------------------------------------------------------------------------------------------------\n\n");

            }
            system("pause");
            break;
    case 4 :

            printf("Entrer le numero de l'employe que vous voulez modifier \n");
            scanf("%d", &num );
            printf("Entrer le nouveau nom de l'employe\n");
            scanf("%s", nom );
            printf("Entrer la nouvelle fonction de l'employe\n");
            scanf("%s", fonction );
            printf("Entrer le nouvelle age de l'employe\n");
            scanf("%d", &age);
            printf("Entrer le nouveau salaire de l'employe\n");
            scanf("%d", &salaire);
            arbre= modifierEmploye(arbre, num, nom, fonction, age, salaire);
            system("pause");
            break;
     case 5 :
            printf("Entrer le numero de l'employe que vous voulez supprimer\n");
            scanf("%d", &num );
            arbre=supprimerEmploye(arbre, num);
            system("pause");
            break;
    case 6 :
            printf("Entrer salaire du noeud que vous souhaiter supprimer\n");
            scanf("%d", &salaire);
            pNoeud noeud=chercherSalaire( arbre, salaire);
            if (noeud !=NULL)
            {
                arbre= supprimerNoeud(arbre, noeud);
                Pile_de_noeuds = creerPileN();
                MAJPileDeNoeuds(arbre);
            }

            else printf ("Salaire non existant\n");
            system("pause");
            break;

    case 7 :
            supprimerArbre(arbre);

            break;

    case 8 :
            ecrireFichier(arbre, f2);
            break;
    case 9:
            printf("\n\nA bientot!\n\n");
            break;

}
}
}
