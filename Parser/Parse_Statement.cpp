#include "Parser.h"

/* =========================================================================================================================
 * -------------------- Parse Assignment
 * =========================================================================================================================
 */
std::unique_ptr<AST_Assignment>  Parser::parseAssignment(int& index){
    int rollback_index = index;
    tokenised_t token = nextToken(index);


    // --------------------------------------------------- Check for aissignment node 
    if(token.token_type == token_t::IDENTIFIER){

        std::unique_ptr<AST_Assignment> assignment_node = std::make_unique<AST_Assignment>();
        assignment_node->identifier = token.lexeme_string;

        
        // --------------------------------------------------- Check for index for arrays
        if(peekToken(index).token_type == token_t::OPEN_SQUARE){
            nextToken(index); // Consume Token
            
            std::unique_ptr<AST_Expr> index_expression_node = parseExpression(index);
            verifyNode(index_expression_node.get(), index, "parseAssignment", "Expression for Index");
            assignment_node->setExprI(std::move(index_expression_node));

            verifyNext(token_t::CLOSE_SQUARE, index, "parseAssignment", "Index Expression");
        }else{
            assignment_node->setExprI(nullptr);
        }

        // --------------------------------------------------- Assignment Expression
        verifyNext(token_t::EQUAL, index, "parseAssignment");

        std::unique_ptr<AST_Expr> expression_node = parseExpression(index);
        verifyNode(expression_node.get(), index, "parseAssignment", "Expression");

        assignment_node->setExpr(std::move(expression_node));

        return std::move(assignment_node);
        

    // --------------------------------------------------- If not assignment -> roll back
    }else{
        index = rollback_index;
        return nullptr;
    }
}

/* =========================================================================================================================
 * -------------------- Parse Variable Declaration
 * =========================================================================================================================
 */
