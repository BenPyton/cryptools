#ifndef _AES_H
#define _AES_H

#include <cassert>
#include <ostream>
#include <string>
#include "matrix.h"


Matrix shiftRows(const Matrix& _m);
Matrix deshiftRows(const Matrix& _m);

int mult(int _a, int _b);

Matrix mixColumns(const Matrix& _m);
Matrix demixColumns(const Matrix& _m);

Matrix addRoundKey(const Matrix& _m, const Matrix& _k);

Matrix subBytes(const Matrix& _m);
Matrix desubBytes(const Matrix& _m);

void scheduleKey(const Matrix& _k, Matrix out[10]);


Matrix str2mat(std::string str);
std::string mat2str(Matrix& mat);


bool EncryptFile(std::string filename, std::string outputFile, Matrix& key);
bool DecryptFile(std::string filename, std::string outputFile, Matrix& key);


void DisplayProgression(int currentStep, int maxStep);
float DisplayLoadingBar(float percentage, int barLength = 10);



#endif // _AES_H