
/* placer ici vos fonctions */
int RechercheQuinetSchyns(char* NomFichier,int Reference ,struct Record *UnRecord)
{
  FILE *file ;

  printf("\nLancement du programme de recherche");
  printf("\necrit par Quinet Romain et Schyns Andy\n");
  file = fopen(NomFichier,"r") ;

  /*Si le fichier n'existe pas*/
  if ( file == NULL )
  {
    fprintf(stderr,"Echec Ouverture\n") ;
    printf("appuyer sur une touche pour retourner au menu");
    getchar();
    return 0;
  }
  //Si le fichier existe et peut etre ouvert*/
  else
    fprintf(stderr,"Ouverture reussie \n") ;

  /*Lecture du 1er record*/
  fread(UnRecord,sizeof(struct Record),1,file) ;

  /*Tant qu'on n'est pas à la fin du fichier ou que la référence n'est pas la bonne*/
  while (!feof(file) && UnRecord->Reference != Reference )
  {
    fread(UnRecord,sizeof(struct Record),1,file) ;
  } ;

  /*Si on s'est arreté avant la fin du fichier, on a trouvé une reference correspondante*/
  if (!feof(file))
  {
    fclose(file);
    return 1;
  }

  fclose(file) ;
  return 0;
}
