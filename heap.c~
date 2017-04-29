#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*         structures principales        */

//structure qui contient toutes les données 

typedef struct noeud
{
  int value; //value contenue 
  int degree; //nombre de fils  
  struct noeud* parent; //noeud parent 
  struct noeud* child;  // pointeur vers le fils le plus a gauche 
  struct noeud* sibling; //pointeur vers le frere du fils qui se trouve donc a sa droite  
 
}Noeud;  


void afficher(Noeud* c);


/*    Premiere fonction: Creation de noeud d'un arbre  */


Noeud* create_node(int i)
{
  Noeud * current=malloc(sizeof(Noeud)); 
  current->value=i; 
  current->degree=0; 
  current->parent=NULL; 
  current->child=NULL; 
  current->sibling=NULL; 
  return current; 
}


/*   Seconde fonction: Fusion de deux noeuds pour la création d'un nouvel arbre   */

Noeud* link_node(Noeud* node1, Noeud* node2) 
{
  node2->parent=node1; 
  node2->sibling=node1->child; 
  node1->child=node2;  
  node1->degree+=1;
  return node2; 
}


/* Troisieme fonction:   Fusion de deux arbres pour la creation d'un tas    */


Noeud* create_heap(Noeud* un, Noeud* deux)
{
 
  Noeud* final=NULL;
  Noeud* one=un; 
  Noeud* two=deux; //on copie, on ne fait jamais les modifications directement 
  Noeud* tmp;
  Noeud* tmp2; 

  if (un==NULL || deux==NULL)
    {
      final=two; 
    }

  else
    {

      if (one->degree<two->degree)
	final=one; 

      if(one->degree>two->degree)
	final=two; 
    
      else
	final=one; // si egalite on prend soit l'un soit l'autre   
    }
  
  // va permettre de mettre les choses en ordre 
  
  while (one !=NULL && two!=NULL)
    {
      if(one->degree > two->degree) // on echange de maniere a mettre two avant one 
	{
	  tmp=two->sibling; 
	  two->sibling=one; 
	  two=tmp; 
	    
	}

      if(one->degree==two->degree) // on echange de maniere a mettre one avant two 
	{
	  tmp2=one->sibling;
	  one->sibling=two; 
	  one=tmp2; 

	}

      else if (one->degree < two -> degree)
	one=one->sibling; // on passe au suivant 

    }


  return final; 
}


/*    Quatrieme fonction : recuperer le minimum   */


Noeud* min_heap(Noeud* tasso)
{
  int min=10000; //prend la value du premier element  
  Noeud* tas; // on fait une copie 
  tas=tasso;
  Noeud* tmp;

  if(tas==NULL)
    {
      return tas; //rien a extraire 
    }

  else
    {
      while(tas->sibling!=NULL)
	{
	  if(tas->sibling->value<min) // si c'est inferieur on change min
	    {
	      min=tas->sibling->value; 
	      tmp=tas; 
	      tas=tas->sibling; 
	    }
	  if(tas->sibling!=NULL)
	    tas=tas->sibling; //on passe a l'element suivant 
	}

      if(tmp==NULL && tas->sibling==NULL)
	tasso=NULL;
      
      else if(tmp==NULL)
	tasso=tas->sibling; 
      
      else if(tmp->sibling==NULL)
	tmp=NULL; 
      
      else
	tmp->sibling=tas->sibling; 
    }

  
  return tmp; 

}


 
/*    Cinquieme  fonction : Union de deux tas pour la formation d'un tas    */


Noeud* union_heap(Noeud* truc1, Noeud* truc2)
{

  Noeud* tas1=truc1; 
  Noeud* tas2=truc2; 
  Noeud* final=NULL; 
  final=create_heap(tas1,tas2); //on cree un tas
  Noeud* prec=NULL; // pointeurs qui vont permettre de parcourir la structure 
  Noeud* suiv=final->sibling;// on ne peut pas definir precedent pour l'instant car on commence au debut  
  
  if(final==NULL) //si le tas est null, on renvoie un tas null forcément 
    return final; 
  
  Noeud* copie=final; 
  
  while(suiv!=NULL) // tant qu'on a pas fini de parcourir le tas 
    {
      if(copie->value!=suiv->value) // si on a pas la meme valeur entre les deux elements, sinon on place le noeud
	{
	  prec=copie; // on passe a l'element suivant 
	  copie=suiv; 

	}
      
      if(suiv->sibling!=NULL && suiv->sibling->value==copie->value) // si le tas n'est pas fini et que l'element suivant a une valeur egale on fait la meme chose 
	{
	  prec=copie; 
	  copie=suiv; 

	}

      else // si on est pas dans les cas predecent on peut essayer de placer le noeud en respectant les caracteristiques des noeuds binomiaux
	{
	  if(copie->value<=suiv->value) // si la value du premier noeud est inferieur a celle du noeud suivant 
	    {
	      copie->sibling=suiv->sibling; // on passe à l'élément suivant 
	      suiv->parent=copie;
	      suiv->sibling=copie->child;
	      copie->child=suiv; 
	      copie->degree+=1; // on lie les deux 
	    }
	  
	  else 
	    {
	      if(prec==NULL) // si l'un des deux tas se termine avant l'autre 
		final=suiv; 
	      
	      else
		prec->sibling=suiv; 
		
	      copie->parent=suiv;
	      copie->sibling=suiv->child;
	      suiv->child=copie;
	      suiv->degree+=1; // on lie les deux
	      copie=suiv; 
	    }
	}
	  
      suiv=copie->sibling; 
    }

  return final; 
}


