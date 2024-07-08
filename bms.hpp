//***************************************
// Jan Zboril
// xzbori20
// BMS projekt
// 2023
//
// bms.hpp
//***************************************

#ifndef BMS_HPP
#define BMS_HPP

#include <getopt.h>

#include <iostream>
#include <string>
#include <vector>

#include "decode.hpp"
#include "encode.hpp"
#include "ldpc_matrix.hpp"
#include "utils.hpp"

using namespace std;

/**
 * @brief Load data from standard input, generate LDPC matrices, encode or decode the message
 *
 * @param argc
 * @param argv [-e|-d] [input]
 * @return int Return 0 on success, 1 on failure
 */
int main(int argc, char **argv);

#endif
