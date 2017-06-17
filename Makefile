CPP=g++
FLAGS= -std=c++11 -g -Wall

all: solucionExacta solucionGreedyConstructiva solucionLocal tiempoExacta tiempoGreedy

solucionLocal: SolucionLocal.cpp ResolverLocal.cpp ResolverLocal.h ResolverGreedyConstructiva.cpp ResolverGreedyConstructiva.h
	$(CPP) $(FLAGS) -o  $@ ResolverLocal.cpp ResolverGreedyConstructiva.cpp $<

solucionGreedyConstructiva: SolucionGreedyConstructiva.cpp ResolverGreedyConstructiva.cpp ResolverGreedyConstructiva.h
	$(CPP) $(FLAGS) -o  $@ ResolverGreedyConstructiva.cpp $<

solucionExacta: SolucionExacta.cpp ResolverExacta.cpp ResolverExacta.h
	$(CPP) $(FLAGS) -o  $@ ResolverExacta.cpp $<

tiempoExacta: TiempoExacta.cpp  ResolverExacta.cpp ResolverExacta.h
	$(CPP) $(FLAGS) -o  $@  ResolverExacta.cpp $<

tiempoGreedy: TiempoGreedy.cpp  ResolverGreedyConstructiva.cpp ResolverGreedyConstructiva.h
	$(CPP) $(FLAGS) -o  $@  ResolverGreedyConstructiva.cpp $<

solucionGrasp: SolucionGrasp.cpp ResolverGrasp.cpp ResolverExacta.cpp
	$(CPP) $(FLAGS) -o  $@ ResolverGrasp.cpp ResolverLocal.cpp ResolverGreedyConstructiva.cpp $<

%.o: %.cpp
	$(CPP) $(FLAGS) -c -o $@ $<

clean:
	rm -f *.o
	rm -f solucionExacta
	rm -f solucionGreedyConstructiva
	rm -f solucionLocal
	rm -f tiempoExacta
	rm -f tiempoGreedy
	rm -f solucionGrasp
