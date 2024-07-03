#ifndef AST_H
#define AST_H

#include <iostream>
#include <vector>
#include <string>
#include <memory> // For std::unique_ptr
#include "../../Utility/types/Tokens.h"

/* =========================================================================================================================
 *   Class Declaration
 * =========================================================================================================================
 */
class Program;

class AST_Identifier;               
class AST_Relational;               class AST_Multiplicative;                   class AST_Additive;
class AST_Boolean;                  class AST_Integer;                          class AST_Float;
class AST_Colour;

class AST_Width;                    class AST_Height;                           class AST_Read;
class AST_Print;                    class AST_Delay;                            class AST_Write_Box;
class AST_Write;                    class AST_Clear;

class AST_ActualParams;             class AST_FunctionCall;
class AST_Form_Param;               class AST_Form_Params;                      class AST_Func_Dec;

class AST_SubExpression;            class AST_Unary;                            class AST_Random;
class AST_Term;                     class AST_Simple_Expr;                      class AST_Expr;
class AST_Assignment;               class AST_VariableDec_Suffix;               class AST_VariableDec_Suffix_Norm;
class AST_Block;                    class AST_VariableDec;                      class AST_Return;
class AST_If;                       class AST_For;                              class AST_While;
class AST_Weak_Block;               class AST_VariableDec_Suffix_Array;



/* =========================================================================================================================
 *   Virtual Visitor
 * =========================================================================================================================
 */
class AST_Visitor {
public:
    virtual ~AST_Visitor() {}
    virtual void visit_program_start        (const Program*                         node) = 0;
    virtual void visit_program_end          (const Program*                         node) = 0;

    // ---------------------------------------------------------------------------------------- Statements
    virtual void visit_assignment           (const AST_Assignment*                  node) = 0;
    virtual void visit_var_dec              (const AST_VariableDec*                 node) = 0;
    virtual void visit_var_dec_suf_norm     (const AST_VariableDec_Suffix_Norm*     node) = 0;
    virtual void visit_var_dec_suf_array    (const AST_VariableDec_Suffix_Array*    node) = 0;

    virtual void visit_print                (const AST_Print*                       node) = 0;
    virtual void visit_delay                (const AST_Delay*                       node) = 0;
    virtual void visit_write_box            (const AST_Write_Box*                   node) = 0;
    virtual void visit_write                (const AST_Write*                       node) = 0;
    virtual void visit_clear                (const AST_Clear*                       node) = 0;

    virtual void visit_return               (const AST_Return*                      node) = 0;

    virtual void visit_start_if             (const AST_If*                          node) = 0;
    virtual void visit_end_if               (const AST_If*                          node) = 0;
    virtual void visit_start_else           (const AST_If*                          node) = 0;
    virtual void visit_end_else             (const AST_If*                          node) = 0;

    virtual void visit_start_for            (const AST_For*                         node) = 0;
    virtual void visit_jump_for             (const AST_For*                         node) = 0;
    virtual void visit_skip_for             (const AST_For*                         node) = 0;
    virtual void visit_end_for              (const AST_For*                         node) = 0;

    virtual void visit_start_while          (const AST_While*                       node) = 0;
    virtual void visit_skip_while           (const AST_While*                       node) = 0;
    virtual void visit_end_while            (const AST_While*                       node) = 0;

    virtual void visit_func_dec_start       (const AST_Func_Dec*                    node) = 0;
    virtual void visit_func_dec_skip        (const AST_Func_Dec*                    node) = 0;
    virtual void visit_func_dec_end         (const AST_Func_Dec*                    node) = 0;
    virtual void visit_form_params          (const AST_Form_Params*                 node) = 0;
    virtual void visit_form_param           (const AST_Form_Param*                  node) = 0;

    virtual void visit_start_block          (const AST_Block*                       node) = 0;
    virtual void visit_end_block            (const AST_Block*                       node) = 0;

    virtual void visit_start_weak_block     (const AST_Weak_Block*                  node) = 0;
    virtual void visit_end_weak_block       (const AST_Weak_Block*                  node) = 0;
    

    // ---------------------------------------------------------------------------------------- Expressions
    virtual void visit_term                 (const AST_Term*                        node) = 0;
    virtual void visit_simple_expr          (const AST_Simple_Expr*                 node) = 0;
    virtual void visit_expr                 (const AST_Expr*                        node) = 0;

