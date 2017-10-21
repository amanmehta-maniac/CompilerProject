#include <bits/stdc++.h>

#include "classdef.h"

using namespace std;
using namespace llvm;

map< string, int > symtab;

#define TBS printTabs()
#define outs(x)cout<<#x<<" is "<<x<<endl
ofstream out("XML_Vistor.txt");
int tabs_needed = 0;
const int tab_width = 4;
extern int errors;
/* Usefull Variables */
static Module *TheModule = new Module("Decaf compiler jit",llvm::getGlobalContext());
static LLVMContext &Context = getGlobalContext();
static IRBuilder<> Builder(Context);
static std::map<std::string, llvm::AllocaInst *> NamedValues;
static FunctionPassManager *TheFPM;

/* Usefull Functions */

static AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, const std::string &VarName, string type) {
  /* Allocates memory for local variables  on the stack of the function */

  /* Get the builder for current context */
  IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
  AllocaInst* Alloca;
  if(type == "int"){
    Alloca = TmpB.CreateAlloca(Type::getInt32Ty(getGlobalContext()), 0, VarName.c_str());
  }
  else if (type == "boolean"){
    Alloca = TmpB.CreateAlloca(Type::getInt1Ty(getGlobalContext()), 0, VarName.c_str());
  }
  return Alloca;
}



program::program(class declblocks* decls, class codeblocks* methods){
  this->codes = methods;
  this->decls = decls;
  cout<<"program finished\n";
  
}

void program::generateCode(){
  cout << "Generating LLVM IR Code\n";
  TheModule->dump();
}



declblocks::declblocks(){
  this->cnt = 0;
}

void declblocks::push_back(class declblock* var){
  decl_list.push_back(var);
  cnt++;
}



declblock::declblock(class Vars* vars){
  this->dataType = dataType;
  this->var_list = vars->getVarsList();
  for(int i = 0; i < var_list.size(); i++){
    var_list[i]->setDataType(dataType);
  }
}

vector<class Var*> declblock::getVarsList(){
  return var_list;
}



ifStmt::ifStmt(class boolExpr* cond, class codeblocks* block1){
  this->cond = cond;
  this->if_part = block1;
  // cout<<cond->expr1->lastVar->var<<" "<<cond->expr2->number<<"\n";
}

ifStmt::ifStmt(class boolExpr* cond, class codeblocks* block1, class codeblocks* block2){
  this->cond = cond;
  this->if_part = block1;
  this->else_part = block2;
}


vector<class Var*> Vars::getVarsList(){
  return vars_list;
}

void Vars::push_back(class Var* var){
  vars_list.push_back(var);
  // cout<<var->name<<" ";
  cnt++;
}

Var::Var(string declType, string name, unsigned int length){
  this->declType = declType;
  this->name = name;
  this->length = length;
}

Var::Var(string declType, string name, string flag, int init_val){
  this->declType = declType;
  this->name = name;
  this->init_val = init_val;
}

Var::Var(string declType, string name){
  this->declType = declType;
  this->name = name;
}

bool Var::isArray(){
  return (declType.compare("Array") == 0);
}

void Var::setDataType(string datatype){
  /* Sets the data type for the variable */
  this->dataType = datatype;
}

string Var::getName(){
  return name;
}


codeblock::codeblock(){
}

codeblocks::codeblocks(){
  this->cnt = 0;
}

void codeblocks::push_back(class codeblock* code){
  code_list.push_back(code);
  cnt++;
}

void codeblocks::push_back(class codeblock* code, string label){
  code_list.push_back(code);
  code->label = label;
  cnt++;
}



Expr::Expr(string expr_type, class binExpr* binex){
  this->expr_type = expr_type;
  this->binexpr = binex;
}

Expr::Expr(string expr_type, class last* temp){
  this->expr_type = expr_type;
  this->lastVar = temp;
}

Expr::Expr(string expr_type, int num){
  this->expr_type = expr_type;
  this->number = num;
}

boolExpr::boolExpr(class Expr* e1,class OperandType* oper_type,class Expr* e2){
  this->expr1 = e1;
  this->expr2 = e2;
  this->oper_type = oper_type;

}
boolExpr::boolExpr(class boolExpr* bexpr1,string oper,class boolExpr* bexpr2){
  this->bexpr1 = bexpr1;
  this->bexpr2 = bexpr2;
  this->oper = oper;
}


binExpr::binExpr(class Expr* lhs, string opr, class Expr* rhs){
  this->lhs = lhs;
  this->rhs = rhs;
  this->opr = opr;
}


last::last(string var, string last_type, class Expr* expr){
  this->var = var;
  this->last_type = last_type;
  this->expr = expr;
}

last::last(string var, string last_type){
  this->var = var;
  this->last_type = last_type;
}

gotoStmt::gotoStmt(string type, string label){
  this->type = type;
  this->label = label;
}

gotoStmt::gotoStmt(string type, string label, class boolExpr* cond){
  this->type = type;
  this->label = label;
  this->cond = cond;
}

