/*!
 *	\file 	structure.h
 *	\date		2016
 *	\author 	Rouby Pierre-Antoine
 * \version 1.0
 *	\brief	Definition structure
 *
 */

#define MAX_DATA_NUMBER 10000

/*!
 *	\struct 	DataStruct
 * \typedef DataStruct
 * \brief	Permet stocker les donnees extraite de la base sqlite.
 */
typedef struct DataStruct DataStruct ;
struct DataStruct
{
	int 				id ;
	unsigned long 	date ;
	unsigned int 	vitesse ;
	char 				direction[4] ;
} ;
