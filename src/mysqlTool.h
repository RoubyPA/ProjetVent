/*!
 *	\file 	mysqlTool.h
 *	\date		2016
 *	\author 	Rouby Pierre-Antoine
 * \version 1.0
 *	\brief	Outils pour la gestion de mysql
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/*	lib mysql	*/
#include <mysql/mysql.h>
/* Structure   */
#include "structure.h"
/*	MySQL arg	*/
#define USER_NAME       "root"
#define PASSWORD        "rootdb"
#define DATA_BASE       "donnees_meteo"
#define TABLE_INFO      "Informations_vents"
#define TABLE_STATION   "Station(s)"
#define SQL_SELECT      "SELECT * FROM Informations_vents WHERE Station_idStation = "
#define SQL_INSERT      "INSERT INTO Informations_vents (Vitesse, Periode, Direction, Station_idStation) VALUES ("
#define SQL_GET_ID      "SELECT idStation from `Station(s)` WHERE Nom = \'"

/* Variable globale	*/
MYSQL	   mysql ;
char     idStation[16] ;
/* Variable extern   */
extern   DataStruct  listDataSqlite    [MAX_DATA_NUMBER] ; // Recuperation du tableau de structure definie dans le main.h
extern   char        hostNameStation   [64] ;

/*	Prototype	*/
bool  mysqlInit             (const char *ip) ;
int   isExistOnMysql        (const int periode) ;
int   verifValue            (const int idLocal) ;
bool  InsertIntoMysql       (int dataIndex) ;
void  getStationIdByHostName(void) ;
void  mysqlCloseConnection  (void) ;
