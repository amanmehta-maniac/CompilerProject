#include <bits/stdc++.h>

#include "classdef.h"

using namespace std;
using namespace llvm;

map< string, int > symtab;
map< string, int > labtab;
map<string, BasicBlock*> lab_tab;
bool ERROR = false;
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
FunctionType *FT = llvm::FunctionType::get(Builder.getVoidTy(), false);

Function *F = llvm::Function::Create(FT, Function::ExternalLinkage, "main", TheModule);
Constant *print_func = TheModule->getOrInsertFunction("printf",FunctionType::get(IntegerType::getInt32Ty(Context), PointerType::get(Type::getInt8Ty(Context), 0), true));

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
  if(ERROR) cout<<"Program has some errors to be fixed, check printed errors\n";
  else cout<<"program finished without errors\n";
  
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



ifStmt::ifStmt(string type, class boolExpr* cond, class codeblocks* block1){
  this->cond = cond;
  this->type = type;
  this->if_part = block1;
  // cout<<cond->expr1->lastVar->var<<" "<<cond->expr2->number<<"\n";
}

ifStmt::ifStmt(string type, class boolExpr* cond, class codeblocks* block1, class codeblocks* block2){
  this->cond = cond;
  this->type = type;
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
  this->label = "";
}

codeblocks::codeblocks(){
  this->cnt = 0;
}

void codeblocks::push_back(class codeblock* code){
  code_list.push_back(code);
  code->label = "NULL";
  cnt++;
}