    // ---------------------------------------------------------------------------------------- Factors
    virtual void visit_iden                 (const AST_Identifier*                  node) = 0;
    virtual void visit_act_params           (const AST_ActualParams*                node) = 0;
    virtual void visit_func_call            (const AST_FunctionCall*                node) = 0;
    virtual void visit_sub_expr             (const AST_SubExpression*               node) = 0;
    virtual void visit_unary                (const AST_Unary*                       node) = 0;
    virtual void visit_random               (const AST_Random*                      node) = 0;

    // ---------------------------------------------------------------------------------------- Litterals
    virtual void visit_bool                 (const AST_Boolean*                     node) = 0;
    virtual void visit_int                  (const AST_Integer*                     node) = 0;
    virtual void visit_float                (const AST_Float*                       node) = 0;
    virtual void visit_colour               (const AST_Colour*                      node) = 0;
    virtual void visit_width                (const AST_Width*                       node) = 0;
    virtual void visit_height               (const AST_Height*                      node) = 0;
    virtual void visit_read                 (const AST_Read*                        node) = 0;

    // ---------------------------------------------------------------------------------------- Operators
    virtual void visit_rel                  (const AST_Relational*                  node) = 0;
    virtual void visit_mult                 (const AST_Multiplicative*              node) = 0;
    virtual void visit_add                  (const AST_Additive*                    node) = 0;


    // ---------------------------------------------------------------------------------------- Other Functions
    virtual void reset() = 0;
    virtual void inc_tab() = 0;
    virtual void dec_tab() = 0;
};



/* =========================================================================================================================
 *   Unfinished Classe
 * Classes that in the language definition have an | between two/more sublanguages, to be able to point to the same node
 * We specify a virtual parent node.
 * =========================================================================================================================
 */
class AST_Node                                  { public: virtual void accept (AST_Visitor& visitor)             = 0;               };

class AST_Statement : public AST_Node           { public: virtual void accept (AST_Visitor& visitor) override    = 0;               };
class AST_Write_St  : public AST_Statement      { public: virtual void accept (AST_Visitor& visitor) override    = 0;               };


class AST_Factor    : public AST_Node           { public: virtual void accept (AST_Visitor& visitor) override    = 0;               };

class AST_Literal   : public AST_Factor         { public: virtual void accept (AST_Visitor& visitor) override    = 0;               };


class AST_VariableDec_Suffix : public AST_Node  { public: virtual void accept (AST_Visitor& visitor) override   = 0;  token_t type; };

/* =========================================================================================================================
 *   Program Grammer
 * =========================================================================================================================
 */
class Program {
public:
    void sendVisitor(AST_Visitor& visitor) {
        visitor.visit_program_start(this);

        for (std::unique_ptr<AST_Statement>& statement : statementlist) {
            visitor.inc_tab();
            statement->accept(visitor);
            visitor.dec_tab();
        }
        
        visitor.visit_program_end(this);
    }

    void pushStatement(std::unique_ptr<AST_Statement> statement) {
        statementlist.push_back(std::move(statement));
    }

public:
    std::vector<std::unique_ptr<AST_Statement>> statementlist;
};


/* =========================================================================================================================
 *   Statment Grammer
 * =========================================================================================================================
 */

// ------------------------------------------------------------------------------------------ Variable Assignment
class AST_Assignment : public AST_Statement{
public:
    void accept     ( AST_Visitor&                      visitor ) override ;
    void setExpr    ( std::unique_ptr<AST_Expr>         exp     );
    void setExprI   ( std::unique_ptr<AST_Expr>         exp_ind );

    std::string identifier;
public:
    std::unique_ptr<AST_Expr> expression;
    std::unique_ptr<AST_Expr> array_index_expression;
};

// ------------------------------------------------------------------------------------------ Variable Declaration
class AST_VariableDec : public AST_Statement {
public:
    void accept     ( AST_Visitor&                              visitor ) override ;
    void setSuffix  ( std::unique_ptr<AST_VariableDec_Suffix>   suf     );

    std::string identifier;
    int length;
public:
    std::unique_ptr<AST_VariableDec_Suffix> dec_suffix;
};

