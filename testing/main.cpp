// #include <algorithm>
// #include <cstdlib>
// #include <fstream>
// #include <iomanip>
// #include <iostream>
// #include <numeric>
// #include <string>
// #include <vector>

// using namespace std;

// // Define the LDPCBitFlippingDecoder class
// class LDPCBitFlippingDecoder {
// public:
//   LDPCBitFlippingDecoder(const std::vector<std::vector<int>>
//   &parityCheckMatrix)
//       : parityCheckMatrix_(parityCheckMatrix) {
//     numVariableNodes_ = parityCheckMatrix[0].size();
//     numCheckNodes_ = parityCheckMatrix.size();
//     receivedBits_.resize(numVariableNodes_, 0);
//     Initialize();
//   }

//   std::vector<int> Decode(const std::vector<int> &receivedBits,
//                           int maxIterations) {
//     receivedBits_ = receivedBits;

//     for (int iteration = 0; iteration < maxIterations; ++iteration) {
//       UpdateVariableNodes();
//       UpdateCheckNodes();

//       if (Converged()) {
//         break;
//       }
//     }

//     return receivedBits_;
//   }

// private:
//   std::vector<std::vector<int>> parityCheckMatrix_;
//   std::vector<int> receivedBits_;
//   int numVariableNodes_;
//   int numCheckNodes_;

//   void Initialize() {
//     // Perform any necessary initialization
//   }

//   void UpdateVariableNodes() {
//     for (int i = 0; i < numVariableNodes_; ++i) {
//       int syndrome = 0;
//       for (int j = 0; j < numCheckNodes_; ++j) {
//         if (parityCheckMatrix_[j][i] == 1) {
//           syndrome += receivedBits_[j];
//         }
//       }

//       // If the syndrome is non-zero, flip the variable node
//       if (syndrome % 2 != 0) {
//         receivedBits_[i] = 1 - receivedBits_[i];
//       }
//     }
//   }

//   void UpdateCheckNodes() {
//     for (int i = 0; i < numCheckNodes_; ++i) {
//       int parity = 0;
//       for (int j = 0; j < numVariableNodes_; ++j) {
//         if (parityCheckMatrix_[i][j] == 1) {
//           parity += receivedBits_[j];
//         }
//       }

//       // Update variable nodes based on parity
//       for (int j = 0; j < numVariableNodes_; ++j) {
//         if (parityCheckMatrix_[i][j] == 1) {
//           receivedBits_[j] = parity % 2;
//         }
//       }
//     }
//   }

//   bool Converged() {
//     // Check for convergence based on specific criteria
//     // (e.g., all parity-check equations are satisfied)
//     // Return true if converged, false otherwise
//     return true; // Placeholder, actual convergence check needed
//   }
// };

// //-------------------------------------------------------------------------

// // Function to perform LDPC decoding using Belief Propagation
// std::vector<int>
// ldpcDecode(const std::vector<int> &receivedBits,
//            const std::vector<std::vector<int>> &parityCheckMatrix) {
//   int n = receivedBits.size();

//   // Initialize variable nodes and check nodes
//   std::vector<double> variableNodes(n, 0.0);
//   std::vector<double> checkNodes(parityCheckMatrix.size(), 0.0);

//   // Set received bits as the initial values of variable nodes
//   for (int i = 0; i < n; ++i) {
//     variableNodes[i] = receivedBits[i];
//   }

//   // Number of iterations (you can adjust this based on your requirements)
//   int maxIterations = 50;

//   // Perform Belief Propagation iterations
//   for (int iteration = 0; iteration < maxIterations; ++iteration) {
//     // Update check nodes based on variable node values
//     for (int i = 0; i < parityCheckMatrix.size(); ++i) {
//       checkNodes[i] = 0.0;
//       for (int j = 0; j < n; ++j) {
//         if (parityCheckMatrix[i][j] == 1) {
//           checkNodes[i] += variableNodes[j];
//         }
//       }
//       // Take into account the received bits in the check nodes update
//       checkNodes[i] += receivedBits[i];
//     }

//     // Update variable nodes based on check node values
//     for (int i = 0; i < n; ++i) {
//       variableNodes[i] = receivedBits[i];
//       for (int j = 0; j < parityCheckMatrix.size(); ++j) {
//         if (parityCheckMatrix[j][i] == 1) {
//           variableNodes[i] += checkNodes[j];
//         }
//       }
//       // Apply hard decision (0 or 1)
//       variableNodes[i] = (variableNodes[i] >= 0) ? 1 : 0;
//     }
//   }

//   // Convert double values to integers (hard decisions)
//   std::vector<int> decodedBits(n);
//   for (int i = 0; i < n; ++i) {
//     decodedBits[i] = static_cast<int>(variableNodes[i]);
//   }

//   return decodedBits;
// }

// //-------------------------------------------------------------------------