void codeblocks::push_back(class codeblock* code, string gotolabel){
  code_list.push_back(code);
  code->label = gotolabel;
  // cout<<"label: "<<gotolabel<<"\nCNt: "<<cnt<<"\n";
  labtab[gotolabel] = cnt;
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

boolExpr::boolExpr(string boolType, class Expr* e1,class OperandType* oper_type,class Expr* e2){
  this->expr1 = e1;
  this->boolType = boolType;
  this->expr2 = e2;
  this->oper_type = oper_type;

}
boolExpr::boolExpr(string boolType, class boolExpr* bexpr1,string oper,class boolExpr* bexpr2){
  this->bexpr1 = bexpr1;
  this->boolType = boolType;
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
  this->forType = 1;


}
forStmt::forStmt(string i, class Expr* initial, class unitClass* endcond, class unitClass* incval, class codeblocks* stmts){
  this->i = i;
  this->initial = initial;
  this->endcond = endcond;
  this->incval = incval;
  this->stmts = stmts;
  this->forType = 2;

}


readStmt::readStmt(class last* toread){
  this->toread = toread;

}

Assign::Assign(class last* loc, string opr, class Expr* expr){
  this->loc = loc;
  this->opr = opr;
  this->expr = expr;
}

content::content(string toprint,string content_type){
  this->type=1;
  this->toprint = toprint;
  this->content_type = content_type;
}

content::content(int num,string content_type){
  this->type=2;
  this->num = num;
  this->content_type = content_type;
}

content::content(class last* lastval,string content_type){
  this->type=3;
  this->lastval = lastval;
  this->content_type = content_type;
  // cout<<"lastval: "<<lastval->var;
}

void printStmt::push_back(class content* var){
  outs.push_back(var);
}


/* INTERPRETERS */

int Interpreter::visit(class program* obj){
  // cout<<"in prog\n";
  Interpreter *it = new Interpreter();
  obj->decls->accept(it);
  obj->codes->accept(it);
  // for(auto i: labtab){
  //   cout<<i.first<<" "<<i.second<<"\n";
  // }
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
  // cout<<"\n";
  // for(auto i: symtab){
  //   cout<<i.first<<" "<<i.second<<"\n";
  // }

  return 0;
}

int Interpreter::visit(class codeblocks* e){
  Interpreter *it = new Interpreter();
  int cnt = 0;
  int sz = e->cnt;
  int i = 0;
  while(i<sz){
      int x = e->code_list[i]->accept(it);
      if(x==-100){
        // cout<<"statemt: "<<i<<"\n";
        string lab = e->code_list[i]->getlabel();
        if(labtab.find(lab)==labtab.end()){
          cout<<"ERR->Label: "<<lab<<" no found!\n";
          ERROR = true;
          break;
          return 0;
        }
        // cout<<"next is: "<<lab<<"\ncnt: "<<labtab[lab];
        i = labtab[lab];
      }
      else{
        i++;
      }
  }
  return 0;
}

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
  if(e->boolType=="expr"){
    if(e->oper_type->op=="=="){
      return e->expr1->accept(it) == e->expr2->accept(it);
    }
    if(e->oper_type->op=="!="){
      return e->expr1->accept(it) != e->expr2->accept(it);
    }
    if(e->oper_type->op==">="){
      return e->expr1->accept(it) >= e->expr2->accept(it);
    }
    if(e->oper_type->op=="<="){
      return e->expr1->accept(it) <= e->expr2->accept(it);
    }
    if(e->oper_type->op==">"){
      return e->expr1->accept(it) > e->expr2->accept(it);
    }
    if(e->oper_type->op=="<"){
      return e->expr1->accept(it) < e->expr2->accept(it);
    }
  }
  else{
    if(e->oper=="OR"){
      return (e->bexpr1->accept(it) || e->bexpr2->accept(it));
    }
    if(e->oper=="AND"){
      return (e->bexpr1->accept(it) && e->bexpr2->accept(it));
    }
  }
  return 0;
}
int Interpreter::visit(class OperandType* e){
  Interpreter *it = new Interpreter();
  if(e->op=="==") return 1;
  if(e->op=="!=") return 2;
  if(e->op==">=") return 3;
  if(e->op=="<=") return 4;
  if(e->op==">") return 5;
  if(e->op=="<") return 6;
  return 0;
}
int Interpreter::visit(class unitClass* e){
  Interpreter *it = new Interpreter();

  return 0;
}
int Interpreter::visit(class last* e){
  Interpreter *it = new Interpreter();
  if(e->last_type == "Normal"){
    if (symtab.find(e->var)==symtab.end()){
    cout<<"ERR->Variable: "<<e->var<<" is being used without being previously defined\n";
    ERROR = true;
    return 0;
  }
    return symtab[e->var];
  }
  else{
    return e->expr->accept(it);
  }
  return 0;
}
int Interpreter::visit(class codeblock* e){
  return 0;
}
int Interpreter::visit(class Assign* e){
  Interpreter *it = new Interpreter();
  if(e->loc->last_type=="Normal"){
    if (symtab.find(e->loc->var)==symtab.end()){
      cout<<"ERR->Variablesassign: "<<e->loc->var<<" is being used without being previously defined\n";
      ERROR = true;
      return 0;
    }
    if(e->opr=="=") symtab[e->loc->var] = e->expr->accept(it);
    else if(e->opr=="+=") symtab[e->loc->var] += e->expr->accept(it);
    else symtab[e->loc->var] -= e->expr->accept(it);
    return 0;
  }
  else{
    if(e->opr=="=") symtab[to_string(e->loc->expr->accept(it)) + e->loc->var] = e->expr->accept(it);
    else if(e->opr=="+=") symtab[to_string(e->loc->expr->accept(it)) + e->loc->var] += e->expr->accept(it);
    else symtab[to_string(e->loc->expr->accept(it)) + e->loc->var] -= e->expr->accept(it);
    return 0;
  }
}
int Interpreter::visit(class forStmt* e){
  Interpreter *it = new Interpreter();
  if(e->forType==1){
    // cout<<"fortype==1\n";
    if (symtab.find(e->i)==symtab.end()){
      cout<<"ERR->Variable: "<<e->i<<" is being used without being previously defined\n";
      ERROR = true;
      return 0;
    }
    symtab[e->i] = e->initial->accept(it);
    if(e->endcond->type=="id"){
        if (symtab.find(e->endcond->name)==symtab.end()){
          cout<<"ERR->Variable: "<<e->endcond->name<<" is being used without being previously defined\n";
          ERROR = true;
          return 0;
        }

      while(symtab[e->i]<symtab[e->endcond->name]){
        e->stmts->accept(it);
        symtab[e->i] = symtab[e->i] + 1;
      }
    }
    else{
      while(symtab[e->i]<e->endcond->value){
        e->stmts->accept(it);
        symtab[e->i] = symtab[e->i] + 1;
      }

    }
  }
  else{
    // cout<<"fortype==2\n";
    if (symtab.find(e->i)==symtab.end()){
      cout<<"ERR->Variable: "<<e->i<<" is being used without being previously defined\n";
      ERROR = true;
      return 0;
    }

    symtab[e->i] = e->initial->accept(it);
    if(e->endcond->type=="id"){
        if (symtab.find(e->endcond->name)==symtab.end()){
          cout<<"ERR->Variable: "<<e->endcond->name<<" is being used without being previously defined\n";
          ERROR = true;
          return 0;
        }

      while(symtab[e->i]<symtab[e->endcond->name]){
        e->stmts->accept(it);
        if(e->incval->type=="id") {
          if (symtab.find(e->incval->name)==symtab.end()){
          cout<<"ERR->Variable: "<<e->incval->name<<" is being used without being previously defined\n";
          ERROR = true;
          return 0;
        }
          symtab[e->i] = symtab[e->i] + symtab[e->incval->name];
        }
        if(e->incval->type!="id") symtab[e->i] = symtab[e->i] + e->incval->value;
      }
    }
    else{
      while(symtab[e->i]<e->endcond->value){
        e->stmts->accept(it);
        if(e->incval->type=="id") {
            if (symtab.find(e->incval->name)==symtab.end()){
            cout<<"ERR->Variable: "<<e->incval->name<<" is being used without being previously defined\n";
            ERROR = true;
            return 0;
          }
          symtab[e->i] = symtab[e->i] + symtab[e->incval->name];
        }
        if(e->incval->type!="id") symtab[e->i] = symtab[e->i] + e->incval->value;
      }
    }
  }
  // cout<<"after FOR\n";
  // for(auto i: symtab){
  //   cout<<i.first<<" "<<i.second<<"\n";
  // }
  return 0;
}
int Interpreter::visit(class gotoStmt* e){
  Interpreter *it = new Interpreter();
  if(e->type=="uncond"){
    return -100;
  }
  else{
    // cout<<"conditional!\n";
    if(e->cond->accept(it)) return -100;
  }
  return 0;
}
int Interpreter::visit(class readStmt* e){
  Interpreter *it = new Interpreter();
  if(e->toread->last_type=="Normal") {
    if (symtab.find(e->toread->var)==symtab.end()){
          cout<<"ERR->Variable: "<<e->toread->var<<" is being used without being previously defined\n";
          ERROR = true;
          return 0;
        }
    symtab[e->toread->var] = e->toread->accept(it);
  }
  else {
    if (symtab.find(to_string(e->toread->expr->accept(it))+e->toread->var)==symtab.end()){
          cout<<"ERR->Variable: "<<e->toread->var<<"["<<to_string(e->toread->expr->accept(it))<<"] is being used without being previously defined\n";
          ERROR = true;
          return 0;
        }
    symtab[to_string(e->toread->expr->accept(it)) + e->toread->var] = e->toread->accept(it);
  }
  return 0;
}
int Interpreter::visit(class printStmt* e){
  Interpreter *it = new Interpreter();
  if(e->type==2){
    for(auto i: e->outs) {
      i->accept(it);
    }
    cout<<"\n";
  }
  else{
    for(auto i: e->outs) {
      i->accept(it);
    }
  }
  return 0;
}