std::unique_ptr<AST_VariableDec> Parser::parseVariableDeclaration(int& index){
    int rollback_index = index;
    tokenised_t token = nextToken(index);

    if(token.token_type == token_t::LET){
        std::unique_ptr<AST_VariableDec> declaration_node = std::make_unique<AST_VariableDec>();

        /*---------------------------------------------------
         * Check for 
         * - identifier,
         * - colon symbol
         * - type
         */
        token                   = verifyNext(token_t::IDENTIFIER, index, "parseVariableDeclaration");
                                  verifyNext(token_t::COLON, index, "parseVariableDeclaration");
        tokenised_t var_type    = verifyType(index, "parseVariableDeclaration");

        declaration_node->identifier = token.lexeme_string;
        token = nextToken(index);


        switch (token.token_type){
            // --------------------------------------------------- Normal Variable
            case token_t::EQUAL:
                {   
                    /* ---------------------------------------------------
                    * This part is for non array variable 
                    * declarations here we will simply check for
                    * an expression which we will then attach 
                    * to the suffix node
                    */
                    std::unique_ptr<AST_VariableDec_Suffix_Norm> suffix_node = std::make_unique<AST_VariableDec_Suffix_Norm>();

                    suffix_node->type = var_type.token_type;

                    std::unique_ptr<AST_Expr> expression_node = parseExpression(index);

                    verifyNode(expression_node.get(), index, "parseVariableDeclaration", "Normal", "Expression");
                    
                    suffix_node->setExpr(std::move(expression_node));
                    declaration_node->setSuffix(std::move(suffix_node));
                    declaration_node->length = -1;
                    
                }
                break;

            // --------------------------------------------------- Array Variable
            case token_t::OPEN_SQUARE:
                {
                    /* ---------------------------------------------------
                    * This part will check for array declarations
                    * there are 2 ways an array can be 
                    * declared, either through all the 
                    * values being specified or by setting 
                    * it to the same value.
                    */
                    std::unique_ptr<AST_VariableDec_Suffix_Array> suffix_node = std::make_unique<AST_VariableDec_Suffix_Array>();
                    suffix_node->type = convert_Type_to_Array(var_type.token_type);

                    // --------------------------------------------------- array: type[] = {literal, literal, ...}
                    if(peekToken(index).token_type == token_t::CLOSE_SQUARE){
                        nextToken(index); // Consume next Token

                        /* ---------------------------------------------------
                         * Check for at least 1 litteral
                         */

                        verifyNext(token_t::EQUAL,          index, "parseVariableDeclaration", "Array Type 1");
                        verifyNext(token_t::OPEN_SQUARE,    index, "parseVariableDeclaration", "Array Type 1");

                        std::unique_ptr<AST_Literal> literal_node = parseLiteral(index);

                        verifyNode(literal_node.get(),      index, "parseVariableDeclaration", "Array Type 1", "Litteral");
                        suffix_node.get()->pushLiteral(std::move(literal_node));

                        /* ---------------------------------------------------
                         * for consecutive litterals
                         */
                        while(true){
                            if(peekToken(index).token_type == token_t::CLOSE_SQUARE){
                                /* Finish decleration*/
                                nextToken(index); // Consume next Token
                                declaration_node->length = suffix_node.get()->literal_list.size();
                                declaration_node->setSuffix(std::move(suffix_node));
                                break;
                            }

                            verifyNext(token_t::COMMA,   index, "parseVariableDeclaration", "Array Type 1");

                            literal_node = parseLiteral(index);
                            verifyNode(literal_node.get(), index, "parseVariableDeclaration", "Array Type 1", "Litteral Or ']'");
                            suffix_node.get()->pushLiteral(std::move(literal_node));
                        }

                    // --------------------------------------------------- array: type[num] = [item]
                    }else{
                        tokenised_t array_length = verifyNext(token_t::INTEGER, index, "parseVariableDeclaration", "Array Type 2");
                        suffix_node->type = convert_Type_to_Array(var_type.token_type);
                        declaration_node->length = std::stoi(array_length.lexeme_string);

                        verifyNext(token_t::CLOSE_SQUARE,   index, "parseVariableDeclaration", "Array Type 2");
                        verifyNext(token_t::EQUAL,          index, "parseVariableDeclaration", "Array Type 2");
                        verifyNext(token_t::OPEN_SQUARE,    index, "parseVariableDeclaration", "Array Type 2");
                        
                        /* ---------------------------------------------------
                         * Keep rolling back reading the same
                         * litteral until its done for the length
                         * of the array, this way the array 
                         * is filled
                         */
                        int literal_rollback = index;
                        for(int i = 0; i < std::stoi(array_length.lexeme_string); i++){
                            index = literal_rollback;
                            std::unique_ptr<AST_Literal> literal_node = parseLiteral(index);
                            verifyNode(literal_node.get(), index, "parseVariableDeclaration", "Array Type 2", "Litteral");
                            suffix_node.get()->pushLiteral(std::move(literal_node));
                        }
                        declaration_node->setSuffix(std::move(suffix_node));

                        verifyNext(token_t::CLOSE_SQUARE,   index, "parseVariableDeclaration", "Array Type 2");
                    }
                    
                }
                break;

            default:
                errMS("parseVariableDeclaration", "'=' or '['", index-1);
        }

        return std::move(declaration_node);

    }else{
        index = rollback_index;
        return nullptr;
    }
}
/* =========================================================================================================================
 * -------------------- Parse Block
 * =========================================================================================================================
 */
