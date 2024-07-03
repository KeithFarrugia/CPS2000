#include "Gen_Visitor.h"
/* ==========================================================================================================================
 *  ---------------------- Write Program to File
 * Writes the compiled program to a text file
 * This makes it easier to access
 * ==========================================================================================================================
 */

void Gen_Visitor::writeToFile(const std::string& filename) {
    std::ofstream file(filename, std::ofstream::trunc);

    if (!file.is_open()) { std::cerr << "Error: Failed to open file " << filename << " for writing!" << std::endl;  return; }

    for (const std::string& line : compiled_code) {  file << line << std::endl; }
    
    file.close();

    std::cout << "Compilation result has been written to file " << filename << std::endl;
}