int Interpreter::visit(class ifStmt* e){
  Interpreter *it = new Interpreter();
  if(e->cond->accept(it) || e->type=="if"){
    e->if_part->accept(it);
  }
  else{
    e->else_part->accept(it);
  }
  return 0;
}
int Interpreter::visit(class whileStmt* e){
  Interpreter *it = new Interpreter();
  while(e->cond->accept(it)){
    e->stmts->accept(it);
  }
  return 0;
}


int Interpreter::visit(class labelStmt* e){
  Interpreter *it = new Interpreter();
  return 0;
}
int Interpreter::visit(class binExpr* e){
  Interpreter *it = new Interpreter();
  if(e->opr=="+"){
    return e->lhs->accept(it) + e->rhs->accept(it);
  }
  if(e->opr=="-"){
    return e->lhs->accept(it) - e->rhs->accept(it);
  }
  if(e->opr=="*"){
    return e->lhs->accept(it) * e->rhs->accept(it);
  }
  if(e->opr=="/"){
    return e->lhs->accept(it) / e->rhs->accept(it);
  }
  return 0;
}
int Interpreter::visit(class content* e){
  Interpreter *it = new Interpreter();
  if(e->content_type=="string") cout<<e->toprint<<" ";
  else if(e->content_type=="num") cout<<e->num<<" ";
  else{
    cout<<e->lastval->accept(it)<<" ";
  }
  return 0;
}

