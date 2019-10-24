#pragma once

#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <iomanip>
#include <string>
#include <map>
#include <sstream>
#include <ctime>

#define pr pair<int, int>
#define mp map <pr, double>
#define vc vector <double>
#define st set <pr>

using namespace std;

mp::iterator it;
mp::iterator iter;
mp::iterator it_res;
st::iterator it_set;

class Matrix
{
public:
	Matrix()
	{
		//cout << "Basic class Matrix" << endl;
	}
	virtual ~Matrix() {}
};

class SparseMatrix;

class DenseMatrix : public Matrix
{
private:
	int height;
	int width;
	vc array;

public:
	DenseMatrix(string& NameFile)
	{
		int n = 0, m = 0;
		ifstream fin(NameFile);
		string line;
		vector <double> arr;
		while (getline(fin, line))
		{
			n++;
			double Number;
			istringstream iss(line);
			while (iss >> Number)
			{
				arr.push_back(Number);
			}
		}
		fin.close();
		m = arr.size() / n;
		height = n;
		width = m;
		array = arr;
	}
	DenseMatrix(int heightNew, int widthNew, vc arrayNew)
	{
		height = heightNew;
		width = widthNew;
		array = arrayNew;
	}
	~DenseMatrix()
	{
		//cout << "День добрый, Я Деструктор DenseMatrix, я тут мусор пособираю, я быстренько)" << endl;
		array.clear();
	}
	bool Equals(DenseMatrix &b)
	{
		if (height == b.height && width == b.width)
		{
			if (array == b.array)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	bool Equals(SparseMatrix &a);
	pr getSize()
	{
		return { height, width };
	}
	DenseMatrix Multiply(DenseMatrix &b)
	{
		vc a;
		if (width != b.height)
			return DenseMatrix(-1, -1, a);
		int heightNew = height;
		int widthNew = b.width;
		vector <double> arrayNew(heightNew * widthNew);
		for (int i = 0; i < heightNew; i++)
		{
			for (int j = 0; j < widthNew; j++)
			{
				for (int z = 0; z < width; z++)
				{
					arrayNew[i * widthNew + j] += array[i * width + z] * b.array[z * b.width + j];
				}
			}
		}
		return DenseMatrix(heightNew, widthNew, arrayNew);
	}
	DenseMatrix DenseMatrix::Multiply(SparseMatrix &a);
	DenseMatrix Summ(DenseMatrix &b)
	{
		vc a;
		vc arrayNew(height * width);
		if (height != b.height || width != b.width)
		{
			return DenseMatrix(-1, -1, a);
		}
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				arrayNew[i * width + j] = array[i * width + j] + b.array[i * width + j];
			}
		}
		return DenseMatrix(height, width, arrayNew);
	}
	string to_String()
	{
		long long p = 131;
		long long mod = 157543;
		long long a = 0;
		for (int i = 0; i < height * width; i++)
		{
			a = (a * p + int(array[i]));
			a %= mod;
		}
		return to_string(a);
	}
	void WriteFile()
	{
		ofstream fout("output.txt");
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				fout << fixed << setprecision(3) << array[i * width + j] << " ";
			}
			fout << endl; 
		}
		fout.close();
	}
	SparseMatrix Dense_to_Sparse();
};

