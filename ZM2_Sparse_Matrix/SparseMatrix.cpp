#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(int numberOfDimensions, int *dimensionSizes, int defaultValue):
	numberOfDimensions(numberOfDimensions), dimensionSizes(dimensionSizes), defaultValue(defaultValue) {
	name = DEFAULT_MATRIX_NAME;
	definedArrayCapacity = DEFAULT_DEFINED_ARRAY_CAPACITY;
	numberOfDefinedValues = 0;
	definedValuesArray = new SparseCell*[definedArrayCapacity];
	std::cout << MSG_CREATE + COLON + SPACE << name << std::endl;
}

SparseMatrix::SparseMatrix(int numberOfDimensions, int *dimensionSizes, int defaultValue, std::string name):
	numberOfDimensions(numberOfDimensions), dimensionSizes(dimensionSizes), defaultValue(defaultValue), name(name){
	definedArrayCapacity = DEFAULT_DEFINED_ARRAY_CAPACITY;
	numberOfDefinedValues = 0;
	definedValuesArray = new SparseCell*[definedArrayCapacity];
	std::cout << MSG_CREATE + COLON + SPACE << name << std::endl;
}

SparseMatrix::SparseMatrix(SparseMatrix &other){
	this->numberOfDimensions = other.numberOfDimensions;
	this->dimensionSizes = new int[this->numberOfDimensions];
	arrayUtils::copyArray(this->dimensionSizes, other.dimensionSizes, this->numberOfDimensions);
	this->defaultValue = other.defaultValue;
	this->name = other.name + MSG_COPY;
	this->definedArrayCapacity = other.definedArrayCapacity;
	this->numberOfDefinedValues = other.numberOfDefinedValues;
	this->definedValuesArray = new SparseCell*[definedArrayCapacity];
	for (int i = 0; i < numberOfDefinedValues; i++) {
		this->definedValuesArray[i] = new SparseCell(*(other.definedValuesArray[i]), numberOfDimensions);
	}
	std::cout << MSG_CREATE + COLON + SPACE << name << std::endl;
}

SparseMatrix::~SparseMatrix() {
	delete[] dimensionSizes;
	for (int i = 0; i < numberOfDefinedValues; i++) {
		delete definedValuesArray[i];
	}
	delete[] definedValuesArray;
	std::cout << MSG_DESTROY + COLON + SPACE << name << std::endl;
}


int SparseMatrix::defineDimensionsAndSizes(int numberOfDimensions, int *dimensionSizes) {
	if (this->numberOfDefinedValues == 0) {
		this->numberOfDimensions = numberOfDimensions;
		delete[] this->dimensionSizes;
		this->dimensionSizes = dimensionSizes;
		return ERROR_CODES::SUCCESS;
	}
	else {
		return ERROR_CODES::ALREADY_DEFINED_VALUES;
	}
}

void SparseMatrix::changeDefaultValue(int defaultValue) {
	this->defaultValue = defaultValue;
}

int SparseMatrix::setValueAt(int *coordinates, int numberOfCoordinates, int newValue) {
	if (numberOfCoordinates != this->numberOfDimensions) {
		return ERROR_CODES::INVALID_ARGUMENTS_NUMBER;
	}
	else {
		if (coordinatesCorrect(coordinates)) {
			SparseCell **definedSparseCellPtr = findSparseCell(coordinates);
			if (definedSparseCellPtr == nullptr) {
				if (newValue != this->defaultValue) {
					ensureCapacity();
					this->definedValuesArray[numberOfDefinedValues++] = new SparseCell(coordinates, newValue);
				}
			}
			else {
				if (newValue != this->defaultValue) {
					(*definedSparseCellPtr)->value = newValue;
				}
				else {
					delete *definedSparseCellPtr;
					arrayUtils::moveArrayLeftByOne(definedSparseCellPtr + 1, definedValuesArray
						+ numberOfDefinedValues - definedSparseCellPtr - 1);
					numberOfDefinedValues--;
					//definedSparseCellPtr + 1 is the pointer to an object after the one that's being deleted
					//definedValuesArray + numberOfDefinedValues is a pointer to the end of the array
					//the argument is therefore the number of elements between the first one moved and the last in the array
				}
			}
			return ERROR_CODES::SUCCESS;
		}
		else {
			return ERROR_CODES::INVALID_ARGUMENTS;
		}
	}
}

