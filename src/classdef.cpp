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
	class ifElseStmt* ifst;
	class whileStmt* whilest;
	class printStmt* printst;
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
	string opr; /* how it is assigned = or -= or += */
public:
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


class ifElseStmt:public Stmt{
private:
	class Expr* condition; /* condition for if statement */
	class Block* if_block; /* if block */
	class Block* else_block; /* else block */
public:
	ifElseStmt(class Expr*, class Block*, class Block*);
	void traverse();
	Value* codegen();
	bool has_return(){
		bool status = false;
		if(if_block != NULL){
			status = status | if_block->has_return();
		}
		if(else_block != NULL){
			status = status | if_block->has_return();
		}
		return status;
	}
};




