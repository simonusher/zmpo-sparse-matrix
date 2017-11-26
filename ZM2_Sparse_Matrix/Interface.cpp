#include "Interface.h"

Interface::Interface() {
	this->sparseMatrixManager = new SparseMatrixManager();
	this->finished = false;
}

Interface::~Interface() {
	delete this->sparseMatrixManager;
}

void Interface::run() {
	while (!finished) {
		printCommandPrompt();
		readCommand();
		splitCurrentCommand();
		selectAndPerformOperation();
		printProgramResponse();
	}
	std::cin.get();
}

void Interface::readCommand() {
	std::getline(std::cin, this->currentCommand);
}

void Interface::splitCurrentCommand() {
	std::istringstream iss(currentCommand);
	std::copy(std::istream_iterator<std::string>(iss),
		std::istream_iterator<std::string>(),
		std::back_inserter(args));
}

void Interface::selectAndPerformOperation() {
	if (args.size() > 0) {
		if (args.at(0) == COMMAND_LIST) {
			processCommandList();
		}
		else if (args.at(0) == COMMAND_DELALL) {
			processCommandDelAll();
		}
		else if (args.at(0) == COMMAND_DEL) {
			processCommandDel();
		}
		else if (args.at(0) == COMMAND_PRINT) {
			processCommandPrint();
		}
		else if (args.at(0) == COMMAND_CLONE) {
			processCommandClone();
		}
		else if (args.at(0) == COMMAND_RENAME) {
			processCommandRename();
		}
		else if (args.at(0) == COMMAND_ADDMAT) {
			processCommandAddmat();
		}
		else if (args.at(0) == COMMAND_DEF) {
			processCommandDef();
		}
		else if (args.at(0) == COMMAND_EXIT) {
			sparseMatrixManager->deleteAllMatrices();
			this->finished = true;
			programResponse = PROMPT_EXIT;
		}
		else {
			programResponse = APOSTROPHE + args.at(0) + APOSTROPHE + PROMPT_ERROR_INVALID_COMMAND;
		}
	}
	else {
		programResponse = EMPTY_STRING;
	}
	this->currentCommand = EMPTY_STRING;
	this->args.clear();
}

void Interface::processCommandDelAll() {
	if (this->args.size() != 1) {
		programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_NUMBER_FOR_COMMAND + APOSTROPHE + COMMAND_DELALL + APOSTROPHE + FULL_STOP;
	}
	else {
		sparseMatrixManager->deleteAllMatrices();
		programResponse = PROMPT_DELETED_ALL_MATRICES;
	}
}

void Interface::processCommandList() {
	if (this->args.size() != 1) {
		programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_NUMBER_FOR_COMMAND + APOSTROPHE + COMMAND_LIST + APOSTROPHE + FULL_STOP;
	}
	else {
		programResponse = sparseMatrixManager->listMatrices();
	}
}

void Interface::processCommandDel() {
	if (this->args.size() != 2) {
		programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_NUMBER_FOR_COMMAND + APOSTROPHE + COMMAND_DEL + APOSTROPHE + FULL_STOP;
	}
	else if (isArgumentAtIndexANumber(1) && !argumentAtIndexOverflowsInt(1)) {
		int errorCode = sparseMatrixManager->deleteMatrix(std::atoi(args.at(1).c_str()));
		if (errorCode == SUCCESS) {
			programResponse = PROMPT_DELETED_MATRIX_AT_OFFSET + args.at(1) + FULL_STOP;
		}
		else {
			programResponse = PROMPT_ERROR_MATRIX_OFFSET_OUT_OF_BOUNDS;
		}
	}
	else {
		programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_FOR_COMMAND + APOSTROPHE + COMMAND_DEL + APOSTROPHE + FULL_STOP;
	}
}

void Interface::processCommandPrint() {
	if (this->args.size() != 2) {
		programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_NUMBER_FOR_COMMAND + APOSTROPHE + COMMAND_PRINT + APOSTROPHE + FULL_STOP;
	}
	else if (isArgumentAtIndexANumber(1) && !argumentAtIndexOverflowsInt(1)) {
		int errorCode = sparseMatrixManager->printMatrix(std::atoi(args.at(1).c_str()), this->programResponse);
		if (errorCode != SUCCESS) {
			programResponse = PROMPT_ERROR_MATRIX_OFFSET_OUT_OF_BOUNDS;
		}
	}
	else {
		programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_FOR_COMMAND + APOSTROPHE + COMMAND_DEL + APOSTROPHE + FULL_STOP;
	}
}