std::unique_ptr<AST_Block> Parser::parseBlock(int& index) {
    int rollback_index = index;
    std::unique_ptr<AST_Block> blockNode = std::make_unique<AST_Block>();
    
    // --------------------------------------------------- Check for Open Curly Bracket
    if(nextToken(index).token_type == token_t::OPEN_CURL){

        /* --------------------------------------------------- 
         * Validated Statements until a non 
         * valid statement is found
         */
        while (true) {
            rollback_index = index;
            std::unique_ptr<AST_Statement> statement = parseStatement(index);
            
            // --------------------------------------------------- Check for invalid statements
            if (statement != nullptr) {
                blockNode->pushStatement(std::move(statement)); // Move ownership
            } else {
                index = rollback_index;
                break;
            }
        }

        /* --------------------------------------------------- 
         * If the next token is not a 
         * Close Curly Bracket and there 
         * are no more valid statements 
         * -> invalid block structure
         */
        verifyNext(token_t::CLOSE_CURL, index, "parseBlock");

    // ------------------------------- If there is no Open Curly Bracket then whatever we are trying to parse is not a block statement
    } else {
        index = rollback_index;
        blockNode.reset(); // Release memory
        return nullptr;
    }

    return std::move(blockNode);
}
/* =========================================================================================================================
 * -------------------- Weak Block
 * =========================================================================================================================
 */
std::unique_ptr<AST_Weak_Block> Parser::parseWeakBlock(int& index) {
    int rollback_index = index;
    std::unique_ptr<AST_Weak_Block> weakblockNode = std::make_unique<AST_Weak_Block>();
    
    // ------------------------------- Check for Open Curly Bracket
    if(nextToken(index).token_type == token_t::OPEN_CURL){

        // ----------------------------------- Validated Statements until a non valid statement is found
        while (true) {
            rollback_index = index;
            std::unique_ptr<AST_Statement> statement = parseStatement(index);
            
            // ------------------ Check for invalid statements
            if (statement != nullptr) {
                weakblockNode->pushStatement(std::move(statement)); // Move ownership
            } else {
                index = rollback_index;
                break;
            }
        }

        // ----------------------------------- If the next token is not a Close Curly Bracket and there are no more valid statements -> invalid block structure
        verifyNext(token_t::CLOSE_CURL, index, "parseWeakBlock");

    // ------------------------------- If there is no Open Curly Bracket then whatever we are trying to parse is not a block statement
    } else {
        index = rollback_index;
        weakblockNode.reset(); // Release memory
        return nullptr;
    }

    return std::move(weakblockNode);
}
/* =========================================================================================================================
 * -------------------- Parse Statement
 * =========================================================================================================================
 */
