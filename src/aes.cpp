#include "aes.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <time.h>

byte sbox[] = {	 
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16};

byte sbox_inv[] = {	
	0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D};

Matrix mix(
	2, 3, 1, 1,
	1, 2, 3, 1,
	1, 1, 2, 3,
	3, 1, 1, 2);


Matrix demix(
	14, 11, 13, 9,
	9, 14, 11, 13,
	13, 9, 14, 11,
	11, 13, 9, 14);

Matrix shiftRows(const Matrix& _m)
{
	Matrix out;
	for(int i = 0; i < 4; i++)
	{
		out(i, 0) = _m(i, (i+0)%4);
		out(i, 1) = _m(i, (i+1)%4);
		out(i, 2) = _m(i, (i+2)%4);
		out(i, 3) = _m(i, (i+3)%4);
	}
	return out;
}

Matrix deshiftRows(const Matrix& _m)
{
	Matrix out;
	for(int i = 0; i < 4; i++)
	{
		out(i, 0) = _m(i, (4-i+0)%4);
		out(i, 1) = _m(i, (4-i+1)%4);
		out(i, 2) = _m(i, (4-i+2)%4);
		out(i, 3) = _m(i, (4-i+3)%4);
	}
	return out;
}

byte mult(byte _a, byte _b)
{
	byte p = 0;
	for(int k = 0; k < 8; k++)
	{
		if((_b & 1) == 1)
		{
			p ^= _a;
		}
		byte n = _a & 0x80;
		_a <<= 1;
		_a &= 0xff;
		if(n == 0x80)
		{
			_a ^= 0x1b;
		}
		_b >>= 1;
	}
	return p;
}

Matrix mixColumns(const Matrix& _m)
{
	Matrix out;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			out(i,j) = mult(_m(0,j), mix(i,0)) 
					 ^ mult(_m(1,j), mix(i,1)) 
					 ^ mult(_m(2,j), mix(i,2)) 
					 ^ mult(_m(3,j), mix(i,3));
		}
	}
	return out;
}
Matrix demixColumns(const Matrix& _m)
{
	Matrix out; 

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			out(i,j) = mult(_m(0,j), demix(i,0)) 
					 ^ mult(_m(1,j), demix(i,1)) 
					 ^ mult(_m(2,j), demix(i,2)) 
					 ^ mult(_m(3,j), demix(i,3));
		}
	}
	return out;
}

Matrix addRoundKey(const Matrix& _m, const Matrix& _k)
{
	Matrix out;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			out(i,j) = _m(i,j) ^ _k(i,j);
		}
	}
	return out;
}

Matrix subBytes(const Matrix& _m)
{
	Matrix out;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			out(i,j) = sbox[_m(i,j)];
		}
	}
	return out;
}
Matrix desubBytes(const Matrix& _m)
{
	Matrix out;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			out(i,j) = sbox_inv[_m(i,j)];
		}
	}
	return out;
}

// Return a list of key
void scheduleKey(const Matrix& _k, Matrix out[10])
{
	Matrix key(_k);
	byte rcon[4][10] = 
	{{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}	};

	for(int m = 0; m < 10; m++)
	{
		for(int i = 0; i < 4; i++)
		{
			out[m](i,0) = key(i,0) ^ sbox[key((i+1) % 4, 3)] ^ rcon[i][m];
			for(int j = 1; j < 4; j++)
			{
				out[m](i,j) = key(i,j) ^ out[m](i,j-1);
			}
		}
		key = out[m];
	}
}

Matrix str2mat(std::string str)
{
	Matrix mat;

	// fill string with spaces if size < 16
	while(str.size() < 16)
	{
		str += " ";
	}

	if(str.size() > 16)
	{
		str = str.substr(0, 16);
	}

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			mat(i,j) = (byte)str[i*4 + j];
		}
	}

	return mat;
}

std::string mat2str(Matrix& mat)
{
	std::string str;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			str += (char)mat(i,j);
		}
	}

	return str;
}


