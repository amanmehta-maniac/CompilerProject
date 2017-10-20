#include <bits/stdc++.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/Support/raw_ostream.h>


union Node{
	int number;
	char* ch;
	class Prog* prog;
	class declblocks* decls;
	class declblock* decl;
	class Vars* vars;
	class Var* var;
	class codeblocks* codes;
	class codeblock* code;
	// class Block* block;
	// class varDecls* var_decls;
	// class varDecl* var_decl;
	class Stmts* stmts;
	class Stmt* stmt;
	class Expr* expr;

	// class calloutArg* callout_arg;
	// class calloutArgs* callout_args;
	// class Params* parameters;
	// class methodArgs* method_args;
	// class methodArg* method_arg;
	// class methodCall* method_call;
	// class Location* location;
	class Assign* assign;
	class forStmt* forst;
	class ifStmt* ifst;
	class whileStmt* whilest;
	class printStmt* printst;
	class labelStmt* labelst;
	class binExpr* binexpr;
	// class Literal* literal;
	// class stringList* mylist;

	Node(){
		// number = 0;
		// value = NULL;
		// fields = NULL;
		// field = NULL;
		// methods = NULL;
		// method = NULL;
		// var_decls = NULL;
		// stmts = NULL;
		// callout_args = NULL;
		// method_args = NULL;
	}
	~Node(){};
};


class astNode{
	virtual Value* codegen(){}
};


class program:public astNode{
private:
	class declblocks* decls; /* list of decl */
	class codeblocks* codes; /* list of code */
public:
	program(class declblocks*,class codeblocks*);
	void traverse();
	Value* codegen();
	void generateCode();
};

class declblocks:public astNode{
private:
	vector<class declblock*> decl_list;
	int cnt;
public:
	declblocks();
	void push_back(class declblock*);
	void traverse();
	Value* codegen();
};


class declblock:public astNode{
private:
	string dataType; /* Field declaration can have datatype and vaariables */
	vector<class Var*> var_list;
public:
	declblock(string,class Vars*);
	vector<class Var*> getVarsList();
	void traverse();
	Value* codegen();
};


class Vars:public astNode{
private:
	vector<class Var*> vars_list;
	int cnt;
public:
	Vars(){}
	void push_back(class Var*);
	vector<class Var*> getVarsList();
	void traverse();
	Value* codegen();
};


class Var:public astNode{
private:
	string declType; /* Array or Normal */
	string name; /* Name of the variable */
	string dataType; /* type of variable */
	unsigned int length; /* if it is an Array then length */
public:
	/* Constructors */
	Var(string,string,unsigned int);
	Var(string,string);
	bool isArray();
	/* Methods */
	void setDataType(string); /* Set the data Type */
	void traverse();
	string getName();
	Value* codegen();
	int getLength(){return length;}
};

class codeblocks:public astNode{
private:
	vector< class codeblock* > decl_list;
	int cnt;
public:
	codeblocks();
	void push_back(class codeblock*);
	void traverse();
	Value* codegen();
};

class codeblock:public astNode{
private:
	string type; /* return type of the function */
	string name; /* name of the function */
	class methodArgs* arg_list; /* List of arguments for the functions */
	class Block* body; /* Body of the function */
public:
	codeblock(string type, string name, class methodArgs*, class Block*);
	void traverse();
	Function* codegen();
};


class Stmts:public astNode{
private:
	vector<class Stmt*> stmts;
	int cnt;
public:
	Stmts();
	void push_back(class Stmt*);
	void traverse();
	bool has_return();
	Value* codegen();
};

class Stmt:public astNode{
protected:
		stmtType stype;
public:
	virtual void traverse(){}
	virtual Value* codegen(){}
	virtual bool has_return(){return false;}
	void setStype(stmtType x){this->stype = x;}
	stmtType getStype(){return this->stype;}
};


class Assign:public Stmt{
private:
	class Location* loc;/* location to which Assign is done */
	class Expr* expr; /* what is assigned */
	class 
	string opr; /* how it is assigned = or -= or += */
public:
	Assign(class Location*, string, class Expr*);
	Assign(class Location*, string, class Expr*);
	void traverse();
	Value* codegen();
};


class forStmt:public Stmt{
private:
	string var;/* variable to be initialised */
	class Expr* init; /* Value for initialisation */
	class Expr* condition; /* condition for loop */
	class Block* body; /* body of the loop */
public:
	forStmt(string, class Expr*, class Expr*, class Block*);
	bool has_return(){this->body->has_return();}
	void traverse();
	Value* codegen();
};


class ifStmt:public Stmt{
private:
  string type;
  class BoolExpr* cond;
  class StatementList *if_part, *else_part;
public:
  IfStmt(string,class BoolExpr*,class StatementList*);
  IfStmt(string,class BoolExpr*,class StatementList*,class StatementList*);
};

class whileStmt:public Stmt{
private:
  class BoolExpr* cond;
  class StatementList *stmts;
public:
  whileStmt(class BoolExpr*,class StatementList*);
};

class gotoStmt:public Stmt{
private:
  string type,label;
  class BoolExpr* cond;
public:
  gotoStmt(string,string);
  gotoStmt(string,string,class BoolExpr*);
};

class forStmt:public Stmt{
private:
  class AssignExpr* intial;
  class Terminal *end_cond, * inc_value;
  class StatementList* stmts;
public:
  forStmt(class AssignExpr*,class Terminal*,class StatementList*);
  forStmt(class AssignExpr*,class Terminal*,class Terminal*,class StatementList*);
};



class readStmt:public Stmt{
private:
  class Terminal* obj;
public:
  readStmt(class Terminal*);
};

class printStmt:public Stmt{
private:
  vector< class Terminal* > outs;
public:
  printStmt(){}
  void push_back(class Terminal*);
};

class boolExpr:public astNode{
private:
  class Expr  *expr1,*expr2;
  class boolExpr *bexpr1,*bexpr2;
  string oper;
public:
  boolExpr(class Expr*,string,class Expr*);
  boolExpr(class BoolExpr*,string,class BoolExpr*);
};


class last: public Expr{
private:
	string var; /* name used in location */
	string location_type; /* Array or normal */
	class Expr* expr; /* if it is array then we have the address */
public:
	last(string,string,class Expr*);
	last(string,string);
	void traverse();
	string getVar();/* returns the var name */
	bool is_array(); /* tells if its array or not */
	class Expr* getExpr();
	Value* codegen();
}



class Expr:public astNode{
private: 
	string op;
protected:
	exprType etype; /* Binary or unary or literal or location */
public:
	void setEtype(exprType x){etype = x;}
	exprType getEtype(){return etype;}
	virtual string toString(){}
	virtual void traverse(){}
	virtual Value* codegen(){}
};

class EnclExpr:public Expr{
private:
	class Expr* expr;
public:
	EnclExpr(class Expr*);
	void traverse();
	Value* codegen();
};

class unExpr:public Expr{
private:
	class Expr* body; /* body of expression */
	string opr; /* Unary Expression */
public:
	unExpr(string,class Expr*);
	void traverse();
	Value* codegen();
};

class binExpr:public Expr{
private:
	class Expr* lhs; /* left hand side */
	class Expr* rhs; /* right hand side */
	string opr; /* operator in between */
public:
	binExpr(class Expr*, string, class Expr*);
	void traverse();
	Value* codegen();
};

