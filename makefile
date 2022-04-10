# caminhos de origem e destino
SRCFOLDER = source
DBGFOLDER = objects/debug
RLSFOLDER = objects/release
BINFOLDER = .
# flags de compilação
DBGCFLAGS = -c -Wall -g -DDEBUG_MODE
RLSCFLAGS = -c -Wall



all: clean release

clean:
	rm -rf ${DBGFOLDER}/*.o ${BINFOLDER}/*~ ${BINFOLDER}/mids



debug: ${DBGFOLDER}/main.o ${DBGFOLDER}/Solver.o ${DBGFOLDER}/Instance.o
	g++ -o ${BINFOLDER}/mids ${DBGFOLDER}/main.o ${DBGFOLDER}/Solver.o ${DBGFOLDER}/Instance.o

${DBGFOLDER}/Instance.o: ${SRCFOLDER}/Instance.cpp ${SRCFOLDER}/Instance.hpp ${SRCFOLDER}/Macros.hpp
	g++ -o ${DBGFOLDER}/Instance.o ${SRCFOLDER}/Instance.cpp ${DBGCFLAGS}

${DBGFOLDER}/Solver.o: ${SRCFOLDER}/Solver.cpp ${SRCFOLDER}/Solver.hpp ${SRCFOLDER}/Instance.hpp
	g++ -o ${DBGFOLDER}/Solver.o ${SRCFOLDER}/Solver.cpp ${DBGCFLAGS}

${DBGFOLDER}/main.o: ${SRCFOLDER}/main.cpp ${SRCFOLDER}/Solver.hpp ${SRCFOLDER}/Instance.hpp
	g++ -o ${DBGFOLDER}/main.o ${SRCFOLDER}/main.cpp ${DBGCFLAGS}



release: ${RLSFOLDER}/main.o ${RLSFOLDER}/Solver.o ${RLSFOLDER}/Instance.o
	g++ -o ${BINFOLDER}/mids ${RLSFOLDER}/main.o ${RLSFOLDER}/Solver.o ${RLSFOLDER}/Instance.o

${RLSFOLDER}/Instance.o: ${SRCFOLDER}/Instance.cpp ${SRCFOLDER}/Instance.hpp ${SRCFOLDER}/Macros.hpp
	g++ -o ${RLSFOLDER}/Instance.o ${SRCFOLDER}/Instance.cpp ${RLSCFLAGS}

${RLSFOLDER}/Solver.o: ${SRCFOLDER}/Solver.cpp ${SRCFOLDER}/Solver.hpp ${SRCFOLDER}/Instance.hpp
	g++ -o ${RLSFOLDER}/Solver.o ${SRCFOLDER}/Solver.cpp ${RLSCFLAGS}

${RLSFOLDER}/main.o: ${SRCFOLDER}/main.cpp ${SRCFOLDER}/Solver.hpp ${SRCFOLDER}/Instance.hpp
	g++ -o ${RLSFOLDER}/main.o ${SRCFOLDER}/main.cpp ${RLSCFLAGS}


