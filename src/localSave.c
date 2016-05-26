/**
 *	\file 	localSave.c
 *	\date		2016
 *	\author 	Rouby Pierre-Antoine
 * \version 1.0
 *	\brief 	Sauvegarde les donner envoier sur la base de données local
 *				(sqlit3)
 */

#include <stdio.h>
#include <stdlib.h>
/*	lib sqlite3 */
#include <sqlite3.h>
/*	to use strcat() */
#include <string.h>

#define DATA_BASE       "data/local.sqlite"
#define TABLES          "Informations_vents"
#define CHAMP_ID        "idInformations_vents"
#define CHAMP_PERIODE   "Periode"
#define CHAMP_VITESSE   "Vitesse"
#define CHAMP_DIRECTION "Direction"
#define SQL_DELETE		"DELETE FROM 'Informations_vents' WHERE Periode < "

/**
 * \fn 		int main(int argc, char **argv)
 *	\brief	Fonction principale, enregister les valeur envoier
 *				dans la base de données sqlite.
 *
 * \param	argc Nombre d'agrument envoier au programme
 * \param	argv Argument envoier au programme
 * \return 	EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char* argv[])
{
/* Base de données SQLite   */
	sqlite3 			*db ;
	int 				returnValue ;
/* Variable de recuperation des message d'erreurs   */
	char 				*errMsg 	   = 0 ;
/* Requete sql   */
	char 				*sql 			= malloc(1024) ;
/* Variables des données à enregister  */
	char				*vitesse 	= malloc(32) ;
	char 				*direction 	= malloc(32) ;
	char				*periode 	= malloc(32) ;
	unsigned long 	longDate		= 0 ;

/*	Verification des arguments */
	if (argc < 4)
	{
		fprintf(	stderr, 
					"Usage : %s [vitesse] [direction] [periode]\n",
					argv[0] ) ;
		exit( EXIT_FAILURE ) ;
	}

/* Lecture des données   */
	vitesse 		= argv[1] ;
	direction 	= argv[2] ;
	periode		= argv[3] ;
	longDate 	= atol(periode) ;

/*	Periode - 8930	*/
	longDate = longDate - 8930 ;

/*	Ouverture de la base de données SQLite */
	returnValue = sqlite3_open(DATA_BASE, &db) ;
	if (returnValue)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db)) ;
      exit( EXIT_FAILURE ) ;
   }

/* Creation de la requette SQL   */
	sprintf(	sql,
				"INSERT INTO %s (%s,%s,%s) VALUES (\'%s\', \'%s\', \'%s\');",
				TABLES, CHAMP_VITESSE, CHAMP_DIRECTION, CHAMP_PERIODE,
            vitesse, direction, periode ) ;

/*	add delete sql request	*/
	strcat(sql, SQL_DELETE) ;
	sprintf(periode, "%ld ;", longDate) ;
	strcat(sql, periode) ;

	#ifdef DEBUG
	printf("%s\n", sql) ;
	#endif

/* Execution de la requete SQL   */
/*	HACK no Callback fonction 		*/
	returnValue = sqlite3_exec(db,
										sql,
										NULL,
										(void*)NULL,
										&errMsg);
	if (returnValue != SQLITE_OK)
	{
      fprintf(stderr, "SQLite error: %s\n", errMsg);
      sqlite3_free(errMsg);
  	}

/*	Fermeture de la base de données  */
	sqlite3_close(db) ;

	return EXIT_SUCCESS ;
}
