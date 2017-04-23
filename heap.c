#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/*         structures principales        */

//structure qui contient toutes les données 

typedef struct noeud
{
  int valeur; //valeur contenue 
  int degree; //nombre de fils  
  struct noeud* parent; //noeud parent 
  struct noeud* soon;  // pointeur vers le fils le plus a gauche 
  struct noeud* brother; //pointeur vers le frere du fils qui se trouve donc a sa droite  
 
}Noeud;  

// structure qui va permettre de parcourir le Tas 

typedef struct node
{
  Noeud* precedent; // premier element 
  Noeud* suivant; // va pointeur vers le suivant 

}Node; 



void afficher(Noeud* c);


/*    Premiere fonction: Creation de noeud d'un arbre  */

Noeud* init()
{
  Noeud* nono; 
  nono=NULL; 
  return nono; 

}



Noeud* create_node(int i)
{
  Noeud * current=malloc(sizeof(Noeud)); 
  current->valeur=i; 
  current->degree=0; 
  current->parent=current->soon=current->brother=NULL; 
  return current; 
}


/*   Seconde fonction: Fusion de deux arbres pour la création d'un nouvel arbre   */

Noeud* create_tree(Noeud* node1, Noeud* node2) // creation d'un arbre plus grand a partir d'un arbre plus petit -> propriété des tas binomiaux  
{

  node2->parent=node1; // le premier noeud pointe vers le second noeud comme si le 2nd était son père                                                             
  node2->brother=node1->soon; // le premier noeud recupère donc le frere du premier noeud                                                                         
  node1->soon=node2;  //mais le premier noeud pointe toujours vers ses babies donc il doit pointer vers son fils                                                  
  node1->degree+=1; //enfin on augmente l'indice du node2 car on a ajouté un élément à la structure                                                                            
  /*  while(node2!=NULL)
    {
      printf("%d",node2->valeur); 
      node2=node2->parent; 
      printf("->"); 
    }
  */
  return node2; 
}


/* Troisieme fonction:   Fusion de deux arbres pour la creation d'un tas    */


Noeud* create_heap(Noeud* un, Noeud* deux)
{
 
  Noeud* final=init(); 
  Noeud* one=un; 
  Noeud* two=deux; //on copie, on ne fait jamais les modifications directement 
  Noeud* tmp;
  Noeud* tmp2; 

  if (un==NULL || deux==NULL)
    {
      final=two; 
      printf("un==NULL || deux==NULL"); 
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
	  tmp=two->brother; 
	  two->brother=one; 
	  two=tmp; 
	  
	}

      if(one->degree==two->degree) // on echange de maniere a mettre one avant two 
	{
	  tmp2=one->brother;
	  one->brother=two; 
	  one=tmp2; 

	}

      else if (one->degree < two -> degree)
	one=one->brother; // on passe au suivant 

    }


  return final; 
}


/*    Quatrieme fonction : recuperer le minimum   */


Noeud* min_heap(Noeud* tasso)
{
  int min; //prend la valeur du premier element  
  Noeud* tas; // on fait une copie 
  tas=tasso;
  Noeud* tmp;
  Noeud* new; 

  if(tas==NULL)
    {
      return tas; //rien a extraire 
    }

  else
    {
      while(tas->brother!=NULL)
	{
	  if(tas->brother->valeur<min) // si c'est inferieur on change min
	    {
	      min=tas->brother->valeur; 
	      tmp=tas; 
	      tas=tas->brother; 
	    }
	  
	  tas=tas->brother; //on passe a l'element suivant 
	}

      if(tmp==NULL && tas->brother==NULL)
	tasso=NULL;
      
      else if(tmp==NULL)
	tasso=tas->brother; 
      
      else if(tmp->brother==NULL)
	tmp=NULL; 
      
      else
	tmp->brother=tas->brother; 
    }

  
  return tmp; 

}




 
/*    Quatrieme fonction : Union de deux tas pour la formation d'un tas    */


Noeud* union_heap(Noeud* truc1, Noeud* truc2)
{

  Noeud* tas1=truc1; 
  Noeud* tas2=truc2; 
  Noeud* final=malloc(sizeof(Noeud)); 
  final=create_heap(tas1,tas2); //on cree un arbre

  if(truc1==NULL || truc2==NULL)
    {  

      return final; 
      
    }


  else
    {
      if(final->valeur<final->brother->valeur) // si la valeur du premier noeud est inferieur a celle du noeud suivant 
	{
	  final->brother=final->brother->brother; // on passe à l'élément suivant 
	  final->brother->parent=final;
	  final->brother->brother=final->soon;
	  final->soon=final->brother; 
	  final->degree+=1; // on lie les deux 
	}
      
      else 
	{
	  if(final==NULL) // si l'un des deux tas se termine avant l'autre 
	    final=final->brother; 

	  else
	    {
	      final->brother->brother=final->brother; 
	      final->parent=final->brother;
	      final->brother=final->brother->soon;
	      final->brother->soon=final;
	      final->brother->degree+=1; // on lie les deux
	    }
	}
      
      final->brother=final->brother->brother; 


    }
  
  return final; 


}


