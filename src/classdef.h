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

using namespace std;
using namespace llvm;

enum stmtType { Return = 1, NonReturn = 2};

union Node{
	int number;
	char* ch;
	class program* prog;
	class declblocks* decls;
	class declblock* decl;
	class Vars* vars;
	class Var* var;
	class codeblocks* codes;
	class codeblock* code;
	class Expr* expr;
	class boolExpr* boolex;
	class OperandType* optype;
	class unitClass* unit;
	class last* last;
	class Assign* assign;
	class forStmt* forst;
	class gotoStmt* gotost;
	class readStmt* readst;
	class printStmt* printst;
	class ifStmt* ifst;
	class whileStmt* whilest;
	class labelStmt* labelst;
	class binExpr* binexpr;
	class content* contnt;
	Node(){
		number = 0;
		ch = NULL;
		prog = NULL;
		decls = NULL;
		decl = NULL;
		vars = NULL;
		var = NULL;
		codes = NULL;
		code = NULL;
		expr = NULL;
		boolex = NULL;
		optype = NULL;
		unit = NULL;
		last = NULL;
		assign = NULL;
		forst = NULL;
		gotost = NULL;
		readst = NULL;
		printst = NULL;
		ifst = NULL;
		whilest = NULL;
		labelst = NULL;
		binexpr = NULL;
		contnt = NULL;
	}
	~Node(){};
};
typedef union Node YYSTYPE;

#define YYSTYPE_IS_DECLARED 1


class Visitor{
public:
	virtual int visit(class program* e) {};
	virtual int visit(class declblocks* e) {};
	virtual int visit(class declblock* e) {};
	virtual int visit(class Vars* e) {};
	virtual int visit(class Var* e) {};
	virtual int visit(class codeblocks* e) {};
	virtual int visit(class codeblock* e) {};
	virtual int visit(class Expr* e) {};
	virtual int visit(class boolExpr* e) {};
	virtual int visit(class OperandType* e) {};
	virtual int visit(class unitClass* e) {};
	virtual int visit(class last* e) {};
	virtual int visit(class Assign* e) {};
	virtual int visit(class forStmt* e) {};
	virtual int visit(class gotoStmt* e) {};
	virtual int visit(class readStmt* e) {};
	virtual int visit(class printStmt* e) {};
	virtual int visit(class ifStmt* e) {};
	virtual int visit(class whileStmt* e) {};
	virtual int visit(class labelStmt* e) {};
	virtual int visit(class binExpr* e) {};
	virtual int visit(class content* e) {};
};

class Interpreter:public Visitor{
public:	
	Interpreter(){}
	int visit(class program* e);
	int visit(class declblocks* e);
	int visit(class declblock* e);
	int visit(class Vars* e);
	int visit(class Var* e);
	int visit(class codeblocks* e);
	int visit(class codeblock* e);
	int visit(class Expr* e);
	int visit(class boolExpr* e);
	int visit(class OperandType* e);
	int visit(class unitClass* e);
	int visit(class last* e);
	int visit(class Assign* e);
	int visit(class forStmt* e);
	int visit(class gotoStmt* e);
	int visit(class readStmt* e);
	int visit(class printStmt* e);
	int visit(class ifStmt* e);
	int visit(class whileStmt* e);
	int visit(class labelStmt* e);
	int visit(class binExpr* e);
	int visit(class content* e);

};



class astNode{
public:
	virtual int accept(Visitor* v){};
};

class OperandType: public astNode{
	public:
		string op;
		OperandType(string);
		 int accept(Visitor* v){return v->visit(this);};
};


class unitClass:public astNode{
public:
  string type;
  int value;
  string name;
  // class unitClass* arr_pos;
public:
  unitClass(string,string);
  unitClass(string,int);
  // unitClass(string,string,class unitClass*);
  int accept(Visitor* v){return v->visit(this);};
};



class program:public astNode{
public:
	class declblocks* decls; /* list of decl */
	class codeblocks* codes; /* list of code */
public:
	program(class declblocks*,class codeblocks*);
	void generateCode();
	int accept(Visitor* v){return v->visit(this);};
};

class declblocks:public astNode{
public:
	vector<class declblock*> decl_list;
	int cnt;
public:
	declblocks();
	void push_back(class declblock*);
	int accept(Visitor* v){return v->visit(this);};
};


class declblock:public astNode{
public:
	string dataType; /* Field declaration can have datatype and vaariables */
	vector<class Var*> var_list;
public:
	declblock(class Vars*);
	vector<class Var*> getVarsList();
	int accept(Visitor* v){return v->visit(this);};
};