/* Sixieme fonction: insertion d'un element  */

Noeud* insertion(Noeud* tas, Noeud* noeud)
{

  tas=union_heap(tas,noeud);   
  return tas;  
}


/*septieme fonction: suppression d'un element */

Noeud* trouver(Noeud* tas, int key)
{
  Noeud* copie=tas; 
  
  if(copie->value==key)
    return copie; 

  if(copie->child!=NULL) // si le noeud de gauche est non nul on verifie 
    copie=trouver(copie->child,key); 

  if(copie->sibling!=NULL) // si le noeud de droite est non nul on verifie  
    copie=trouver(copie->sibling,key);
  return copie; 

}


Noeud* suppression(Noeud* tas, int key)
{ 
  Noeud* prec; // meme principe que pour union
  Noeud* suiv; 
  int tmp; 
  Noeud* elem=trouver(tas,key); 

  if(tas==NULL)
    exit(EXIT_FAILURE); 

    else
    {
          
      elem->value=key; // on cherche la clef qui correspond a la valeur de l'element 
      prec=elem; 
      suiv=elem->parent; 
      
      while(suiv!=NULL && prec->value!=suiv->value) // tant qu'on peut aller a l'element suivant et que les valeurs sont differentes
	{
	  // on inverse les valeurs entre prec et suiv jusqua faire redescendre l'element au debut 
	  tmp=prec->value; 
	  prec->value=suiv->value; 
	  suiv->value=tmp; 
	  prec=suiv; // on pas a l'element suivant 
	  suiv=suiv->sibling; 
	}

      min_heap(tas); 
    
    }

  
  return tas; 

}



 /*    Huitieme fonction: Affichage d'un Heap     */

void  afficher(Noeud* tas)
{
  Noeud* tasso=tas;
 
  if(tas==NULL)
    printf("\n VIDE!");

  while(tasso!=NULL)
    {
      printf("%d",tasso->value);
      if(tasso->sibling!=NULL)
        printf("-->");tasso=tasso->sibling;
      
    }
  printf("\n"); 
}



int main ()
{
  
  printf("Bienvenue dans le jeu de construction des tas binomiaux.\n");

  printf("Création de noeud 3 et 22: "); 
  Noeud* noeud1=create_node(3);
  Noeud* noeud2=create_node(22); 
  afficher(noeud1); 
  afficher(noeud2); 
  printf("\n"); 
  
  printf("Création d'arbre:"); 
  Noeud* arbre1; 
  arbre1=create_heap(noeud1,noeud2); 
  afficher(arbre1); 
  printf("\n"); 
  
  printf("Création de tas: "); 
  printf("\n"); 
  printf("Arbre 2 avec noeuds 4 et 51: "); 
  Noeud* noeud3=create_node(4);
  Noeud* noeud4= create_node(51); 
  Noeud* arbre2; 
  arbre2=create_heap(noeud3,noeud4);
  afficher(arbre2); 
  printf("\n"); 
  printf("Tas: "); 
  Noeud* tasso; 
  tasso=create_heap(arbre1,arbre2); 
  afficher(tasso); 
  printf("\n"); 
  
  /*
  printf("Union de deux tas"); 
  Noeud* tas=malloc(sizeof(Noeud));
    tas=union_heap(arbre1,arbre2); 
  afficher(tas); 
  printf("\n"); 
  */

  printf("Extraction du minimum: ");   
  Noeud* mini=min_heap(tasso);
  afficher(mini);
  printf("\n");
      
  
  printf("Insertion de l'élément 1 dans un tas: "); 
  Noeud* insert=insertion(tasso,create_node(1)); 
  afficher(insert); 
  printf("\n");  
  
      
  printf("Création d'un tas composé des noeuds 8, 12, 6, 3 et suppression de 6: "); 
  printf("\n");                                                             
  printf("Tas: "); 
  Noeud* tassi=create_heap(create_heap(create_node(3),create_node(12)),create_heap(create_node(8),create_node(6))); 
  afficher(tassi); 
  printf("Tas après suppression: "); 
  Noeud* sup; 
  sup=suppression(tassi,1);                                                                            
  afficher(sup);                                                                                     
  printf("\n");     


  /*
    reverse_list pour min_heap
    supp à un soucis, supprime presque tout
    union marche pas sauf dans fonction autre



   */

  
}


