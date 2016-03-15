/******************************************
  Herman Vanstapel
  2014 Basé sur Fichiers
*******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "lib.c"

void DelNewLine(char *Chaine)
{
 Chaine[strlen(Chaine)-1] = 0 ;
}

char ReadChar()
{
 char Tampon[80] ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 return Tampon[0] ;
}

void MonPrintf(char* tempo, int espace,int taille )
{
 int Count ;
 printf("%s",tempo) ;
 Count = espace-taille ;
 while ( Count>0 )
 {
       printf(" ");
       Count-- ;
 }
}


void SaiSieRecord(struct Record *UnRecord )
{
 char Tampon[80] ;
 printf("Saisie Reference :") ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 UnRecord -> Reference = atoi(Tampon) ;
 printf("Saisie Libellé :") ;
 fgets(UnRecord->Produit,sizeof UnRecord->Produit,stdin ) ;
 printf("Saisie Marque du stockage :") ;
 fgets(UnRecord->Stockage,sizeof UnRecord->Stockage,stdin ) ;
 printf("Saisie Quantite :") ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 UnRecord -> Quantite = atoi(Tampon) ;

 DelNewLine(UnRecord->Produit);
 DelNewLine(UnRecord->Stockage);

 printf("%d\n",UnRecord->Reference);
 printf("%s\n",UnRecord->Produit);
 printf("%s\n",UnRecord->Stockage);
 printf("%d\n",UnRecord->Quantite);
 printf("-----------------------\n") ;
 return ;
}



void CreationAjoutFichier(char *NomFichier,struct Record *UnRecord )
{
 FILE *sortie ;
 char Redo ;
 int nbr ;

 sortie = fopen(NomFichier,"a") ; /* Si le fichier existe, on le cree sinon on ajoute */
 if ( sortie == NULL )
    {
     fprintf(stderr,"Echec Ouverture\n") ;
     exit(0) ;
    }
 else
    fprintf(stderr,"Ouverture reussie \n") ;
 setvbuf(sortie, (char *)NULL, _IOLBF, 0) ; /* ceci supprime la bufferisation */

  printf("Position actuelle dans le fichier %ld\n",ftell(sortie)) ;
  nbr = fwrite(UnRecord,sizeof(struct Record),1,sortie) ;
  fflush(sortie) ;
 fclose(sortie) ;
}

void AfficheRecord(struct Record *UnRecord)
{
 char Tampon[80] ;
 sprintf(Tampon,"%d",UnRecord->Reference ) ;  MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%s ",UnRecord->Produit) ;    MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon," %s",UnRecord->Stockage) ; MonPrintf(Tampon,20,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UnRecord->Quantite) ; MonPrintf(Tampon,4,strlen(Tampon)) ;
 printf("\n") ;
}

void AfficheFacture(struct Facture *UneFacture)
{
 char Tampon[80] ;
 sprintf(Tampon,"%d",UneFacture->NumeroFacturation ) ; MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%s",UneFacture->NomClient) ; MonPrintf(Tampon,60,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UneFacture->Quantite) ; MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UneFacture->Reference) ; MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UneFacture->DateFacturation ) ; MonPrintf(Tampon,8,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UneFacture->DateLivraison ) ; MonPrintf(Tampon,8,strlen(Tampon)) ;
 printf("\n") ;
}

void Listing(char *NomFichier)
{
 struct Record UnRecord ;
 FILE *sortie ;
 char Tampon[80] ;
 int  Numero ;
 int  nbr ;

 sortie = fopen(NomFichier,"r") ; /* Si le fichier existe, on le cree sinon on ajoute */
 if ( sortie == NULL )
    {
     fprintf(stderr,"Echec Ouverture\n") ;
     exit(0) ;
    }
 else
    fprintf(stderr,"Ouverture reussie \n") ;


 nbr = fread(&UnRecord,sizeof(UnRecord),1,sortie) ;

 while ( !feof(sortie) )
 {
  fprintf(stderr,"Record lu %d et Position actuelle dans le fichier %ld\n",nbr,ftell(sortie)) ;
  AfficheRecord( &UnRecord) ;
  nbr = fread(&UnRecord,sizeof(UnRecord),1,sortie) ;
 }
 fclose(sortie) ;
}

void ListingFacture(char *NomFichier)
{
 struct Facture UneFacture ;
 FILE *sortie ;
 char Tampon[80] ;
 int  Numero ;
 int  nbr ;

 sortie = fopen(NomFichier,"r") ; /* Si le fichier existe, on le cree sinon on ajoute */
 if ( sortie == NULL )
    {
     fprintf(stderr,"Echec Ouverture\n") ;
     exit(0) ;
    }
 else
    fprintf(stderr,"Ouverture reussie \n") ;


 nbr = fread(&UneFacture,sizeof(struct Facture),1,sortie) ;

 while ( !feof(sortie) )
 {
  fprintf(stderr,"Record lu %d et Position actuelle dans le fichier %ld\n",nbr,ftell(sortie)) ;
  AfficheFacture( &UneFacture) ;
  nbr = fread(&UneFacture,sizeof(struct Facture),1,sortie) ;
 }
 fclose(sortie) ;
}


main()
{
 char Choix ;
 char Tampon[80] ;
 int res ;
 struct Record UnRecord ;
 int Numero ;
 int rechercheReference;
 while(1)
 {
  fflush(stdin);
  printf("----------------------\n") ;
  printf("1) Ajout              \n") ;
  printf("2) Stock              \n") ;
  printf("3) Recherche          \n") ;
  printf("4) Achat              \n") ;
  printf("5) Factures           \n") ;
  printf("6) exit               \n") ;
  printf("----------------------\n") ;
  Choix=ReadChar() ;
  switch(Choix)
  {
   case '1':
   {
    struct Record UnRecord ;
    FILE *sortie ;
    char Redo ;

    Redo='y' ;
    while ( Redo=='Y' || Redo=='y')
    {
      SaiSieRecord(&UnRecord ) ;
      CreationAjoutFichier("Stock",&UnRecord) ;
      printf("Encoder un autre (Y/N) ?") ;
      Redo=ReadChar() ;
    }

    break ;
   }
   case '2':
   {
     Listing("Stock") ;
     break ;
   }

   case '3':
   {
     printf("\nEntrez la reference a rechercher: ");
     scanf("%d", &rechercheReference);

     if(RechercheQuinetSchyns("Stock",rechercheReference, &UnRecord))
     {
       printf("\nUn record trouve!\n=================\n\n");
       AfficheRecord(&UnRecord) ;
     }
     break;
   }

   case '5':
   {
     ListingFacture("Facture") ;
	   break ;
   }
   case '6': exit(0) ;
  }
 }
}
