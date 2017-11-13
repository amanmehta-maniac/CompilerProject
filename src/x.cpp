Value* Decl_data::codegen(){
  for(int i=0;i<var_list.size();i++){
    class Var* var=var_list[i];
    llvm::Type *ty;
    ty=Type::getInt32Ty(Context);
    if(var->isArray()){
      ArrayType* arrType= ArrayType::get(ty,var->getLength());
      PointerType* PointerTy_1 = PointerType::get(ArrayType::get(ty,var->getLength()),0);

      GlobalVariable* gv = new GlobalVariable(*TheModule,arrType,false,GlobalValue::ExternalLinkage,0,var->getName());
      gv->setInitializer(ConstantAggregateZero::get(arrType));
    }
    else{
     TheModule->getOrInsertGlobal(var->getName(),Builder.getInt32Ty());
     PointerType* ptrTy = PointerType::get(ty,0);
     GlobalVariable* gv = TheModule->getNamedGlobal(var->getName());
     gv->setLinkage(GlobalValue::CommonLinkage);
     ConstantInt* const_int_val = ConstantInt::get(Context, APInt(32,0));
     gv->setInitializer(const_int_val);

   }
  }