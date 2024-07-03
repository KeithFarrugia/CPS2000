#include "Gen_Visitor.h"
/* =========================================================================================================================
 * -------------------- Error Handling
 * This function prints an error message neatly before 
 * 
 * If a single location is specified then the error will only specify 1 place for example "Error in Parse during parse Statement"
 * =========================================================================================================================
 */

#define SPACEING 20

void Gen_Visitor::errMS(std::string loc, std::string mes){
    std::cout << "\n\n=============================================================================\n";
    std::cout <<     "=                               Error Message                               =\n";
    std::cout <<     "=                              Code Generation                              =\n";
    std::cout <<     "=============================================================================\n\n";

    std::cout << std::setw(SPACEING) << std::left <<  "\tLocation ";
    std::cout << std::setw(SPACEING) << std::left <<  loc;
    std::cout << "\n";
    std::cout << std::setw(SPACEING) << std::left <<  "\tMessage ";
    std::cout << std::setw(SPACEING) << std::left <<  mes;
    std::cout << "\n";
    std::cout << std::setw(SPACEING) << std::left <<  "\tTab Count ";
    std::cout << std::setw(SPACEING) << std::left <<  std::to_string(tab);
    std::cout << "\n";

    exit(EXIT_FAILURE);
}

void Gen_Visitor::errMS(std::string loc1, std::string loc2, std::string mes){
    std::cout << "\n\n=============================================================================\n";
    std::cout <<     "=                               Error Message                               =\n";
    std::cout <<     "=                              Code Generation                              =\n";
    std::cout <<     "=============================================================================\n\n";

    std::cout << std::setw(SPACEING) << std::left <<  "\tLocation ";
    std::cout << std::setw(SPACEING) << std::left <<  loc1;
    std::cout << "\n";
    std::cout << std::setw(SPACEING) << std::left <<  "\tSub Location ";
    std::cout << std::setw(SPACEING) << std::left <<  loc2;
    std::cout << "\n";
    std::cout << std::setw(SPACEING) << std::left <<  "\tMessage ";
    std::cout << std::setw(SPACEING) << std::left <<  mes;
    std::cout << "\n";
    std::cout << std::setw(SPACEING) << std::left <<  "\tTab Count ";
    std::cout << std::setw(SPACEING) << std::left <<  std::to_string(tab);
    std::cout << "\n";

    exit(EXIT_FAILURE);
}