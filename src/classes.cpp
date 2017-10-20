#include <bits/stdc++.h>

#include "ClassDefs.h"

using namespace std;
using namespace llvm;

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

string getOperation(string opr){
  if(opr.compare("+") == 0){
    return string("Addition");
  }
  else if (opr.compare("-") == 0){
    return string("Subtraction");
  }
  else if(opr.compare("*")  == 0){
    return string("Multiplication");
  }
  else if (opr.compare("/")  == 0){
    return string("Division");
  }
  else if (opr.compare("%") == 0){
    return string("Modulus");
  }
  else if (opr.compare("<") == 0){
    return string("Less_than");
  }
  else if (opr.compare(">") == 0){
    return string("Greater_than");
  }
  else if (opr.compare("<=") == 0){
    return string("Less_than_Equal_to");
  }
  else if (opr.compare(">=") == 0){
    return string("Greater_than_Equal_to");
  }
  else if (opr.compare("==") == 0){
    return string("Compare_equal");
  }
  else if (opr.compare("&&") == 0){
    return string("Conditional_and");
  }
  else if (opr.compare("||") == 0){
    return string("Conditional_or");
  }
  else if (opr.compare("=") == 0){
    return string("Equal_assign");
  }
  else if (opr.compare("-=") == 0){
    return string("Subequal_assign");
  }
  else if (opr.compare("=") == 0){
    return string("Addequal_assign");
  }
}

string replace_newline(string str){
  size_t index = 0;
  string search="\\n";
//  cout << "Called replace for " << str << endl;
  while (true) {
    /* Locate the substring to replace. */
    index = str.find(search, index);
    if (index == std::string::npos) break;

    /* Make the replacement. */
  //  cout << "Replaced\n";
    str.erase( index, search.length() );
    str.insert( index, "\n" );

    /* Advance index forward so the next iteration doesn't pick it up as well. */
    index += 1;
  }
  return str;
}

void printTabs(){
  for(int i = 0; i < tabs_needed; i++){
    for(int j = 0; j < tab_width; j++)
    out << " ";
  }
}

program::program(string name, class declblock* decls, class codeblocks* methods){
  this->methods = methods;
  this->name = name;
  this->fields = decls;
}

Value* program::codegen(){
  Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
  V = fields->codegen();
  V = methods->codegen();
  return V;
}
void program::generateCode(){
  cout << "Generating LLVM IR Code\n";
  TheModule->dump();
}

void program::traverse(){
  TBS;
  out << "<program>\n";
  tabs_needed++;
  fields->traverse();
  methods->traverse();
  tabs_needed--;
  TBS;
  out << "</program>\n";
}


declblocks::declblocks(){
  this->cnt = 0;
}

void declblocks::push_back(class declblock* var){
  decl_list.push_back(var);
  cnt++;
}

Value* declblocks::codegen(){
  for(int i = 0; i < decl_list.size(); i++){
    decl_list[i]->codegen();
  }
  Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
  return v;
}

void declblocks::traverse(){
  TBS;
  out << "<field_declarations count=\"" << cnt << "\">\n";
  tabs_needed++;
  for (int i = 0; i < decl_list.size(); i++){
    decl_list[i]->traverse();
  }
  tabs_needed--;
  TBS;
  out << "</field_declarations>\n";

}

declblock::declblock(string dataType, class Vars* vars){
  this->dataType = dataType;
  this->var_list = vars->getVarsList();
  for(int i = 0; i < var_list.size(); i++){
    var_list[i]->setDataType(dataType);
  }
}

vector<class Var*> declblock::getVarsList(){
  return var_list;
}

