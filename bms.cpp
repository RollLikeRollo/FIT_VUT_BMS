//***************************************
// Jan Zboril
// xzbori20
// BMS projekt
// 2023
//
// bms.cpp
//***************************************

#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;

#include "bms.hpp"

using namespace std;

/**
 * @brief Load input, generate LDPC matrices, encode or decode the message
 *
 * @param argc
 * @param argv
 * @return int Return 0 on success, 1 on failure
 */
int main(int argc, char **argv) {
    /**
     * Define arguments and parse them
     *
     */
    char enc_dec;
    string working_string;
    while (true) {
        switch (getopt(argc, argv, "edh")) {
            case 'h':
                cerr << "Usage: " << argv[0] << " -e [ascii] -d [znaky hodnot bitu]"
                     << endl;
                cerr << "  -e [ascii]       ASCII symbols to encode" << endl;
                cerr << "  -d [0/1 string]  Bit representation to decode" << endl;
                return 0;
            case 'e':
                enc_dec = 'e';
                working_string = readStdIn();
                break;
            case 'd':
                enc_dec = 'd';
                working_string = readStdIn();
                break;
            default:
                break;
        }
        break;
    }

    // Check input and filter out invalid characters
    pair<bool, string> check = checkInput(working_string, enc_dec);
    if (!check.first) {
        cerr << "Invalid input" << endl;
        return 1;
    }
    working_string = check.second;

    // convert input to binary
    string binary_string;
    if (enc_dec == 'e') {
        binary_string = stringToBinary(working_string);
    } else if (enc_dec == 'd') {
        binary_string = working_string;
    }

    // define LDPC parameters
    int bsl = binary_string.length();
    int codeword_length = 2 * bsl;
    int d_c = bsl;
    int d_v = bsl - 1;

    // encode or decode the message
    if (enc_dec == 'e') {
        // generate LDPC matrices
        ldpc_matrices matrices =
            generateMatrices(codeword_length, d_c, d_v);

        vector<int> encoded = encode(binary_string, matrices.G);
        printResult(encoded);

        /**
         * save matrices to files,
         * same set of matrices is used for encoding and decoding
         */
        saveMatrix(matrices.H, "./H.bms.matrix");
        saveMatrix(matrices.G, "./G.bms.matrix");

    } else if (enc_dec == 'd') {
        matrix parity_check_matrix = loadMatrix("./H.bms.matrix");
        matrix coding_matrix = loadMatrix("./G.bms.matrix");

        // decode means to retrieve the send codewords
        auto decoded = decode(binary_string, parity_check_matrix, 1000);
        // extract message from codewords
        auto message = getMessage(coding_matrix, decoded);
        printResult(message);
    }

    return 0;
}
