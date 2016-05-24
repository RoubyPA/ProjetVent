################################################################################
# 		Fichier : 		makefile																	 #
# 		Projet :			Projet vent																 #
#		Date edition :	2016																		 #
#		Créer par :		Rouby Pierre-Antoine													 #
################################################################################

DEBUG=yes
CC=gcc
dox=doxygen
binPath=./bin/
binPathPi=./bin/pi/
binPathServ=./bin/server/
binPath=./bin/
srcPath=./src/
objPath=./obj/
docPath=./doc/
installPiDir=/home/pi/ProjetVent/
installServDir=/home/adminvent/ProjetVent/

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

# make all programme
all : mkrep comparaison2db localSave scanUSB

# make programme for server
server : rmdir mkrep comparaison2db

# make programme for rpi
rpi : rmdir mkrep localSave scanUSB

################################################################################
# Compilation instruction																		 #
################################################################################

# Comparaison2db
comparaison2db : $(objPath)mysqlTool.o $(objPath)sqliteTool.o $(objPath)main.o
	$(CC) $(objPath)main.o $(objPath)sqliteTool.o $(objPath)mysqlTool.o \
	-lmysqlclient -lsqlite3 -o $(binPathServ)comparaison2db

$(objPath)main.o : $(srcPath)main.c
	$(CC) -c $(srcPath)main.c $(CFLAGS) $(DFLAGS) -o $(objPath)main.o

$(objPath)sqliteTool.o : $(srcPath)sqliteTool.c
	$(CC) -c $(srcPath)sqliteTool.c $(CFLAGS) $(DFLAGS) -o $(objPath)sqliteTool.o

$(objPath)mysqlTool.o : $(srcPath)mysqlTool.c
	$(CC) -c $(srcPath)mysqlTool.c $(CFLAGS) $(DFLAGS) -o $(objPath)mysqlTool.o

# localSave
localSave : $(srcPath)localSave.c
	$(CC) -l sqlite3 $(srcPath)localSave.c $(CFLAGS) $(DFLAGS) \
	-o $(binPathPi)localSave

# scanUSB
scanUSB : $(srcPath)scanUSB.c
	$(CC) $(srcPath)scanUSB.c $(CFLAGS) $(DFLAGS) -o $(binPathPi)scanUSB

################################################################################
# Directorie																						 #
################################################################################
mkrep :
	mkdir bin/server
	mkdir obj

# rmdir
rmdir :
	rm -r $(objPath)
	rm -r $(binPathServ)


################################################################################
# Install																							 #
################################################################################

installPi : rpi
	mkdir $(installPiDir)
	# Copy programme
	cp $(binPathPi)autostart.pl $(installPiDir)autostart.pl
	cp $(binPathPi)localSave $(installPiDir)localSave
	cp $(binPathPi)scanUSB $(installPiDir)scanUSB
	# make scanUSB a daemon
	ln -s $(installPiDir)scanUSB /etc/init.d/scanUSB
	update-rc.d scanUSB default
	# cp database
	mkdir $(installPiDir)data/
	cp data/local.sqlite $(installPiDir)data/local.sqlite

# /home/adminvent/ProjetVent
installServer : clean
	mkdir $(installServDir)
	# Copy programme
	cp $(binPathServ)comparaison2db


# Doc
doc :
	$(dox) doxyConfig

# cleandoc
cleandoc :
	rm -rf $(docPath)

# Clean
clean :
	rm -vf $(objPath)*.o
