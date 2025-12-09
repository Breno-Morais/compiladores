#ifndef ASM_HDL_COMP
#define ASM_HDL_COMP

#include "../tacs/tacs.h"
#include <sstream>

// --- Arithmetic Handlers ---
void handle_BinOp(std::ostringstream& oss, TAC* code, const std::string& instruction);
void handle_Mul(std::ostringstream& oss, TAC* code);
void handle_Div(std::ostringstream& oss, TAC* code);
void handle_Mod(std::ostringstream& oss, TAC* code);
void handle_Shift(std::ostringstream& oss, TAC* code, bool toLeft);

// --- Logic/Comparison Handlers ---
void handle_Cmp(std::ostringstream& oss, TAC* code, const std::string& set_instruction);
void handle_And(std::ostringstream& oss, TAC* code, int& LCCounter);
void handle_Or(std::ostringstream& oss, TAC* code, int& LCCounter);
void handle_Not(std::ostringstream& oss, TAC* code);

// --- Control Flow Handlers ---
void handle_Label(std::ostringstream& oss, TAC* code);
void handle_Jump(std::ostringstream& oss, TAC* code);
void handle_IfZ(std::ostringstream& oss, TAC* code);
void handle_BeginFun(std::ostringstream& oss, TAC* code);
void handle_EndFun(std::ostringstream& oss, TAC* code);
void handle_Return(std::ostringstream& oss, TAC* code);
void handle_Call(std::ostringstream& oss, TAC* code);
void handle_Arg(std::ostringstream& oss, TAC* code);

// --- I/O and Move Handlers ---
void handle_Move(std::ostringstream& oss, TAC* code);
void handle_Read(std::ostringstream& oss, TAC* code);
void handle_Print(std::ostringstream& oss, TAC* code, int& LCCounter);

#endif /* ASM_HDL_COMP */