/* cinquieme fonction: insertion d'un element  */

Noeud* insertion(Noeud* tas, Noeud* noeud)
{
  Noeud* noeud_copie=noeud; 
  Noeud* final=tas; 
  final=union_heap(tas,noeud_copie); 
  afficher(final); 
  return final;  
}






/*sixieme fonction: suppression d'un element */

Noeud* suppression(Noeud* tas, Noeud* sup)
{
  Noeud* min; 
  Noeud* tmp=tas; // on copie tas 

  if(tas==NULL)
    exit(EXIT_FAILURE); 

  else
    {
      while(tas->valeur!=sup->valeur)
	{
	  tas=tas->brother; // on continue 
      
	}

      if(tas->valeur==sup->valeur)
	{
	  Noeud* premier=tmp->brother;// on fait pointer sur tas suivant 
	  tmp=premier; 
	  free(tas); // on perd l'adresse en mémoire 
	}
      
    }

  return tmp; 

}




 /*    Sixieme fonction: Affichage d'un Heap     */

void  afficher(Noeud* H)
{
  Noeud* p;
  if(H==NULL)
    {
      printf("\n Vide!");

    }
  printf("\nLes noeuds sont:\n");
  p=H;
  while(p!=NULL)
    {
      printf("%d",p->valeur);
      if(p->brother!=NULL)
        printf("-->");p=p->brother;
    }
  printf("\n");

}



int main ()
{

  Noeud* noeud1; 
  Noeud* noeud2; 
  Noeud* noeud3; 
  Noeud* noeud4; 
  Noeud* arbre1=malloc(sizeof(Noeud)); 
  Noeud* arbre2=malloc(sizeof(Noeud));
  Noeud* arbre3=malloc(sizeof(Noeud));
  Noeud* arbre4=malloc(sizeof(Noeud));
  Noeud* tas; 
  Noeud* mini; 
  Noeud* n1; 
  Noeud* n2; 
  Noeud* n3; 
  Noeud* n4; 
  Noeud* tasso; 
  Noeud* heap; 


  int taille; 
  int i; 
  int valeur; 
  
  printf("Bienvenue dans le jeu de construction des tas binomiaux.");
  printf("\n");


  noeud1=create_node(28); 
  noeud2=create_node(3);
  noeud3=create_node(12); 
  noeud4=create_node(22); 


  n1=create_node(2); 
  n2=create_node(12); 
  n3=create_node(1); 
  n4=create_node(56); 

  printf("afficher noeud 1:"); 
  afficher(noeud1); 


  printf("Arbre numéro 1:"); 
  arbre1=create_tree(noeud1,noeud2); 
  
  printf("on reaffiche"); 
  afficher(arbre1); 

  printf("\n"); 
  printf("Arbre numéro 2:"); 
  arbre2=create_tree(noeud3,noeud4); 

  printf("\n");

  arbre3=create_tree(n1,n2); 
  arbre4=create_tree(n3,n4); 


  printf("Fusion des deux arbres:"); 
  printf("\n");  
  tas= create_heap(arbre1,arbre2);
  tasso=create_heap(arbre3,arbre4); 
  afficher(tas); 
  printf("Tasso:"); 
  afficher(tasso); 
  printf("\n");
  

  printf("Extraction du minimum:"); 
  printf("\n"); 
  mini=min_heap(tas); 
  afficher(mini); 
  printf("\n"); 

  printf("Union pour création de tas:"); 
  printf("\n"); 
  heap=union_heap(tas,tasso);  
  afficher(heap); 


  printf("Insertion:");
  printf("\n");
  Noeud * insert; 
  Noeud* nono=create_node(8); 
  //  insert=insertion(heap,nono); 
  //afficher(insert); 
  printf("\n");

  
  printf("Suppression:"); 
  printf("\n"); 
  Noeud* sup; 
  //  sup=suppression(insert,noeud1); 
  printf("\n"); 

  /*
  printf("Minimum du Tas:"); 
  mini=min_heap(tas); 
  afficher(mini); 
  printf("\n"); 
  */

  free(arbre1); 
  free(arbre2); 
  free(arbre3); 
  free(arbre4); 

}


