### What is LLVM?
LLVM is a set of tools used to build compilers and optimize code for different computer systems. It's like a toolkit that helps turn code written in programming languages (like C, C++, Rust, Swift, Go, ObjC, Kotlin, CUDA and many many more languages!) into machine code that a computer can understand and execute.

### LLVM Compiler Pipeline
![image](https://aosabook.org/static/llvm/LLVMCompiler1.png)

The LLVM compiler pipeline consists of several stages that transform high-level source code into machine code.

#### 1. Frontend (Source Code → LLVM IR)
- **Parsing**: Reads and analyzes the source code written in a high-level language (e.g., C, C++, or maybe your own custom language :)).
- **Lexical and Syntax Analysis**: Breaks code into tokens and arranges them into a syntax tree.
- **Semantic Analysis**: Ensures the program is logically correct.
- **LLVM IR Generation**: Converts the source code into LLVM Intermediate Representation (IR), a platform-independent, low-level code.
- **Frontend examples**: clang(c compiler), clang++ (c++ compiler), swiftc (swift compiler), rustc(rust compiler)

**Output**: LLVM IR code.

#### 2. Optimization (LLVM IR → Optimized IR)
- **LLVM Optimizer**: Applies various optimization techniques to improve code performance (e.g., dead code elimination, loop unrolling).
  
**Output**: Optimized LLVM IR.

#### 3. Backend (LLVM IR → Machine Code)
- **Code Generation**: Converts the optimized LLVM IR into machine-specific assembly code for the target architecture (e.g., x86, ARM).
- **Register Allocation**: Efficiently allocates CPU registers.
- **Instruction Selection**: Maps LLVM IR operations to target-specific instructions.

**Output**: Assembly code.


##### Summary
1. **Frontend**: Translates source code into LLVM IR.
2. **Optimization**: Improves the IR to make it more efficient.
3. **Backend**: Converts IR into machine-specific assembly.

### Getting started with LLVM Unix
1. Install `llvm`: `brew install llvm` or `sudo apt install llvm`
2. If required `export PATH=/opt/homebrew/Cellar/llvm/<version:19.1.6>/bin:$PATH`
3. Confirm by running: `llvm-config --version`
3. Add to vscode includePath: `/opt/homebrew/Cellar/llvm/<version:19.1.6>/include`

### Example: Factorial code
```bash
mkdir build && cd build
cmake ..
cmake --build .
./LLVM_EXAMPLE
```
#### Output
```llvm
; ModuleID = 'FactorialModule'
source_filename = "FactorialModule"

define i32 @factorial(i32 %n) {
entry:
  %is_base_case = icmp sle i32 %n, 1
  br i1 %is_base_case, label %base_case, label %recursive_base

base_case:                                        ; preds = %entry
  br label %merge

recursive_base:                                   ; preds = %entry
  %n_minus_one = sub i32 %n, 1
  %recursive_call = call i32 @factorial(i32 %n_minus_one)
  %result = mul i32 %n, %recursive_call
  br label %merge

merge:                                            ; preds = %recursive_base, %base_case
  %phi = phi i32 [ 1, %base_case ], [ %result, %recursive_base ]
  ret i32 %phi
}

```

*NOTE*: I might add more examples only if I manage some time...