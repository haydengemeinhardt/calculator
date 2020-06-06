/*
		Author: Hayden Gemeinhardt
		main.cpp
		Since: 6/6/2020
*/
#include "Stack.h"
#include <iostream>
#include <string>
#include <cctype>
#include <math.h>

using namespace std;

string stringToDigit(string equation, int* i)
{
	string x = "", y = "";
	int n = 0, p = 0;
	if (equation[*i] == '~')
	{
		(*i)++;
		n = 1;
	}
	y = equation[*i];
	while (isdigit(equation[*i+1]))
	{
		(*i)++;
		x = equation[*i];
		y = to_string(stoi(y) * 10 + stoi(x));
	}
	if (equation[*i+1] == '.')
	{
		(*i)++;
		while (isdigit(equation[*i + 1]))
		{
			p++;
			x = equation[*i + 1];
			y = to_string(stold(y) + (stold(x) / (pow(10, p))));
			(*i)++;
		}
	}
	if (n == 1)
	{
		y = to_string(0 - stold(y));
	}
	return y;
}

long double exponent(long double b, long double e)
{
	if (e < 0)
		return 0;
	if (e == 0)
		return 1;
	if (e == 1)
		return b;
	if (fmod(e,2) == 1)
		return b * exponent(b, e - 1);
	return exponent(b * b, e / 2);
}

bool isOperator(string s)
{
	return (s == "+" || s == "-" || s == "*" || s == "/" || s == "%" || s == "^");
}

int precedence(string oper)
{
	if (oper[0] == '+' || oper[0] == '-')
		return 2;
	if (oper[0] == '*' || oper[0] == '/' || oper[0] == '%')
		return 3;
	if (oper[0] == '^')
		return 4;
	cout << "Error" << endl;
	return -1;
}