/*--------CODEGENS---------*/


Value* declblocks::codegen(){
  int sz = decl_list.size();
  for (int i = 0; i < sz; ++i)
  {
    decl_list[i]->codegen();
    /* code */
  }
  Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
  return v;
}

Value* declblock::codegen(){
  int sz = var_list.size();
  for (int i = 0; i < sz; ++i){
    class Var* var = var_list[i];
    Type* ty = Type::getInt32Ty(Context);
    if(var->declType=="Normal"){
     TheModule->getOrInsertGlobal(var->name,Builder.getInt32Ty());
     PointerType* ptrTy = PointerType::get(ty,0);
     GlobalVariable* gv = TheModule->getNamedGlobal(var->name);
     gv->setLinkage(GlobalValue::CommonLinkage);
     ConstantInt* const_int_val = ConstantInt::get(Context, APInt(32,0));
     gv->setInitializer(const_int_val);
    }

    else if(var->declType=="NormalInit"){
     TheModule->getOrInsertGlobal(var->name,Builder.getInt32Ty());
     PointerType* ptrTy = PointerType::get(ty,0);
     GlobalVariable* gv = TheModule->getNamedGlobal(var->name);
     gv->setLinkage(GlobalValue::CommonLinkage);
     ConstantInt* const_int_val = ConstantInt::get(Context, APInt(32,var->init_val));
     gv->setInitializer(const_int_val);
    }
    else if(var->declType=="Array"){
      ArrayType* arrType= ArrayType::get(ty,var->length);
      PointerType* PointerTy_1 = PointerType::get(ArrayType::get(ty,var->length),0);
      GlobalVariable* gv = new GlobalVariable(*TheModule,arrType,false,GlobalValue::ExternalLinkage,0,var->getName());
      gv->setLinkage(GlobalValue::CommonLinkage);
      gv->setInitializer(ConstantAggregateZero::get(arrType));
    }

  }
  Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
  return v;
}

Value* program::codegen(){
  Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
  decls->codegen();
  BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", F);
  Builder.SetInsertPoint(BB);
  codes->codegen();
  Builder.CreateRetVoid();
  return v;
} 

Value* codeblocks::codegen(){
  Value *v = ConstantInt::get(getGlobalContext(), APInt(32,1));
  int sz = code_list.size();
  for (int i = 0; i < sz; ++i)
  {
    if(code_list[i]->label != "NULL"){
      BasicBlock *BB = BasicBlock::Create(getGlobalContext(),code_list[i]->label, F);
      Builder.SetInsertPoint(BB);
      lab_tab[code_list[i]->label]= BB;
      code_list[i]->codegen();
    }
    else {
      code_list[i]->codegen();

    }
  }
  return v;
}

Value* Assign::codegen(){
  Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
  Value* lhsv_register = loc->codegen();
  Value* rhsv = expr->codegen();
  if(expr->expr_type=="last"){
    cout<<"yep my expr is last type\n";
    rhsv = Builder.CreateLoad(rhsv);
  }
  if(opr=="="){
    rhsv = Builder.CreateStore(rhsv,lhsv_register);
  }
  else if(opr=="+="){
    rhsv = Builder.CreateAdd(lhsv_register, rhsv,"addEqualToTmp");
    rhsv = Builder.CreateStore(rhsv,lhsv_register);
  }
  else if (opr == "-="){
    rhsv = Builder.CreateSub(lhsv_register, rhsv,"subEqualToTmp");
    rhsv = Builder.CreateStore(rhsv,lhsv_register);
  }
  return rhsv;
}

Value* Expr::codegen(){
  Value* v = ConstantInt::get(getGlobalContext(), llvm::APInt(32,0));
  if(expr_type=="num"){
    return ConstantInt::get(getGlobalContext(), llvm::APInt(32,number));
  }
  else if(expr_type=="last"){
    cout<<"yes in last!! with variable = "<<lastVar->var<<"with type= "<<lastVar->last_type<<"\n";
    return lastVar->codegen();
  }
  else if(expr_type=="expr"){
    return binexpr->codegen();
  }
  return v;
}


