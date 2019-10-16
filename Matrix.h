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

#define pr pair<int, int>
#define mp map <pr, double>
#define vc vector <double>

using namespace std;

mp::iterator it;
mp::iterator iter;


class Matrix
{
public:
	Matrix()
	{
		//cout << "Basic class Matrix" << endl;
	}
	virtual ~Matrix() {}
};

class DenseMatrix : public Matrix
{
private:
	int height;
	int width;
	vc array;

public:
	DenseMatrix(string NameFile)
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
	bool Equals(DenseMatrix b)
	{
		if (height == b.height && width == b.width && array == b.array)
		{
			return true;
		}
		else
			return false;
	}
	pr getSize()
	{
		return{ height, width };
	}
	bool Multiply(DenseMatrix b)
	{
		if (width != b.height)
			return false;
		int heightNew = height;
		int widthNew = width;
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
		height = heightNew;
		width = widthNew;
		array = arrayNew;
		return true;
	}
	bool Multiply(SparseMatrix a)
	{
		DenseMatrix b = a.Sparse_to_Dense();
		//--------------------------------------
		if (width != b.height)
			return false;
		int heightNew = height;
		int widthNew = width;
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
		height = heightNew;
		width = widthNew;
		array = arrayNew;
		return true;
	}
	bool Summ(DenseMatrix b)
	{
		if (height != b.height || width != b.width)
		{
			return false;
		}
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				array[i * width + j] += b.array[i * width + j];
			}
		}
		return true;
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
	}
	SparseMatrix Dense_to_Sparse()
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
};

class SparseMatrix : public Matrix
{
private:
	int height;
	int width;
	mp array;

public:
	SparseMatrix(string NameFile)
	{
		int n = 0, m = 0;
		int i = 0, j = 0;
		mp arr;
		ifstream fin(NameFile);
		string line;
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
				}
				j++;
			}
			i++;
		}
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
	bool Equals(SparseMatrix b)
	{
		if (height == b.height && width == b.width && array == b.array)
		{
			return true;
		}
		else
			return false;	
	}
	bool Multiply(SparseMatrix b)
	{
		if (width != b.height)
			return false;
		int heightNew = height;
		int widthNew = b.width;
		mp arrayNew;
		int n = width;
		for (int i = 0; i < heightNew; i++)
		{
			for (int j = 0; j < widthNew; j++)
			{
				double result = 0;
				for (int z = 0; z < n; z++)
				{
					it = array.find({ i, z });
					iter = b.array.find({ z, j });
					if (it != array.end() && iter != b.array.end())
						result += it->second * iter->second;
				}
				if (result != 0)
				{
					arrayNew.insert({ { i, j }, result });
				}
			}
		}
		array = arrayNew;
		return true;
	}
	bool Multiply(DenseMatrix a)
	{
		SparseMatrix b = a.Dense_to_Sparse();
		//------------------------------------
		if (width != b.height)
			return false;
		int heightNew = height;
		int widthNew = b.width;
		mp arrayNew;
		int n = width;
		for (int i = 0; i < heightNew; i++)
		{
			for (int j = 0; j < widthNew; j++)
			{
				double result = 0;
				for (int z = 0; z < n; z++)
				{
					it = array.find({ i, z });
					iter = b.array.find({ z, j });
					if (it != array.end() && iter != b.array.end())
						result += it->second * iter->second;
				}
				if (result != 0)
				{
					arrayNew.insert({ { i, j }, result });
				}
			}
		}
		array = arrayNew;
		return true;
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
	bool Summ(SparseMatrix b)
	{
		mp arrayNew;
		if (height != b.height || width != b.width)
			return false;
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
};