// std::vector<std::vector<int>> loadMatrix(string filename) {
//   ifstream myfile(filename);
//   string line;
//   std::vector<std::vector<int>> m;
//   while (getline(myfile, line)) {
//     vector<int> row;
//     stringstream ss(line);
//     int i;
//     while (ss >> i) {
//       row.push_back(i);
//       if (ss.peek() == ' ') {
//         ss.ignore();
//       }
//     }
//     m.push_back(row);
//   }
//   return m;
// }

// // int ldpcDecodeBitFlip(std::vector<int> receivedBits,
// //                       std::vector<std::vector<int>> parityCheckMatrix,
// //                       std::vector<int> &correct_codeword,
// //                       bool printResult = true) {
// //   int h_rows = parityCheckMatrix.size();
// //   vector<int> s_vec(h_rows, 0);
// //   int s_vec_sum = 0;

// //   printf("Received bits: [");
// //   for (int i = 0; i < receivedBits.size(); i++) {
// //     printf("%d, ", receivedBits[i]);
// //   }
// //   printf("]\n");

// //   for (int row = 0; row < h_rows; row++) {
// //     int sum = 0;
// //     for (int col = 0; col < parityCheckMatrix[row].size(); col++) {
// //       int idx = parityCheckMatrix[row][col] - 1;
// //       sum += receivedBits[idx];
// //     }
// //     int tmp = sum % 2;
// //     printf("Sum: %d, tmp: %d\n", sum, tmp);
// //     s_vec_sum += sum;
// //     s_vec[row] = sum;
// //     for (int i = 0; i < s_vec.size(); i++) {
// //       printf("%d, ", s_vec[i]);
// //     }
// //     printf("]\n");
// //   }

// //   if (printResult) {
// //     // print s_n
// //     cout << "S_N: [";
// //     for (int i = 0; i < h_rows; i++) {
// //       cout << s_vec[i] << ", ";
// //     }
// //     cout << "]" << endl;
// //     cout << "Sum s_n: " << s_vec_sum << endl;
// //   }

// //   /* If the sum of sumvec == 0, we are done */
// //   if (s_vec_sum == 0) {
// //     printf("suma je 0\n");
// //     return 0;
// //   }

// //   /* Step 2 */
// //   int h_cols = parityCheckMatrix[0].size();
// //   vector<int> f_vec(h_cols, 0);
// //   vector<int> f_vec_max_idx;
// //   int f_vec_current_max = 0;

// //   for (int col = 0; col < h_cols; col++) {
// //     int sum = 0;
// //     for (int row = 0; row < h_rows; row++) {
// //       int idx = parityCheckMatrix[row][col] - 1;
// //       sum += s_vec[idx];
// //     }
// //     f_vec[col] = sum;

// //     /* Save the indexes of the maximums */
// //     if (sum > f_vec_current_max) {
// //       // The new max
// //       f_vec_current_max = sum;
// //       f_vec_max_idx.clear();
// //       f_vec_max_idx.push_back(col);
// //     } else if (sum == f_vec_current_max) {
// //       f_vec_max_idx.push_back(col);
// //     }
// //   }

// //   if (printResult) {
// //     // print f_n
// //     cout << "F_N: [";
// //     for (int i = 0; i < h_cols; i++) {
// //       cout << f_vec[i] << ", ";
// //     }
// //     cout << "]" << endl;
// //     cout << "Max f_n: " << f_vec_current_max << endl;
// //     cout << "F_N max idx vector: [";
// //     for (int i = 0; i < f_vec_max_idx.size(); i++) {
// //       cout << f_vec_max_idx.at(i) << ", ";
// //     }
// //     cout << "]" << endl;
// //   }

// //   /* Step 3 */
// //   /* Flip the bits with the largest sum */
// //   for (auto idx : f_vec_max_idx) {
// //     // cout << "Mod idx: " << idx << endl;
// //     correct_codeword[idx] = (correct_codeword[idx] + 1) % 2;
// //   }

// //   return 1;
// // }

// // Function to calculate syndrome
// vector<int> calculateSyndrome(const vector<int> &y,
//                               const vector<vector<int>> &H) {
//   vector<int> s_n;
//   for (size_t j = 0; j < H.size(); ++j) {
//     int tmp = 0;
//     for (size_t k = 0; k < y.size(); ++k) {
//       tmp += y[k] * H[j][k];
//     }
//     s_n.push_back(tmp % 2);
//   }
//   return s_n;
// }

// void printVector(const vector<int> &v) {
//   for (int i = 0; i < v.size(); i++) {
//     printf("%d, ", v[i]);
//   }
//   printf("\n");
// }
// void printVector(const vector<size_t> &v) {
//   for (int i = 0; i < v.size(); i++) {
//     printf("%d, ", v[i]);
//   }
//   printf("\n");
// }

// // Function to check if syndrome is all zero
// bool isSyndromeZero(const vector<int> &s_n) {
//   return (std::accumulate(s_n.begin(), s_n.end(), 0) == 0);
// }

// // Function to perform error correction
// int errorCorrection(vector<int> &y, const vector<vector<int>> &H) {
//   // Calculate syndrome
//   vector<int> s_n = calculateSyndrome(y, H);

