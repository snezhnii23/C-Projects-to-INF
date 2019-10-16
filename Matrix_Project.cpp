// Matrix_Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matrix.h"
#include <string>


int main()
{
	int n = 3;
	string Name1 = "1_";
	string Name2 = "2_";
	for (int i = 0; i < n; i++)
	{
		string NameFile1 = Name1 + to_string(i) + ".txt";
		string NameFile2 = Name2 + to_string(i) + ".txt";
		string NameFile3 = "test" + to_string(i) + ".txt";
		SparseMatrix a(NameFile1);
		SparseMatrix b(NameFile2);
		DenseMatrix c(NameFile3);
		if (!a.Multiply(b))
		{
			cout << "Error. Check your data" << endl;
		}
		else
		{
			if (a.Equals(c))
			{
				cout << "Yes. That's right answer" << endl;
			}
			else
				cout << "No. You have a mistake" << endl;
			a.WriteFile();
			int q = 0;
		}
	}
	return 0;
}