// ------------------------------------------------------------------------------------------ Variable Declaration Suffix Norm
class AST_VariableDec_Suffix_Norm : public AST_VariableDec_Suffix {
public:
    void accept     ( AST_Visitor&                  visitor ) override;
    void setExpr    ( std::unique_ptr<AST_Expr>     exp     );
public:
    std::unique_ptr<AST_Expr> expression;
};

// ------------------------------------------------------------------------------------------ Variable Declaration Suffix Array
class AST_VariableDec_Suffix_Array : public AST_VariableDec_Suffix {
public:
    void accept     ( AST_Visitor&                  visitor ) override;
    void pushLiteral ( std::unique_ptr<AST_Literal>  lit    );
public:
    std::vector<std::unique_ptr<AST_Literal>> literal_list;
};
// ------------------------------------------------------------------------------------------ Print
class AST_Print : public AST_Statement {
public:
    void accept     ( AST_Visitor&                  visitor ) override;
    void setExpr    ( std::unique_ptr<AST_Expr>     exp     );
public:
    std::unique_ptr<AST_Expr> expression;
};

// ------------------------------------------------------------------------------------------ Delay
class AST_Delay : public AST_Statement {
public:
    void accept     ( AST_Visitor&                  visitor ) override ;
    void setExpr    ( std::unique_ptr<AST_Expr>     exp     );
public:
    std::unique_ptr<AST_Expr> expression;
};

// ------------------------------------------------------------------------------------------ Write Box
class AST_Write_Box : public AST_Write_St {
public:
    void accept     ( AST_Visitor&                  visitor ) override;
    void setExpr1   ( std::unique_ptr<AST_Expr>     exp     );
    void setExpr2   ( std::unique_ptr<AST_Expr>     exp     );
    void setExpr3   ( std::unique_ptr<AST_Expr>     exp     );
    void setExpr4   ( std::unique_ptr<AST_Expr>     exp     );
    void setExpr5   ( std::unique_ptr<AST_Expr>     exp     );
public:
    std::unique_ptr<AST_Expr> expression1;
    std::unique_ptr<AST_Expr> expression2;
    std::unique_ptr<AST_Expr> expression3;
    std::unique_ptr<AST_Expr> expression4;
    std::unique_ptr<AST_Expr> expression5;
};

// ------------------------------------------------------------------------------------------ Write
class AST_Write : public AST_Write_St {
public:
    void accept     ( AST_Visitor&                  visitor ) override ;
    void setExpr1   ( std::unique_ptr<AST_Expr>     exp     );
    void setExpr2   ( std::unique_ptr<AST_Expr>     exp     );
    void setExpr3   ( std::unique_ptr<AST_Expr>     exp     );
public:
    std::unique_ptr<AST_Expr> expression1;
    std::unique_ptr<AST_Expr> expression2;
    std::unique_ptr<AST_Expr> expression3;
};

// ------------------------------------------------------------------------------------------ Clear
class AST_Clear : public AST_Statement {
public:
    void accept     ( AST_Visitor&                  visitor ) override;
    void setExpr    ( std::unique_ptr<AST_Expr>     exp     );
public:
    std::unique_ptr<AST_Expr> expression;
};

// ------------------------------------------------------------------------------------------ Return
class AST_Return : public AST_Statement {
public:
    void accept     ( AST_Visitor&                  visitor ) override;
    void setExpr    ( std::unique_ptr<AST_Expr>     exp     );
public:
    std::unique_ptr<AST_Expr> expression;
};

// ------------------------------------------------------------------------------------------ If/Else
class AST_If : public AST_Statement {
public:
    void accept     ( AST_Visitor&                  visitor ) override;
    void setExpr    ( std::unique_ptr<AST_Expr>     exp     );
    void setBlock1  ( std::unique_ptr<AST_Block>    b       );
    void setBlock2  ( std::unique_ptr<AST_Block>    b       );
public:
    std::unique_ptr<AST_Block> block1;
    std::unique_ptr<AST_Block> block2;
    std::unique_ptr<AST_Expr> expression;
};

// ------------------------------------------------------------------------------------------ For Loop
class AST_For : public AST_Statement {
public:
    void accept         ( AST_Visitor&                      visitor ) override;
    void setVarAssign   ( std::unique_ptr<AST_Assignment>   assign  );
    void setExpr        ( std::unique_ptr<AST_Expr>         exp     );
    void setVarDec      ( std::unique_ptr<AST_VariableDec>  dec     );
    void setBlock       ( std::unique_ptr<AST_Block>        b       );
public:
    std::unique_ptr<AST_Block> block;
    std::unique_ptr<AST_Expr> expression;
    std::unique_ptr<AST_VariableDec> var_dec;
    std::unique_ptr<AST_Assignment> var_assign;
};

