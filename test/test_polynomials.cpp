#include "Polynomials.h"
#include <gtest.h>

TEST(List, can_create_polynomial)
{
	ASSERT_NO_THROW(Polynomial);
}

TEST(List, can_create_polynomial_from_correct_string)
{
	ASSERT_NO_THROW(Polynomial("x^2 + 2x + 1"));
}

TEST(List, throws_when_creating_polynomial_from_incorrect_string)
{
	ASSERT_ANY_THROW(Polynomial("2^x + 2x + 1"));
}

TEST(List, can_create_copied_polynomial)
{
	Polynomial pol("x^2 + 2x + 1");
	ASSERT_NO_THROW(List<int>(pol));
}

TEST(List, can_get_coeff_of_the_existing_monomial)
{
	Polynomial pol("x^2 + 2x + 1");
	EXPECT_EQ(2, pol.Get_coeff(1));
}

TEST(List, throws_when_getting_coeff_of_the_non_existing_monomial)
{
	Polynomial pol("x^2 + 2x + 1");
	ASSERT_ANY_THROW(pol.Get_coeff(5));
}

TEST(List, can_add_existing_monomial)
{
	Polynomial pol("x^2 + 2x + 1");
	pol.Add(3, 1);
	EXPECT_EQ(5, pol.Get_coeff(1));
}

TEST(List, can_add_non_existing_monomial)
{
	Polynomial pol("x^2 + 2x + 1");
	pol.Add(3, 5);
	EXPECT_EQ(3, pol.Get_coeff(5));
}

TEST(List, can_set_coeff_of_the_existing_monomial)
{
	Polynomial pol("x^2 + 2x + 1");
	pol.Set_coeff(3, 1);
	EXPECT_EQ(3, pol.Get_coeff(1));
}

TEST(List, throws_when_setting_coeff_of_the_non_existing_monomial)
{
	Polynomial pol("x^2 + 2x + 1");
	ASSERT_ANY_THROW(pol.Set_coeff(3, 5));
}

TEST(List, can_add_number_with_plus_operator)
{
	Polynomial pol("x^2 + 2x + 1");
	pol = pol + 3;
	EXPECT_EQ(4, pol.Get_coeff(0));
}

TEST(List, can_multiply_a_polynomial_by_a_number)
{
	Polynomial pol("x^2 + 2x + 1");
	pol = pol * 3;
	EXPECT_EQ(3, pol.Get_coeff(2));
}

TEST(List, can_add_a_polynomial_to_a_polynomial)
{
	Polynomial pol1("x^2 + 2x + 1");
	Polynomial pol2("5x^3 + 4x");
	Polynomial pol3 = pol1 + pol2;
	EXPECT_EQ(6, pol3.Get_coeff(1));
}

TEST(List, can_multiply_a_polynomial_by_a_polynomial)
{
	Polynomial pol1("x^2 + 2x + 1");
	Polynomial pol2("5x^3 + 4x");
	Polynomial pol3 = pol1 * pol2;
	EXPECT_EQ(5, pol3.Get_coeff(5));
}