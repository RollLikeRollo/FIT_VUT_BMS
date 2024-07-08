//***************************************
// Jan Zboril
// xzbori20
// BMS projekt
// 2023
//
// utils.cpp
//***************************************

#include "utils.hpp"

using namespace std;

void printResult(vector<int> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
    }
    cout << endl;
}

void printResult(string &s) { cout << s << endl; }

vector<int> binaryDotProduct(const matrix &X, const vector<int> &Y) {
    int m = X.size();
    int n = Y.size();

    vector<int> A(m, 0);

    for (int i = 0; i < m; ++i) {
        for (int k = 0; k < n; ++k) {
            A[i] += X[i][k] * Y[k];
        }
        // binary modulo
        A[i] %= 2;
    }

    return A;
}

int binaryDotProduct(const vector<int> &X, const vector<int> &Y) {
    int m = X.size();

    int A = 0;

    for (int i = 0; i < m; ++i) {
        A += X[i] * Y[i];
    }

    // binary modulo
    A %= 2;

    return A;
}

matrix binaryDotProduct(const matrix &X, const matrix &Y) {
    int m = X.size();
    int n = Y[0].size();
    int p = Y.size();

    matrix A(m, vector<int>(n, 0));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < p; ++k) {
                A[i][j] += X[i][k] * Y[k][j];
            }
            // binary modulo
            A[i][j] %= 2;
        }
    }

    return A;
}

matrix gaussjordan(matrix &X) {
    matrix A = X;
    int n = A[0].size();
    int m = A.size();

    matrix P = matrix(m, vector<int>(m, 0));
    for (int i = 0; i < m; i++) {
        P[i][i] = 1;
    }

    int pivot;
    int pivot_old = -1;
    for (int j = 0; j < n; ++j) {
        vector<int> filtre_down;
        for (int i = pivot_old + 1; i < m; ++i) {
            filtre_down.push_back(A[i][j]);
        }

        pivot = pivot_old + 1;
        for (int i = pivot_old + 2; i < m; ++i) {
            if (filtre_down[i - pivot_old - 1] > filtre_down[pivot - pivot_old - 1]) {
                pivot = i;
            }
        }

        if (A[pivot][j] != 0) {
            pivot_old += 1;
            if (pivot_old != pivot) {
                swap(A[pivot], A[pivot_old]);
                swap(P[pivot], P[pivot_old]);
            }

            for (int i = 0; i < m; ++i) {
                if (i != pivot_old && A[i][j] != 0) {
                    for (int k = 0; k < m; ++k) {
                        P[i][k] = abs(P[i][k] - P[pivot_old][k]);
                    }

                    for (int k = 0; k < n; ++k) {
                        A[i][k] = abs(A[i][k] - A[pivot_old][k]);
                    }
                }
            }
        }

        if (pivot_old == m - 1) {
            break;
        }
    }

    // select return A or P
    // I need to return P only
    return P;
}

pair<matrix, vector<int>> gaussElimination(const matrix &tG, const vector<int> &x) {
    int n = tG.size();
    int k = tG[0].size();

    // copies of the arguments so they are not modified
    vector<vector<int>> rtG(tG);
    vector<int> rx(x);

    for (int i = 0; i < k; ++i) {
        // Find a non-zero pivot in the column
        int pivotRow = -1;
        for (int j = i; j < n; ++j) {
            if (rtG[j][i] != 0) {
                pivotRow = j;
                break;
            }
        }

        if (pivotRow == -1) {
            // continue to next column if no pivot found
            continue;
        }

        // Swap rows to make the pivot the current element
        swap(rtG[i], rtG[pivotRow]);
        swap(rx[i], rx[pivotRow]);

        // Make the diagonal element 1
        int pivot = rtG[i][i];
        for (int j = 0; j < k; ++j) {
            rtG[i][j] = (rtG[i][j] * pivot) % 2;
        }
        rx[i] = (rx[i] * pivot) % 2;

        // Eliminate other elements below the diagonal in the column
        for (int row = 0; row < n; ++row) {
            if (row != i) {
                int factor = rtG[row][i];
                for (int j = 0; j < k; ++j) {
                    rtG[row][j] = (rtG[row][j] + factor * rtG[i][j]) % 2;
                }
                rx[row] = (rx[row] + factor * rx[i]) % 2;
            }
        }
    }

    // return the row reduced matrix and the solution
    return make_pair(rtG, rx);
}

pair<bool, string> checkInput(string input, char mode) {
    // only mode 'e' and 'd' are valid
    if (mode != 'e' && mode != 'd') {
        return make_pair(false, "");
    }
    string output = "";

    // encode -> check if input is printable ASCII, filter out non-printable
    // characters
    if (mode == 'e') {
        for (size_t i = 0; i < input.length(); i++) {
            if (input[i] < 127 && input[i] > 32) {
                output += input[i];
            }
        }
    }
    // decode -> check if input is binary, filter out non 1/0 characters
    if (mode == 'd') {
        for (size_t i = 0; i < input.length(); i++) {
            if (input[i] == '0' || input[i] == '1') {
                output += input[i];
            }
        }
    }
    // return success and filtered input
    return make_pair(true, output);
}

void printVector(vector<int> &v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i != v.size() - 1) {
            cout << " ";
        }
    }
    cout << "]" << endl;
}

void printMatrix(matrix &m) {
    cout << "[" << endl;
    for (size_t i = 0; i < m.size(); i++) {
        cout << "[";
        for (size_t j = 0; j < m[i].size(); j++) {
            cout << m[i][j];
            if (j != m[i].size() - 1) {
                cout << " ";
            }
        }
        cout << "]" << endl;
    }
    cout << "\b]" << endl;
}

matrix transposeMatrix(matrix m) {
    int row = m.size();
    int column = m[0].size();
    matrix t(column, vector<int>(row, 0));
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j) {
            t[j][i] = m[i][j];
        }
    return t;
}

matrix permuteMatrixRows(matrix m) {
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(m.begin(), m.end(), g);
    return m;
}

string stringToBinary(string input) {
    string output = "";
    size_t i = 0;
    while (i < input.length()) {
        bitset<8> b(input[i]);
        output += b.to_string();
        i++;
    }
    return output;
}

string StringFromBinary(string input) {
    string output = "";
    size_t i = 0;
    while (i < input.length()) {
        bitset<8> b(input.substr(i, 8));
        output += char(b.to_ulong());
        i += 8;
    }
    return output;
}

string readStdIn() {
    string s = "";
    string line;
    while (std::getline(std::cin, line)) {
        s += line;
    }
    return s;
}

string binaryVectorToAsciiString(vector<int> v) {
    vector<char> v2;
    for (size_t i = 0; i < v.size(); i++) {
        v2.push_back(v[i] + '0');
    }
    string s(v2.begin(), v2.end());
    return StringFromBinary(s);
}

void saveMatrix(matrix m, string filename) {
    ofstream myfile;
    myfile.open(filename);
    for (size_t i = 0; i < m.size(); i++) {
        for (size_t j = 0; j < m[i].size(); j++) {
            myfile << m[i][j];
            if (j != m[i].size() - 1) {
                myfile << " ";
            }
        }
        myfile << endl;
    }
    myfile.close();
}

matrix loadMatrix(string filename) {
    ifstream myfile(filename);
    string line;
    matrix m;
    while (getline(myfile, line)) {
        vector<int> row;
        stringstream ss(line);
        int i;
        while (ss >> i) {
            row.push_back(i);
            // ignore next space and go to next char
            if (ss.peek() == ' ') {
                ss.ignore();
            }
        }
        m.push_back(row);
    }
    return m;
}