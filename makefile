# caminhos de origem e destino
SRCFOLDER = source
DBGFOLDER = objects/debug
RLSFOLDER = objects/release
BINFOLDER = .
# caminhos das bibliotecas
LIB1 = source/CppLib/DataStructures/header
# flags de compilação
DBGCFLAGS = -c -std=c++17 -g -DDEBUG_MODE # -Wall
RLSCFLAGS = -c -std=c++17



all: clean release

clean:
	rm -rf ${DBGFOLDER}/*.o ${RLSFOLDER}/*.o ${BINFOLDER}/*~ ${BINFOLDER}/mids



debug: ${DBGFOLDER}/main.o ${DBGFOLDER}/FileHandler.o ${DBGFOLDER}/Instance.o ${DBGFOLDER}/Solution.o ${DBGFOLDER}/Solvers.o
	g++ -o ${BINFOLDER}/mids ${DBGFOLDER}/main.o ${DBGFOLDER}/FileHandler.o ${DBGFOLDER}/Instance.o ${DBGFOLDER}/Solution.o ${DBGFOLDER}/Solvers.o 

${DBGFOLDER}/FileHandler.o: ${SRCFOLDER}/FileHandler.cpp ${SRCFOLDER}/FileHandler.hpp ${SRCFOLDER}/Macros.hpp
	g++ -o ${DBGFOLDER}/FileHandler.o ${SRCFOLDER}/FileHandler.cpp ${DBGCFLAGS}

${DBGFOLDER}/Instance.o: ${SRCFOLDER}/Instance.cpp ${SRCFOLDER}/Instance.hpp ${SRCFOLDER}/Macros.hpp
	g++ -o ${DBGFOLDER}/Instance.o ${SRCFOLDER}/Instance.cpp ${DBGCFLAGS}

${DBGFOLDER}/Solution.o: ${SRCFOLDER}/Solution.cpp ${SRCFOLDER}/Solution.hpp ${SRCFOLDER}/Instance.hpp
	g++ -o ${DBGFOLDER}/Solution.o ${SRCFOLDER}/Solution.cpp ${DBGCFLAGS}

${DBGFOLDER}/Solvers.o: ${SRCFOLDER}/Solvers.cpp ${SRCFOLDER}/Solvers.hpp ${SRCFOLDER}/Instance.hpp ${SRCFOLDER}/Solution.hpp
	g++ -o ${DBGFOLDER}/Solvers.o ${SRCFOLDER}/Solvers.cpp ${DBGCFLAGS}

${DBGFOLDER}/main.o: ${SRCFOLDER}/main.cpp ${SRCFOLDER}/Solvers.hpp
	g++ -o ${DBGFOLDER}/main.o ${SRCFOLDER}/main.cpp ${DBGCFLAGS}




release: ${RLSFOLDER}/main.o ${RLSFOLDER}/FileHandler.o ${RLSFOLDER}/Instance.o ${RLSFOLDER}/Solution.o ${RLSFOLDER}/Solvers.o
	g++ -o ${BINFOLDER}/mids ${RLSFOLDER}/main.o ${RLSFOLDER}/FileHandler.o ${RLSFOLDER}/Instance.o ${RLSFOLDER}/Solution.o ${RLSFOLDER}/Solvers.o 

${RLSFOLDER}/FileHandler.o: ${SRCFOLDER}/FileHandler.cpp ${SRCFOLDER}/FileHandler.hpp ${SRCFOLDER}/Macros.hpp
	g++ -o ${RLSFOLDER}/FileHandler.o ${SRCFOLDER}/FileHandler.cpp ${RLSCFLAGS}

${RLSFOLDER}/Instance.o: ${SRCFOLDER}/Instance.cpp ${SRCFOLDER}/Instance.hpp ${SRCFOLDER}/Macros.hpp
	g++ -o ${RLSFOLDER}/Instance.o ${SRCFOLDER}/Instance.cpp ${RLSCFLAGS}

${RLSFOLDER}/Solution.o: ${SRCFOLDER}/Solution.cpp ${SRCFOLDER}/Solution.hpp ${SRCFOLDER}/Instance.hpp
	g++ -o ${RLSFOLDER}/Solution.o ${SRCFOLDER}/Solution.cpp ${RLSCFLAGS}

${RLSFOLDER}/Solvers.o: ${SRCFOLDER}/Solvers.cpp ${SRCFOLDER}/Solvers.hpp ${SRCFOLDER}/Instance.hpp ${SRCFOLDER}/Solution.hpp
	g++ -o ${RLSFOLDER}/Solvers.o ${SRCFOLDER}/Solvers.cpp ${RLSCFLAGS}

${RLSFOLDER}/main.o: ${SRCFOLDER}/main.cpp ${SRCFOLDER}/Solvers.hpp
	g++ -o ${RLSFOLDER}/main.o ${SRCFOLDER}/main.cpp ${RLSCFLAGS}