Value* binExpr::codegen(){
  Value* v = ConstantInt::get(getGlobalContext(), llvm::APInt(32,0));
  // cout<<"inbinexpr\n";
  Value* left = lhs->codegen();
  Value* right = rhs->codegen();
  if(lhs->expr_type == "last"){
    left = Builder.CreateLoad(left);
  }
  if(rhs->expr_type == "last"){
    right = Builder.CreateLoad(right);
  }
  if(left == 0){
    errors++;
    return reportError::ErrorV("Error in left operand of " + opr);
  }
  else if(right == 0){
    errors++;
    return reportError::ErrorV("Error in right operand of " + opr);
  }

  if(opr=="+"){
    v = Builder.CreateAdd(left,right,"addtmp");
  }
  else if (opr == "-"){
    v = Builder.CreateSub(left,right,"subtmp");
  }
  else if (opr == "*"){
    v = Builder.CreateMul(left,right,"multmp");
  }
  else if (opr == "/"){
    v = Builder.CreateUDiv(left,right,"divtmp");
  }
  return v;
}

Value* ifStmt::codegen(){

  Value* v = ConstantInt::get(getGlobalContext(), llvm::APInt(32,2));
  Value* v2 = ConstantInt::get(getGlobalContext(), llvm::APInt(32,2));
  Value* condi = cond->codegen();
  BasicBlock *ifBlock = BasicBlock::Create(Context, "if", F);
  BasicBlock *elseBlock = BasicBlock::Create(Context, "else",F);
  BasicBlock *nextBlock = BasicBlock::Create(Context, "ifcont",F);
  Builder.CreateCondBr(condi, ifBlock, elseBlock);
  Builder.SetInsertPoint(ifBlock);
  // Builder.CreateAdd(v,v2,"PPPPP");
  // Builder.CreateSub(v,v2,"QQQQ");
  Value* ifval  = if_part->codegen();
  if(ifval == 0){
    return v;
  }

  Builder.CreateBr(nextBlock);
  // ifBlock = Builder.GetInsertBlock();

  // ifBlock = 
  F->getBasicBlockList().push_back(elseBlock);
  Builder.SetInsertPoint(elseBlock);
  Value* elseval;
  // cout<<"type is: "<<type<<"\n";
  if(type == "else")
  {
    elseval = else_part->codegen();
    if(elseval == 0){
      return v;
    }
  }
  Builder.CreateBr(nextBlock);
  F->getBasicBlockList().push_back(nextBlock);  
  // unsigned PhiSize = 2;
  // elseBlock = Builder.GetInsertBlock();
  Builder.SetInsertPoint(nextBlock);
  // PHINode *phi = Builder.CreatePHI(Type::getInt32Ty(getGlobalContext()),PhiSize,"iftmp");
  // phi->addIncoming(ifval,ifBlock);
  // phi->addIncoming(elseval,elseBlock);
  return elseval;
}

Value* boolExpr::codegen(){
  Value* v;
  if(boolType=="expr")
  {
    Value* lhs = expr1->codegen();
    Value* rhs = expr2->codegen();
    if(expr1->expr_type == "last"){
      lhs = Builder.CreateLoad(lhs);
    }
    if(expr2->expr_type == "last"){
      rhs = Builder.CreateLoad(rhs);
    }
    string opr = oper_type->op;
    if (opr == "<"){
      v =  Builder.CreateICmpULT(lhs,rhs,"ltcomparetmp");
    }
    else if (opr == ">"){
      v =  Builder.CreateICmpUGT(lhs,rhs,"gtcomparetmp");
    }
    else if (opr == "<="){
      v =  Builder.CreateICmpULE(lhs,rhs,"lecomparetmp");
    }
    else if (opr == ">="){
      v =  Builder.CreateICmpUGE(lhs,rhs,"gecomparetmp");
    }
    else if (opr == "=="){
      v =  Builder.CreateICmpEQ(lhs,rhs,"equalcomparetmp");
    }
    else if (opr == "!="){
      v =  Builder.CreateICmpNE(lhs,rhs,"notequalcomparetmp");
    }  
  }
  return v;
}


