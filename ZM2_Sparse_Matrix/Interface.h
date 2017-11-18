#pragma once
#include "SparseMatrixManager.h"
//constants
//commands
//0 arguments
const std::string COMMAND_LIST = "list";
const std::string COMMAND_DELALL = "delall";
//1 argument
const std::string COMMAND_DEL = "del";
const std::string COMMAND_PRINT = "print";
const std::string COMMAND_CLONE = "clone";
//2 arguments
const std::string COMMAND_RENAME = "rename";
//3+ arguments
const std::string COMMAND_ADDMAT = "addmat";
const std::string COMMAND_DEF = "def";
const std::string COMMAND_EXIT = "exit";

const std::string COMMAND_PROMPT = "$ ";
const std::string PROMPT_DELETED_ALL_MATRICES = "Deleted all matrices.";
const std::string PROMPT_DELETED_MATRIX_AT_OFFSET = "Successfully deleted matrix at offset: ";
const std::string PROMPT_DEFINED_VALUE_IN_MATRIX_AT_OFFSET = "Successfully defined value in matrix at offset: ";
const std::string PROMPT_EXIT = "Program finished by user. Press any key to exit.";

//error messages
const std::string PROMPT_ERROR_INVALID_COMMAND = " is not recognized as an internal command.";
const std::string PROMPT_ERROR_INVALID_ARGUMENTS_NUMBER_FOR_COMMAND = "Invalid number of arguments for command ";
const std::string PROMPT_ERROR_INVALID_ARGUMENTS_FOR_COMMAND = "Invalid arguments for command ";
const std::string PROMPT_ERROR_INVALID_DIMENSION_SIZES_NUMBER = "Invalid dimension sizes number.";
const std::string PROMPT_ERROR_INVALID_DIMENSION_SIZE = "Invalid dimension size.";
const std::string PROMPT_ERROR_MATRIX_OFFSET_OUT_OF_BOUNDS = "Matrix offset out of bounds.";
const std::string FULL_STOP = ".";
const std::string EMPTY_STRING = "";
const std::string APOSTROPHE = "'";

class Interface {
public:
	Interface();
	~Interface();
	void run();
	
private:
	SparseMatrixManager* sparseMatrixManager;
	bool finished;
	std::string currentCommand;
	std::string programResponse;
	std::vector<std::string> args;
	void readCommand();
	void splitCurrentCommand();
	void selectAndPerformOperation();
	void processCommandDelAll();
	void processCommandList();
	void processCommandDel();
	void processCommandPrint();
	void processCommandClone();
	void processCommandRename();
	void processCommandAddmat();
	void addMat(bool hasName);
	void processCommandDef();

	void printProgramResponse();
	void printCommandPrompt();
	bool isArgumentAtIndexNumber(int indexOfArgument);
	bool overflowsInt(int indexOfArgument);
	bool isRangeOfArgumentsCorrect(int firstArgumentIndex, int lastArgumentIndex);
};