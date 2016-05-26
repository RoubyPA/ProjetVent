/*!
 *	\file 	sqliteTool.h
 *	\date		2016
 *	\author 	Rouby Pierre-Antoine
 * \version 1.0
 *	\brief	Outils pour la gestion de sqlite
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/* lib sqlite3 */
#include <sqlite3.h>
/*	Structure	*/
#include "structure.h"
/*	SQLite arg	*/
#define DATA_BASE          "local.dataBase.sqlite"
#define TABLES             "Informations_vents"
#define CHAMP_ID           "idInformations_vents"
#define CHAMP_PERIODE      "Periode"
#define CHAMP_VITESSE      "Vitesse"
#define CHAMP_DIRECTION    "Direction"
#define SQL_SELECT_REQUEST "SELECT * FROM Informations_vents ;"

/*	Variable globale	*/
int			dataIndex 	= 0 ;
char			*zErrMsg		= 0 ;
const char  *data 		= "sqliteCallback fonction call" ;
sqlite3		*db ;

/* Variable extern   */
/* Recuperation du tableau de structure definie dans le main.h */
extern		DataStruct   listDataSqlite    [MAX_DATA_NUMBER] ;
extern      char         hostNameStation   [64] ;

/*	Prototype	*/
bool 			sqliteInit		(const char *dataBaseName) ;
static int 	sqliteCallback	(void *data, int idMax, char **value, char **champ) ;
void        sqliteClose    (void) ;
bool        readHostName   (const char *path, char *hostName) ;
