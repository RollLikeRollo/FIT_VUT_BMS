//***************************************
// Jan Zboril
// xzbori20
// BMS projekt
// 2023
//
// bms.hpp
//***************************************

#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

#include "ldpc_matrix.hpp"

using namespace std;

/**
 * @brief Binary matrix is represented as a vector of vectors of ints
 *
 */
using matrix = vector<vector<int>>;

/**
 * @brief  Checks if input is valid and filter unwanted characters
 *          based on mode
 *          mode 'e' - encode - filter all characters except printable ASCII
 *          mode 'd' - decode - filter all characters except 0 and 1
 *
 * @param input  Input string to check
 * @param mode  Mode of operation - 'e' = encode, or 'd' = decode
 * @return pair<bool,string> Returns pair of bool and string. Bool is true if
 * input is valid, false otherwise. String is filtered input.
 */
pair<bool, string> checkInput(string input, char mode);

/**
 * @brief  Transpose matrix m, returns new transposed matrix of m
 *
 * @param m - matrix to transpose (vector of vectors of ints)
 * @return matrix - transposed matrix of m
 */
matrix transposeMatrix(matrix m);

/**
 * @brief Randomly shuffles rows of matrix m
 *
 * @param m - matrix to shuffle (vector of vectors of ints)
 * @return matrix - new shuffled matrix of m
 */
matrix permuteMatrixRows(matrix m);

/**
 * @brief Converts ASCII string into a string made of ASCII 0/1 representing the origina lstring in binary
 *
 * @param input ASCII string of characters
 * @return string - new string containg only chars 0 and 1 - binary representation of ASCII input string
 */
string stringToBinary(string input);

/**
 * @brief Reads Standard input into a string
 *
 * @return string
 */
string readStdIn();

/**
 * @brief Computes the row reduced form of a matrix
 *        Zeroes below a diagonal
 *
 * @param G  a binary matrix represented by vector of vectors of ints
 * @return matrix Row reduced matrix
 */
matrix gaussjordan(matrix &G);

/**
 * @brief Computes the binary dot product of vector Y and matrix X
 *        Returns new matrix as a result. Neither X nor Y are changed
 *        Result depends on theorder of inputs
 *
 * @param X matrix 1
 * @param Y vector 2
 * @return vector<int>
 */
vector<int> binaryDotProduct(const matrix &X, const vector<int> &Y);

/**
 * @brief Computes the binary dot product of two matrices X and Y
 *        Returns new matrix as a result. Neither X nor Y are changed
 *        Result depends on the order of inputs
 *
 * @param X matrix 1
 * @param Y matrix 2
 * @return matrix dost product of X and Y
 */
matrix binaryDotProduct(const matrix &X, const matrix &Y);

/**
 * @brief Computes the binary dot product of two vectors X and Y
 *        Returns new vector as a result. Neither X nor Y are changed
 *
 * @param X vector 1
 * @param Y vector 2
 * @return int
 */
int binaryDotProduct(const vector<int> &X, const vector<int> &Y);

/**
 * @brief print the argument to a standard output
 *
 * @param m matrix to print
 */
void printVector(vector<int> &v);

/**
 * @brief print the argument to a standard output
 *
 * @param m matrix to print
 */
void printMatrix(matrix &m);

/**
 * @brief prints the argument to a standard output
 *
 * @param v vector to print
 */
void printResult(vector<int> &v);

/**
 * @brief Prints the argumets to a standard output
 *
 * @param s
 */
void printResult(string &s);

/**
 * @brief Saves matrix represented by vector of vectors of ints into a file
 *        Matrix fields in a file are separated by spaces, rows by new line
 *
 * @param m - matrix to save
 * @param filename - save location
 */
void saveMatrix(matrix m, string filename);

/**
 * @brief Read matrix from a file
 *        Matrix represented by vector of vetors of ints
 *        File is matrix cells divided by spaces, rows separated by new lines
 *
 * @param filename file location from which to read
 * @return matrix obtaind from file
 */
matrix loadMatrix(string filename);

/**
 * @brief Converts a vector of ints representing binary values
 *        to a string of ASCII characters
 *
 * @param v vector of ints
 * @return string
 */
string binaryVectorToAsciiString(vector<int> v);

/**
 * @brief Performs Gauss Elimination on a binary matrix tG and vector x
 *        x represents the right side of system of linear equations
 *        tG represents the left side of system of linear equations
 *
 * @param tG
 * @param x
 * @return pair<matrix, vector<int>> matrix is the reduced tG,
 *         vector is the solution of the system of linear equations
 */
pair<matrix, vector<int>> gaussElimination(const matrix &tG, const vector<int> &x);

#endif