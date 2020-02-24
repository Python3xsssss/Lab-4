#pragma once
#ifndef _MATH_EXP_H_
#define _MATH_EXP_H_

#include <iostream>
#include <string>
#include <type_traits>
#include "List.h"

using std::size_t;
using std::cout;
using std::endl;
using std::string;
using std::istream;
using std::stod;
using std::stoi;


class Polynomial
{
private:
	struct Monomial
	{
		double coeff;
		size_t power;

		Monomial() : coeff(0), power(0) {}
		Monomial(double cf, size_t pw) : coeff(cf), power(pw) {}
		Monomial(const Monomial& mon) : coeff(mon.coeff), power(mon.power) {}
		Monomial& operator=(const Monomial& mon);
		Monomial operator*(const double& val);
		Monomial operator+(const Monomial& mon);
		Monomial operator*(const Monomial& mon);
	};

	List<Monomial> elements;
	bool Find(size_t power, int& index);
	void Insert(const Monomial& mon);
	void Delete(size_t power);
	void Clear();

public:
	Polynomial() : elements() {}
	Polynomial(const Polynomial& pol);
	Polynomial(string str);

	~Polynomial() {}

	Polynomial& operator=(const Polynomial& pol);
	Polynomial operator+(const double& val);
	Polynomial operator*(const double& val);
	Polynomial operator+(const Monomial& mon);
	Polynomial operator*(const Monomial& mon);
	Polynomial operator+(const Polynomial& pol);
	Polynomial operator*(const Polynomial& pol);

	
	void Add(double coeff, size_t power);
	void Set_coeff(double coeff, size_t power);
	double Get_coeff(size_t power);


	friend ostream& operator<<(ostream& out, Monomial& mon)
	{
		if (mon.coeff > 0)
			out << " ";
		else
			out << "- ";
		if (mon.power == 0)
			out << abs(mon.coeff);
		else if (abs(mon.coeff) != 1)
			out << abs(mon.coeff);
		if (mon.power > 0)
		{
			out << "x";
			if (mon.power > 1)
				out << "^" << mon.power;
		}

		return out;
	}


	friend ostream& operator<<(ostream& out, Polynomial& pol)
	{
		for (List<Monomial>::Iterator it = pol.elements.begin(); it != pol.elements.end(); it++)\
		{
			Monomial& tmp = *it;
			if (tmp.coeff > 0 && it != pol.elements.begin())
				out << "+";
			out << *it << " ";
		}
			
		return out;
	}
};


typename Polynomial::Monomial& Polynomial::Monomial::operator=(const Monomial& mon)
{
	if (this == &mon)
		return *this;

	coeff = mon.coeff;
	power = mon.power;
	return *this;
}



typename Polynomial::Monomial Polynomial::Monomial::operator*(const double& val)
{
	Monomial tmp(*this);

	tmp.coeff *= val;
	return tmp;
}



typename Polynomial::Monomial Polynomial::Monomial::operator+(const Monomial& mon)
{
	if (mon.power != power)
		throw "Error: couldn't add up monomials with different powers";

	Monomial tmp(*this);
	tmp.coeff += mon.coeff;
	return tmp;
}



typename Polynomial::Monomial Polynomial::Monomial::operator*(const Monomial& mon)
{
	Monomial tmp(*this);
	tmp.coeff *= mon.coeff;
	tmp.power += mon.power;
	return tmp;
}


bool Polynomial::Find(size_t power, int& index)
{
	int down = 0, up = elements.GetSize(), mid;
	bool is_found = false;
	while (down < up)
	{
		mid = int(up + (down - up) / 2.0);
		if (elements[mid].power < power)
			up = mid;
		else if (elements[mid].power > power)
			down = mid + 1;
		else
		{
			is_found = true;
			up = mid;
			down = mid;
			index = mid;
		}
	}

	if (!is_found)
		index = up;

	return is_found;
}


void Polynomial::Insert(const Polynomial::Monomial& mon)
{
	if (mon.coeff != 0)
	{
		int index = -1;
		if (Find(mon.power, index))
		{
			elements[index].coeff += mon.coeff;
		}
		else if (index == 0)
			elements.Push_top(mon);
		else if (index == elements.GetSize())
			elements.Push_bot(mon);
		else
			elements.Insert(index, mon);
	}
}


void Polynomial::Delete(size_t power)
{
	int index = -1;
	if (Find(power, index))
		elements.Delete(index);
}

void Polynomial::Clear()
{
	size_t old_size = elements.GetSize();
	for (size_t i = 0; i < old_size; i++)
		elements.Pop_top();
}

Polynomial::Polynomial(const Polynomial& pol)
{
	for (List<Monomial>::Iterator it = pol.elements.begin(); it != pol.elements.end(); it++)
		Insert(*it);
}



