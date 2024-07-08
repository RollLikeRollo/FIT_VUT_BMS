//***************************************
// Jan Zboril
// xzbori20
// BMS projekt
// 2023
//
// ldpc_matrix.hpp
//***************************************

#ifndef LDPC_MATRIX_HPP
#define LDPC_MATRIX_HPP

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "utils.hpp"

using namespace std;

using matrix = vector<vector<int>>;

struct ldpc_matrices {
    matrix H;
    matrix G;
};

/**
 * @brief  Generate LDPC matrices H and G
 *        H is a check matrix, G is a generating matrix
 *        First, generate H using psedo randomness and column permuation.
 *        Generator matrix G is then computed from H by row reduction - done by Gauss-Jordan elimination.
 *
 * @param codeword_length  Length of codeword
 * @param d_c  Column weight
 * @param d_v  Row weight
 * @return ldpc_matrices  Returns pair of matrices H and G
 */
ldpc_matrices generateMatrices(int codeword_length, int d_c, int d_v);

/**
 * @brief  Generate LDPC check matrix H
 *        Decide the size of the first block of H based on d_c and d_v.
 *        Fill the first block with with pattern of 1s and 0s.:- depending on d_c and d_v.
 *        In our case of assignement
 *        [1 1 1 1 0 0 0 0]
 *        [0 0 0 0 1 1 1 1]
 *        Then use column permutation od the first block to fill the rest of H.
 *        The comlumn permutation is done via transposing the first block, permuting the rows and transposing back.
 *
 * @param codeword_length  Length of codeword
 * @param d_c  Column weight
 * @param d_v  Row weight
 * @param seed  Seed for pseudo randomness
 * @return matrix  Returns matrix H
 */
matrix genCheckMatrix(int codeword_length, int d_c, int d_v, int seed);

/**
 * @brief Generated coding matrix G from check matrix H
 *       X is computed by row reduction of transposed H using Gauss-Jordan elimination.
 *       Matrix Y with H.size() rows and H.size()/2 columns is created.
 *       First half of rows are filled with zeroes.
 *       Second half of rows are filled with identity matrix.
 *       Transposed matrix G is obtauned by dot product of transposed X and the matrix Y described above.
 *       If the resulting matrix G is not correct (diagonal of the bottom halfp is not 1), the function is called recursively
 *       until the matrix is correct.
 *
 * @param H Check matrix
 * @return matrix Returns transposed generator matrix tG
 */
matrix genCodingMatrix(matrix H);

#endif