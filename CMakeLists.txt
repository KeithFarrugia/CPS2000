cmake_minimum_required(VERSION 3.0.0)
project(CompilerTest VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

 
# =========================================== LEXER ==============================================
set(LEXER_HEADER
    Lexer/DFSA/DFSA.h
    Lexer/Lexer.h
)
set(LEXER_SOURCE
    Lexer/Lexer.cpp

    Lexer/DFSA/DFSA.cpp 

    Lexer/Utility/TokenMap.cpp
    Lexer/Utility/Transitions.cpp
    Lexer/Utility/Generate.cpp
    Lexer/Utility/Validate.cpp
)
 
# ============================================ PARSER ============================================
set(PARSER_HEADER
    Parser/Parser.h
    Parser/Abstract_Syntax_Tree/AST_Nodes.h
)
set(PARSER_SOURCE
    Parser/Parser.cpp
    Parser/Parse_Expr.cpp
    Parser/Parse_Factor.cpp
    Parser/Parse_Literal.cpp
    Parser/Parse_Op.cpp
    Parser/Parse_Statement.cpp

    Parser/Abstract_Syntax_Tree/AST_Expression.cpp
    Parser/Abstract_Syntax_Tree/AST_Factor.cpp
    Parser/Abstract_Syntax_Tree/AST_Literals.cpp
    Parser/Abstract_Syntax_Tree/AST_Operators.cpp
    Parser/Abstract_Syntax_Tree/AST_Statements.cpp
)

# =========================================== VISITOR ============================================
set(VISITOR_HEADER
    Parser/Abstract_Syntax_Tree/Visitor/Display_Visitor.h
)
set(VISITOR_SOURCE
    Parser/Abstract_Syntax_Tree/Visitor/Display_Visitor.cpp
)

# =========================================== SEMANTIC ===========================================
set(SEMANTIC_HEADER
    Semantic/Semantic_Visitor.h
)
set(SEMANTIC_SOURCE
    Semantic/Semantic_Visitor.cpp
    Semantic/Semantic_Scope_Functions.cpp
    Semantic/Semantic_Err.cpp
)
# ========================================== GENERATOR ===========================================
set(GENERATOR_HEADER
    CodeGenerator/Gen_Visitor.h
)
set(GENERATOR_SOURCE
    CodeGenerator/Gen_Visitor.cpp
    CodeGenerator/Generator_Scope_Functions.cpp
    CodeGenerator/Gen_Err.cpp
    CodeGenerator/Gen_File_Func.cpp
)

# ====================================== LIBRARY GENERATION ======================================
add_library(LEXER_LIB       ${LEXER_HEADER}         ${LEXER_SOURCE}     )
add_library(PASRSER_LIB     ${PARSER_HEADER}        ${PARSER_SOURCE}    )
add_library(VISITOR_LIB     ${VISITOR_HEADER}       ${VISITOR_SOURCE}   )
add_library(SEMANTIC_LIB    ${SEMANTIC_HEADER}      ${SEMANTIC_SOURCE}  )
add_library(CODE_GEN_LIB    ${GENERATOR_HEADER}     ${GENERATOR_SOURCE} )



# ============================================= MAIN =============================================

set(SOURCE_FILES_COMP Compiler.cpp)   

add_executable          (Compiler  ${SOURCE_FILES_COMP}             )
target_link_libraries   (Compiler  LEXER_LIB                        )
target_link_libraries   (Compiler  PASRSER_LIB                      )
target_link_libraries   (Compiler  VISITOR_LIB                      )
target_link_libraries   (Compiler  SEMANTIC_LIB                     )
target_link_libraries   (Compiler  CODE_GEN_LIB                     )



# ============================================ TESTS =============================================
set(SOURCE_FILES_LEXER Lexer_Tester.cpp)   

add_executable          (Lexer_Test     ${SOURCE_FILES_LEXER}       )
target_link_libraries   (Lexer_Test     LEXER_LIB                   )


set(SOURCE_FILES_PARSER Parser_Tester.cpp)   

add_executable          (Parser_Test    ${SOURCE_FILES_PARSER}      )
target_link_libraries   (Parser_Test    LEXER_LIB                   )
target_link_libraries   (Parser_Test    PASRSER_LIB                 )
target_link_libraries   (Parser_Test    VISITOR_LIB                 )

set(SOURCE_FILES_SEMANTIC Semantic_Tester.cpp)   

add_executable          (Semantic_Test  ${SOURCE_FILES_SEMANTIC}    )
target_link_libraries   (Semantic_Test  LEXER_LIB                   )
target_link_libraries   (Semantic_Test  PASRSER_LIB                 )
target_link_libraries   (Semantic_Test  VISITOR_LIB                 )
target_link_libraries   (Semantic_Test  SEMANTIC_LIB                )


# ============================================ PROJECT ===========================================
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