// ------------------------------------------------------------------------------------------ While Loop
class AST_While : public AST_Statement {
public:
    void accept     ( AST_Visitor&                  visitor ) override;
    void setExpr    ( std::unique_ptr<AST_Expr>     exp     );
    void setBlock   ( std::unique_ptr<AST_Block>    b       );
public:
    std::unique_ptr<AST_Expr> expression;
    std::unique_ptr<AST_Block> block;
};

// ------------------------------------------------------------------------------------------ Function Declaration 
class AST_Func_Dec : public AST_Statement {
public:
    void accept         ( AST_Visitor&                      visitor ) override;
    void setParams      ( std::unique_ptr<AST_Form_Params>  par     );
    void setWeakBlock   ( std::unique_ptr<AST_Weak_Block>   b       );

    std::string identifier;
    token_t type;
    int length;
public:
    std::unique_ptr<AST_Form_Params> params;
    std::unique_ptr<AST_Weak_Block> weakblock;
};

// ------------------------------------------------------------------------------------------ Formal Parameters 
class AST_Form_Params : public AST_Node {
public:
    void accept     ( AST_Visitor&                      visitor ) override;
    void pushParam  ( std::unique_ptr<AST_Form_Param>   par     );
public:
    std::vector<std::unique_ptr<AST_Form_Param>> params;
};

// ------------------------------------------------------------------------------------------ Formal Parameter
class AST_Form_Param : public AST_Node {
public:
    void accept     ( AST_Visitor&                      visitor ) override;
    
    std::string identifier;
    token_t type;
    int length;
public:

};

// ------------------------------------------------------------------------------------------ Block
class AST_Block : public AST_Statement {
public:
    void accept         ( AST_Visitor&                       visitor     ) override;
    void pushStatement  ( std::unique_ptr<AST_Statement>     statement   );
public:
    std::vector<std::unique_ptr<AST_Statement>> statementlist;
};
// ------------------------------------------------------------------------------------------ Weak Block
class AST_Weak_Block : public AST_Statement {
public:
    void accept         ( AST_Visitor&                       visitor     ) override;
    void pushStatement  ( std::unique_ptr<AST_Statement>     statement   );
public:
    std::vector<std::unique_ptr<AST_Statement>> statementlist;
};



/* =========================================================================================================================
 *   Expression Grammer
 * =========================================================================================================================
 */

// ------------------------------------------------------------------------------------------ Term
class AST_Term : public AST_Node {
public:
    void accept     ( AST_Visitor&                           visitor ) override;
    void pushFactor ( std::unique_ptr<AST_Factor>            factor  );
    void pushMult   ( std::unique_ptr<AST_Multiplicative>    mult   );
public:
    std::vector<std::unique_ptr<AST_Factor>> factor_list;
    std::vector<std::unique_ptr<AST_Multiplicative>> mult_list;
};

// ------------------------------------------------------------------------------------------ Simple Expression
class AST_Simple_Expr : public AST_Node {
public:
    void accept     ( AST_Visitor&                           visitor ) override;
    void pushTerm   ( std::unique_ptr<AST_Term>              term    );
    void pushAdd    ( std::unique_ptr<AST_Additive>          add     );
public:
    std::vector<std::unique_ptr<AST_Term>> term_list;
    std::vector<std::unique_ptr<AST_Additive>> add_list;
};

// ------------------------------------------------------------------------------------------ Expression
class AST_Expr : public AST_Node {
public:
    void accept         ( AST_Visitor&                      visitor     ) override;
    void pushSimpleExpr ( std::unique_ptr<AST_Simple_Expr>  sim_expr    );
    void pushRel        ( std::unique_ptr<AST_Relational>   rel         );

    token_t forced_type;
public:
    std::vector<std::unique_ptr<AST_Simple_Expr>> simple_expr_list;
    std::vector<std::unique_ptr<AST_Relational>> rel_list;
};




/* =========================================================================================================================
 *   Factors Grammer
 * =========================================================================================================================
 */

