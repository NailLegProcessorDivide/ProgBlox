#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <map>

class Variable;
class Block;
class Function;
class RuntimeState;

class VariableBase {
	union {
		uint32_t type;
		uint16_t moduleType[2];
	};
};

class Variable {
private:
	VariableBase* varBase;
	void* value;
	bool constant;
public:
	Variable();
	void* getValue();
	bool isConstant();
	std::string toString();
};

struct BlockBase {
public:
	union {
		uint32_t type;
		uint16_t moduleType[2];
	};
	int numParameters;
	std::vector<uint32_t> paramTypes;
};

class Block {
private:
	BlockBase* blockBase;
	std::vector<Variable> parameters;

	std::vector<Block*> subBlocks;
	int numSubBlocks;
public:
	Block();
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
	const int getNumBlocks();
};

class StackFrame {
public:
	std::vector<Variable> varBase;
};

class RuntimeState {
private:
	std::vector<StackFrame> stackFrames;
	std::vector<int> stackFrame;
	std::vector<Variable> globalVariables;
	std::vector<int> PC;
public:

};

class BlockLibrary {
private:
	std::map<uint16_t, VariableBase> variables;
	std::map<uint16_t, BlockBase> blocks;
};

class ProgBlox {

};