class SparseMatrix : public Matrix
{
private:
	int height;
	int width;
	mp array;

public:
	SparseMatrix(string& NameFile)
	{
		int n = 0, m = 0;
		int i = 0, j = 0;
		mp arr;
		ifstream fin(NameFile);
		string line;
		st set_string, set_column;
		while (getline(fin, line))
		{
			j = 0;
			n++;
			double Number;
			istringstream iss(line);
			while (iss >> Number)
			{
				m++;
				if (Number != 0)
				{
					arr.insert({ { i, j }, Number });
					set_string.insert({ i, i });
					set_column.insert({ j, j });
				}
				j++;
			}
			i++;
		}
		fin.close();
		m /= n;
		height = n;
		width = m;
		array = arr;
	}
	SparseMatrix(int heightNew, int widthNew, mp arrayNew)
	{
		height = heightNew;
		width = widthNew;
		array = arrayNew;
	}
	~SparseMatrix()
	{
		//cout << "День добрый, Я Деструктор SparseMatrix, я тут мусор пособираю, я быстренько)" << endl;
		array.clear();
	}
	bool Equals(SparseMatrix &b)
	{
		if (height == b.height && width == b.width)
		{
			if (array == b.array)
				return true;
			else
				return false;
		}
		else
			return false;	
	}
	bool Equals(DenseMatrix &a)
	{
		SparseMatrix b = a.Dense_to_Sparse();
		//------------------------------------
		if (height == b.height && width == b.width)
		{
			if (array == b.array)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	SparseMatrix Multiply(SparseMatrix &b)
	{
		mp q;
		if (width != b.height)
			return SparseMatrix(-1, -1, q);
		int heightNew = height;
		int widthNew = b.width;
		mp arrayNew;
		int n = width;
		for (it = array.begin(); it != array.end(); ++it)
		{
			for (iter = b.array.begin(); iter != b.array.end(); ++iter)
			{
				if (it->first.second == iter->first.first)
				{
					double res = 0;
					it_res = arrayNew.find({ it->first.first, iter->first.second });
					if (it_res != arrayNew.end())
					{
						it_res->second += it->second * iter->second;
						if (it_res->second == 0)
						{
							arrayNew.erase(it_res);

						}
					}
					else
					{
						res = it->second * iter->second;
						if (res)
							arrayNew.insert({ { it->first.first, iter->first.second }, res });
					}
				}
			}
		}
		return SparseMatrix(heightNew, widthNew, arrayNew);
	}
	SparseMatrix Multiply(DenseMatrix &a)
	{
		//clock_t t0 = clock();
		SparseMatrix b = a.Dense_to_Sparse();
		//cout << fixed << setprecision(6) << double(clock() - t0) / CLOCKS_PER_SEC << endl;
		//------------------------------------
		mp q;
		if (width != b.height)
			return SparseMatrix(-1, -1, q);
		int heightNew = height;
		int widthNew = b.width;
		mp arrayNew;
		int n = width;
		for (it = array.begin(); it != array.end(); ++it)
		{
			for (iter = b.array.begin(); iter != b.array.end(); ++iter)
			{
				if (it->first.second == iter->first.first)
				{
					double res = 0;
					it_res = arrayNew.find({ it->first.first, iter->first.second });
					if (it_res != arrayNew.end())
					{
						it_res->second += it->second * iter->second;
						if (it_res->second == 0)
						{
							arrayNew.erase(it_res);

						}
					}
					else
					{
						res = it->second * iter->second;
						if (res)
							arrayNew.insert({ { it->first.first, iter->first.second }, res });
					}
				}
			}
		}
		return SparseMatrix(heightNew, widthNew, arrayNew);
	}
	DenseMatrix Sparse_to_Dense()
	{
		vc arrayNew(height * width);
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				it = array.find({ i, j });
				if (it != array.end())
				{
					arrayNew[i * width + j] = it->second;
				}
			}
		}
		return DenseMatrix(height, width, arrayNew);
	}
	SparseMatrix Summ(SparseMatrix &b)
	{
		mp arrayNew;
		mp a;
		if (height != b.height || width != b.width)
			return SparseMatrix(-1, -1, a);
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				it = array.find({ i, j });
				iter = b.array.find({ i, j });
				if (it != array.end())
				{
					if (iter != b.array.end())
						arrayNew.insert({ { i, j }, it->second + iter->second });
					else
						arrayNew.insert({ { i, j }, it->second });
				}
				else
				{
					if (iter != b.array.end())
						arrayNew.insert({ { i, j }, iter->second });
				}
			}
		}
		array = arrayNew;
	}
	void WriteFile()
	{
		ofstream fout("output.txt");
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				double element = 0;
				it = array.find({ i, j });
				if (it != array.end())
					element = it->second;
				fout << fixed << setprecision(3) << element << " ";
			}
			fout << endl;
		}
	}
	pr getSize()
	{
		return	{ height, width };
	}
};

DenseMatrix DenseMatrix::Multiply(SparseMatrix &a)
{
	DenseMatrix b = a.Sparse_to_Dense();
	//--------------------------------------
	vc c;
	if (width != b.height)
		return DenseMatrix(-1, -1, c);
	int heightNew = height;
	int widthNew = b.width;
	vector <double> arrayNew(heightNew * widthNew);
	for (int i = 0; i < heightNew; i++)
	{
		for (int j = 0; j < widthNew; j++)
		{
			for (int z = 0; z < width; z++)
			{
				arrayNew[i * widthNew + j] += array[i * width + z] * b.array[z * b.width + j];
			}
		}
	}
	return DenseMatrix(heightNew, widthNew, arrayNew);
}
SparseMatrix DenseMatrix::Dense_to_Sparse()
{
	mp arrayNew;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (array[i * width + j] != 0)
			{
				arrayNew.insert({ { i, j }, array[i * width + j] });
			}
		}
	}
	return SparseMatrix(height, width, arrayNew);
}
bool DenseMatrix::Equals(SparseMatrix &a)
{
	DenseMatrix b = a.Sparse_to_Dense();
	//-----------------------------------
	if (height == b.height && width == b.width)
	{
		if (array == b.array)
			return true;
		else
			return false;
	}
	else
		return false;
}

DenseMatrix operator * (DenseMatrix& a, DenseMatrix& b)
{
	return a.Multiply(b);
}
DenseMatrix operator * (DenseMatrix& a, SparseMatrix& b)
{
	return a.Multiply(b);
}
SparseMatrix operator * (SparseMatrix& a, DenseMatrix& b)
{
	return a.Multiply(b);
}
SparseMatrix operator * (SparseMatrix& a, SparseMatrix& b)
{
	return a.Multiply(b);
}

bool operator == (DenseMatrix& a, DenseMatrix& b)
{
	return a.Equals(b);
}
bool operator == (DenseMatrix& a, SparseMatrix& b)
{
	return a.Equals(b);
}
bool operator == (SparseMatrix& a, DenseMatrix& b)
{
	return a.Equals(b);
}
bool operator == (SparseMatrix& a, SparseMatrix& b)
{
	return a.Equals(b);
}

