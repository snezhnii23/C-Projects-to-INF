// Matrix_Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matrix.h"
#include <string>


int main()
{
	setlocale(LC_ALL, "Russian");
	int n = 1;
	string Name1 = "1_";
	string Name2 = "2_";
	for (int i = 0; i < n; i++)
	{
		/*string NameFile1 = Name1 + to_string(i) + ".txt";
		string NameFile2 = Name2 + to_string(i) + ".txt";
		string NameFile3 = "test" + to_string(i) + ".txt";
		*/
		string NameFile1 = "m1.txt"; // Name1 + to_string(i) + ".txt";
		string NameFile2 = "m2.txt"; // Name2 + to_string(i) + ".txt";
		string NameFile3 = "result.txt"; // "test" + to_string(i) + ".txt";
		
		clock_t t0 = clock();
		SparseMatrix a(NameFile1);
		clock_t t1 = clock();
		cout << fixed << setprecision(5) << "time: " << double(t1 - t0) / CLOCKS_PER_SEC << endl;
		t0 = clock();
		SparseMatrix b(NameFile2);
		t1 = clock();
		cout << fixed << setprecision(5) << "time: " << double(t1 - t0) / CLOCKS_PER_SEC << endl;
		t0 = clock();
		SparseMatrix c(NameFile3);
		t1 = clock();
		cout << fixed << setprecision(5) << "time: " << double(t1 - t0) / CLOCKS_PER_SEC << endl;
		SparseMatrix d = a * b;
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

