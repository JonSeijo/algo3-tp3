CPP=g++
FLAGS= -std=c++11 -g -Wall

all: solucionExacta solucionGreedyConstructiva solucionGreedyVariante solucionLocal tiempoExacta tiempoGreedy tiempoGrasp solucionGrasp

solucionLocal: SolucionLocal.cpp ResolverLocal.cpp ResolverLocal.h ResolverGreedyVariante.cpp ResolverGreedyConstructiva.h
	$(CPP) $(FLAGS) -o  $@ ResolverLocal.cpp ResolverGreedyVariante.cpp $<

solucionGreedyConstructiva: SolucionGreedyConstructiva.cpp ResolverGreedyConstructiva.cpp ResolverGreedyConstructiva.h
	$(CPP) $(FLAGS) -o  $@ ResolverGreedyConstructiva.cpp $<

solucionGreedyVariante: SolucionGreedyVariante.cpp ResolverGreedyVariante.cpp ResolverGreedyVariante.h
	$(CPP) $(FLAGS) -o  $@ ResolverGreedyVariante.cpp $<

solucionExacta: SolucionExacta.cpp ResolverExacta.cpp ResolverExacta.h
	$(CPP) $(FLAGS) -o  $@ ResolverExacta.cpp $<

tiempoExacta: TiempoExacta.cpp  ResolverExacta.cpp ResolverExacta.h
	$(CPP) $(FLAGS) -o  $@  ResolverExacta.cpp $<

tiempoGreedy: TiempoGreedy.cpp  ResolverGreedyConstructiva.cpp ResolverGreedyConstructiva.h
	$(CPP) $(FLAGS) -o  $@  ResolverGreedyConstructiva.cpp $<

solucionGrasp: SolucionGrasp.cpp ResolverGrasp.h ResolverGreedyVariante.h
	$(CPP) $(FLAGS) -o  $@ ResolverGrasp.cpp ResolverLocal.cpp ResolverGreedyVariante.cpp $<

tiempoGrasp: TiempoGrasp.cpp ResolverGrasp.h ResolverLocal.h ResolverGreedyVariante.h
	$(CPP) $(FLAGS) -o  $@ ResolverGrasp.cpp ResolverLocal.cpp ResolverGreedyVariante.cpp $<

%.o: %.cpp
	$(CPP) $(FLAGS) -c -o $@ $<

clean:
	rm -f *.o
	rm -f solucionExacta
	rm -f solucionGreedyConstructiva
	rm -f solucionGreedyVariante
	rm -f solucionLocal
	rm -f tiempoExacta
	rm -f tiempoGreedy
	rm -f solucionGrasp
