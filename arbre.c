
#include "arbre.h"

//fonctions deja developpees
pPileN creerPileN() {
    pPileN p = (pPileN)malloc(sizeof(PileN));

    if(p==NULL)
    {
        perror("erreur: pile.c : fonction creerPileN: manque de memoire");
        return NULL;
    }

	p->iSommet = -1;

	return p;
}

int	pileVideN ( pPileN p) {
    if(p == NULL)
    {
        perror("erreur: pile.c : fonction pileVideN: pointeur NULL");
        return ERROR;
    }

	if (p->iSommet == -1)
		return 1;
	else
		return 0;
}

int	pilePleineN( pPileN p) {
    if(p == NULL)
    {
        perror("erreur: pile.c : fonction pilePleineN: pointeur NULL");
        return ERROR;
    }

	if (p->iSommet == (MAX_SIZE_PILE -1) )
		return 1;
	else
		return 0;
}

void empilerN( pPileN p, pNoeud pN) {
    if(p == NULL || pN == NULL)
    {
        perror("erreur: pile.c : fonction empilerN: pointeur NULL");
        return;
    }

	if (pilePleineN(p)) {
		printf("erreur: pile.c : fonction empilerN: la Pile est pleine\n");
		return;
	}

	p->iSommet = p->iSommet + 1;
	p->tabNoeud[ p->iSommet] = pN;
}

pNoeud depilerN( pPileN p) {
	pNoeud pN;
    if(p == NULL)
    {
        perror("erreur: pile.c : fonction depilerN: pointeur NULL");
        return NULL;
    }

	if (pileVideN(p)) {
		printf("erreur: pile.c : fonction depilerN: la Pile est vide\n");
		return NULL;
	}

	pN = p->tabNoeud[ p->iSommet];
	p->iSommet = p->iSommet-1;
	return pN;
}

pNoeud SommetNoeud( pPileN p )
{
     if(p == NULL)
    {
        perror("erreur: pile.c : fonction SommetNoeud: pointeur NULL");
        return NULL;
    }

	if (pileVideN(p)) {
		printf("erreur: pile.c : fonction SommetNoeud: la Pile est vide\n");
		return NULL;
	}

	return p->tabNoeud[ p->iSommet];
}


void supprimerPileN(pPileN p)
{
    pNoeud pN;

    if(p == NULL)
    {
        perror("erreur: pile.c : fonction supprimerPileN: pointeur NULL");
        return;
    }

    while(!pileVideN(p))
    {
      pN = depilerN(p);
      free(pN);
    }

	free(p);
}


pNoeud minimumABR(pNoeud arbre)
{
    pNoeud pN;
    pN = arbre;

    if(arbre==NULL)
    {
         perror("erreur: arbre.c : fonction minimumABR: pointeur NULL");
         return NULL;
    }

    while(pN->gch!=NULL)
    pN = pN->gch;

    return pN;
}

pNoeud succeseurABR(pNoeud noeud)
{
      pNoeud pNX,pNY;

      if(noeud->drt != NULL)
            return minimumABR(noeud->drt);

      pNY = noeud->pere;
      pNX = noeud;

      while(pNY!=NULL && pNX == pNY->drt)
      {
        pNX = pNY;
        pNY = pNY->pere;
      }
      return pNY;
}

void copyEmployer(pEmploye pe1, pEmploye pe2)
{
    pe1->num = pe2->num;
    strcpy(pe1->nom,pe2->nom);
    strcpy(pe1->fct,pe2->fct);
    pe1->age = pe2->age;
    pe1->salaire = pe2->salaire;
}


//fonctions a developper. libre a vous de rajouter des autres fonctions si necessaire

pNoeud nouveauNoeud(int salaire)
{
    pNoeud n =(pNoeud)malloc(sizeof(Noeud));
    if (n==NULL)
    {
        printf("pas de memoire \n");
        return NULL;
    }
    n->salaire=salaire;
    n->drt=NULL;
    n->gch=NULL;
    n->pere=NULL;
    n->pileEmploye= creerPile();
    return n;

}
pEmploye nouveauEmploye(int num, char * nom, char * fonction,  int age, int salaire)
{
    pEmploye e =(pEmploye)malloc(sizeof(Employe));
    if (e==NULL)
    {
        printf("Pas de memoire\n");
        return e;
    }
    e->num=num;
    strcpy(&(e->nom), nom);
    strcpy(&(e->fct), fonction);
    e->age=age;
    e->salaire=salaire;

    return e;
}

