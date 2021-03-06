#pragma once
#include <string>
#include "SparseCell.h"
#include <iostream>
#include "constants.h"
#include "arrayUtils.h"

const std::string DEFAULT_MATRIX_NAME = "def_name";
const std::string MSG_MATRICES = "matrices";
const std::string MSG_SIZE = "size";
const std::string MSG_VALUES = "values";
const std::string MSG_CREATE = "create";
const std::string MSG_COPY = "_copy";
const std::string MSG_DESTROY = "destroy";

class SparseMatrix {
	friend class SparseMatrixManager;
	SparseMatrix(int numberOfDimensions, int *dimensionSizes, int defaultValue);
	SparseMatrix(int numberOfDimensions, int *dimensionSizes, int defaultValue, std::string name);
	SparseMatrix(SparseMatrix &other);
	~SparseMatrix();

	int defineDimensionsAndSizes(int numberOfDimensions, int *dimensionSizes);
	void changeDefaultValue(int defaultValue);
	int setValueAt(int *coordinates, int numberOfCoordinates, int value);
	int getValueAt(int *coordinates, int numberOfCoordinates, int &result);
	void copyOtherMatrixState(SparseMatrix &other);
	void setName(std::string newName);
	std::string getName();
	std::string getInfo();
	std::string toList();

	int numberOfDimensions;
	int *dimensionSizes;
	int defaultValue;
	int definedArrayCapacity;
	int numberOfDefinedValues;
	SparseCell **definedValuesArray;
	std::string name;
	void ensureCapacity();
	void printHelper(std::string &result, int *tab, int n);
	bool coordinatesCorrect(int *coordinates);
	SparseCell **findSparseCell(int *coordinates);
};