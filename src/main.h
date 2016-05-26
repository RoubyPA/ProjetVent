/*!
 *	\file 	main.h
 *	\date		2016
 *	\author 	Rouby Pierre-Antoine
 * \version 1.0
 *	\brief	Main file Header
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
/* Structure   */
#include "structure.h"

/* Usage */
#define USAGE "Usage : comparaison2db [sqlite db] [hostName] \
[ip (mysql serveur)] "

/*	Variable globale	*/
/* Definition du tableau de structure */
DataStruct  listDataSqlite    [MAX_DATA_NUMBER] ;
char        hostNameStation   [64] ;

/*	Prototype	*/
bool init(int argc, char **argv) ;
