CPP=g++
FLAGS= -std=c++11 -g -Wall

all: solucionExacta solucionGreedyConstructiva tiempoExacta

solucionGreedyConstructiva: SolucionGreedyConstructiva.cpp ResolverGreedyConstructiva.cpp ResolverGreedyConstructiva.h
	$(CPP) $(FLAGS) -o  $@ ResolverGreedyConstructiva.cpp $<

solucionExacta: SolucionExacta.cpp ResolverExacta.cpp ResolverExacta.h
	$(CPP) $(FLAGS) -o  $@ ResolverExacta.cpp $<

tiempoExacta: TiempoExacta.cpp  ResolverExacta.cpp ResolverExacta.h
	$(CPP) $(FLAGS) -o  $@  ResolverExacta.cpp $<

%.o: %.cpp
	$(CPP) $(FLAGS) -c -o $@ $<

clean:
	rm -f *.o
	rm -f solucionExacta
	rm -f solucionGreedyConstructiva
	rm -f tiempoExacta
