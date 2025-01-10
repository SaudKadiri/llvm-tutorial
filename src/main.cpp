/*
 * Date: January 10, 2025
 * Description: This is the main file,
 * Author: Saud
 * */

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>

int main() {
    llvm::LLVMContext Context;
    llvm::Module *Module = new llvm::Module("FactorialModule", Context);
    llvm::IRBuilder<> Builder(Context);
    
    // Define the factorial function type: int32(int32)
    llvm::FunctionType *FuncType = llvm::FunctionType::get(Builder.getInt32Ty(), { Builder.getInt32Ty() }, false);

    // Create a simple function: int factorial(int32 $0)
    llvm::Function *FactorialFunc = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, "factorial", Module);
    
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(Context, "entry", FactorialFunc);
    Builder.SetInsertPoint(BB);

    // Add argument name instead of $0: int factorial(int32 n)
    llvm::Argument *ArgN = FactorialFunc->getArg(0);
    ArgN->setName("n");

    // Create the cases:
    llvm::BasicBlock *BaseCaseBB = llvm::BasicBlock::Create(Context, "base_case", FactorialFunc);
    llvm::BasicBlock *RecursiveCaseBB = llvm::BasicBlock::Create(Context, "recursive_base", FactorialFunc);
    llvm::BasicBlock *MergeBB = llvm::BasicBlock::Create(Context, "merge", FactorialFunc);
    
    // base case n <= 1; Integer Comparison Signed Less Than or Equal 
    llvm::Value *One = Builder.getInt32(1);
    llvm::Value *IsBaseCase = Builder.CreateICmpSLE(ArgN, One, "is_base_case");
    Builder.CreateCondBr(IsBaseCase, BaseCaseBB, RecursiveCaseBB);

    Builder.SetInsertPoint(BaseCaseBB);
    Builder.CreateBr(MergeBB);

    // recursive case n * factorial(n - 1)
    Builder.SetInsertPoint(RecursiveCaseBB);
    llvm::Value *NMinusOne = Builder.CreateSub(ArgN, One, "n_minus_one");
    llvm::Value *RecursiveCall = Builder.CreateCall(FactorialFunc, { NMinusOne }, "recursive_call");
    llvm::Value *Result = Builder.CreateMul(ArgN, RecursiveCall, "result");
    Builder.CreateBr(MergeBB);

    Builder.SetInsertPoint(MergeBB);
    llvm::PHINode *PHI = Builder.CreatePHI(Builder.getInt32Ty(), 2, "phi");
    PHI->addIncoming(One, BaseCaseBB);
    PHI->addIncoming(Result, RecursiveCaseBB);
    Builder.CreateRet(PHI);

    // Print the LLVM IR to stdout
    Module->print(llvm::outs(), nullptr);

    delete Module;
    return 0;
}
