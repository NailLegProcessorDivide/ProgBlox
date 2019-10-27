#pragma once
#include <cstdint>
#include <string>
#include <vector>

class Variable;
class Block;
class Function;
class RuntimeState;

class Variable {
private:
	union {
		uint32_t type;
		uint16_t moduleType[2];
	};
	void* value;
	bool constant;
public:
	Variable();
	void* getValue();
	bool isConstant();
	std::string toString();
};

class Block {
private:
	union {
		uint32_t type;
		uint16_t moduleType[2];
	};
	int numParameters;
	std::vector<uint32_t> paramTypes;;
	std::vector<int> parameters;//stack frame index

	std::vector<Block*> subBlocks;
	int numSubBlocks;
public:
	virtual bool run(RuntimeState& rt);
	const int getNumParams();
	const uint32_t getParamType(int i);
	Variable& getVariable(int i);
	const int getNumSubBlocks();
	Block* getSubBlock();

};

class Function : public Block {
private:
	std::vector<Block*> blocks;//used when run but can't be seen when recursing over blocks
	int numblocks;
public:
	bool run(RuntimeState& rt);
	Block* getBlock(int index);
};

class StackFrame {
public:
	std::vector<Variable> variables;
};

class RuntimeState {
private:
	std::vector<StackFrame> stackFrames;
	std::vector<int> stackFrame;
	std::vector<Variable> globalVariables;
public:

};