// ------------------------------------------------------------------------------------------ Identifier
class AST_Identifier: public AST_Factor{ 
public:
    void accept         ( AST_Visitor&              visitor ) override;
    void setExpression  (std::unique_ptr<AST_Expr>  expr    );

    std::string identifier;
    std::unique_ptr<AST_Expr> index_expression;
};

// ------------------------------------------------------------------------------------------ Actual Param
class AST_ActualParams: public AST_Node{
public:
    void accept         ( AST_Visitor&                  visitor ) override;
    void pushExpression ( std::unique_ptr<AST_Expr>     expr    );
public:
    std::vector<std::unique_ptr<AST_Expr>> expression_list;
};

// ------------------------------------------------------------------------------------------ Function Call
class AST_FunctionCall: public AST_Factor{
public:
    void accept             ( AST_Visitor&                          visitor ) override;
    void setActualParam     ( std::unique_ptr<AST_ActualParams>     param   );
    void setIden            ( std::unique_ptr<AST_Identifier>       iden    );
    std::string identifier;
public:
    std::unique_ptr<AST_ActualParams> actualparam;
};

// ------------------------------------------------------------------------------------------ Sub Expresion 
class AST_SubExpression : public AST_Factor{
public:
    void accept             (AST_Visitor&               visitor ) override;
    void setExpression      (std::unique_ptr<AST_Expr>  expr    );
public:
    std::unique_ptr<AST_Expr> expression;
};

// ------------------------------------------------------------------------------------------ Unary
class AST_Unary : public AST_Factor{
public:
    void accept             (AST_Visitor&               visitor ) override;
    void setFactor          (std::unique_ptr<AST_Factor>  fact    );
    
    token_t op;
public:
    std::unique_ptr<AST_Factor> factor;
};
    
// ------------------------------------------------------------------------------------------ Random
class AST_Random : public AST_Factor{
public:
    void accept         ( AST_Visitor&              visitor ) override;
    void setExpression  ( std::unique_ptr<AST_Expr> expr    );
public:
    std::unique_ptr<AST_Expr> expression;
};




/* =========================================================================================================================
 *   Litterals Grammer
 * =========================================================================================================================
 */

// ------------------------------------------------------------------------------------------ Boolean Node
class AST_Boolean: public AST_Literal{
public:
    void accept( AST_Visitor& visitor ) override;

    token_t bool_token;
};

// ------------------------------------------------------------------------------------------ Integer Node
class AST_Integer: public AST_Literal{
public:
    void accept( AST_Visitor& visitor ) override;

    std::string integer_value;
};

// ------------------------------------------------------------------------------------------ Float Node
class AST_Float: public AST_Literal{
public:
    void accept( AST_Visitor& visitor ) override;

    std::string float_value;
};

// ------------------------------------------------------------------------------------------ Colour Node
class AST_Colour: public AST_Literal{ 
public:
    void accept( AST_Visitor& visitor ) override;

    std::string colour_value;
};

// ------------------------------------------------------------------------------------------  Width Node
class AST_Width: public AST_Literal{
public:
    void accept( AST_Visitor& visitor ) override;
};

// ------------------------------------------------------------------------------------------ Height Node
class AST_Height: public AST_Literal{
public:
    void accept( AST_Visitor& visitor ) override;
};

// ------------------------------------------------------------------------------------------ Read
class AST_Read: public AST_Literal{ // ----------------- Read Node
public:
    void accept             ( AST_Visitor&                  visitor     ) override;
    void setExpression1     ( std::unique_ptr<AST_Expr>     expression  );
    void setExpression2     ( std::unique_ptr<AST_Expr>     expression  );
public:
    std::unique_ptr<AST_Expr> expression1;
    std::unique_ptr<AST_Expr> expression2;
};




/* =========================================================================================================================
 *   Operators Grammer
 * =========================================================================================================================
 */

// ------------------------------------------------------------------------------------------ Relational
class AST_Relational: public AST_Node{
public :
    void accept(AST_Visitor& visitor) override;

    token_t relational_token;
};

// ------------------------------------------------------------------------------------------ Multiplicative
class AST_Multiplicative: public AST_Node{
public :
    void accept(AST_Visitor& visitor) override;

    token_t mult_token;
};

// ------------------------------------------------------------------------------------------ Additive
class AST_Additive: public AST_Node{
public :
    void accept(AST_Visitor& visitor) override;

    token_t add_token;
};


#endif // AST_H