Polynomial::Polynomial(string str)
{
	size_t len = str.length();
	if (len == 0)
		return;
	
	Monomial new_element(1, 0);
	bool flags[6] = { true, false, false, false, false, false };
	enum flag_indexes { SIGN = 0, COEFFICIENT, VARIABLE, CARET, POWER, MULTIPLY };
	enum condition { FAILURE = -1, SUCCESS, START, MONOM, END } status = START;
	size_t expected_symbol;

	int i = 0;
	while (status > SUCCESS)
	{
		while ((i < len) && (str[i] == ' '))
			i++;
		char tmp = (i < len) ? str[i] : '\0';

		switch (status)
		{
		case START:
			if (str[i] == '-')
				new_element.coeff = -1;
			else
				i--;
			status = MONOM;
			break;
		case MONOM:
			expected_symbol = 0;
			while (expected_symbol < MULTIPLY && flags[expected_symbol])
				expected_symbol++;
			if (tmp == '\0')
				status = END;
			else if ((tmp == '+' || tmp == '-') && expected_symbol > COEFFICIENT && (expected_symbol != VARIABLE || flags[MULTIPLY] == false) && expected_symbol != POWER)
			{
				if (expected_symbol == CARET)
					new_element.power = 1;
				Insert(new_element);
				for (size_t i = SIGN; i <= MULTIPLY; i++)
					flags[i] = false;
				flags[SIGN] = true;
				new_element.coeff = (tmp == '+') ? 1 : -1;
				new_element.power = 0;
			}
			else if ((tmp >= '0') && (tmp <= '9'))
			{
				if (expected_symbol == COEFFICIENT)
				{
					size_t pos;
					new_element.coeff *= stod(&(str[i]), &pos);
					i += pos - 1;
					flags[COEFFICIENT] = true;
				}
				else if (expected_symbol == POWER)
				{
					size_t pos;
					new_element.power = stod(&(str[i]), &pos);
					i += pos - 1;
					flags[POWER] = true;
				}
				else
					status = FAILURE;
			}
			else if (tmp == 'x' && (expected_symbol == VARIABLE || expected_symbol == COEFFICIENT))
			{
				flags[COEFFICIENT] = true;
				flags[VARIABLE] = true;
			}
			else if (tmp == '^' && expected_symbol == CARET)
				flags[CARET] = true;
			else if (tmp == '*' && expected_symbol == VARIABLE)
				flags[MULTIPLY] = true;
			else
				status = FAILURE;
			break;
		case END:
			expected_symbol = 0;
			while (expected_symbol < MULTIPLY && flags[expected_symbol])
				expected_symbol++;

			if (expected_symbol > COEFFICIENT && (expected_symbol != VARIABLE || flags[MULTIPLY] == false) && expected_symbol != POWER)
			{
				if (expected_symbol == CARET)
					new_element.power = 1;
				Insert(new_element);
				status = SUCCESS;
			}
			else
				status = FAILURE;
			break;
		default:
			break;
		}

		i++;
	}

	if (status == FAILURE)
		throw "Error: incorrect string";
}



Polynomial& Polynomial::operator=(const Polynomial& pol)
{
	if (this == &pol)
		return *this;

	Clear();
	for (List<Monomial>::Iterator it = pol.elements.begin(); it != pol.elements.end(); it++)
		Insert(*it);
		
	return *this;
}



Polynomial Polynomial::operator+(const double& val)
{
	Polynomial out(*this);
	Monomial tmp(val, 0);

	out.Insert(tmp);
	return out;
}



Polynomial Polynomial::operator*(const double& val)
{
	Polynomial out(*this);

	if (val != 0)
		for (List<Monomial>::Iterator it = out.elements.begin(); it != out.elements.end(); it++)
		{
			Monomial& tmp = *it;
			tmp.coeff *= val;
		}
		
	return out;
}



Polynomial Polynomial::operator+(const Monomial& mon)
{
	Polynomial out(*this);

	out.Insert(mon);
	return out;
}



Polynomial Polynomial::operator*(const Monomial& mon)
{
	Polynomial out(*this);

	if (mon.coeff != 0)
		for (List<Monomial>::Iterator it = out.elements.begin(); it != out.elements.end(); it++)
		{
			Monomial& tmp = *it;
			tmp.coeff *= mon.coeff;
			tmp.power += mon.power;
		}
		
	return out;
}



Polynomial Polynomial::operator+(const Polynomial& pol)
{
	Polynomial out(*this);

	for (List<Monomial>::Iterator it = pol.elements.begin(); it != pol.elements.end(); it++)
		out.Insert(*it);
	return out;
}



Polynomial Polynomial::operator*(const Polynomial& pol)
{
	Polynomial out;

	for (List<Monomial>::Iterator it = pol.elements.begin(); it != pol.elements.end(); it++)
	{
		out = out + (*this) * (*it);
	}
		

	return out;
}



void Polynomial::Add(double coeff, size_t power)
{
	Monomial tmp(coeff, power);
	Insert(tmp);
}

void Polynomial::Set_coeff(double coeff, size_t power)
{
	int index;
	if (Find(power, index))
		if (coeff != 0)
			elements[index].coeff = coeff;
		else
			elements.Delete(index);
	else
		throw "Error: the polynomial doesn't contain an element with specified power";
}

double Polynomial::Get_coeff(size_t power)
{
	int index;
	if (Find(power, index))
		return elements[index].coeff;
	else
		throw "Error: the polynomial doesn't contain an element with specified power";
}
#endif
