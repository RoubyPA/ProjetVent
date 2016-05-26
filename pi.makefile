################################################################################
# 		Fichier : 		pi.makefile																 #
# 		Projet :			Projet vent																 #
#		Date edition :	2016																		 #
#		Créer par :		Rouby Pierre-Antoine													 #
################################################################################

################################################################################
# init																								 #
################################################################################

DEBUG=yes
CC=gcc
dox=doxygen
binPath=./bin/
binPathPi=./bin/pi/
binPath=./bin/
srcPath=./src/
objPath=./obj/
docPath=./doc/
installPiDir=/home/pi/ProjetVent/

# DEBUG
ifeq ($(DEBUG),yes)
	CFLAGS=-Wall -pedantic
	LDFLAGS=
	DFLAGS=-DDEBUG
else
	CFLAGS=-W
	LDFLAGS=
	DFLAGS=
endif

# make programme for rpi
all : localSave scanUSB

################################################################################
# Compilation instruction																		 #
################################################################################

# localSave
localSave : $(srcPath)localSave.c
	$(CC) -l sqlite3 $(srcPath)localSave.c $(CFLAGS) $(DFLAGS) \
	-o $(binPathPi)localSave

# scanUSB
scanUSB : $(srcPath)scanUSB.c
	$(CC) $(srcPath)scanUSB.c $(CFLAGS) $(DFLAGS) -o $(binPathPi)scanUSB

################################################################################
# Install																							 #
################################################################################

install : rpi
	mkdir $(installPiDir)
	# Copy programme
	cp $(binPathPi)autostart.pl $(installPiDir)autostart.pl
	cp $(binPathPi)localSave $(installPiDir)localSave
	cp $(binPathPi)scanUSB $(installPiDir)scanUSB
	# make scanUSB a daemon
	ln -s $(installPiDir)scanUSB /etc/init.d/scanUSB
	echo "#Config ProjetVent" >> /etc/fstab
	cat fstab | xargs echo >> /etc/fstab
	sleep 2
	update-rc.d -f scanUSB default
	# cp database
	mkdir $(installPiDir)data/
	cp data/local.sqlite $(installPiDir)data/local.sqlite

################################################################################
# Doc																									 #
################################################################################
doc :
	$(dox) doxyConfig

################################################################################
# Clean 																								 #
################################################################################
cleandoc :
	rm -rf $(docPath)
