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