Value* forStmt::codegen(){
  Value* v = ConstantInt::get(getGlobalContext(), llvm::APInt(32,0));
  Value* initval = initial->codegen();


  BasicBlock* loopBB = BasicBlock::Create(getGlobalContext(),"loop",F);
  BasicBlock *afterBB = BasicBlock::Create(getGlobalContext(), "afterloop", F);
  // Builder.CreateBr(loopBB);
  Value* endcondval;
  if(endcond->type=="num") {
    endcondval = ConstantInt::get(getGlobalContext(), llvm::APInt(32,endcond->value));
  }
  else{
    endcondval = TheModule->getNamedGlobal(endcond->name);  
  }
  endcondval = Builder.CreateICmpULT(initval,endcondval,"ltcomparetmp");
  BasicBlock* preheaderBB = Builder.GetInsertBlock();

  Builder.CreateCondBr(endcondval, loopBB, afterBB);

  Builder.SetInsertPoint(loopBB);
  PHINode* phi = Builder.CreatePHI(Type::getInt32Ty(getGlobalContext()), 2, i.c_str());
  phi->addIncoming(initval,preheaderBB);
  if(stmts->codegen()==0){
    return 0;
  }
  Value* jump;
  cout<<"firtpye is: "<<forType<<"\n";
  if(forType==2){
    if(incval->type=="num"){
      jump = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), incval->value);
    }
    else{
      jump = TheModule->getNamedGlobal(incval->name);  
    }
  }
  else{
    jump = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), 1);
  }
  Value* nextval = Builder.CreateAdd(phi, jump, "nextval");
  if(endcond->type=="num") {
    endcondval = ConstantInt::get(getGlobalContext(), llvm::APInt(32,endcond->value));
  }
  else{
    endcondval = TheModule->getNamedGlobal(endcond->name);  
  }
  endcondval = Builder.CreateICmpULT(nextval,endcondval,"ltcomparetmp");
  BasicBlock *loopEndBlock = Builder.GetInsertBlock();
  Builder.CreateCondBr(endcondval, loopBB, afterBB);
  Builder.SetInsertPoint(afterBB);
  phi->addIncoming(nextval, loopEndBlock);


  llvm::Value *V = ConstantInt::get(getGlobalContext(), APInt(32,1));
  return V;
}

Value* last::codegen(){
  llvm::Value *v = TheModule->getNamedGlobal(var);  
  if(v==0){
    errors++;
    return reportError::ErrorV("Unknown Variable name " + var);
  }
  if(last_type=="Normal"){
    cout<<"hurray normal\n";
    // v = Builder.CreateLoad(v);
    return v;
  }
  // cout<<"in arrrr, var: "<<var<<"\n";
  v = TheModule->getNamedGlobal(var); 
  Value* index = expr->codegen();
  if(expr->expr_type == "last"){
    // index = TheModule->getNamedGlobal(index); 
    index = Builder.CreateLoad(index);
    cout<<"index created hafjkdaf\n";
  }
  cout<<"before index"<<"\n";
  if(index==0){
    errors++;
    return reportError::ErrorV("Invalid array index");
  }
  // cout<<"after index1"<<"\n";
  vector<Value*> array_index;
  // cout<<"after index2"<<"\n";
  array_index.push_back(Builder.getInt32(0));
  // cout<<"after index3"<<"\n";
  array_index.push_back(index);
  // cout<<"after index4"<<"\n";
  v = Builder.CreateGEP(v, array_index, var+"_Index");
  // cout<<"after index5"<<"\n";
  return v;  
}


Value* whileStmt::codegen(){
  llvm::Value *v = ConstantInt::get(getGlobalContext(), APInt(32,1));
  Value* endcondval = cond->codegen();
  BasicBlock* loopBB = BasicBlock::Create(getGlobalContext(),"loop",F);
  BasicBlock *afterBB = BasicBlock::Create(getGlobalContext(), "afterloop", F);
  Builder.CreateCondBr(endcondval, loopBB, afterBB);
  Builder.SetInsertPoint(loopBB);
  // Builder.CreateBr(loopBB);
  if(stmts->codegen()==0){
    return 0;
  }
  Builder.CreateCondBr(endcondval, loopBB, afterBB);
  BasicBlock *loopEndBlock = Builder.GetInsertBlock();
  Builder.SetInsertPoint(afterBB);
  return v;  
}

// Value* printStmt::codegen(){

//   llvm::Value *toprint = builder.CreateGlobalStringPtr();
// }

