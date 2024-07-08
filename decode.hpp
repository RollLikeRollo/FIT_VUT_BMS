//***************************************
// Jan Zboril
// xzbori20
// BMS projekt
// 2023
//
// decode.hpp
//***************************************

#ifndef DECODE_HPP
#define DECODE_HPP

#include <numeric>
#include <string>
#include <vector>

#include "utils.hpp"

/**
 * @brief Makes a binary vector of ints from a string of 0s and 1s
 *      Each character of the string is converted to an int and appended to the vector
 *      iteratively calls the errorCorrection function to correct errors in the vector
 *      using the bit-flipping algorithm and parity check matrix H.
 *      It then process the messages in a same way as in https://github.com/hichamjanati/pyldpc/blob/master/pyldpc/decoder.py
 *      Returns the corrected vector of ints
 *
 * @param binary_string Binary string to decode (string of 0s and 1s)
 * @param parity_check_matrix Parity check matrix H of the LDPC code
 * @param max_iterations Specifies the maximum number of iterations of the bit-flipping algorithm
 * @return vector<int>  Decoded message in binary vector of ints
 */
vector<int> decode(string binary_string, matrix &parity_check_matrix,
                   int max_iterations);

/**
 * @brief Extracts the message from the decoded vector of ints by solving system of linear equations
 *        using the generator matrix G of the LDPC code as the equations and the decoded vector of ints as
 *        the right-hand side of the equations.
 *        The system of linear equations is solved using Gaussian elimination.
 *
 *        Returns the decoded message as a string.
 *
 * @param tG
 * @param decoded
 * @return string
 */
string getMessage(matrix &tG, vector<int> &decoded);

/**
 * @brief Computes the syndrome of a vector y and a parity check matrix H
 *        using the dot product of a vector Y and a parity check matrix H.
 *        The syndrome is a vector of dot products of each row of H and y.
 *        Syndrome values are binary - dot product modulo 2.
 *
 *        Iterates over the rows of matrix H. For each row, it computes the dot product
 *        of the vector y and the corresponding row of H, takes the sum modulo 2,
 *        and appends the result to result vector.
 *
 *        Neither the vector y nor the matrix H are modified during the computation.
 *
 * @param y
 * @param H
 * @return vector<int> Binary syndrome vector
 */
vector<int> syndrome(const vector<int> &y, const vector<vector<int>> &H);

/**
 * @brief Detects if a vector contains only zeros
 *
 * @param v
 * @return true if v contains only zeros
 * @return false otherwise
 */
bool isZeroVector(const vector<int> &v);

/**
 * @brief Does one step of the bit-flipping algorithm
 *        First calculates the syndrome of the vector y and the parity check matrix H
 *        Returns 0 if the syndrome is zero, meaning there are no errors in the vector y
 *        Else, make product of each column of H and the syndrome, then place the sum into
 *        fail vector at index i. Find index of largest sums. Flip the bits of the vector y
 *        at the index of the largest sum. If more than one index has the largest sum, flip only
 *        the last one.
 *
 *        Modifies the vector y during computation. Use vector y in the next iteration until
 *        the syndrome is zero.
 *
 * @param y vector of ints to correct
 * @param H parity check matrix
 * @return int 0 if no errors, 1 if vector y was modified (contained errors)
 */
int errorCorrection(vector<int> &y, const vector<vector<int>> &H);

#endif