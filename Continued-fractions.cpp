﻿#include <iostream>
#include <Windows.h>
#include <fstream>
#include <thread>
#include <stdio.h>
#include <cstdlib>

using namespace std;

int CheckInput(const char* msg)
{
	string tmp;
	int value;
	while (true)
	{
		cout << msg;
		cin >> tmp;
		try
		{
			value = stoi(tmp);
			cin.ignore((numeric_limits<unsigned char>::max)(), '\n');
			return value;
		}
		catch (invalid_argument)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
		}
		catch (out_of_range)
		{
			cin.ignore((numeric_limits<unsigned char>::max)(), '\n');
		}
	}
}

void ConvertFraction(int numerator, int denominator, int j)
{
	cout << "Continued Fraction: (";
	cout << numerator / denominator;
	int tmp = denominator;
	denominator = (numerator % denominator);
	numerator = tmp;
	if (denominator != 0)
		cout << ";";
	while (numerator > denominator && denominator != 0)
	{
		cout << numerator / denominator;
		if (denominator == 1)
			break;
		int tmp = denominator;
		denominator = (numerator % denominator);
		numerator = tmp;
		if (denominator == 0)
			break;
		cout << ",";
	}
	cout << ")\n";
}
void ConvertContinuedFractions(unsigned short array1[], int j)
{
	int numerator = 1; int denominator = array1[j - 1]; int a = 0; cout << "\n";
	int x = numerator;
	numerator = array1[j - 2] * denominator; numerator += x;
	int tmp = numerator;
	numerator = denominator;
	denominator = tmp;
	for (int i = j - 3; i >= 0; i--)
	{
		a = array1[i];
		int x = numerator;
		numerator = a * denominator; numerator += x;
		int tmp = numerator;
		numerator = denominator;
		denominator = tmp;
	}
	cout << "\n" << denominator << "/" << numerator;
}

int main()
{
	int num, denom;
	bool tmp;
	tmp = CheckInput("Enter 0 to convert fractions\nEnter 1 to convert continued fractions\n");
	if (tmp)
	{
		int j = 0; cout << "Enter through space odds of continued fraction and enter 0 to end input\n";
		unsigned short a = 0;
		ofstream out;
		out.open("Odds.txt");
		if (out.is_open())
		{
			while (true)
			{
				cin >> a; if (a == 0) break;
				out << a << " ";
				j++;
			}
		}
		out.close();
		unsigned short* array = new unsigned short[j];
		ifstream in("Odds.txt");
		if (in.is_open())
		{
			for (int i = 0; i < j; i++)
				in >> array[i];
		}
		in.close();
		remove("Odds.txt");
		ConvertContinuedFractions(array, j);
	}
	else
	{
		num = CheckInput("Enter numerator value\n");
		denom = CheckInput("Enter denominator value\n");
		int j = 1;
		ConvertFraction(num, denom, j);
	}
	return 0;
}