Value* declblock::codegen(){
  for(int i = 0; i < var_list.size(); i++){
    /* Allocate one location of global variable for all */
    class Var* var = var_list[i];
    llvm::Type *ty;
    if(dataType == "int"){
      ty = Type::getInt32Ty(Context);
    }
    else if(dataType == "boolean"){
      ty = Type::getInt1Ty(Context);
    }
    if(var->isArray()){
      ArrayType* arrType = ArrayType::get(ty,var->getLength());
      PointerType* PointerTy_1 = PointerType::get(ArrayType::get(ty,var->getLength()),0);
      GlobalVariable* gv = new GlobalVariable(*TheModule,arrType,false,GlobalValue::ExternalLinkage,0,var->getName());
      gv->setInitializer(ConstantAggregateZero::get(arrType));
    }
    else{
      PointerType* ptrTy = PointerType::get(ty,0);
      GlobalVariable* gv = new GlobalVariable(*TheModule,ptrTy , false,GlobalValue::ExternalLinkage, 0, var->getName());
    }
  }
  Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
  return v;
}

void declblock::traverse(){
  for(int i = 0;  i < var_list.size(); i++){
    var_list[i]->traverse();
  }
}

declblock::declblock(string dataType, class Vars* vars){
  this->dataType = dataType;
  this->var_list = vars->getVarsList();
  for(int i = 0; i < var_list.size(); i++){
    var_list[i]->setDataType(dataType);
  }
}



Value* declblock::codegen(){
  for(int i = 0; i < var_list.size(); i++){
    /* Allocate one location of global variable for all */
    class Var* var = var_list[i];
    llvm::Type *ty;
    if(dataType == "int"){
      ty = Type::getInt32Ty(Context);
    }
    else if(dataType == "boolean"){
      ty = Type::getInt1Ty(Context);
    }
    if(var->isArray()){
      ArrayType* arrType = ArrayType::get(ty,var->getLength());
      PointerType* PointerTy_1 = PointerType::get(ArrayType::get(ty,var->getLength()),0);
      GlobalVariable* gv = new GlobalVariable(*TheModule,arrType,false,GlobalValue::ExternalLinkage,0,var->getName());
      gv->setInitializer(ConstantAggregateZero::get(arrType));
    }
    else{
      PointerType* ptrTy = PointerType::get(ty,0);
      GlobalVariable* gv = new GlobalVariable(*TheModule,ptrTy , false,GlobalValue::ExternalLinkage, 0, var->getName());
    }
  }
  Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
  return v;
}

Stmts::Stmts(){
  this->cnt = 0;
}

bool Stmts::has_return(){
  for(int i = 0; i < stmts.size(); i++){
    if(stmts[i]->has_return()){
      return true;
    }
  }
  return false;
}

Value* Stmts::codegen(){
  Value* v = ConstantInt::get(getGlobalContext(), llvm::APInt(32,1));
  for(int i = 0; i < stmts.size(); i++){
    v = stmts[i]->codegen();
  }
  return v;
}

void Stmts::traverse(){
  TBS;
  out << "<statements count=\"" << cnt << "\">\n";
  tabs_needed++;
  for(int i = 0; i < stmts.size(); i++){
    stmts[i]->traverse();
  }
  tabs_needed--;
  TBS;
  out << "</statements>\n";
}


void Stmts::push_back(class Stmt* stmt){
  stmts.push_back(stmt);
  cnt++;
}

ifStmt::ifStmt(class Expr* cond, class Block* block1, class Block* block2){
  this->stype = stmtType::NonReturn;
  this->condition = cond;
  this->if_block = block1;
  this->else_block = block2;
}


Value* ifStmt::codegen(){
  Value *cond = condition->codegen();
  if(cond == 0){
    errors++;
    return reportError::ErrorV("Invalid Expression in the IF");
  }
  Function* TheFunction = Builder.GetInsertBlock()->getParent();
  BasicBlock *ifBlock = BasicBlock::Create(Context, "if", TheFunction);
  BasicBlock *elseBlock = BasicBlock::Create(Context, "else");
  BasicBlock *nextBlock = BasicBlock::Create(Context, "ifcont");
  Builder.CreateCondBr(cond, ifBlock, elseBlock);

  Builder.SetInsertPoint(ifBlock);

  Value* ifval  = if_block->codegen();
  if(ifval == 0){
    return 0;
  }

  Builder.CreateBr(nextBlock);
  ifBlock = Builder.GetInsertBlock();

  TheFunction->getBasicBlockList().push_back(elseBlock);
  Builder.SetInsertPoint(elseBlock);
  Value* elseval;
  if(else_block != NULL)
  {
    elseval = else_block->codegen();
    if(elseval == 0){
      return 0;
    }
  }
  Builder.CreateBr(nextBlock);
  elseBlock = Builder.GetInsertBlock();
  TheFunction->getBasicBlockList().push_back(nextBlock);
  Builder.SetInsertPoint(nextBlock);

  bool phi_if = false,phi_else = false;
  if(if_block->has_return()){
    phi_if = true;
  }
  if(else_block != NULL && else_block->has_return()){
      phi_else = true;
  }
  if(phi_if||phi_else){
    PHINode *PN = Builder.CreatePHI(Type::getInt32Ty(getGlobalContext()), 2,"iftmp");
    if(phi_if)
      PN->addIncoming(ifval, ifBlock);
    if(phi_else){
        PN->addIncoming(elseval, elseBlock);
    }
    return PN;
  }

  Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
  return V;
}

