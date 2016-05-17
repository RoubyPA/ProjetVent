/*!
 *	\file 	sqliteTool.c
 *	\date		2016
 *	\author 	Rouby Pierre-Antoine
 * \version 1.0
 *	\brief	Outils pour la gestion de sqlite
 *
 */

#include "sqliteTool.h"

/*!
 * \fn 		bool sqliteInit(const char *dataBaseName)
 * \brief	Initialisation de la base de données sqlite.
 *
 * \param	Nom du fichier de base de données
 * \return 	true or false if error
 */
bool sqliteInit(const char *dataBaseName)
{
	int returnValue = 0 ;

/*	Open sqlite db	*/
	if (sqlite3_open(dataBaseName, &db) )
	{
		fprintf(stderr, "Can't open dataBase %s\n", dataBaseName) ;
		return false ;
	}

/* exec sql SELECT FROM	*/
	returnValue = sqlite3_exec(db,
										SQL_SELECT_REQUEST,
										sqliteCallback,
										(void*)data,
										&zErrMsg) ;
	if (returnValue != SQLITE_OK)
	{
		fprintf(stderr, "SQL SELECT error : %s\n", zErrMsg) ;
		sqliteClose() ;
		return false ;
	}

/*	last data id = NULL	*/
	listDataSqlite[dataIndex].id = 0 ;

	sqliteClose() ;

	#ifdef DEBUG
	printf("Init sqlite Ok !\n\n") ;
	#endif

	return true ;
}

/*!
 * \fn 		static int sqliteCallback(void *data, int idMax, char **value, char **champ)
 * \brief	Foncton de Callback pour la recuperation des valeur.
 *
 * \param	data Données optionel envoie a la fonction
 * \param	idMax Nombre de données
 * \param	value Valeur envoier dans un tableau de caratere
 * \param	champ Valeur des champ de la base de donnée dans un tableau de caratere
 * \return 	EXIT_SUCCESS
 */
static int sqliteCallback(void *data, int idMax, char **value, char **champ)
{
	int i ;

/*	Lecture de la ligne
	+ enregistrement des données dans la structure	*/
	for (i = 0 ; i<idMax ; i++)
	{
		if (strcmp(champ[i], CHAMP_ID) == 0)
			listDataSqlite[dataIndex].id = atoi(value[i]) ;
		else if (strcmp(champ[i], CHAMP_PERIODE) == 0)
			listDataSqlite[dataIndex].date = atol(value[i]) ;
		else if (strcmp(champ[i], CHAMP_VITESSE) == 0)
			listDataSqlite[dataIndex].vitesse = atoi(value[i]) ;
		else if (strcmp(champ[i], CHAMP_DIRECTION) == 0)
			strcpy(listDataSqlite[dataIndex].direction, value[i]) ;
		else
			fprintf(stderr, "Error champ inconnu\n") ;

		#ifdef DEBUG
		printf("%s\t%s\n", champ[i], value[i]);
		#endif
	}

/*	HACK Best solution ? */
/*	init next struct data	*/
	listDataSqlite[dataIndex+1].id 			= 0 ;
	listDataSqlite[dataIndex+1].date 		= 0 ;
	listDataSqlite[dataIndex+1].vitesse 	= 0 ;
	//listDataSqlite[dataIndex+1].direction 	= NULL ;

	dataIndex++ ;

	return EXIT_SUCCESS ;
}

/*!
 * \fn 		bool readHostName(const char *path, char *hostName)
 * \brief	Foncton de recuperation du nom d'hote de la station
 *
 * \param	path Chemin du fichier hostName
 * \param	hostName Tableau de caratere pour la recuperation du nom de l'hote
 * \return 	EXIT_SUCCESS
 */
bool readHostName(const char *path, char *hostName)
{
	FILE *fichierHostName = NULL ;

	fichierHostName = fopen(path, "r") ;
	if(fichierHostName == NULL)
	{
		fprintf(stderr, "Le ficher %s ne peut pas etre ouvert\n", path) ;
		return false ;
	}

	fscanf(fichierHostName, "%s", hostNameStation) ;
	fclose(fichierHostName) ;

	#ifdef DEBUG
	printf("%s\n", hostName) ;
	#endif

	return true ;
}

/*!
 * \fn 		void sqliteClose(void)
 * \brief	Foncton de fermeture de la base de données
 *
 * \return 	no return
 */
void sqliteClose(void)
{
	sqlite3_free(zErrMsg) ;
	sqlite3_close(db) ;
}
