#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to generate 5x5 key matrix
vector<vector<char>> generateMatrix(string key) {
    vector<vector<char>> matrix(5, vector<char>(5));
    string used = "";
    key.erase(remove(key.begin(), key.end(), ' '), key.end());
    for (char& c : key) {
        c = tolower(c);
        if (c == 'j') c = 'i';
    }

    int r = 0, c = 0;
    for (char ch : key) {
        if (used.find(ch) == string::npos && isalpha(ch)) {
            matrix[r][c] = ch;
            used += ch;
            if (++c == 5) {
                c = 0;
                r++;
            }
        }
    }

    for (char ch = 'a'; ch <= 'z'; ch++) {
        if (ch == 'j') continue;
        if (used.find(ch) == string::npos) {
            matrix[r][c] = ch;
            used += ch;
            if (++c == 5) {
                c = 0;
                r++;
            }
        }
    }

    return matrix;
}

// Helper to find position in matrix
void findPos(vector<vector<char>>& matrix, char ch, int& row, int& col) {
    if (ch == 'j') ch = 'i';
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (matrix[r][c] == ch) {
                row = r;
                col = c;
                return;
            }
        }
    }
}

// Decrypt pair of characters
string decryptPair(vector<vector<char>>& matrix, char a, char b) {
    int r1, c1, r2, c2;
    findPos(matrix, a, r1, c1);
    findPos(matrix, b, r2, c2);

    if (r1 == r2) {
        return string(1, matrix[r1][(c1 + 4) % 5]) + matrix[r2][(c2 + 4) % 5];
    }
    else if (c1 == c2) {
        return string(1, matrix[(r1 + 4) % 5][c1]) + matrix[(r2 + 4) % 5][c2];
    }
    else {
        return string(1, matrix[r1][c2]) + matrix[r2][c1];
    }
}

// Full decryption
string decrypt(string ciphertext, string key) {
    vector<vector<char>> matrix = generateMatrix(key);
    string result = "";

    ciphertext.erase(remove(ciphertext.begin(), ciphertext.end(), ' '), ciphertext.end());
    for (char& c : ciphertext) {
        c = tolower(c);
        if (c == 'j') c = 'i';
    }

    for (size_t i = 0; i < ciphertext.size(); i += 2) {
        result += decryptPair(matrix, ciphertext[i], ciphertext[i + 1]);
    }

    return result;
}

int main() {
    string key = "monarchy";
    string ciphertext = "gatlmzclrqtx";

    string plaintext = decrypt(ciphertext, key);
    cout << "Decrypted message: " << plaintext << endl;

    return 0;
}