whileStmt::whileStmt(class boolExpr* cond,class codeblocks* stmts){
  this->cond = cond;
  this->stmts = stmts;
  // cout<<"yo while\n";
}

OperandType::OperandType(string op){
  this->op = op;
}

unitClass::unitClass(string type, string name){
  this->type = type;
  this->name = name;
}

unitClass::unitClass(string type, int value){
  this->type = type;
  this->value = value;
}

forStmt::forStmt(string i, class Expr* initial, class unitClass* endcond, class codeblocks* stmts){
  this->i = i;
  this->initial = initial;
  this->endcond = endcond;
  this->stmts = stmts;

}
forStmt::forStmt(string i, class Expr* initial, class unitClass* endcond, class unitClass* incval, class codeblocks* stmts){
  this->i = i;
  this->initial = initial;
  this->endcond = endcond;
  this->incval = incval;
  this->stmts = stmts;

}


readStmt::readStmt(class unitClass* toread){
  this->toread = toread;

}

Assign::Assign(class last* loc, string opr, class Expr* expr){
  this->loc = loc;
  this->opr = opr;
  this->expr = expr;
  // cout<<loc->var<<opr<<expr->number<<"\n";
}

content::content(string toprint){
  this->toprint = toprint;
}

content::content(int num){
  this->num = num;
}

content::content(class last* lastval){
  this->lastval = lastval;
  // cout<<"lastval: "<<lastval->var;
}

void printStmt::push_back(class content* var){
  outs.push_back(var);
}

int Interpreter::visit(class program* obj){
  cout<<"in prog\n";
  Interpreter *it = new Interpreter();
  obj->decls->accept(it);
  obj->codes->accept(it);
  return 0;
}

int Interpreter::visit(class declblocks* obj){
  Interpreter *it = new Interpreter();
  for(auto i: obj->decl_list){
    i->accept(it);
  }
  return 0;
}

int Interpreter::visit(class declblock* obj){
  Interpreter *it = new Interpreter();
  for(auto i: obj->var_list){
    i->accept(it);
  }
  return 0;

}


int Interpreter::visit(class Vars* obj){
  Interpreter *it = new Interpreter();
  for(auto i: obj->vars_list){
    i->accept(it);
  }
  return 0;
}

int Interpreter::visit(class Var* obj){

  if(obj->declType == "Normal"){
    symtab[obj->name] = 0;
  }
  if(obj->declType == "NormalInit" or obj->declType == "NormalInit2"){
    symtab[obj->name] = obj->init_val;
  }
  if(obj->declType == "Array"){
    for(int i = 0; i< obj->length; i++){
      symtab[to_string(i) + obj->name] = 0;
      
    }
  }
  for(auto i: symtab){
    // cout<<i.first<<" "<<i.second<<"\n";
  }
  return 0;
}

int Interpreter::visit(class codeblocks* e){
  Interpreter *it = new Interpreter();
  for(auto i: e->code_list){
    i->accept(it);
  }
  return 0;
}
// int Interpreter::visit(class codeblock* e){
//   Interpreter *it = new Interpreter();
//   return 0;
// }
int Interpreter::visit(class Expr* e){
  Interpreter *it = new Interpreter();
  if(e->expr_type=="num") return e->number;
  else if(e->expr_type=="last") {
    return e->lastVar->accept(it);
  }
  else{
    return e->binexpr->accept(it);
  }
  return 0;
}
int Interpreter::visit(class boolExpr* e){
  Interpreter *it = new Interpreter();
  return 0;
}
int Interpreter::visit(class OperandType* e){
  Interpreter *it = new Interpreter();
  return 0;
}
int Interpreter::visit(class unitClass* e){
  Interpreter *it = new Interpreter();

  return 0;
}
int Interpreter::visit(class last* e){
  Interpreter *it = new Interpreter();
  if(e->last_type == "Normal"){
    return symtab[e->var];
  }
  else{
    return 0;
  }
  return 0;
}
int Interpreter::visit(class codeblock* e){
  return 0;
}
int Interpreter::visit(class Assign* e){
  Interpreter *it = new Interpreter();
  symtab[e->loc->var] = e->expr->accept(it);
  return 0;
}
int Interpreter::visit(class forStmt* e){
  Interpreter *it = new Interpreter();
  return 0;
}
int Interpreter::visit(class gotoStmt* e){
  Interpreter *it = new Interpreter();
  return 0;
}
int Interpreter::visit(class readStmt* e){
  Interpreter *it = new Interpreter();
  return 0;
}
int Interpreter::visit(class printStmt* e){
  Interpreter *it = new Interpreter();
  return 0;
}
int Interpreter::visit(class ifStmt* e){
  Interpreter *it = new Interpreter();
  return 0;
}
int Interpreter::visit(class whileStmt* e){
  Interpreter *it = new Interpreter();
  return 0;
}
int Interpreter::visit(class labelStmt* e){
  Interpreter *it = new Interpreter();
  return 0;
}
int Interpreter::visit(class binExpr* e){
  Interpreter *it = new Interpreter();
  return 0;
}
int Interpreter::visit(class content* e){
  Interpreter *it = new Interpreter();
  return 0;
}



