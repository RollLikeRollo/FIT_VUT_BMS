//***************************************
// Jan Zboril
// xzbori20
// BMS projekt
// 2023
//
// encode.cpp
//***************************************
#include "encode.hpp"

vector<int> encode(string input, matrix &G) {
    // convert codewords to ints
    // each codeword is a vector of ints
    vector<int> input_int;
    for (size_t i = 0; i < input.size(); i++) {
        input_int.push_back(input[i] - '0');
    }

    // encode the binary input by multipliying codewords by G
    vector<int> codewords_encoded = binaryDotProduct(G, input_int);

    return codewords_encoded;
}