# 		Fichier : 		makefile
# 		Projet :			Projet vent
#		Date edition :	2016
#		Créer par :		Rouby Pierre-Antoine

DFLAG=
#-DDEBUG

all : comparaison2db localSave scanUSB

# Comparaison2db
comparaison2db : mysqlTool.o sqliteTool.o main.o
	gcc main.o sqliteTool.o mysqlTool.o -lmysqlclient -lsqlite3 -o comparaison2db

main.o : src/main.c
	gcc -Wall -c src/main.c $(DFLAG) -o main.o

sqliteTool.o : src/sqliteTool.c
	gcc -Wall -c src/sqliteTool.c $(DFLAG) -o sqliteTool.o

mysqlTool.o : src/mysqlTool.c
	gcc -Wall -c src/mysqlTool.c $(DFLAG) -o mysqlTool.o

# localSave
localSave : src/localSave.c
	gcc -Wall -l sqlite3 src/localSave.c -o localSave

# localSave
scanUSB : src/scanUSB.c
	gcc -Wall src/scanUSB.c -o scanUSB

# Install
install : all clean

# Doc
doc :
	doxygen doxyConfig

# cleandoc
cleandoc :
	rm -rf ./doc/

# Clean
clean :
	rm -vf *.o