void Interface::processCommandClone() {
	if (this->args.size() != 2) {
		programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_NUMBER_FOR_COMMAND + APOSTROPHE + COMMAND_CLONE + APOSTROPHE + FULL_STOP;
	}
	else if (isArgumentAtIndexANumber(1) && !argumentAtIndexOverflowsInt(1)) {
		int errorCode = sparseMatrixManager->cloneMatrix(std::atoi(args.at(1).c_str()));
		if (errorCode != SUCCESS) {
			programResponse = PROMPT_ERROR_MATRIX_OFFSET_OUT_OF_BOUNDS;
		}
	}
	else {
		programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_FOR_COMMAND + APOSTROPHE + COMMAND_CLONE + APOSTROPHE + FULL_STOP;
	}
}

void Interface::processCommandRename() {
	if (this->args.size() != 3) {
		programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_NUMBER_FOR_COMMAND + APOSTROPHE + COMMAND_RENAME + APOSTROPHE + FULL_STOP;
	}
	else if (isArgumentAtIndexANumber(1) && !argumentAtIndexOverflowsInt(1)) {
		int errorCode = sparseMatrixManager->renameMatrix(std::atoi(args.at(1).c_str()), args.at(2));
		if (errorCode != SUCCESS) {
			programResponse = PROMPT_ERROR_MATRIX_OFFSET_OUT_OF_BOUNDS;
		}
	}
	else {
		programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_FOR_COMMAND + APOSTROPHE + COMMAND_RENAME + APOSTROPHE + FULL_STOP;
	}
}

void Interface::processCommandAddmat() {
	int lastArgumentIndex = args.size() - 1;
	if (this->args.size() < 4) {
		programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_NUMBER_FOR_COMMAND + APOSTROPHE + COMMAND_ADDMAT + APOSTROPHE + FULL_STOP;
	}
	else {
		addMatHelper(!isArgumentAtIndexANumber(lastArgumentIndex));
	}
}

void Interface::addMatHelper(bool hasName) {
	int numberOfDimensions;
	int defaultValue;
	int *dimensionSizes = nullptr;
	int lastArgumentIndex = args.size() - 1;
	int lastNumericArgumentIndex;
	if (hasName) {
		lastNumericArgumentIndex = lastArgumentIndex - 1;
	}
	else {
		lastNumericArgumentIndex = lastArgumentIndex;
	}

	bool numericArgumentsCorrect = isRangeOfArgumentsCorrect(1, lastNumericArgumentIndex);

	if (numericArgumentsCorrect) {
		numberOfDimensions = std::atoi(args.at(1).c_str());
		defaultValue = std::atoi(args.at(lastNumericArgumentIndex).c_str());
		int errorCode;
		if (hasName) {
			if (numberOfDimensions == args.size() - 4) {
				std::string matrixName = args.at(lastArgumentIndex);
				dimensionSizes = new int[numberOfDimensions];
				for (int i = 0; i < numberOfDimensions; i++) {
					dimensionSizes[i] = std::atoi(args.at(i + 2).c_str());
				}
				errorCode = sparseMatrixManager->addNewMatrix(numberOfDimensions, dimensionSizes, defaultValue, matrixName);
			}
			else {
				if (numberOfDimensions < 1) {
					errorCode = INVALID_NUMBER_OF_DIMENSIONS;
				}
				else {
					errorCode = INVALID_ARGUMENTS_NUMBER;
				}
			}
		}
		else {
			if (numberOfDimensions == args.size() - 3) {
				dimensionSizes = new int[numberOfDimensions];
				for (int i = 0; i < numberOfDimensions; i++) {
					dimensionSizes[i] = std::atoi(args.at(i + 2).c_str());
				}
				errorCode = sparseMatrixManager->addNewMatrix(numberOfDimensions, dimensionSizes, defaultValue);
			}
			else {
				if (numberOfDimensions < 1) {
					errorCode = INVALID_NUMBER_OF_DIMENSIONS;
				}
				else {
					errorCode = INVALID_ARGUMENTS_NUMBER;
				}
			}
		}
		switch (errorCode) {
		case SUCCESS:
			programResponse = EMPTY_STRING;  //constructor prints to screen so there's no need to print anything more
			break;
		case ERROR_CODES::NEGATIVE_DIMENSION_NUMBER:
			programResponse = PROMPT_ERROR_INVALID_DIMENSION_SIZES_NUMBER;
			delete[] dimensionSizes;
			break;
		case ERROR_CODES::INVALID_DIMENSION_SIZE:
			programResponse = PROMPT_ERROR_INVALID_DIMENSION_SIZE;
			delete[] dimensionSizes;
			break;
		case ERROR_CODES::INVALID_ARGUMENTS_NUMBER:
			programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_NUMBER_FOR_COMMAND + APOSTROPHE + COMMAND_ADDMAT + APOSTROPHE + FULL_STOP;
			break;
		case ERROR_CODES::INVALID_NUMBER_OF_DIMENSIONS:
			programResponse = PROMPT_ERROR_INVALID_DIMENSION_SIZES_NUMBER;
			break;
		}
	}
	else {
		programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_FOR_COMMAND + APOSTROPHE + COMMAND_ADDMAT + APOSTROPHE + FULL_STOP;
	}
}