pNoeud chercherEmploye(pNoeud arbre, int numero)
{
    int i=0;
    while ( i<=Pile_de_noeuds->iSommet)
    {
        pEmploye e = chercherEmployePile(Pile_de_noeuds->tabNoeud[i]->pileEmploye, numero);
        if (e==NULL)
        {
            i++;// on avance dans la pile
        }
        else
        {
            return Pile_de_noeuds->tabNoeud[i];// on retourne l'adresse du noeud
        }
    }

    if (i==Pile_de_noeuds->iSommet+1)// si on a pas trouvé notre element
    {
        return NULL;
    }

}
pNoeud chercherSalaire(pNoeud arbre, int salaire)
{
    int i=0;
    while ( i<=Pile_de_noeuds->iSommet)
    {

        if (Pile_de_noeuds->tabNoeud[i]->salaire== salaire)
        {
            return Pile_de_noeuds->tabNoeud[i];// on retourne l'adresse du noeud

        }
        else
        {
             i++;// on avance dans la pile
        }
    }

    if (i==Pile_de_noeuds->iSommet+1)// si on a pas trouvé notre element
    {
        return NULL;
    }

}

pNoeud insererEmploye(pNoeud arbre, pEmploye employe)
{
    if (arbre==NULL)
    {
        arbre = nouveauNoeud(employe->salaire);
        empiler( arbre->pileEmploye, employe );  // on ajoute l'employe dans la pile des employes
        Pile_de_noeuds = creerPileN(); //on cree la pile des noeuds et on y ajoute l'employe
        empilerN(Pile_de_noeuds, arbre );// on empile arbre qui sera le premier element de la pile
        return arbre;

    }

    else
        {
            pNoeud tmp1=chercherEmploye(arbre, employe->num);// on cherche le salarié
            if (tmp1!=NULL)// si le salarié existe deja
            {
                printf("Le salarie deja existant il ne sera pas ajouté\n");
                return arbre;
            }
            else {// si le salarié n'existe pas
                    pNoeud tmp=arbre;// on va parcourir l'arbre et ajouter le noeud la ou il faut
                    pNoeud tmp2= arbre;
                    while (tmp!=NULL)
                    {
                            tmp2=tmp;
                            if ((employe->salaire) < (tmp->salaire) )
                            {
                                tmp=tmp->gch;
                            }
                            else if ((employe->salaire) > (tmp->salaire) )
                            {
                                tmp = tmp->drt;
                            }
                            else
                            {
                                break;
                            }


                    }
                    if (tmp==NULL)
                    {
                        pNoeud n = nouveauNoeud(employe->salaire);
                        empiler( n->pileEmploye, employe );
                        n->pere=tmp2;
                        if (tmp2->salaire > employe->salaire)
                        {
                            tmp2->gch=n;
                        }
                        else tmp2->drt=n;

                        //on met a jour la pile des noeuds
                        empilerN(Pile_de_noeuds, n );


                    }
                    else
                    {
                        empiler( tmp->pileEmploye, employe );
                    }


            }

        }

return arbre;

}
void supprimerNoeudPileN(pPileN p, pNoeud noeud )
{


    pPileN p2 = creerPileN();
    pNoeud pN= NULL;
    pNoeud pN2=NULL;

    if(p == NULL)
    {
        printf("La pile est invalide\n");
        return;
    }

	if (pileVideN(p)) {
		printf("La pile est vide\n");
		return;
	}

    while(!pileVideN(p))
    {
        pN2 = depilerN(p);
        if(pN2 == noeud)
        {
            pN = pN2;
            break;
        }
        else
            empilerN(p2,pN2);
    }

    while(!pileVide(p2))
    {
        pN2 = depilerN(p2);
        empilerN(p,pN2);
    }

    supprimerPileN(p2);
    //free(pN);

}


