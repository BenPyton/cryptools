#include "matrix.h"
#include <cassert>

Matrix::Matrix()
{ 
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			m_matrix[i][j] = 0;
}

Matrix::Matrix(
	int _00, int _10, int _20, int _30,
	int _01, int _11, int _21, int _31, 
	int _02, int _12, int _22, int _32, 
	int _03, int _13, int _23, int _33)
{
	m_matrix[0][0] = _00; m_matrix[1][0] = _10; m_matrix[2][0] = _20; m_matrix[3][0] = _30;
	m_matrix[0][1] = _01; m_matrix[1][1] = _11; m_matrix[2][1] = _21; m_matrix[3][1] = _31;
	m_matrix[0][2] = _02; m_matrix[1][2] = _12; m_matrix[2][2] = _22; m_matrix[3][2] = _32;
	m_matrix[0][3] = _03; m_matrix[1][3] = _13; m_matrix[2][3] = _23; m_matrix[3][3] = _33;
}

Matrix::Matrix(const Matrix& _m)
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			m_matrix[i][j] = _m.m_matrix[i][j];
}

byte& Matrix::operator()(unsigned int _i, unsigned int _j) 
{
	assert(_i < 4 && _j < 4);
	return m_matrix[_i][_j];
}

byte Matrix::operator()(unsigned int _i, unsigned int _j) const
{
	assert(_i < 4 && _j < 4);
	return m_matrix[_i][_j];
}

Matrix& Matrix::operator=(const Matrix& _m)
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			m_matrix[i][j] = _m.m_matrix[i][j];
	return *this;
}

bool Matrix::operator==(const Matrix& _m)
{
	bool equals = true;
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
		{
			if(_m(i,j) != (*this)(i,j))
				equals = false;
		}
	return equals;
}

std::ostream& operator<<(std::ostream& _o, const Matrix& _m)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
			_o << std::hex << (int)_m.m_matrix[i][j] << " ";
		_o << std::endl;
	}
	return _o;
}