class Vars:public astNode{
public:
	vector<class Var*> vars_list;
	int cnt;
public:
	Vars(){}
	void push_back(class Var*);
	vector<class Var*> getVarsList();
	int accept(Visitor* v){return v->visit(this);};
};


class Var:public astNode{
public:
	string declType; /* Array or Normal */
	string name; /* Name of the variable */
	string dataType; /* type of variable */
	int init_val;
	string flag;
	unsigned int length; /* if it is an Array then length */
	Var(string,string,unsigned int);
	Var(string, string, string, int);
	Var(string,string);
	bool isArray();
	/* Methods */
	void setDataType(string); /* Set the data Type */
	string getName();
	int getLength(){return length;}
	int accept(Visitor* v){return v->visit(this);};
};

class codeblocks:public astNode{
public:
	vector< class codeblock* > code_list;
	string gotolabel;
	int cnt;
public:
	codeblocks();
	void push_back(class codeblock*);
	void push_back(class codeblock*, string);
	int accept(Visitor* v){return v->visit(this);};
};

class codeblock:public astNode{

public:
	virtual string getlabel(){}
	string label;
	codeblock();
	int accept(Visitor* v){return v->visit(this);};
};



class Assign:public codeblock{
public:
	class last* loc;/* location to which Assign is done */
	class Expr* expr; /* what is assigned */
	string opr; /* how it is assigned = or -= or += */
public:
	Assign(class last*, string, class Expr*);
	int accept(Visitor* v){return v->visit(this);};
};




class Expr:public astNode{
public: 
	class last* lastVar;
	class binExpr* binexpr;
	int number;
	string expr_type;
public:
	Expr(string,class last*);
	Expr(string,class binExpr*);

	Expr(){}
	Expr(string, int);
	int accept(Visitor* v){return v->visit(this);};
};


class ifStmt:public codeblock{
public:
  string type;
  class boolExpr* cond;
  class codeblocks *if_part, *else_part;
public:
  ifStmt(string,class boolExpr*,class codeblocks*);
  ifStmt(string,class boolExpr*,class codeblocks*,class codeblocks*);
  int accept(Visitor* v){return v->visit(this);};
};

class whileStmt:public codeblock{
public:
  class boolExpr* cond;
  class codeblocks *stmts;
public:
  whileStmt(class boolExpr*,class codeblocks*);
  int accept(Visitor* v){return v->visit(this);};
};

class gotoStmt:public codeblock{
public:
  string type, label;
  class boolExpr* cond;
public:
	string getlabel(){
		return this->label;	
	}
  gotoStmt(string,string);
  gotoStmt(string,string,class boolExpr*);
  int accept(Visitor* v){return v->visit(this);};
};

class forStmt:public codeblock{
public:
  string i;
  class Expr* initial;
  class unitClass *endcond, *incval;
  class codeblocks* stmts;
  int forType;
public:
  forStmt(string, class Expr*, class unitClass*, class codeblocks*);
  forStmt(string, class Expr*, class unitClass*, class unitClass*, class codeblocks*);
  int accept(Visitor* v){return v->visit(this);};
};


class readStmt:public codeblock{
public:
  class last* toread;
public:
  readStmt(class last*);
  int accept(Visitor* v){return v->visit(this);};
};

class printStmt:public codeblock{
public:
  vector< class content* > outs;
  bool nline;
  int type;
public:
  printStmt(){}
  void push_back(class content*);
  int accept(Visitor* v){return v->visit(this);};
};

class content: public codeblock{

public:
	class last* lastval;
	string toprint;
	int num;
	int type;
	content(string);
	content(class last*);
	content(int);
	int accept(Visitor* v){return v->visit(this);};
};

class boolExpr:public astNode{
public:
  class Expr  *expr1,*expr2;
  class boolExpr *bexpr1,*bexpr2;
  class OperandType* oper_type;
  string oper;
  string boolType;
public:
  boolExpr(string, class Expr*,class OperandType*,class Expr*);
  boolExpr(string, class boolExpr*,string,class boolExpr*);
  int accept(Visitor* v){return v->visit(this);};
};


class last: public Expr{
public:
	string var; /* name used in location */
	string last_type; /* Array or normal */
	class Expr* expr; /* if it is array then we have the address */
public:
	last(string,string,class Expr*);
	last(string,string);
	string getVar();/* returns the var name */
	bool is_array(); /* tells if its array or not */
	class Expr* getExpr();
	int accept(Visitor* v){return v->visit(this);};
};


class binExpr:public Expr{
public:
	class Expr* lhs; /* left hand side */
	class Expr* rhs; /* right hand side */
	string opr; /* operator in between */
public:
	binExpr(class Expr*, string, class Expr*);
	 int accept(Visitor* v){return v->visit(this);return v->visit(this);};
};