//   // If syndrome is all zero, we are done
//   if (isSyndromeZero(s_n)) {
//     printf("Syndrome is zero\n");
//     return 0;
//   }
//   printf("Syndrome is not zero ");
//   printVector(s_n);

//   // Calculate error locations
//   vector<int> f_vec(H[0].size(), 0);
//   vector<int> f_vec_max_idx;
//   int f_vec_current_max = 0;
//   for (size_t col = 0; col < H[0].size(); col++) {
//     int sum = 0;
//     for (size_t row = 0; row < H.size(); row++) {
//       sum += s_n[row] * H[row][col];
//     }
//     f_vec_max_idx.push_back(sum);

//     // if (sum > f_vec_current_max) {
//     //   // The new max
//     //   f_vec_current_max = sum;
//     //   f_vec_max_idx.clear();
//     //   f_vec_max_idx.push_back(col);
//     // } else if (sum == f_vec_current_max) {
//     //   f_vec_max_idx.push_back(col);
//     // }
//   }
//   printf("f_vec_max_idx: ");
//   printVector(f_vec_max_idx);

//   // Find index of largest sums
//   int m = *max_element(f_vec_max_idx.begin(), f_vec_max_idx.end());
//   int idx = 0;
//   for (size_t i = 0; i < f_vec_max_idx.size(); ++i) {
//     if (f_vec_max_idx[i] == m) {
//       idx = i;
//     }
//   }
//   printf("idx: %d\n", idx);
//   // printVector(idx);

//   // Flip the bits with the largest sum
//   y[idx] = (y[idx] + 1) % 2;
//   printf("\n");
//   return 1;
// }

// int main() {
//   // Example usage
//   vector<vector<int>> H = {{1, 0, 1}, {0, 1, 1}, {1, 1, 0}};
//   vector<int> y = {1, 0, 1};

//   std::vector<std::vector<int>> parityCheckMatrix = loadMatrix("H.txt");
//   for (auto &row : parityCheckMatrix) {
//     for (auto &col : row) {
//       std::cout << col << " ";
//     }
//     std::cout << "\n";
//   }

//   std::vector<int> originalbits = {0, 0, 1, 1, 1, 0, 0, 1,
//                                    1, 0, 1, 1, 0, 0, 0, 1};

//   printf("original bits:  [");
//   for (int i = 0; i < originalbits.size(); i++) {
//     printf("%d, ", originalbits[i]);
//   }
//   printf("]\n");

//   std::vector<int> receivedBits = {0, 0, 1, 1, 1, 0, 0, 1,
//                                    1, 0, 1, 1, 0, 1, 1, 0};

//   printf("Received bits:  [");
//   for (int i = 0; i < receivedBits.size(); i++) {
//     printf("%d, ", receivedBits[i]);
//   }
//   printf("]\n");

//   // Perform error correction
//   // errorCorrection(y, H);

//   int maxiter = 10000;
//   for (int i = 0; i < maxiter; i++) {
//     int ret = errorCorrection(receivedBits, parityCheckMatrix);
//     if (ret == 0) {
//       printf("Converged after %d iterations\n", i);
//       break;
//     }
//     if (i == maxiter - 1) {
//       printf("Did not converge after %d iterations\n", i);
//     }
//   }

//   // Output corrected vector
//   // cout << "Corrected Vector: ";
//   // for (int bit : y) {
//   //   cout << bit << " ";
//   // }
//   // cout << endl;
//   // Output corrected vector
//   printf("corrected bits: [");
//   for (int i = 0; i < receivedBits.size(); i++) {
//     printf("%d, ", receivedBits[i]);
//   }
//   printf("]\n");

//   return 0;
// }

// // int main() {
// //   // Example usage:
// //   std::vector<std::vector<int>> parityCheckMatrix = loadMatrix("H.txt");
// //   for (auto &row : parityCheckMatrix) {
// //     for (auto &col : row) {
// //       std::cout << col << " ";
// //     }
// //     std::cout << "\n";
// //   }
// //   std::vector<int> receivedBits = {0, 0, 1, 1, 1, 0, 0, 1,
// //                                    1, 0, 1, 1, 0, 0, 0, 1};

// //   //   LDPCBitFlippingDecoder decoder(parityCheckMatrix);
// //   //   std::vector<int> decodedBits = decoder.Decode(receivedBits, 10);

// //   // auto decodedBits = ldpcDecodeBitFlip(receivedBits,
// parityCheckMatrix);

// //   std::vector<int> decoded(receivedBits.size(), 0);

// //   const int N_ITER = 20;
// //   for (int i = 0; i < N_ITER; i++) {
// //     printf("Iteration %d\n", i);
// //     if (ldpcDecodeBitFlip(receivedBits, parityCheckMatrix, decoded, true)
// //     ==
// //         0) {
// //       break;
// //     }
// //   }

// // // Output the result
// // std::cout << "Decoded Bits: ";
// // for (int bit : decodedBits) {
// //   std::cout << bit << " ";
// // }
// // std::cout << "\n";

// // return 0;
// // }