pNoeud supprimerNoeud(pNoeud arbre, pNoeud noeud)
{
    pNoeud tmp=NULL;
    supprimerNoeudPileN(Pile_de_noeuds, noeud );

     if (arbre==noeud)// si ce que l'on veut supprimer est la racine de l'arbre
     {
         if ((noeud->drt==NULL) && (noeud->gch==NULL))// si l'arbre contient qu'un seul noeud
             {
                 supprimerPile(noeud->pileEmploye);
                free(noeud);
                return NULL;
             }
         else if ( (noeud->drt==NULL) || (noeud->gch==NULL))// si la racine possede que un seul des sous arbres droit ou gauche
             {
                     if (noeud->drt!=NULL)
                    {
                        arbre = noeud->drt;
                    }
                    else
                    {
                        arbre = noeud->gch;
                    }
                    supprimerPile(noeud->pileEmploye);
                    free(noeud);
                    return arbre;
             }
         else// si la racine possede deux sous arbres
              {
               tmp= succeseurABR(noeud);
               if (tmp!=NULL)
               {
               noeud->salaire=tmp->salaire;
               supprimerPile(noeud->pileEmploye);
               noeud->pileEmploye= (pPile)malloc(sizeof(Pile));
               noeud->pileEmploye->iSommet=-1;
               while(pileVide(tmp->pileEmploye)==0){
                       pEmploye e =(pEmploye)malloc(sizeof(Employe));
                       copyEmployer(e,depiler(tmp->pileEmploye));
                       empiler(noeud->pileEmploye,e);

                   }
               arbre= supprimerNoeud(arbre, tmp);
               }
                return arbre;
              }
     }

    else {// ce que l'on veut supprimer n'est pas la racine
        if ((noeud->drt==NULL) && (noeud->gch==NULL))// si l'element que l'on veux supprimer est une feuille
        {
                tmp = noeud->pere;
                if (tmp->gch==noeud)
                {
                    tmp->gch=NULL;
                }
                else if(tmp->drt==noeud)
                {
                    tmp->drt=NULL;
                }
                supprimerPile(noeud->pileEmploye);
                free(noeud);
                return arbre;

        }
        else if ( (noeud->drt==NULL) || (noeud->gch==NULL))// si l'element que l'on veut supprimer possede un seul sous arbre
        {

                if (noeud->drt!=NULL)
                {
                    tmp=noeud->drt;
                }
                else
                {
                    tmp=noeud->gch;
                }
                pNoeud tmp2= noeud->pere;
                tmp->pere=tmp2;
                if (tmp2->gch==noeud)
                {
                    tmp2->gch=tmp;
                }
                else if (tmp2->drt==noeud)
                {
                    tmp2->drt=tmp;
                }
                supprimerPile(noeud->pileEmploye);
                free(noeud);
                return arbre;

        }
        else
        {
               tmp= succeseurABR(noeud);
               if (tmp!=NULL)
               {
               noeud->salaire=tmp->salaire;
               supprimerPile(noeud->pileEmploye);
               noeud->pileEmploye= (pPile)malloc(sizeof(Pile));
               noeud->pileEmploye->iSommet=-1;
               while(pileVide(tmp->pileEmploye)==0){
                       pEmploye e =(pEmploye)malloc(sizeof(Employe));
                       copyEmployer(e,depiler(tmp->pileEmploye));
                       empiler(noeud->pileEmploye,e);



                   }
               arbre= supprimerNoeud(arbre, tmp);
               }
               return arbre;

        }

    }


}
/* Fonction récursive réalisant un parcourt infixe de l'arbre */

/*
void afficherEmployes(pNoeud arbre)
{
    pNoeud tmp=arbre;

    if (tmp!=NULL)
     {
        afficherEmployes(tmp->gch);


       int i=0;
        if (tmp->pileEmploye->iSommet!=-1)
        {
                    for (i=0; i<=tmp->pileEmploye->iSommet; i++)
                {
                    printf ("\n|      %d      \t|    %s                \t|        %s        \t|     %d     \t|     %d       \t|\n", tmp->pileEmploye->tabEmploye[i]->num, tmp->pileEmploye->tabEmploye[i]->nom, tmp->pileEmploye->tabEmploye[i]->fct, tmp->pileEmploye->tabEmploye[i]->age,tmp->pileEmploye->tabEmploye[i]->salaire);
                }
        }

        afficherEmployes(tmp->drt);
    }

}  */


/* Fonction itérative pour affichage de l'arbre */

void afficherEmployes(pNoeud arbre)
{
    int i=0;
    while ( i<=Pile_de_noeuds->iSommet)
    {

            ltrie=ajoutListeTri(ltrie,Pile_de_noeuds->tabNoeud[i]);
            i++;// on avance dans la pile

    }
    liste tmp=ltrie;

    while (tmp!=NULL)
    {
        for (i=0; i<=tmp->n->pileEmploye->iSommet; i++)
                {
         printf ("\n|      %d      \t|    %s                \t|        %s        \t|     %d     \t|     %d       \t|\n", tmp->n->pileEmploye->tabEmploye[i]->num, tmp->n->pileEmploye->tabEmploye[i]->nom, tmp->n->pileEmploye->tabEmploye[i]->fct, tmp->n->pileEmploye->tabEmploye[i]->age,tmp->n->pileEmploye->tabEmploye[i]->salaire);
                }
        tmp=tmp->next;
    }

}
liste ajoutListeTri(liste l , pNoeud najout)
{
    element* x=malloc(sizeof(element));
    x->n=najout;
    x->next=NULL;

    if (l==NULL )
    {
        return x;
    }
    else if(najout->salaire< l->n->salaire)
    {
        x->next=l;
        return x;
    }
    else
    {
        liste tmp=l;
        liste tmp2=l;
        while (tmp->n->salaire < najout->salaire)
        {
            tmp2=tmp;
            tmp=tmp->next;
            if(tmp==NULL)
            break;
        }
        x->next=tmp;
        tmp2->next=x;
        return l;
    }

}
pNoeud supprimerEmploye(pNoeud arbre, int numero)
{
    pNoeud tmp= chercherEmploye(arbre, numero);

    if (tmp==NULL)
    {
        printf ("L'employe qui possede le numero que vous avez entrer n'existe pas\n");
        return arbre;
    }

    else
    {
        supprimerEmployePile(tmp->pileEmploye, numero);

        if (pileVide ( tmp->pileEmploye))
        {
            arbre=supprimerNoeud (arbre, tmp);
        }
        printf("L'employe a bien ete supprimer\n");
    }

return arbre;

}

