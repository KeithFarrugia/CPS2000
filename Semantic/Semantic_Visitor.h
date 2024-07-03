#ifndef SEMANTIC_VISITOR_H
#define SEMANTIC_VISITOR_H
#include "../Parser/Abstract_Syntax_Tree/AST_Nodes.h"
#include "../Utility/types/Scope.h"
#include "../Utility/Utility.h"
#include <cctype>
#include <iomanip>

class Semantic_Visitor : public AST_Visitor{
public:
    Semantic_Visitor();

    void visit_program_start        (const Program*                         node) override;
    void visit_program_end          (const Program*                         node) override;
    // ---------------------------------------------------------------------------------------- Statements
    void visit_assignment           (const AST_Assignment*                  node) override;
    void visit_var_dec              (const AST_VariableDec*                 node) override;
    void visit_var_dec_suf_norm     (const AST_VariableDec_Suffix_Norm*     node) override;
    void visit_var_dec_suf_array    (const AST_VariableDec_Suffix_Array*    node) override;

    void visit_print                (const AST_Print*                       node) override;
    void visit_delay                (const AST_Delay*                       node) override;
    void visit_write_box            (const AST_Write_Box*                   node) override;
    void visit_write                (const AST_Write*                       node) override;
    void visit_clear                (const AST_Clear*                       node) override;

    void visit_return               (const AST_Return*                      node) override;

    void visit_start_if             (const AST_If*                          node) override;
    void visit_end_if               (const AST_If*                          node) override;
    void visit_start_else           (const AST_If*                          node) override;
    void visit_end_else             (const AST_If*                          node) override;

    void visit_start_for            (const AST_For*                         node) override;
    void visit_jump_for             (const AST_For*                         node) override;
    void visit_skip_for             (const AST_For*                         node) override;
    void visit_end_for              (const AST_For*                         node) override;

    void visit_start_while          (const AST_While*                       node) override;
    void visit_skip_while           (const AST_While*                       node) override;
    void visit_end_while            (const AST_While*                       node) override;

    void visit_func_dec_start       (const AST_Func_Dec*                    node) override;
    void visit_func_dec_skip        (const AST_Func_Dec*                    node) override;
    void visit_func_dec_end         (const AST_Func_Dec*                    node) override;
    void visit_form_params          (const AST_Form_Params*                 node) override;
    void visit_form_param           (const AST_Form_Param*                  node) override;

    void visit_start_block          (const AST_Block*                       node) override;
    void visit_end_block            (const AST_Block*                       node) override;

    
    void visit_start_weak_block     (const AST_Weak_Block*                  node) override;
    void visit_end_weak_block       (const AST_Weak_Block*                  node) override;

    // ---------------------------------------------------------------------------------------- Expressions
    void visit_term                 (const AST_Term*                        node) override;
    void visit_simple_expr          (const AST_Simple_Expr*                 node) override;
    void visit_expr                 (const AST_Expr*                        node) override;

    // ---------------------------------------------------------------------------------------- Factors
    void visit_iden                 (const AST_Identifier*                  node) override;
    void visit_act_params           (const AST_ActualParams*                node) override;
    void visit_func_call            (const AST_FunctionCall*                node) override;
    void visit_sub_expr             (const AST_SubExpression*               node) override;
    void visit_unary                (const AST_Unary*                       node) override;
    void visit_random               (const AST_Random*                      node) override;

    // ---------------------------------------------------------------------------------------- Litterals
    void visit_bool                 (const AST_Boolean*                     node) override;
    void visit_int                  (const AST_Integer*                     node) override;
    void visit_float                (const AST_Float*                       node) override;
    void visit_colour               (const AST_Colour*                      node) override;
    void visit_width                (const AST_Width*                       node) override;
    void visit_height               (const AST_Height*                      node) override;
    void visit_read                 (const AST_Read*                        node) override;

    // ---------------------------------------------------------------------------------------- Operators
    void visit_rel                  (const AST_Relational*                  node) override;
    void visit_mult                 (const AST_Multiplicative*              node) override;
    void visit_add                  (const AST_Additive*                    node) override;


    // ---------------------------------------------------------------------------------------- Other Functions
    void reset      () override { tab = 0;  }
    void inc_tab    () override { tab++;    }
    void dec_tab    () override { tab--;    }

private:

    // ---------------------------------------------------------------------------------------- Function Declaration
    std::vector<scope_t>&   getCurrentScopeStack    ();

    type_set_t              popTypeStack            ();
    void                    pushTypeStack           (token_t    t               );
    void                    pushTypeStack           (token_t    t,      int l   );
    void                    pushVarToScope          (variable_t var             );

    const variable_t        findVariable            (std::string variable_name);
    const function_t        findFunction            (std::string function_name);
    bool                    isVariableNameUsed      (std::string variable_name);
    bool                    isFunctionNameUsed      (std::string function_name);

    void                    errMS( std::string loc ,                   std::string mes);
    void                    errMS( std::string loc1, std::string loc2, std::string mes);

    // ---------------------------------------------------------------------------------------- Variables
    int tab;

    bool in_main_scope;
    bool func_has_return;

    std::vector<scope_t>        main_scope;
    std::vector<scope_t>        func_scope; // This is for function declarations
    std::vector<type_set_t>     type_stack;
    std::vector<function_t>     global_functions;
};

#endif //SEMANTIC_VISITOR_H