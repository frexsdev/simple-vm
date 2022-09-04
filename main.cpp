#include <fstream>
#include <ios>
#include <iostream>
#include <vector>

using namespace std;

enum class Inst_Type {
  Push,
  Add,
  Print,
};

class Inst {
public:
  Inst_Type type;
  int operand;

  Inst(Inst_Type type) { this->type = type; }
  Inst(Inst_Type type, int operand) {
    this->type = type;
    this->operand = operand;
  }
};

vector<Inst> program{
    Inst(Inst_Type::Push, 35),
    Inst(Inst_Type::Push, 34),
    Inst(Inst_Type::Add),
    Inst(Inst_Type::Print),
};

vector<int> stack;

int stack_pop() {
  int result = stack.at(stack.size() - 1);
  stack.pop_back();
  return result;
}

void save_program_to_file(string file_path) {
  ofstream f(file_path, ios::binary);
  if (f.is_open()) {
    f.write((char *)&program, sizeof(program));
    f.close();
  } else {
    cerr << "ERROR: cannot open file '" << file_path << "'" << endl;
    exit(1);
  }
}

int main(void) {
  save_program_to_file("program.vm");

  for (Inst inst : program) {
    switch (inst.type) {
    case Inst_Type::Push:
      stack.push_back(inst.operand);
      break;
    case Inst_Type::Add: {
      int a = stack_pop();
      int b = stack_pop();
      stack.push_back(a + b);
    } break;
    case Inst_Type::Print:
      cout << stack_pop() << endl;
      break;
    }
  }

  return 0;
}