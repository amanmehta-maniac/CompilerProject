Value* PrintStmt::codegen(){
  Value* V;
   for (unsigned int i = 0, e = outs.size(); i != e; ++i){
     vector<Value *> ArgsV;
     ArgsV.clear();
     if(outs[i]->type=="id"){
       Value *to_print = outs[i]->codegen();
       Value* val=Builder.CreateGlobalStringPtr("%d");
       ArgsV.push_back(val);
       ArgsV.push_back(to_print);
    }
   else if(outs[i]->type=="strlit"){
     Value* val = Builder.CreateGlobalStringPtr("%s");
     Value* to_print = Builder.CreateGlobalStringPtr(outs[i]->name.substr(1,outs[i]->name.length()-2));
     ArgsV.push_back(val);
     ArgsV.push_back(to_print);
   }
   V =  Builder.CreateCall(CalleeF, ArgsV, "printfCall");
   ArgsV.clear();
   if(i!=e-1){
     Value* val = Builder.CreateGlobalStringPtr("%s");
     Value* to_print = Builder.CreateGlobalStringPtr(" ");
     ArgsV.push_back(val);
     ArgsV.push_back(to_print);
     V =  Builder.CreateCall(CalleeF, ArgsV, "printfCall");
   }
  }