//Nouvelle fonction 'modifier' après s'être rendus compte que l'ancienne
// ne fonctionnait pas correctement (après démonstration jeudi 14 juin)
pNoeud modifierEmploye(pNoeud arbre, int num, char * nom, char * fonction, int age, int salaire)
{


            pEmploye ne=nouveauEmploye(num, nom,fonction,age,salaire);
            arbre=supprimerEmploye(arbre, num);
            arbre=insererEmploye(arbre, ne);

  return arbre;

}
/* Première fonction initialement codée avant la démonstration du jeudi 14 juin */

/*
pNoeud modifierEmploye(pNoeud arbre, int numero, char * nom, char * fonction, int age, int salaire)
{

     pNoeud tmp= chercherEmploye(arbre, numero);

    if (tmp==NULL)
    {
        printf ("employe non existant\n");
        return arbre;
    }
    else
    {
        pEmploye e=chercherEmployePile(tmp->pileEmploye, numero);
        e->age=age;
        e->salaire=salaire;
        strcpy(&(e->nom), nom);
        strcpy(&(e->fct), fonction);
        if (e->salaire!=salaire)
        {
            arbre = supprimerEmploye(arbre, e->num);
            arbre = insererEmploye(arbre, e);
        }
    }

    return arbre;

}*/
void supprimerArbre(pNoeud arbre)
{
    int i=0;
    if (!pileVideN(Pile_de_noeuds))
    {
        while ( i<=Pile_de_noeuds->iSommet)
        {
            arbre = supprimerNoeud(arbre, Pile_de_noeuds->tabNoeud[i]);
            i++;
        }
    }
    Pile_de_noeuds = creerPileN();
    arbre->salaire=-1;
    arbre->drt=NULL;
    arbre->gch=NULL;
    arbre->pere=NULL;
    arbre->pileEmploye= creerPile();

}


pNoeud lireFichier(pNoeud arbre, char * f)
{
    FILE* pfile;

      char temp[100];

      Employe * nouveaue;
      if((pfile=fopen(f,"r"))!=NULL){
          fscanf(pfile,"%s",temp);
          fscanf(pfile,"%s",temp);
          fscanf(pfile,"%s",temp);
          fscanf(pfile,"%s",temp);
          fscanf(pfile,"%s",temp);
          nouveaue= (Employe *) malloc(sizeof(Employe));
          while(fscanf(pfile,"%d",&nouveaue->num)!=EOF)
          {
              fscanf(pfile,"%s",nouveaue->nom);
              fscanf(pfile,"%s",nouveaue->fct);
              fscanf(pfile,"%d",&nouveaue->age);
              fscanf(pfile,"%d",&nouveaue->salaire);

              arbre= insererEmploye(arbre, nouveaue);
              nouveaue=(Employe *) malloc(sizeof(Employe));

          }
          fclose(pfile);
      }
      else
      {
          printf("Error open file %s",f);
      }
return arbre;
}
 void ecrireFichier(pNoeud arbre, char * f)
{
    FILE* pfile;

    char temp[100];
    int num =0;
    char nom[50];
    char fonction[50];
    int age=0;
    int salaire=0;


    pfile=fopen(f,"w");
   liste ltrie=malloc(sizeof(element));
   ltrie=NULL;
   int i=0;

fputs("ID\tNOM\tFONCTION\tAGE\tSALAIRE\n", pfile);
    while ( i<=Pile_de_noeuds->iSommet)
    {

            ltrie=ajoutListeTri(ltrie,Pile_de_noeuds->tabNoeud[i]);
            i++;// on avance dans la pile

    }

    liste tmp=ltrie;


    while (tmp!=NULL)
    {
        for (i=0; i<=tmp->n->pileEmploye->iSommet; i++)
                {
                       pEmploye e = tmp->n->pileEmploye->tabEmploye[i];
                       fprintf(pfile,"%d\t",e->num);
                       fprintf(pfile,"%s\t",e->nom);
                       fprintf(pfile,"%s\t", e->fct);
                       fprintf(pfile,"%d\t", e->age);
                       fprintf(pfile,"%d\n",e->salaire);

                }
        tmp=tmp->next;


    }


   fclose(pfile);

}
