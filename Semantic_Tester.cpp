#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Parser/Abstract_Syntax_Tree/Visitor/Display_Visitor.h"
#include "Semantic/Semantic_Visitor.h"

int main() {
    std::string fileContent = readFileToString("../Test_Benches/Semantic_Test_Bench.txt");
    Lexer l = Lexer();
    std::vector<tokenised_t> toks = l.GenerateTokens(fileContent, false);

    printTokenisedList(toks);

    Parser p = Parser(toks);
    int index = 0;
    std::unique_ptr<Program> program_ast = p.parseProgram(index);

    Display_Visitor v = Display_Visitor();
    program_ast->sendVisitor(v);

    Semantic_Visitor s = Semantic_Visitor();
    program_ast->sendVisitor(s);
    
    return 0;   
}