int main()
{
	int command = 0, mode = 1, menuCommand = 0;
	while (command != 4)
	{
		cout << "**************************************" << endl << "Menu" << endl << "1: Arithmetic" << endl << "2: Options" << endl << "3: Help" << endl << "4: End program" << endl << "**************************************" << endl << "Input choice-> ";
		cin >> command;
		if (command == 1)
		{
			Stack <string>* buffer = new Stack<string>();
			Stack <string>* operators = new Stack<string>();
			string token[100], x = "", equation = "";
			int tlength = 0, w = 0, i = 0, p = 0;
			long double e = 0;

			cout << endl << "Input your equation, then press enter." << endl;
			cout << "Functionalities:" << endl << "sqrt(#) | ~ for negative | PI | sin/cos/tan" << endl << "If you use - for negatives, it will crash" << endl;
			if (mode == 1)
				cout << "Mode: Radian" << endl;
			else
				cout << "Mode: Degree" << endl;
			cout << "Example: ~8.77+PI^2*(sqrt(2)/sin(9))" << endl << endl;

			cin.ignore();
			getline(cin,equation);

			/* check if empty */
			if (equation.length() == 0)
			{
				cout << "Error: nothing inputted";
				goto jmp;
			}
			/* turn user input string into an array */
			for (i = 0; i < equation.length(); i++)
			{
				begin: x = equation[i];
				if (equation[i] == ' ')
				{
					i++;
					goto begin;
				}
				else if (equation[i] == 's' && equation[i+1] == 'q')
				{
					i += 5;
					token[w] = to_string(sqrt(stold(stringToDigit(equation, &i))));
					i++;
				}
				else if (isOperator(x) == true)
				{
					token[w] = x;
				}
				else if (equation[i] == '(' || equation[i] == ')')
				{
					token[w] = x;
				}
				else if (isdigit(equation[i]) || equation[i] == '~')
				{
					token[w] = stringToDigit(equation, &i);
				}
				/* trigonometry */
				else if (mode == 1)
				{
					if (equation[i] == 'P' && equation[i + 1] == 'I')
					{
						token[w] = to_string(3.14159265);
						i++;
					}
					else if (equation[i] == 's' && equation[i + 1] == 'i' && equation[i + 2] == 'n')
					{
						i += 4;
						token[w] = to_string(sin(stold(stringToDigit(equation, &i))));
						i++;
					}
					else if (equation[i] == 'c' && equation[i + 1] == 'o' && equation[i + 2] == 's')
					{
						i += 4;
						token[w] = to_string(cos(stold(stringToDigit(equation, &i))));
						i++;
					}
					else if (equation[i] == 't' && equation[i + 1] == 'a' && equation[i + 2] == 'n')
					{
						i += 4;
						token[w] = to_string(tan(stold(stringToDigit(equation, &i))));
						i++;
					}
					else if (equation[i] == 'a' && equation[i + 1] == 's' && equation[i + 2] == 'i' && equation[i + 3] == 'n')
					{
						i += 4;
						token[w] = to_string(asin(stold(stringToDigit(equation, &i))));
						i++;
					}
					else if (equation[i] == 'a' && equation[i + 1] == 'c' && equation[i + 2] == 'o' && equation[i + 3] == 's')
					{
						i += 4;
						token[w] = to_string(acos(stold(stringToDigit(equation, &i))));
						i++;
					}
					else if (equation[i] == 'a' && equation[i + 1] == 't' && equation[i + 2] == 'a' && equation[i + 3] == 'n')
					{
						i += 4;
						token[w] = to_string(atan(stold(stringToDigit(equation, &i))));
						i++;
					}
				}
				else if (mode == 2)
				{
					if (equation[i] == 'P' && equation[i + 1] == 'I')
					{
						token[w] = to_string(3.14159265);
						i++;
					}
					else if (equation[i] == 's' && equation[i + 1] == 'i' && equation[i + 2] == 'n')
					{
						i += 4;
						token[w] = to_string(sin(stold(stringToDigit(equation, &i)) * 3.14159 / 180));
						i++;
					}
					else if (equation[i] == 'c' && equation[i + 1] == 'o' && equation[i + 2] == 's')
					{
						i += 4;
						token[w] = to_string(cos(stold(stringToDigit(equation, &i)) * 3.14159 / 180));
						i++;
					}
					else if (equation[i] == 't' && equation[i + 1] == 'a' && equation[i + 2] == 'n')
					{
						i += 4;
						token[w] = to_string(tan(stold(stringToDigit(equation, &i)) * 3.14159 / 180));
						i++;
					}
					else if (equation[i] == 'a' && equation[i + 1] == 's' && equation[i + 2] == 'i' && equation[i + 3] == 'n')
					{
						i += 4;
						token[w] = to_string(asin(stold(stringToDigit(equation, &i)) * 3.14159 / 180));
						i++;
					}
					else if (equation[i] == 'a' && equation[i + 1] == 'c' && equation[i + 2] == 'o' && equation[i + 3] == 's')
					{
						i += 4;
						token[w] = to_string(acos(stold(stringToDigit(equation, &i)) * 3.14159 / 180));
						i++;
					}
					else if (equation[i] == 'a' && equation[i + 1] == 't' && equation[i + 2] == 'a' && equation[i + 3] == 'n')
					{
						i += 4;
						token[w] = to_string(atan(stold(stringToDigit(equation, &i)) * 3.14159 / 180));
						i++;
					}
				}
				w++;
				tlength++;
			}

			/* convert to postfix */
			for (i = 0; i < tlength; i++)
			{
				if (token[i] == "(")
					operators->push(token[i]);
				else if (token[i] == ")")
				{
					while (operators->top() != "(")
					{
						buffer->push(operators->top());
						operators->pop();
					}
					operators->pop();
				}
				else if (isOperator(token[i]) != true)
					buffer->push(token[i]);
				else if (isOperator(token[i]) == true)
				{
					while (operators->empty() != true && operators->top() != "(" && (precedence(operators->top()) >= precedence(token[i])))
					{
						buffer->push(operators->top());
						operators->pop();
					}
					operators->push(token[i]);
				}
			}
			while (operators->empty() != true)
			{
				buffer->push(operators->top());
				operators->pop();
			}


			Stack <string>* stack = new Stack<string>();
			Stack <long double>* value = new Stack<long double>();

			/* flip the list around */
			while (buffer->empty() == false)
			{
				stack->push(buffer->top());
				buffer->pop();
			}


			/* evaluate the postfix notation */
			while (stack->empty() != true)
			{
				if (isOperator(stack->top()) == false)
					value->push(stold(stack->top()));
				else
				{
					long double operand2 = value->top();
					value->pop();
					long double operand1 = value->top();
					value->pop();
					if (stack->top() == "+")
						e = operand1 + operand2;
					else if (stack->top() == "-")
						e = operand1 - operand2;
					else if (stack->top() == "*")
						e = operand1 * operand2;
					else if (stack->top() == "/")
						e = operand1 / operand2;
					else if (stack->top() == "^")
						e = exponent(operand1, operand2);
					value->push(e);
				}
				stack->pop();
			}
			cout << "=" << value->top();
		}




		else if (command == 2)
		{
			cout << endl << "**************************************" << endl << "Menu:Options" << endl << "1: Radian/Degree" << endl << "2: Return" << endl << "**************************************" << endl << "Input choice-> ";
			cin >> menuCommand;
			if (menuCommand == 1)
			{
				cout << endl << "**************************************" << endl << "Menu:Options:Rad/Deg" << endl << "1. Radian Mode" << endl << "2. Degree Mode" << endl << "**************************************" << endl << "Input choice-> ";
				cin >> mode;
			}
		}


		else if (command == 3)
		{
			cout << endl << "**************************************" << endl << "Menu:Help" << endl << "1: Functionalities" << endl << "2: Credit" << endl << "3: Return" << endl << "**************************************" << endl << "Input choice-> ";
			cin >> menuCommand;
			if (menuCommand == 1)
			{
				cout << endl << "**************************************" << endl << "Menu:Help:Functionalities" << endl;
				cout << "Supports PEMDAS" << endl << "Operations: + - * / sqrt(x) sin/cos/tan/asin/acos/atan(x)" << endl << "To implement negatives, use ~" << endl;
			}
			else if (menuCommand == 2)
			{
				cout << endl << "**************************************" << endl << "Menu:Help:Credit" << endl << "Created by Hayden Gemeinhardt";
			}
		}


	/* if error */
	jmp: cout << endl << endl;
	}
}