#pragma once
#include "SparseMatrix.h"
#include <vector>
#include "constants.h"

class SparseMatrixManager {
public:
	SparseMatrixManager();
	~SparseMatrixManager();
	int addNewMatrix(int numberOfDimensions, int *dimensionSizes, int defaultValue, std::string name);
	int addNewMatrix(int numberOfDimensions, int *dimensionSizes, int defaultValue);
	std::string listMatrices();
	int deleteMatrix(int matrixOffset);
	int deleteAllMatrices();
	int defineMatrixValue(int matrixOffset, int *coordinates, int numberOfCoordinates, int newValue);
	int printMatrix(int matrixOffset, std::string &result);
	int cloneMatrix(int matrixOffset);
	int renameMatrix(int matrixOffset, std::string newName);
private:
	std::vector<SparseMatrix*> matrices;
	int argumentsCorrect(int numberOfDimensions, int *dimensionSizes);
};