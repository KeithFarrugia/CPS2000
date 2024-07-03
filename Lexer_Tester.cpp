#include "Lexer/Lexer.h"
#include <algorithm>

int main() {
    std::string fileContent = readFileToString("../Test_Benches/Lexer_Test_Bench.txt");
    Lexer l = Lexer();
    l.displayTable();
    std::vector<tokenised_t> toks = l.GenerateTokens(fileContent, true);

    printTokenisedList(toks);
    return 0;   
}
