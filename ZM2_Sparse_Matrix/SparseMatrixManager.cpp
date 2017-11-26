#include "SparseMatrixManager.h"

SparseMatrixManager::SparseMatrixManager() {
};

SparseMatrixManager::~SparseMatrixManager() {
	deleteAllMatrices();
}
int SparseMatrixManager::addNewMatrix(int numberOfDimensions, int *dimensionSizes, int defaultValue, std::string name) {
	int errorCode = argumentsCorrect(numberOfDimensions, dimensionSizes);
	if (errorCode == SUCCESS) {
		matrices.push_back(new SparseMatrix(numberOfDimensions, dimensionSizes, defaultValue, name));
	}
	return errorCode;
}

int SparseMatrixManager::addNewMatrix(int numberOfDimensions, int *dimensionSizes, int defaultValue) {
	int errorCode = argumentsCorrect(numberOfDimensions, dimensionSizes);
	if (errorCode == SUCCESS) {
		matrices.push_back(new SparseMatrix(numberOfDimensions, dimensionSizes, defaultValue));
	}
	return errorCode;
}

std::string SparseMatrixManager::listMatrices() {
	std::string result;
	int numberOfMatrices = matrices.size();
	result.append(std::to_string(numberOfMatrices));
	result.append(SPACE + MSG_MATRICES + COLON);
	if (numberOfMatrices > 0) {
		result.append(NEWLINE);
	}
	for (int i = 0; i < numberOfMatrices; i++) {
		result.append(OPENING_SQUARE_BRACKET + std::to_string(i) + CLOSING_SQUARE_BRACKET + SPACE + MINUS + SPACE);
		result.append(matrices.at(i)->toList());
		if (i < numberOfMatrices - 1) {
			result.append(NEWLINE);
		}
	}
	return result;
}

int SparseMatrixManager::deleteAllMatrices() {
	for each (SparseMatrix* matrix in matrices) {
		delete matrix;
	}
	matrices.clear();
	return ERROR_CODES::SUCCESS;
}

int SparseMatrixManager::defineMatrixValue(int matrixOffset, int *coordinates, int numberOfCoordinates, int newValue) {
	if (matrixOffset < 0 || matrixOffset >= matrices.size()) return ERROR_CODES::INVALID_MATRIX_OFFSET;
	return matrices.at(matrixOffset)->setValueAt(coordinates, numberOfCoordinates, newValue);
}

int SparseMatrixManager::printMatrix(int matrixOffset, std::string &result) {
	if (matrixOffset < 0 || matrixOffset >= matrices.size()) return ERROR_CODES::INVALID_MATRIX_OFFSET;
	result = matrices.at(matrixOffset)->getInfo();
	return SUCCESS;
}

int SparseMatrixManager::cloneMatrix(int matrixOffset) {
	if (matrixOffset < 0 || matrixOffset >= matrices.size()) return ERROR_CODES::INVALID_MATRIX_OFFSET;
	matrices.push_back(new SparseMatrix(*matrices.at(matrixOffset)));
	return SUCCESS;
}

int SparseMatrixManager::renameMatrix(int matrixOffset, std::string newName) {
	if (matrixOffset < 0 || matrixOffset >= matrices.size()) return ERROR_CODES::INVALID_MATRIX_OFFSET;
	matrices.at(matrixOffset)->setName(newName);
	return SUCCESS;
}

int SparseMatrixManager::argumentsCorrect(int numberOfDimensions, int *dimensionSizes){
	if (numberOfDimensions < 1) return ERROR_CODES::INVALID_NUMBER_OF_DIMENSIONS;
	else {
		bool correct = true;
		for (int i = 0; i < numberOfDimensions && correct; i++) {
			if (dimensionSizes[i] < 1) {
				correct = false;
			}
		}
		return correct ? SUCCESS : ERROR_CODES::INVALID_DIMENSION_SIZE;
	}
}

int SparseMatrixManager::deleteMatrix(int matrixOffset) {
	if (matrixOffset < 0 || matrixOffset >= matrices.size()) return ERROR_CODES::INVALID_MATRIX_OFFSET;
	delete matrices.at(matrixOffset);
	matrices.erase(matrices.begin() + matrixOffset);
	return SUCCESS;
}