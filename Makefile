#VARIABLES:
#----------
COMP=gcc
EDL=gcc
EXE=TpMultiThread
#Flags:
CPPFLAGS=-g -O3 -Wall
EDLFLAGS=
#Paths:
INCPATH=#-I /home/samuel/Documents/TpMultiTache
LIBPATH=#-L /home/samuel/Documents/TpMultiTache
#Affichage:
ECHO=@echo #pour le mode silencieux
#Suppression:
RM=@rm
RMFLAGS=-f
#
INT=Tp_multiThread.h#Mere.h Clavier.h Entree.h Sortie.h
REAL=$(INT:.h=.cpp)
OBJ=$(INT:.h=.o)
LIBS=-lpthread -lm#-ltp -lncurses -ltcl
#Clean:
CLEAN=clean
.PHONY:$(CLEAN)


#Règles:
#-------

$(EXE): $(OBJ)
	$(ECHO) + EDL de $(EXE)
	$(EDL) -o $(EXE) $(OBJ) $(EDLFLAGS) $(LIBPATH) $(LIBS)


#Patterns:
#---------

%.o : %.c
	$(ECHO) + Compliation de $<
	$(COMP) -c $(CPPFLAGS) $(INCPATH) $<
Tp_multiThread : Tp_multiThread.c

#Nettoyage:
#----------

$(CLEAN):
	$(ECHO) --- NETTOYAGE ---
	$(RM) $(RMFLAGS) $(OBJ) #$(EXE) #Core 
