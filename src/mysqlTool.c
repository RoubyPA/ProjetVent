/*!
 *	\file 	mysqlTool.c
 *	\date		2016
 *	\author 	Rouby Pierre-Antoine
 * \version 1.0
 *	\brief	Outils pour la gestion de mysql
 *
 */

#include "mysqlTool.h"

/*!
 * \fn 		bool mysqlInit(const char *ip)
 * \brief	Initialisation de la connection mysql.
 *
 * \param	ip du serveur mysql
 * \return 	true or false if failure
 */
bool mysqlInit(const char *ip)
{
	#ifdef DEBUG
	printf("MySQL client version: %s\n", mysql_get_client_info() ) ;
	#endif

	mysql_init(&mysql) ;

/*	Connection a la base de données	*/
	mysql_real_connect(	&mysql,
								ip,
								USER_NAME,
								PASSWORD,
								DATA_BASE,
								0, NULL, 0) ;
	if (&mysql == NULL)
	{
		fprintf(stderr, "Echec de connection a la base\n") ;
		return false ;
	}

	getStationIdByHostName() ;

	#ifdef DEBUG
	printf("Init mysql Ok !\n\n") ;
	#endif

	return true ;
}

/*!
 * \fn 		int isExistOnMysql(const int periode)
 * \brief	Verification de l'existence de l'enregistrement
 *				dans la base de données.
 *
 * \param	periode Periode de l'enregistrement
 * \return 	-1 if mysql error
 *				0 if row don't exist
 *				id row if row exist
 */
int isExistOnMysql(const int periode)
{
	int 			i,
					row_len,
					valueToReturn = 0 ;
	char 			*sql 		= malloc(4096),
	 				*buffer 	= malloc(4096) ;
	MYSQL_RES 	*result ;
	MYSQL_ROW 	row ;

	strcpy(sql, SQL_SELECT) ;
	strcat(sql, idStation) ;
	strcat(sql, " AND periode = ") ;
	sprintf(buffer, "%d", periode) ; /* int to char * */
	strcat(sql, buffer) ;
	strcat(sql, " ;") ;

	#ifdef DEBUG
	printf("Sql requete %s\n", sql) ;
	#endif

/*	Execution de la requete sql	*/
	if (mysql_query(&mysql, sql) )
	{
		fprintf(stderr, "%s\n", mysql_error(&mysql) ) ;
		mysqlCloseConnection() ;
		valueToReturn = -1 ;
	}

/*	Recuperation du retour de la requete sql	*/
	result = mysql_store_result(&mysql) ;
	if (result == NULL)
	{
		fprintf(stderr, "echec mysql_store_result !\n") ;
		mysqlCloseConnection() ;
		valueToReturn = -1 ;
	}

/*	Recuperation du nombre de ligne	*/
	row_len = mysql_num_fields(result) ;

/*	Lecture du resultat ligne par ligne	*/
	while( (row = mysql_fetch_row(result) ) )
	{

		if (atoi(row[1]) == periode)
		{
			#ifdef DEBUG
			for (i = 0 ; i < row_len ; i++)
				printf("%s\t", row[i] ? row[i] : NULL) ;
			printf("\n") ;
			#endif
/*			return id of row */
			valueToReturn = atoi(row[0]) ;
		}

		#ifdef DEBUG
		//printf("%d != %d\t", atoi(row[1]) , periode) ;
		for (i = 0 ; i < row_len ; i++)
		{
			printf("%s\t", row[i] ? row[i] : NULL) ;
		}
		printf("\n") ;
		#endif
	}
	#ifdef DEBUG
	printf("\n") ;
	#endif

	return valueToReturn ;
}

/*!
 * \fn 		int verifValue(const int periode)
 * \brief	Verification de l'enregistrement
 *
 * \param	periode Periode de l'enregistrement
 * \return 	-1 if mysql error
 *				0 if row don't exist
 *				id row if row exist
 */
