################################################################################
# 		Fichier : 		serveur.makefile														 #
# 		Projet :			Projet vent																 #
#		Date edition :	2016																		 #
#		Créer par :		Rouby Pierre-Antoine													 #
################################################################################

################################################################################
# Init																								 #
################################################################################

DEBUG=yes
CC=gcc
dox=doxygen
binPath=./bin/
binPathServ=./bin/server/
binPath=./bin/
srcPath=./src/
objPath=./obj/
docPath=./doc/
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

# make all programme for server
all : mkrep comparaison2db

################################################################################
# Compilation instruction																		 #
################################################################################

# Comparaison2db
comparaison2db : $(objPath)mysqlTool.o $(objPath)sqliteTool.o $(objPath)main.o
	$(CC) $(objPath)main.o $(objPath)sqliteTool.o $(objPath)mysqlTool.o \
	-lmysqlclient -lsqlite3 -o $(binPathServ)comparaison2db

$(objPath)main.o : $(srcPath)main.c $(srcPath)main.h
	$(CC) -c $(srcPath)main.c $(CFLAGS) $(DFLAGS) -o $(objPath)main.o

$(objPath)sqliteTool.o : $(srcPath)sqliteTool.c $(srcPath)sqliteTool.h
	$(CC) -c $(srcPath)sqliteTool.c $(CFLAGS) $(DFLAGS) -o $(objPath)sqliteTool.o

$(objPath)mysqlTool.o : $(srcPath)mysqlTool.c $(srcPath)mysqlTool.h
	$(CC) -c $(srcPath)mysqlTool.c $(CFLAGS) $(DFLAGS) -o $(objPath)mysqlTool.o


################################################################################
# Directorie																						 #
################################################################################
mkrep :
	mkdir -p bin/server
	mkdir -p obj

# rmdir
rmdir :
	rm -r $(objPath)
	rm -r $(binPathServ)


################################################################################
# Install																							 #
################################################################################
install :
	mkdir $(installServDir)
	# Copy programme
	cp $(binPathServ)comparaison2db


################################################################################
# Doc																									 #
################################################################################
doc :
	$(dox) doxyConfig


################################################################################
# Clean 																								 #
################################################################################
# cleandoc
cleandoc :
	rm -rf $(docPath)

# Clean
clean :
	rm -rvf $(objPath)

cleanhard :
	rm -rvf $(objPath)
	rm -rvf $(binPathServ)
