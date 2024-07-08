//***************************************
// Jan Zboril
// xzbori20
// BMS projekt
// 2023
//
// decode.cpp
//***************************************

#include "decode.hpp"

vector<int> syndrome(const vector<int> &y, const vector<vector<int>> &H) {
    vector<int> s_n;
    for (size_t j = 0; j < H.size(); ++j) {
        int tmp = binaryDotProduct(y, H[j]);
        s_n.push_back(tmp % 2);
    }
    return s_n;
}

bool isZeroVector(const vector<int> &vec) {
    unsigned int sum = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        sum += vec[i];
    }
    return sum == 0;
}

int errorCorrection(vector<int> &y, const vector<vector<int>> &H) {
    // get the syndrome of y
    vector<int> s_n = syndrome(y, H);

    // if the syndrome is zero, then y is a valid codeword
    if (isZeroVector(s_n))
        return 0;

    // get error vector f
    // f[i] = sum(s_n[j] * H[j][i] for j in range(len(s_n)))
    // make product of each row of H and s_n, then place the sum into f_vec at
    // index i
    vector<int> f_vec(H[0].size(), 0);
    vector<int> f_vec_max_idx;
    for (size_t col = 0; col < H[0].size(); col++) {
        int sum = 0;
        for (size_t row = 0; row < H.size(); row++) {
            sum += s_n[row] * H[row][col];
        }
        f_vec_max_idx.push_back(sum);
    }

    // Find index of largest sums
    int m = *max_element(f_vec_max_idx.begin(), f_vec_max_idx.end());
    int idx = 0;
    for (size_t i = 0; i < f_vec_max_idx.size(); ++i) {
        if (f_vec_max_idx[i] == m) {
            idx = i;
        }
    }

    // Flip the bits with the largest sum
    y[idx] = (y[idx] + 1) % 2;

    // syndrome was not 0, meaning there was an error
    // another iteration is needed, so return 1
    return 1;
}

vector<int> decode(string binary_string, matrix &parity_check_matrix,
                   int max_iterations) {
    // Convert string to vector<int>
    vector<int> binary_vector;
    for (size_t i = 0; i < binary_string.size(); i++) {
        binary_vector.push_back(binary_string[i] - '0');
    }

    int max_iter = 100;
    for (int i = 0; i < max_iter; i++) {
        int res_val = errorCorrection(binary_vector, parity_check_matrix);
        if (res_val == 0) {
            break;
        }
    }

    return binary_vector;
}

string getMessage(matrix &tG, vector<int> &x) {
    int n = tG.size();
    int k = tG[0].size();

    auto result = gaussElimination(tG, x);
    matrix rtG = result.first;
    vector<int> rx = result.second;

    vector<int> message(k, 0);

    message[k - 1] = rx[k - 1];
    for (int i = k - 2; i >= 0; --i) {
        message[i] = rx[i];
        for (int j = i + 1; j < k; ++j) {
            message[i] -= rtG[i][j] * message[j];
        }
    }

    // Take the absolute values of the elements in the message
    for (int &bit : message) {
        bit = abs(bit);
    }

    auto s = binaryVectorToAsciiString(message);
    return s;
}