int verifValue(const int idLocal)
{
	int 			i = 0,
					row_len,
					valueToReturn = 0 ;
	char 			*sql 		= malloc(4096),
	 				*buffer 	= malloc(4096) ;
	MYSQL_RES 	*result ;
	MYSQL_ROW 	row ;

/*	Make sql cmd */
	strcpy(sql, SQL_SELECT) ;
	strcat(sql, idStation) ;

	strcat(sql, " AND periode = ") ;
	sprintf(buffer, "%ld", listDataSqlite[idLocal].date) ; /* int to char * */
	strcat(sql, buffer) ;

	strcat(sql, " AND vitesse = ") ;
	sprintf(buffer, "%d", listDataSqlite[idLocal].vitesse) ; /* long to char * */
	strcat(sql, buffer) ;

	strcat(sql, " AND direction = \'") ;
	strcat(sql, listDataSqlite[idLocal].direction) ;

	strcat(sql, "\' ;") ; /* End of sql commande */

	#ifdef DEBUG
	printf("Sql requete %s\n", sql) ;
	#endif

/*	Execution de la requete sql	*/
	if (mysql_query(&mysql, sql) )
	{
		fprintf(stderr, "%s\n", mysql_error(&mysql) ) ;
		mysqlCloseConnection() ;
		valueToReturn = -1 ;
	}

/*	Recuperation du retour de la requete sql	*/
	result = mysql_store_result(&mysql) ;
	if (result == NULL)
	{
		fprintf(stderr, "echec mysql_store_result !\n") ;
		mysqlCloseConnection() ;
		valueToReturn = -1 ;
	}

/*	Recuperation du nombre de ligne	*/
	row_len = mysql_num_fields(result) ;

/*	Lecture du resultat ligne par ligne	*/
	while( (row = mysql_fetch_row(result) ) )
	{
		if (atoi(row[1]) == listDataSqlite[idLocal].date)
		{
			#ifdef DEBUG
			for (i = 0 ; i < row_len ; i++)
				fprintf(stderr, "%s\t", row[i] ? row[i] : NULL) ;
			printf("\n\n") ;
			#endif
/*			return id of row */
			valueToReturn = atoi(row[0]) ;
		}

		#ifdef DEBUG
		for (i = 0 ; i < row_len ; i++)
		{
			printf("%s\t", row[i] ? row[i] : NULL) ;
		}
		printf("\n") ;
		#endif
	}
	#ifdef DEBUG
	printf("\n") ;
	#endif

	return valueToReturn ;
}


/*!
 * \fn 		bool InsertIntoMysql(int dataIndex)
 * \brief	enregistrement dans la base de données.
 *
 * \param	dataIndex index dans la struct "listDataSqlite"
 * \return 	true or false if error
 */
bool InsertIntoMysql(int dataIndex)
{
	char 	sqlRequestInsert[2048] = "",
			strVitesse[32],
			strDate[32],
			strDirection[32] ;

/*	cast data to string	*/
	sprintf(strVitesse, 		"%d", 		listDataSqlite[dataIndex].vitesse) ;
	sprintf(strDate, 			"%ld", 		listDataSqlite[dataIndex].date) ;
	sprintf(strDirection, 	"\'%s\'", 	listDataSqlite[dataIndex].direction) ;

/*	make sql request	*/
	strcpy(sqlRequestInsert, SQL_INSERT) ;
	strcat(sqlRequestInsert, strVitesse) ;
	strcat(sqlRequestInsert, ", ") ;
	strcat(sqlRequestInsert, strDate) ;
	strcat(sqlRequestInsert, ", ") ;
	strcat(sqlRequestInsert, strDirection) ;
	strcat(sqlRequestInsert, ", ") ;
	strcat(sqlRequestInsert, idStation) ;
	strcat(sqlRequestInsert, ") ;") ;

	#ifdef DEBUG
	printf("Sql request instert %s\n", sqlRequestInsert) ;
	#endif

/*	Execution de la requete sqlRequestInsert	*/
	if (mysql_query(&mysql, sqlRequestInsert) )
	{
		fprintf(stderr, "%s\n", mysql_error(&mysql) ) ;
		mysqlCloseConnection() ;
		return false ;
	}

	return true ;
}

/*!
 * \fn 		void  getStationIdByHostName(void)
 * \brief	Recuperation du non d'hote de la station.
 *
 * \return 	no return
 */
void  getStationIdByHostName(void)
{
	MYSQL_RES 	*result ;
	MYSQL_ROW 	row ;
	char 			*sqlGetId = malloc(2048) ; // Requete sql

	strcpy(sqlGetId, SQL_GET_ID) ;
	strcat(sqlGetId, hostNameStation) ;
	strcat(sqlGetId, "\' ;") ;

	#ifdef DEBUG
	printf("%s\n", sqlGetId) ;
	#endif

/*	Execution de la requete sqlRequestInsert	*/
	if (mysql_query(&mysql, sqlGetId) )
	{
		fprintf(stderr, "%s\n", mysql_error(&mysql) ) ;
		mysqlCloseConnection() ;
		exit(EXIT_FAILURE) ;
	}

/*	Recuperation du retour de la requete sql	*/
	result = mysql_store_result(&mysql) ;
	if (result == NULL)
	{
		fprintf(stderr, "echec mysql_store_result !\n") ;
		mysqlCloseConnection() ;
	}

/*	Lecture du resultat ligne par ligne	*/
	while( (row = mysql_fetch_row(result) ) )
	{
		strcpy(idStation, row[0]) ;
	}
}

/*!
 * \fn 		void mysqlCloseConnection(void)
 * \brief	close connection mysql.
 *
 * \return 	no return
 */
void mysqlCloseConnection(void)
{
	mysql_close(&mysql) ;
}
