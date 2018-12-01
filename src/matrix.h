#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>
typedef unsigned char byte;

class Matrix
{
private:
	byte m_matrix[4][4];
public:
	Matrix();

	Matrix(
		int _00, int _10, int _20, int _30,
		int _01, int _11, int _21, int _31, 
		int _02, int _12, int _22, int _32, 
		int _03, int _13, int _23, int _33);

	Matrix(const Matrix& _m);

	byte& operator()(unsigned int _i, unsigned int _j) ;

	byte operator()(unsigned int _i, unsigned int _j) const;

	Matrix& operator=(const Matrix& _m);
	
	bool operator==(const Matrix& _m);

	friend std::ostream& operator<<(std::ostream& _o, const Matrix& _m);
};

#endif // _MATRIX_H