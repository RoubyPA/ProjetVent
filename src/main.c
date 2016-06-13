/*!
 *	\file 	main.c
 *	\date		2016
 *	\author 	Rouby Pierre-Antoine
 * \version 1.0
 *	\brief	Main file
 *
 */

#include "main.h"

/*!
 * \fn 		int main(int argc, char **argv)
 *	\brief	Fonction principale.
 *
 * \param	argc Nombre d'agrument envoier au programme
 * \param	argv Argument envoier au programme
 * \return 	EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char **argv)
{
	int 	dataIndex = 0 ;
	int 	returnValue,
			randValue ;

/*	Verification des argument	*/
	if (argc < 4)
	{
		fprintf(stderr, "%s\n", USAGE) ;
		exit(EXIT_FAILURE) ;
	}

/*	Initialisation des connection	*/
	if (!init(argc, argv))
	{
		fprintf(stderr, "Init error\n") ;
		exit(EXIT_FAILURE) ;
	}

/*	Random seed 	*/
	srand(time(NULL)) ;

/*	Verification de l'existence de toute les données dans la base mysql	*/
	while(listDataSqlite[dataIndex].id != 0)
	{
		returnValue = isExistOnMysql(listDataSqlite[dataIndex].date) ;
		if (returnValue < 0)
		{
/*			if ERROR SQL	*/
			fprintf(stderr, "Mysql error !\n") ;
			exit(EXIT_FAILURE) ;
		}
		else if(returnValue == 0)
		{
/*			if not exist	*/
			fprintf(	stderr,
						"Data %d not exist on mysql database\n",
	 					listDataSqlite[dataIndex].id) ;
		 	InsertIntoMysql(dataIndex) ;
		}
		else
		{
/*			if exist	*/
/*				returnValue = id */
			#ifdef DEBUG
			printf(	"\nData %d exist on mysql database at id : %d\n",
						listDataSqlite[dataIndex].id, returnValue) ;
			#endif

/* 		Verification des valeur */
			randValue = (rand() % 100) ;
			if (randValue < 2)
			{
				returnValue = verifValue(dataIndex) ;
				if (returnValue < 0)
				{
/*					if ERROR SQL	*/
					fprintf(stderr, "Mysql error !\n") ;
					exit(EXIT_FAILURE) ;
				}
				else if (returnValue == 0)
				{
/*					not fond ! */
					fprintf(	stderr,
								"ERROR in value for id = %d !\n",
								listDataSqlite[dataIndex].id) ;
				}
				else
				{
					#ifdef DEBUG
					printf(	"\nData %d exist with no error on mysql database \
at id : %d\n",
								listDataSqlite[dataIndex].id, returnValue) ;
					#endif
				}
			}
		}

		dataIndex++ ;
	}

	return EXIT_SUCCESS ;
}


/*!
 * \fn 		bool init(int argc, char **argv)
 * \brief	Initialisation des connections sqlite et mysql
 *
 * \param	argc Nombre d'agrument envoier au programme
 * \param	argv Argument envoier au programme
 * \return 	true or false if failure
 */
bool init(int argc, char **argv)
{
/*	Recuperation des arguments	*/
	char 	*sqliteDb		= argv[1] ;
	char 	*hostNamePath 	= argv[2] ;
	char	*ipMysql			= argv[3] ;

/*	Recuperation du nom de la station meteo a partir du fichier hostname	*/
	if(!readHostName(hostNamePath, hostNameStation) )
	{
		fprintf(stderr, "HostName non valide\n") ;
		return false ;
	}

	#ifdef DEBUG
	printf("hostname = %s\n", hostNameStation);
	#endif

/*	Init sqlite connection	*/
	if(!sqliteInit(sqliteDb) )
		return false ;

/*	Init mysql connection	*/
	if(!mysqlInit(ipMysql) )
		return false ;

	return true ;
}
