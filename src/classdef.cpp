class program:public astNode{
private:
	class declblock* methods; /* list of decl */
	class codeblock* fields; /* list of code */
public:
	program(class declblock*,class codeblock*);
	void traverse();
	Value* codegen();
	void generateCode();
};


