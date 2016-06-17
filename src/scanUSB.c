/*!
 *	\file 	scanUSB.c
 *	\date		2016
 *	\author 	Rouby Pierre-Antoine
 * \version 1.0
 *	\brief	Repère quand une clef USB est brancher
 *          et lance l'autostart.pl
 *
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#define REP_DEV "/dev"
#define CMD "perl /home/pi/ProjetVent/autostart.pl"
#define CMD_MOUNT "mount /dev/sda1"
#define CMD_UMOUNT "umount /dev/sda1"

void killDaemon(int signum) ;

/* Vraiable globale  */
DIR *repDev = NULL ;

/*!
 * \fn 		int main(int argc, char **argv)
 *	\brief	Fonction principale.
 *
 * \param	argc Nombre d'agrument envoier au programme (not use)
 * \param	argv Argument envoier au programme (not use)
 * \return 	EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char **argv)
{
   int      signum ;
   time_t   timeExecuted ;
   bool     executed             = false ;
   struct   dirent  *fileList    = NULL ;

   for(signum = 1 ; signum <= NSIG ; signum++)
	{
		if(signal(signum, killDaemon) == SIG_ERR)
		{
/*			Gestion de l'erreur */
		}
	}

   repDev = opendir(REP_DEV) ;
   if (repDev == NULL)
   {
      perror("Error ") ;
      exit(EXIT_FAILURE) ;
   }

   while(1)
   {
      while((fileList = readdir(repDev)) != NULL)
      {
      /* if (strstr(fileList->d_name, "sdb1") != NULL)*/
         if (strncmp(fileList->d_name, "sda1", 4) == 0)
         {
            #ifdef DEBUG
            printf("\t > %s\n", fileList->d_name) ;
            #endif

            if (!executed)
            {
               timeExecuted = time(NULL) ;
/*             Mount USB	*/
              	system(CMD_MOUNT) ;
				  	sleep(5) ;

               system(CMD) ;

/*					Umount USB	*/
					system(CMD_UMOUNT) ;
               executed = !executed ;
            }
         }
/*       reinit (bool)executed */
         if (executed == true && time(NULL) >= (timeExecuted+10) )
         {
            executed = false ;
         }
      }
      sleep(1) ;
/*    return to beginning of fileList */
      seekdir(repDev, 0) ;
   }

   return EXIT_SUCCESS ;
}

/*!
 * \fn 		void killDaemon(int signum)
 *	\brief	Interseption de signal & kill processus
 *
 * \param	signum Numero du Signal
 * \return 	EXIT_FAILURE
 */
void killDaemon(int signum)
{
   if (signum != 17)
   {
      closedir(repDev) ;
      exit(EXIT_FAILURE) ;
   }
}
