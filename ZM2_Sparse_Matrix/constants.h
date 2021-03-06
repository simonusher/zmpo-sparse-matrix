#pragma once
#include <string>

const int DEFAULT_DEFINED_ARRAY_CAPACITY = 4;
const float LOWER_CAPACITY_BOUND = 0.3;
const float UPPER_CAPACITY_BOUND = 0.7;

const std::string MAX_INT_STRING = std::to_string(INT_MAX);
const int MAX_INT_STRING_LENGTH = MAX_INT_STRING.size();


//utility strings
const char MINUS = '-';
const std::string SPACE = " ";
const std::string COLON = ":";
const std::string SEMICOLON = ";";
const std::string NEWLINE = "\n";
const std::string FULL_STOP = ".";
const std::string EMPTY_STRING = "";
const std::string APOSTROPHE = "'";

//error codes

enum ERROR_CODES
{
	SUCCESS,
	ALREADY_DEFINED_VALUES,
	INVALID_ARGUMENTS_NUMBER,
	NEGATIVE_DIMENSION_NUMBER,
	INVALID_ARGUMENTS,
	INVALID_MATRIX_OFFSET, 
	INVALID_NUMBER_OF_DIMENSIONS,
	INVALID_DIMENSION_SIZE
};