std::unique_ptr<AST_Statement> Parser::parseStatement(int& index){
    int rollback_index = index;
    tokenised_t token = peekToken(index);

    switch (token.token_type){
        
        // --------------------------------------------------------------------------------- Variable Assignment
        case token_t::IDENTIFIER:
        {
            std::unique_ptr<AST_Assignment> assignment_node = parseAssignment(index);
            verifyNode(assignment_node.get(), index, "parseStatement", "Assignment");
            verifyNext(token_t::SEMICOLON, index, "parseStatement", "Assignment");
            
            return std::move(assignment_node);
        }

        // --------------------------------------------------------------------------------- Variable Declaration
        case token_t::LET:
        {
            std::unique_ptr<AST_VariableDec> declaration_node = parseVariableDeclaration(index);
            verifyNode(declaration_node.get(), index, "parseStatement", "Declaration");
            verifyNext(token_t::SEMICOLON, index, "parseStatement", "Declaration");

            return std::move(declaration_node);
        }

        // --------------------------------------------------------------------------------- Print
        case token_t::PRINT:
            {
                token = nextToken(index); // Consume Token

                std::unique_ptr<AST_Print> print_node = std::make_unique<AST_Print>();
                std::unique_ptr<AST_Expr> expression_node = parseExpression(index);

                verifyNode(expression_node.get(), index, "parseStatement", "Print", "Expression");
                print_node->setExpr(std::move(expression_node));

                verifyNext(token_t::SEMICOLON, index, "parseStatement", "Print");

                return std::move(print_node);
            }

        // --------------------------------------------------------------------------------- Delay
        case token_t::DELAY:
            {
                token = nextToken(index); // Consume Token

                std::unique_ptr<AST_Delay> delay_node = std::make_unique<AST_Delay>();
                std::unique_ptr<AST_Expr> expression_node = parseExpression(index);

                verifyNode(expression_node.get(), index, "parseStatement", "Delay", "Expression");
                delay_node->setExpr(std::move(expression_node));
                
                verifyNext(token_t::SEMICOLON, index, "parseStatement", "Delay");

                return std::move(delay_node);
            }

        // --------------------------------------------------------------------------------- Write
        case token_t::WRITE:
            {
                token = nextToken(index); // Consume Token

                std::unique_ptr<AST_Write> write_node = std::make_unique<AST_Write>();

                std::unique_ptr<AST_Expr> expression_node1 = parseExpression(index);
                verifyNode(expression_node1.get(), index, "parseStatement", "Write", "Expression1");

                verifyNext(token_t::COMMA, index, "parseStatement", "Write");

                std::unique_ptr<AST_Expr> expression_node2 = parseExpression(index);
                verifyNode(expression_node2.get(), index, "parseStatement", "Write", "Expression2");

                verifyNext(token_t::COMMA, index, "parseStatement", "Write");

                std::unique_ptr<AST_Expr> expression_node3 = parseExpression(index);
                verifyNode(expression_node3.get(), index, "parseStatement", "Write", "Expression3");

                write_node->setExpr1(std::move(expression_node1));
                write_node->setExpr2(std::move(expression_node2));
                write_node->setExpr3(std::move(expression_node3));
                
                verifyNext(token_t::SEMICOLON, index, "parseStatement", "Write");

                return std::move(write_node);
            }

        // --------------------------------------------------------------------------------- Write Box
        case token_t::WRITE_BOX:
            {
                token = nextToken(index); // Consume Token

                std::unique_ptr<AST_Write_Box> write_box_node = std::make_unique<AST_Write_Box>();

                std::unique_ptr<AST_Expr> expression_node1 = parseExpression(index);
                verifyNode(expression_node1.get(), index, "parseStatement", "Write Box", "Expression1");

                verifyNext(token_t::COMMA, index, "parseStatement", "Write Box");

                std::unique_ptr<AST_Expr> expression_node2 = parseExpression(index);
                verifyNode(expression_node2.get(), index, "parseStatement", "Write Box", "Expression2");

                verifyNext(token_t::COMMA, index, "parseStatement", "Write Box");

                std::unique_ptr<AST_Expr> expression_node3 = parseExpression(index);
                verifyNode(expression_node3.get(), index, "parseStatement", "Write Box", "Expression3");

                verifyNext(token_t::COMMA, index, "parseStatement", "Write Box");

                std::unique_ptr<AST_Expr> expression_node4 = parseExpression(index);
                verifyNode(expression_node4.get(), index, "parseStatement", "Write Box", "Expression4");

                verifyNext(token_t::COMMA, index, "parseStatement", "Write Box");

                std::unique_ptr<AST_Expr> expression_node5 = parseExpression(index);
                verifyNode(expression_node5.get(), index, "parseStatement", "Write Box", "Expression5");

                write_box_node->setExpr1(std::move(expression_node1));
                write_box_node->setExpr2(std::move(expression_node2));
                write_box_node->setExpr3(std::move(expression_node3));
                write_box_node->setExpr4(std::move(expression_node4));
                write_box_node->setExpr5(std::move(expression_node5));
                
                verifyNext(token_t::SEMICOLON, index, "parseStatement", "Write Box");

                return std::move(write_box_node);
            }

        // --------------------------------------------------------------------------------- Clear
        case token_t::CLEAR:
            {
                token = nextToken(index); // Consume Token

                std::unique_ptr<AST_Clear> clear_node = std::make_unique<AST_Clear>();
                std::unique_ptr<AST_Expr> expression_node = parseExpression(index);

                verifyNode(expression_node.get(), index, "parseStatement", "Clear", "Expression");
                clear_node->setExpr(std::move(expression_node));
                
                verifyNext(token_t::SEMICOLON, index, "parseStatement", "Clear");

                return std::move(clear_node);
            }

        // --------------------------------------------------------------------------------- If
        case token_t::IF:
            {
                token = nextToken(index); // Consume Token
                std::unique_ptr<AST_If> if_node = std::make_unique<AST_If>(); 
                
                verifyNext(token_t::OPEN_PAR, index, "parseStatement", "If");

                std::unique_ptr<AST_Expr> expression_node = parseExpression(index);
                verifyNode(expression_node.get(), index, "parseStatement", "If", "Expression");

                verifyNext(token_t::CLOSE_PAR, index, "parseStatement", "If");

            
                std::unique_ptr<AST_Block> block_node1 = parseBlock(index);
                verifyNode(block_node1.get(), index, "parseStatement", "If", "Block1");

                if(peekToken(index).token_type == token_t::ELSE){
                    token = nextToken(index); // Consume Token
                    std::unique_ptr<AST_Block> block_node2 = parseBlock(index);
                    verifyNode(block_node2.get(), index, "parseStatement", "If", "Block2");
                    if_node->setBlock2(std::move(block_node2));
                }else{
                    if_node->setBlock2(std::move(nullptr));
                }

                if_node->setExpr(std::move(expression_node));
                if_node->setBlock1(std::move(block_node1));

                return std::move(if_node);
            }

        // --------------------------------------------------------------------------------- For
        case token_t::FOR:
            {
                token = nextToken(index); // Consume Token
                std::unique_ptr<AST_For> for_node = std::make_unique<AST_For>(); 
                std::unique_ptr<AST_VariableDec> declaration_node;
                std::unique_ptr<AST_Assignment> assignment_node;
                std::unique_ptr<AST_Expr> expression_node;

                verifyNext(token_t::OPEN_PAR, index, "parseStatement", "For");

                
                declaration_node = parseVariableDeclaration(index); // no need to validate since it can be empty

                verifyNext(token_t::SEMICOLON, index, "parseStatement", "For");
                
                expression_node = parseExpression(index);
                verifyNode(expression_node.get(), index, "parseStatement", "For", "Expression");

                verifyNext(token_t::SEMICOLON, index, "parseStatement", "For");

                assignment_node = parseAssignment(index); // no need to validate since it can be empty

                
                verifyNext(token_t::CLOSE_PAR, index, "parseStatement", "For");


                std::unique_ptr<AST_Block> block_node = parseBlock(index);
                verifyNode(block_node.get(), index, "parseStatement", "For", "Block");
                

                for_node->setVarDec(std::move(declaration_node));
                for_node->setExpr(std::move(expression_node));
                for_node->setVarAssign(std::move(assignment_node));
                for_node->setBlock(std::move(block_node));

                return std::move(for_node);
            }

        // --------------------------------------------------------------------------------- While
        case token_t::WHILE:
            {
                token = nextToken(index); // Consume Token
                std::unique_ptr<AST_While> while_node = std::make_unique<AST_While>(); 
                std::unique_ptr<AST_Expr> expression_node;

                verifyNext(token_t::OPEN_PAR, index, "parseStatement", "While");

                expression_node = parseExpression(index);
                verifyNode(expression_node.get(), index, "parseStatement", "While", "Expression");
                
                verifyNext(token_t::CLOSE_PAR, index, "parseStatement", "While");

                std::unique_ptr<AST_Block> block_node = parseBlock(index);
                verifyNode(block_node.get(), index, "parseStatement", "While", "Block");
                
                while_node->setExpr(std::move(expression_node));
                while_node->setBlock(std::move(block_node));
                return std::move(while_node);
            }

        // --------------------------------------------------------------------------------- Return
        case token_t::RETURN:
            {
                token = nextToken(index);
                std::unique_ptr<AST_Return> return_node = std::make_unique<AST_Return>();
                std::unique_ptr<AST_Expr> expression_node;
                
                expression_node = parseExpression(index);
                verifyNode(expression_node.get(), index, "parseStatement", "Return", "Expression");
                
                verifyNext(token_t::SEMICOLON, index, "parseStatement", "Return");
                
                return_node->setExpr(std::move(expression_node));
                return std::move(return_node);

            }

        // --------------------------------------------------------------------------------- Function
        case token_t::FUN:
            {
                token = nextToken(index); // Consume Token
                std::unique_ptr<AST_Func_Dec> fun_dec_node = std::make_unique<AST_Func_Dec>();
                std::unique_ptr<AST_Form_Params> formal_params_node;

                /* Check for an Identifier and an '(' */
                token = verifyNext(token_t::IDENTIFIER, index, "parseStatement", "Function Decl");
                        verifyNext(token_t::OPEN_PAR,   index, "parseStatement", "Function Decl");
                fun_dec_node->identifier = token.lexeme_string;

                // ---------------------------- No Parameters
                if(peekToken(index).token_type == token_t::CLOSE_PAR){
                    token = nextToken(index); // Consume Token
                    formal_params_node = std::make_unique<AST_Form_Params>();

                // ---------------------------- Has Parameters
                }else{
                    formal_params_node = std::make_unique<AST_Form_Params>();
                    while(true){
                        std::unique_ptr<AST_Form_Param> formal_param_node = std::make_unique<AST_Form_Param>();

                        // ---------------------------- Parameter Name and Type
                        token = verifyNext(token_t::IDENTIFIER, index, "parseStatement", "Formal Param");
                                verifyNext(token_t::COLON,      index, "parseStatement", "Formal Param");

                        formal_param_node->identifier = token.lexeme_string;

                        token = verifyType(index, "parseStatement", "Formal Param");
                        formal_param_node->type = token.token_type;
                        
                        // ---------------------------- Check For Arrays
                        if(peekToken(index).token_type == token_t::OPEN_SQUARE){
                            token = nextToken(index); // Consume Token
                            tokenised_t array_length = verifyNext(token_t::INTEGER, index, "parseStatement", "Formal Param");
                            formal_param_node->length = stoi(array_length.lexeme_string);
                            formal_param_node->type = convert_Type_to_Array(formal_param_node->type);
                            verifyNext(token_t::CLOSE_SQUARE, index, "parseStatement", "Formal Param");
                        }else{
                            formal_param_node->length = -1;
                        }
                        
                        // ---------------------------- Check For More Parameters
                        if(peekToken(index).token_type == token_t::COMMA){
                            token = nextToken(index); // Consume Token
                            formal_params_node->pushParam(std::move(formal_param_node));
                        }else{
                            formal_params_node->pushParam(std::move(formal_param_node));
                            break;
                        }
                    }
                    
                    verifyNext(token_t::CLOSE_PAR, index, "parseStatement", "Function Decl");

                }

                verifyNext(token_t::POINTER, index, "parseStatement", "Function Decl");
                
                token = verifyType(index, "parseStatement", "Function Decl");
                fun_dec_node->type = token.token_type;
                
                
                // ------------------------------------- check for array return type
                if(peekToken(index).token_type == token_t::OPEN_SQUARE){
                    token = nextToken(index); // Consume Token
                    tokenised_t array_length = verifyNext(token_t::INTEGER, index, "parseStatement", "Formal Param");
                    fun_dec_node->length = stoi(array_length.lexeme_string);
                    fun_dec_node->type = convert_Type_to_Array(fun_dec_node->type);
                    verifyNext(token_t::CLOSE_SQUARE, index, "parseStatement", "Formal Param");
                }else{
                    fun_dec_node->length = -1;
                }

                std::unique_ptr<AST_Weak_Block> block_node = parseWeakBlock(index);
                verifyNode(block_node.get(), index, "parseStatement", "Function Decl");

                fun_dec_node->setParams(std::move(formal_params_node));
                fun_dec_node->setWeakBlock(std::move(block_node));

                return std::move(fun_dec_node);
            }

        // --------------------------------------------------------------------------------- Block
        case token_t::OPEN_CURL:
            {
                std::unique_ptr<AST_Block> block_node = parseBlock(index);
                verifyNode(block_node.get(), index, "parseStatement", "Block");

                return std::move(block_node);
            }
        default:
            index = rollback_index;
            return nullptr;
    }
}