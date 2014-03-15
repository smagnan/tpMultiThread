#VARIABLES:
#----------
COMP=gcc
EDL=gcc
EXE=TpmThread
#Flags:
CPPFLAGS=-g
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
INT=Tp_multThread.h#Mere.h Clavier.h Entree.h Sortie.h
REAL=$(INT:.h=.cpp)
OBJ=$(INT:.h=.o)
LIBS=-lm -lpThread#-ltp -lncurses -ltcl
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
Tp_multThread : Tp_multThread.c

#Nettoyage:
#----------

$(CLEAN):
	$(ECHO) --- NETTOYAGE ---
	$(RM) $(RMFLAGS) $(OBJ) $(EXE) #Core 
