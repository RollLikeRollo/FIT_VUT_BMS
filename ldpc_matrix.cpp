//***************************************
// Jan Zboril
// xzbori20
// BMS projekt
// 2023
//
// ldpc_matrix.cpp
//***************************************

#include "ldpc_matrix.hpp"

using namespace std;

matrix genCheckMatrix(int n_code, int d_c, int d_v, int seed = 42) {
    std::mt19937 rng(seed);

    // check parameter validity
    if (d_v <= 1) {
        throw std::invalid_argument("d_v must be >= 2.");
    }

    if (d_c <= d_v) {
        throw std::invalid_argument("d_c must be >= d_v.");
    }

    if (n_code % d_c != 0) {
        throw std::invalid_argument(
            "d_c must divide n for a regular LDPC matrix H.");
    }

    // how many equations  - used for determining the block size
    int n_equations = (n_code * d_v) / d_c;

    // Initialize H with 0s - first block
    matrix block(n_equations / d_v, std::vector<int>(n_code, 0));
    matrix H(n_equations, std::vector<int>(n_code, 0));
    int block_size = n_equations / d_v;

    // Fill the first block and first block in H with 1s
    for (int i = 0; i < block_size; i++) {
        for (int j = i * d_c; j < (i + 1) * d_c; j++) {
            H[i][j] = 1;
            block[i][j] = 1;
        }
    }

    // Column permutation of the first block
    for (int i = 1; i < d_v; i++) {
        auto c = transposeMatrix(permuteMatrixRows(transposeMatrix(block)));
        for (int j = 0; j < block_size; j++) {
            H[i * block_size + j] = c[j];
        }
    }

    return H;
}

matrix genCodingMatrix(matrix H) {
    // copy H to G to avoid modifying H
    auto G = H;

    // number of matrix columns
    int c = H[0].size();

    matrix tG = transposeMatrix(G);
    matrix tQ = gaussjordan(tG);
    matrix Q = transposeMatrix(tQ);

    // create Y matrix
    // it has c/2 rows and c columns
    // fill the first half of the rows with 0s
    // fill the second half of the rows with 1s at the diagonal, rest 0s
    matrix Y = matrix(c, vector<int>(c / 2, 0));
    int row = c / 2;
    size_t iter_limit = c / 2;
    for (size_t i = 0; i < iter_limit; i++) {
        Y[row][i] = 1;
        row++;
    }

    // transposed generator matrix is the product of Q and Y
    tG = binaryDotProduct(Q, Y);

    // check if the matrix is correct (diag = 1)
    // create another one if not
    bool matrix_ok = false;
    do {
        for (size_t i = 0; i < tG.size() / 2; i++) {
            for (size_t j = 0; j < tG[i].size(); j++) {
                if (tG[i][j] == 1) {
                    matrix_ok = true;
                    break;
                }
            }
            if (matrix_ok) {
                break;
            }
        }
        if (!matrix_ok) {
            tG = genCodingMatrix(H);
            return tG;
        }
    } while (!matrix_ok);

    return tG;
}

ldpc_matrices generateMatrices(int codeword_length, int d_c, int d_v) {
    matrix H = genCheckMatrix(codeword_length, d_c, d_v);
    matrix G = genCodingMatrix(H);
    ldpc_matrices ldpc = {H, G};
    return ldpc;
}
