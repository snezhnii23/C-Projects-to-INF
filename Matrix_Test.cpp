// Matrix_Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MatrixOld.h"
#include <string>
#include <ctime>


int main()
{
	int n = 5;
	string Name1 = "1_";
	string Name2 = "2_";
	for (int i = 0; i < n; i++)
	{
		string NameFile1 = Name1 + to_string(i) + ".txt";
		string NameFile2 = Name2 + to_string(i) + ".txt";
		string NameFile3 = "test" + to_string(i) + ".txt";
		clock_t t0 = clock();
		SparseMatrix a(NameFile1);
		DenseMatrix b(NameFile2);
		SparseMatrix c(NameFile3);
		clock_t t1 = clock();
		SparseMatrix d = a * b;
		cout << fixed << setprecision(5) << "time: " << double(t1 - t0) / CLOCKS_PER_SEC << endl;
		if (d.getSize().first == -1)
		{
			cout << "Error. Check your data" << endl;
		}
		else
		{
			if (d == c)
			{
				cout << "Yes. That's right answer" << endl;
			}
			else
				cout << "No. You have a mistake" << endl;
		}
		//a.WriteFile();
		t1 = clock();
		cout << fixed << setprecision(5) << "time: " << double(t1 - t0) / CLOCKS_PER_SEC << endl;
		int q = 0;
	}
	return 0;
}