void Interface::processCommandDef() {
	int lastArgumentIndex = args.size() - 1;
	int matrixOffset = std::atoi(args.at(1).c_str());
	if (args.size() < 4) {
		programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_NUMBER_FOR_COMMAND + APOSTROPHE + COMMAND_DEF + APOSTROPHE + FULL_STOP;
	}
	else if (isRangeOfArgumentsCorrect(1, lastArgumentIndex)) {
		int numberOfCoordinates = args.size() - 3;
		int newValue = std::atoi(args.at(lastArgumentIndex).c_str());
		int *dimensionSizes = new int[numberOfCoordinates];
		for (int i = 0, k = 2; i < numberOfCoordinates; i++, k++) {
			dimensionSizes[i] = std::atoi(args.at(k).c_str());
		}
		int errorCode = sparseMatrixManager->defineMatrixValue(matrixOffset, dimensionSizes, numberOfCoordinates, newValue);
		switch (errorCode) {
		case SUCCESS:
			programResponse = PROMPT_DEFINED_VALUE_IN_MATRIX_AT_OFFSET + args.at(1);
			break;
		case ERROR_CODES::INVALID_MATRIX_OFFSET:
			delete[] dimensionSizes;
			programResponse = PROMPT_ERROR_MATRIX_OFFSET_OUT_OF_BOUNDS;
			break;
		case ERROR_CODES::INVALID_ARGUMENTS_NUMBER:
			delete[] dimensionSizes;
			programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_NUMBER_FOR_COMMAND + APOSTROPHE + COMMAND_DEF + APOSTROPHE + FULL_STOP;
			break;
		case ERROR_CODES::INVALID_ARGUMENTS:
			delete[] dimensionSizes;
			programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_FOR_COMMAND + APOSTROPHE + COMMAND_DEF + APOSTROPHE + FULL_STOP;
			break;
		}
	}
	else {
		programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_FOR_COMMAND + APOSTROPHE + COMMAND_DEF + APOSTROPHE + FULL_STOP;
	}
}

void Interface::printProgramResponse() {
	if (this->programResponse != EMPTY_STRING) {
		std::cout << programResponse;
		if (!finished) {
			std::cout << std::endl;
		}
		this->programResponse = EMPTY_STRING;
	}
}

void Interface::printCommandPrompt() {
	std::cout << COMMAND_PROMPT + SPACE;
}

bool Interface::isArgumentAtIndexANumber(int indexOfArgument) {
	std::string argument = this->args.at(indexOfArgument);
	if (argument.at(0) == MINUS) argument = argument.substr(1, argument.size() - 1);
	std::string::const_iterator it = argument.begin();
	while (it != argument.end() && isdigit(*it)) {
		++it;
	}
	return !argument.empty() && it == argument.end();
}

bool Interface::argumentAtIndexOverflowsInt(int indexOfArgument) {
	//check string length for overflow
	std::string argument = this->args.at(indexOfArgument);
	if (argument.at(0) == MINUS) argument = argument.substr(1, argument.size() - 1);
	if (argument.size() < MAX_INT_STRING_LENGTH) {
		return false;
	}
	if (argument.size() > MAX_INT_STRING_LENGTH) {
		return true;
	}
	else {
		bool overflows = false;
		std::string::const_iterator it = argument.begin();
		std::string::const_iterator maxIntIt = MAX_INT_STRING.begin();
		while (it != argument.end() && !overflows) {
			if ((*maxIntIt) < (*it)) {
				overflows = true;
			}
			++it;
			++maxIntIt;
		}
		return overflows;
	}
}

bool Interface::isRangeOfArgumentsCorrect(int firstArgumentIndex, int lastArgumentIndex) {
	bool isCorrect = true;
	for (int i = lastArgumentIndex; i >= firstArgumentIndex && isCorrect; i--) {
		if (!isArgumentAtIndexANumber(i) || argumentAtIndexOverflowsInt(i)) {
			isCorrect = false;
		}
	}
	return isCorrect;
}