Value* gotoStmt::codegen(){
  llvm::Value *v = ConstantInt::get(getGlobalContext(), APInt(32,0));
  BasicBlock* labelBB = BasicBlock::Create(getGlobalContext(),"aftergoto",F);
  if(type=="uncond"){
    Builder.CreateBr(lab_tab[label]);
  }
  else{
    Value* res = cond->codegen();
    Builder.CreateCondBr(res,lab_tab[label],labelBB);
  }
  Builder.SetInsertPoint(labelBB);  
  return v;
}

Value* printStmt::codegen(){
  llvm::Value *v = ConstantInt::get(getGlobalContext(), APInt(32,0));
  if(false){
    //   int sz = outs.size();
    //   llvm::Value *helloWorld;
    //   llvm::Constant *putsFunc;
    //   for(int i = 0; i < sz; i++){
    //     if(outs[i]->type==1){
    //       helloWorld = Builder.CreateGlobalStringPtr(string(outs[i]->toprint));
         
    //       std::vector<llvm::Type *> putsArgs;
    //       putsArgs.push_back(Builder.getInt8Ty()->getPointerTo());
    //       llvm::ArrayRef<llvm::Type*>  argsRef(putsArgs);
         
    //       llvm::FunctionType *putsType = 
    //       llvm::FunctionType::get(Builder.getInt32Ty(), argsRef, false);
    //       putsFunc = TheModule->getOrInsertFunction("puts", putsType);
    //     }
    //     else if(outs[i]->type==2){
    //       helloWorld = Builder.CreateGlobalStringPtr(to_string(outs[i]->num));
    //       // helloWorld = TheModule->getNamedGlobal()
    //       std::vector<llvm::Type *> putsArgs;
    //       putsArgs.push_back(Builder.getInt8Ty()->getPointerTo());
    //       llvm::ArrayRef<llvm::Type*>  argsRef(putsArgs);
         
    //       llvm::FunctionType *putsType = 
    //       llvm::FunctionType::get(Builder.getInt32Ty(), argsRef, false);
    //       putsFunc = TheModule->getOrInsertFunction("puts", putsType);
    //     }
    //     else{
    //       helloWorld = TheModule->getNamedGlobal(outs[i]->lastval->var);
    //       std::vector<llvm::Type *> putsArgs;
    //       putsArgs.push_back(Builder.getInt8Ty()->getPointerTo());
    //       llvm::ArrayRef<llvm::Type*>  argsRef(putsArgs);
         
    //       llvm::FunctionType *putsType = 
    //       llvm::FunctionType::get(Builder.getInt32Ty(), argsRef, false);
    //       putsFunc = TheModule->getOrInsertFunction("puts", putsType);

    //     }
    //     Builder.CreateCall(putsFunc, helloWorld);
    // }
  }
  else {
    cout<<"typeis : "<<type<<"\n";
    std::vector<Value *> arguments;
    int sz = outs.size();
    Value *v,*val,*to_print;
    for(int i = 0; i < sz; i++){
      arguments.clear();
      if(outs[i]->content_type=="last"){
        val= Builder.CreateGlobalStringPtr("%d");
        to_print = outs[i]->codegen();
      }
      else if(outs[i]->content_type=="string"){
        to_print = Builder.CreateGlobalStringPtr(outs[i]->toprint.substr(1,outs[i]->toprint.size()-2));
        val = Builder.CreateGlobalStringPtr("%s");
      }
      arguments.push_back(val);
      arguments.push_back(to_print);
      v = Builder.CreateCall(print_func, arguments, "printfCall");
      arguments.clear();
      if(i!=sz-1){
        val = Builder.CreateGlobalStringPtr("%s");
        to_print = Builder.CreateGlobalStringPtr(" ");
        arguments.push_back(val);
        arguments.push_back(to_print);
        v =  Builder.CreateCall(print_func, arguments, "printfCall");
      }
    }
    arguments.clear();
    if(type == 2){
      cout<<"shajsdgsahgidsgsgjkoshk\n";
      val = Builder.CreateGlobalStringPtr("%s");
      to_print = Builder.CreateGlobalStringPtr("\n");
      arguments.push_back(val);
      arguments.push_back(to_print);
      v =  Builder.CreateCall(print_func, arguments, "printfCall");
    }
  }
  return v;  
}