//***************************************
// Jan Zboril
// xzbori20
// BMS projekt
// 2023
//
// encode.hpp
//***************************************
#ifndef ENCODE_HPP
#define ENCODE_HPP

#include <string>
#include <vector>

#include "ldpc_matrix.hpp"
#include "utils.hpp"

/**
 * @brief  Converts input string to binary vector.
 *         Encodes the binary vector by computing a dot product with LDPC matrix G (generating matrix).
 *
 * @param input Input ASCII 0/1 string to encode
 * @param G LDPC generating matrix, as a reference to avoid copying
 * @return vector<int> Encoded binary message represented as a vector of ints
 */
vector<int> encode(string input, matrix &G);

#endif