bool EncryptFile(std::string filename, std::string outputFile, Matrix& key)
{
	bool success = false;

	Matrix keyList[10];
	scheduleKey(key, keyList);
	
	std::ifstream inFile(filename, std::ios::in | std::ios::binary);
	if(inFile.is_open())
	{
		std::ofstream outFile(outputFile, std::ios::out | std::ios::binary);
	
		char c;
		int i = 0;
		int padding = 0;
		
		//get inFile length;
		inFile.seekg(0, std::ios_base::end);
		int length = inFile.tellg();
		inFile.seekg(0, inFile.beg);
		int currentStep = 0;

		DisplayProgression(currentStep, length);

		while(inFile.good())
		{
			// reset
			i = 0;
			Matrix bytes;

			// get maximum 16 char from inFile
			while(i < 16 && inFile.get(c).good())
			{
				bytes(i % 4, i / 4) = (byte)c;
				i++;
			}
			// Block is not complete, we count the padding to add
			if(i != 16)
			{
				padding = 16 - i;
			}

			Matrix mat_encrypt = addRoundKey(bytes, key);
			for(int k = 0; k < 9; k++)
			{
				mat_encrypt = subBytes(mat_encrypt);
				mat_encrypt = shiftRows(mat_encrypt);
				mat_encrypt = mixColumns(mat_encrypt);
				mat_encrypt = addRoundKey(mat_encrypt, keyList[k]);
			}
			mat_encrypt = subBytes(mat_encrypt);
			mat_encrypt = shiftRows(mat_encrypt);
			mat_encrypt = addRoundKey(mat_encrypt, keyList[9]);

			// write bytes in outFile
			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					outFile.put((char)mat_encrypt(j,i));
				}
			}
			
			currentStep += 16;
			if(currentStep % 131072 == 0)
			{
				DisplayProgression(currentStep, length);
			}
		}

		DisplayProgression(currentStep, length);
		// add padding number at the end
		outFile.put((char)padding);
		std::cout << std::endl;
		success = true;
	}

	return success;
}





bool DecryptFile(std::string filename, std::string outputFile, Matrix& key)
{
	bool success = false;

	Matrix keyList[10];
	scheduleKey(key, keyList);
	
	std::ifstream inFile(filename, std::ios::in | std::ios::binary);
	if(inFile.is_open())
	{
		std::ofstream outFile(outputFile, std::ios::out | std::ios::binary);
	
		char c;
		int i = 0;
		int padding = 0;
		
		//get inFile length;
		inFile.seekg(0, inFile.end);
		int length = inFile.tellg();
		inFile.seekg(0, inFile.beg);
		int currentStep = 0;

		Matrix mat_decrypt;
		bool first = true;

		DisplayProgression(currentStep, length);

		while(inFile.good())
		{
			// reset
			i = 0;
			Matrix bytes;

			// get maximum 16 char from inFile
			while(i < 16 && inFile.get(c).good())
			{
				bytes(i % 4, i / 4) = (byte)c;
				i++;
			}

			// if in decryption mode, we get the padding
			if(i != 16)
			{
				padding = (int) bytes(0,0);
				// write bytes in outFile
				for(int i = 0; i < 16 - padding; i++)
				{
					outFile.put((char)mat_decrypt(i%4, i/4));
				}
			}
			else
			{
				// write the previous decrypted matrix
				if(!first)
				{
					// write bytes in outFile
					for(int i = 0; i < 16; i++)
					{
						outFile.put((char)mat_decrypt(i%4, i/4));
					}
				}

				mat_decrypt = addRoundKey(bytes, keyList[9]);
				for(int k = 0; k < 9; k++)
				{
					mat_decrypt = deshiftRows(mat_decrypt);
					mat_decrypt = desubBytes(mat_decrypt);
					mat_decrypt = addRoundKey(mat_decrypt, keyList[8-k]);
					mat_decrypt = demixColumns(mat_decrypt);
				}
				mat_decrypt = deshiftRows(mat_decrypt);
				mat_decrypt = desubBytes(mat_decrypt);
				mat_decrypt = addRoundKey(mat_decrypt, key);

			}
			
			currentStep += 16;
			if(currentStep % 131072 == 0)
			{
				DisplayProgression(currentStep, length);
			}

			first = false;
		}

		DisplayProgression(currentStep, length);
		std::cout << std::endl;
		success = true;
	}

	return success;
}


void DisplayProgression(int currentStep, int maxStep)
{
	if(currentStep >= maxStep) currentStep = maxStep;
	float time = DisplayLoadingBar(currentStep / (float)maxStep, 20);
	std::cout << std::fixed << std::setprecision(1) << currentStep/1000000.0f << "MB / " << maxStep/1000000.0f << "MB "
			  << std::setprecision(3) << currentStep/(1000000.0f * time) << "MB/s   ";
}


float DisplayLoadingBar(float percentage, int barLength)
{
	static clock_t startTime = clock();
	static int index = 0;
	char hourglass[4] = { '|', '/', '-', '\\' };

	int percent = (int)(100 * percentage); 
	if (percent >= 100)
	{
		percent = 100;
	}

	//std::cout << "\r" << hourglass[index];
	std::cout << "\r[" << std::string((int)((float)percent*barLength / 100.0), '/') << std::string(barLength - (int)((float)percent*barLength / 100.0), ' ') << "]";
	std::cout << std::setw(3) << percent << "% ";
	std::cout << hourglass[index] << " ";
	float time = (float)(clock() - startTime) / CLOCKS_PER_SEC;
	std::cout << time << "s ";
	index = (index + 1) % 4;
	return time;
}
