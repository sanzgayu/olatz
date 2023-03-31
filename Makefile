# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = projet.cc simulation.cc robot.cc particule.cc message.cc shape.cc
OFILES = $(CXXFILES:.cc=.o)

# Definition de la premiere regle

projet: $(OFILES)
	$(CXX) $(OFILES) -o projet

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ projet

# DO NOT DELETE THIS LINE
projet.o: projet.cc simulation.h shape.h particule.h robot.h constantes.h \
 message.h
simulation.o: simulation.cc shape.h message.h constantes.h particule.h \
 robot.h simulation.h
robot.o: robot.cc message.h robot.h shape.h particule.h constantes.h
particule.o: particule.cc message.h particule.h shape.h constantes.h
message.o: message.cc message.h
shape.o: shape.cc shape.h