void ifStmt::traverse(){
  TBS;
  out << "<if_else_statement>\n";
  tabs_needed++;
  TBS;
  out << "<condition>\n";
  tabs_needed++;
  condition->traverse();
  tabs_needed--;
  TBS;
  out << "</condition>\n";
  TBS;
  out << "<ifblock>\n";
  tabs_needed++;
  if_block->traverse();
  tabs_needed--;
  TBS;
  out << "</ifblock>\n";
  if(else_block!=NULL){
    TBS;
    out << "<else_block>\n";
    tabs_needed++;
    else_block->traverse();
    tabs_needed--;
    TBS;
    out << "</elseblock>\n";
  }
  tabs_needed--;
  TBS;
  out << "</if_else_statement>\n";
}



vector<class Var*> Vars::getVarsList(){
  return vars_list;
}

void Vars::push_back(class Var* var){
  vars_list.push_back(var);
  cnt++;
}

Value* Vars::codegen(){
  Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
  return V;
}

Var::Var(string declType, string name, unsigned int length){
  this->declType = declType;
  this->name = name;
  this->length = length;
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

Value* Var::codegen(){
  Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
  return V;
}

void Var::traverse(){
  TBS;
  out << declType << endl;
  TBS;
  out << "<declaration name=\"" << name << "\" type=\"" << dataType << "\" ";
  if(declType.compare("Array") == 0){
    out << "size=\"" << length << "\" ";
  }
  out << "/>\n";
}



void codeblock::traverse(){
  TBS;
  out << "<method_declaration return_type=\"" << type << " name=\""<< name << "\">\n";
  tabs_needed++;
  arg_list->traverse();
  body->traverse();
  tabs_needed--;
  TBS;
  out << "</method_declaration>\n";
}


codeblock::codeblock(string ret_type, string name, class methodArgs* args, class Block* block){
  this->type = ret_type;
  this->name = name;
  this->arg_list = args;
  this->body = block;
}

Function* codeblock::codegen(){
  vector<string> argNames;
  vector<string> argTypes;
  vector<class methodArg*> args = arg_list->getArgList();
  vector<Type*> arguments;
  int arg_size = args.size();
  for(int i = 0; i < args.size(); i++){
    /* Iterate over the arguments and get the types of them in llvm */
    string arg_type = args[i]->getType();
    string arg_name = args[i]->getName();
    if(arg_type == "int"){
      arguments.push_back(Type::getInt32Ty(getGlobalContext()));
    }
    else if (arg_type == "boolean"){
      arguments.push_back(Type::getInt1Ty(getGlobalContext()));
    }
    else{
      errors++;
      reportError::ErrorV("Arguments can only be int or boolean");
      return 0;
    }
    argTypes.push_back(string(arg_type));
    argNames.push_back(string(arg_name));
  }

  Type *returnType;
  /* Get the return Type */
  if(type == "int"){
    returnType = Type::getInt32Ty(getGlobalContext());
  }
  else if(type == "boolean"){
    returnType = Type::getInt1Ty(getGlobalContext());
  }
  else if (type == "void"){
    returnType = Type::getVoidTy(getGlobalContext());
  }
  else{
    errors++;
    reportError::ErrorV("Invalid Return Type for " + name + ". Return Type can only be int or boolean or bool");
    return 0;
  }

  /* Get the function type and create a Function */
  FunctionType *FT = llvm::FunctionType::get(returnType, arguments, false);
  Function *F = llvm::Function::Create(FT, Function::ExternalLinkage, name, TheModule);

  /* Iterate through arguments and set the Names for them */

  unsigned Idx = 0;
  for (Function::arg_iterator AI = F->arg_begin(); Idx != arg_size; ++AI, ++Idx) {
    AI->setName(argNames[Idx]);
  }

  /* Create a New block for this Function */
  BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", F);
  Builder.SetInsertPoint(BB);
  Idx = 0;

  /* Allocate memory for the arguments passed */
  for (auto &Arg : F->args()) {
    if(Idx == arg_size){break;}
    AllocaInst *Alloca = CreateEntryBlockAlloca(F, argNames[Idx],argTypes[Idx]);
    Builder.CreateStore(&Arg, Alloca);

    NamedValues[argNames[Idx]] = Alloca;
    Idx++;
  }

  Value *RetVal = body->codegen();
  if(RetVal){
    /* make this the return value */
    if(type != "void")
    Builder.CreateRet(RetVal);
    else
    Builder.CreateRetVoid();
    /* Verify the function */
    verifyFunction(*F);
    return F;
  }
  /* Error Condition */
  F->eraseFromParent();
  return 0;
}

void codeblocks::traverse(){
  TBS;
  out << "<method_declarations count=\"" << cnt << "\">\n";
  tabs_needed++;
  for (int i = 0; i < decl_list.size(); i++){
    decl_list[i]->traverse();
  }
  tabs_needed--;
  TBS;
  out << "</method_declarations>\n";

}


Value* codeblocks::codegen(){
  Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
  for(int i = 0; i < decl_list.size(); i++){
    V = decl_list[i]->codegen();
  }
  return V;
}

void codeblocks::traverse(){
  TBS;
  out << "<method_declarations count=\"" << cnt << "\">\n";
  tabs_needed++;
  for (int i = 0; i < decl_list.size(); i++){
    decl_list[i]->traverse();
  }
  tabs_needed--;
  TBS;
  out << "</method_declarations>\n";

}

codeblocks::codeblocks(){
  this->cnt = 0;
}

void codeblocks::push_back(class codeblock* decl){
  decl_list.push_back(decl);
  cnt++;
}

Value* binExpr::codegen(){
  Value* left = lhs->codegen();
  Value* right = rhs->codegen();
  if(lhs->getEtype() == exprType::location){
    left = Builder.CreateLoad(left);
  }
  if(rhs->getEtype() == exprType::location){
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
  Value* v;
  if(opr == "+"){
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
  else if(opr == "%"){
    v = Builder.CreateURem(left,right,"modtmp");
  }
  else if (opr == "<"){
    v = Builder.CreateICmpULT(left,right,"ltcomparetmp");
  }
  else if (opr == ">"){
    v = Builder.CreateICmpUGT(left,right,"gtcomparetmp");
  }
  else if (opr == "<="){
    v = Builder.CreateICmpULE(left,right,"lecomparetmp");
  }
  else if (opr == ">="){
    v = Builder.CreateICmpUGE(left,right,"gecomparetmp");
  }
  else if (opr == "=="){
    v = Builder.CreateICmpEQ(left,right,"equalcomparetmp");
  }
  else if (opr == "!="){
    v = Builder.CreateICmpNE(left,right,"notequalcomparetmp");
  }
  return v;
}

binExpr::binExpr(class Expr* lhs, string opr, class Expr* rhs){
  this->lhs = lhs;
  this->rhs = rhs;
  this->opr = opr;
  this->etype = exprType::binary;
}


last::last(string var, string location_type, class Expr* expr){
  this->var = var;
  this->location_type = location_type;
  this->expr = expr;
  this->etype = exprType::location;
}

last::last(string var, string location_type){
  this->var = var;
  this->location_type = location_type;
  this->etype = exprType::location;
}