int SparseMatrix::getValueAt(int *coordinates, int numberOfCoordinates, int &result) {
	if (numberOfCoordinates != this->numberOfDimensions) {
		return ERROR_CODES::INVALID_ARGUMENTS_NUMBER;
	}
	else {
		if (coordinatesCorrect(coordinates)) {
			SparseCell **definedSparseCellPtr = findSparseCell(coordinates);
			if (definedSparseCellPtr == nullptr) {
				result = defaultValue;
			}
			else {
				result = (*definedSparseCellPtr)->value;
			}
			return SUCCESS;
		}
		else {
			return ERROR_CODES::INVALID_ARGUMENTS;
		}
	}
}

void SparseMatrix::copyOtherMatrixState(SparseMatrix &other) {
	//delete
	delete[] dimensionSizes;
	for (int i = 0; i < numberOfDefinedValues; i++) {
		delete definedValuesArray[i];
	}
	delete[] definedValuesArray;
	//copy state
	this->numberOfDimensions = other.numberOfDimensions;
	this->dimensionSizes = new int[other.numberOfDimensions];
	arrayUtils::copyArray(this->dimensionSizes, other.dimensionSizes, numberOfDimensions);
	this->numberOfDefinedValues = other.numberOfDefinedValues;
	this->definedArrayCapacity = other.definedArrayCapacity;
	this->definedValuesArray = new SparseCell*[this->definedArrayCapacity];
	for (int i = 0; i < numberOfDefinedValues; i++) {
		this->definedValuesArray[i] = new SparseCell(*(other.definedValuesArray[i]), numberOfDimensions);
	}
}

void SparseMatrix::setName(std::string newName) {
	this->name = newName;
}

std::string SparseMatrix::getName() {
	return this->name;
}

std::string SparseMatrix::getInfo() {
	std::string matrixInfo;
	matrixInfo.append(MSG_SIZE + COLON + SPACE);
	matrixInfo.append(arrayUtils::arrayToString(this->dimensionSizes, this->numberOfDimensions));
	matrixInfo.append(SPACE + MSG_VALUES + COLON + SPACE);
	int *temp = new int[numberOfDimensions];
	printHelper(matrixInfo, temp, 0);
	delete temp;
	return matrixInfo;
}

void SparseMatrix::ensureCapacity() {
	arrayUtils::ensureCapacity(definedArrayCapacity, definedValuesArray, numberOfDefinedValues, LOWER_CAPACITY_BOUND, UPPER_CAPACITY_BOUND, DEFAULT_DEFINED_ARRAY_CAPACITY);
}

bool SparseMatrix::coordinatesCorrect(int *coordinates)
{
	bool correct = true;
	int numberOfDimensions = this->numberOfDimensions;
	for (int i = 0; i < numberOfDimensions && correct; i++) {
		if (coordinates[i] < 0 || coordinates[i] >= dimensionSizes[i]) {
			correct = false;
		}
	}
	return correct;
}

SparseCell **SparseMatrix::findSparseCell(int *coordinates)
{
	bool found = false;
	SparseCell **res = nullptr;
	for (int i = 0; i < this->numberOfDefinedValues && !found; i++) {
		bool correct = true;
		int *definedCoords = ((this->definedValuesArray[i])->coordinates);
		for (int j = 0; j < numberOfDimensions && correct; j++) {
			if (coordinates[j] != definedCoords[j]) {
				correct = false;
			}
		}
		if (correct) {
			res = &(definedValuesArray[i]);
			found = true;
		}
	}
	return res;
}

void SparseMatrix::printHelper(std::string &result, int *tab, int n) {
	for (int i = 0; i < dimensionSizes[n]; i++) {
		tab[n] = i;
		if (n == numberOfDimensions - 1) {
			int value;
			getValueAt(tab, numberOfDimensions, value);
			result.append(arrayUtils::arrayToString(tab, this->numberOfDimensions));
			result.append(COLON);
			result.append(std::to_string(value));
			result.append(SEMICOLON);
		}
		else printHelper(result, tab, n + 1);
	}
}

std::string SparseMatrix::toList() {
	std::string result;
	result.append(name);
	result.append(SPACE + MSG_SIZE + COLON + SPACE);
	result.append(arrayUtils::arrayToString(dimensionSizes, numberOfDimensions));
	return result;
}