CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

target: etapa7

etapa7: symbols/symbols.o ast/ast.o tacs/tacs.o semantic_check/semantic_check.o asm/asm_utils.o asm/asm_data.o asm/asm_handlers.o asm/asm.o lex.yy.o main.o parser.tab.o
	$(CXX) symbols.o ast.o tacs.o semantic_check.o asm_utils.o asm_data.o asm_handlers.o asm.o lex.yy.o main.o parser.tab.o -o etapa7

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $< -c 

parser.tab.hpp: parser.ypp 
	bison parser.ypp -d

parser.tab.cpp: parser.ypp 
	bison parser.ypp

lex.yy.cpp: scanner.l parser.tab.hpp
	flex -o lex.yy.cpp scanner.l 

clean:
	rm etapa7 lex.yy.cpp parser.tab.cpp parser.tab.hpp *.o
