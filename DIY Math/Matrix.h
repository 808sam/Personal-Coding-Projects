#ifndef MATRIX_H
#define MATRIX_H

template<typename T>
class Matrix
{
private:
	T** matrix;
	const size_t H;
	const size_t W;
public:
	Matrix(size_t rows, size_t collumns) : H(rows), W(collumns)
	{
		matrix = new T*[H];
		for (size_t i = 0; i < H; ++i)
		{
			matrix[H] = new T[W];
		}
	}
	~Matrix()
	{
		for (size_t i = 0; i < H; ++i)
		{
			delete[] matrix[i];
		}
		delete[] matrix;

	}
	const size_t height() { return H; }
	const size_t width() { return W;  }
	//returns a chosen row of the matrix
	T* operator[](size_t index) { return matrix[index]; }
	//used to scale a matrix
	Matrix& operator*=(const T& value)
	{
		for (size_t i = 0; i < H; ++i)
		{
			for (size_t j = 0; j < W; ++j)
			{
				matrix[i][j] *= value;
			}
		}
		return this;
	}
	//fills the matrix with a given value
	Matrix& fill(T value)
	{
		for (size_t i = 0; i < H; ++i)
		{
			for (size_t j = 0; j < W; ++j)
			{
				matrix[i][j] = value;
			}
		}
		return this;
	}
};




#endif
