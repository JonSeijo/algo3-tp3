CPP=g++
FLAGS= -std=c++11 -g -Wall

all: solucionExacta solucionGreedyConstructiva solucionGreedyVariante solucionLocal solucionGrasp

solucionExacta: SolucionExacta.cpp ResolverExacta.cpp ResolverExacta.h
	$(CPP) $(FLAGS) -o  $@ ResolverExacta.cpp $<

solucionGreedyConstructiva: SolucionGreedyConstructiva.cpp ResolverGreedyConstructiva.cpp ResolverGreedyConstructiva.h
	$(CPP) $(FLAGS) -o  $@ ResolverGreedyConstructiva.cpp $<

solucionGreedyVariante: SolucionGreedyVariante.cpp ResolverGreedyVariante.cpp ResolverGreedyVariante.h
	$(CPP) $(FLAGS) -o  $@ ResolverGreedyVariante.cpp $<

solucionLocal: SolucionLocal.cpp ResolverLocal.cpp ResolverLocal.h ResolverGreedyVariante.cpp ResolverGreedyConstructiva.h
	$(CPP) $(FLAGS) -o  $@ ResolverLocal.cpp ResolverGreedyVariante.cpp $<

solucionGrasp: SolucionGrasp.cpp ResolverGrasp.cpp ResolverGrasp.h ResolverGreedyGrasp.cpp ResolverGreedyGrasp.h
	$(CPP) $(FLAGS) -o  $@ ResolverGrasp.cpp ResolverLocal.cpp ResolverGreedyGrasp.cpp $<

%.o: %.cpp
	$(CPP) $(FLAGS) -c -o $@ $<

clean:
	rm -f *.o
	rm -f solucionExacta
	rm -f solucionGreedyConstructiva
	rm -f solucionGreedyVariante
	rm -f solucionLocal
	rm -f solucionGrasp
