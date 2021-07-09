// Allen Zohrabians
// Comp 222
// Assignment #2 - Decimal and IEEE-754 Conversion

#include <stdio.h>
#include <math.h>

void DecToIEEE()
{
	float dec_number;

	printf("Enter the decimal representation: \n");
	scanf("%f", &dec_number);

	if (dec_number == 0.0)
	{
		printf("Sign: 0\n");

		printf("Biased exponent: 00000000\n");

		printf("Mantissa:  00000000000000000000000\n");

		printf("IEEE-754: 00000000\n");
		return;
	}

	int sign_bit;
	if (dec_number > 0.0)
	{
		sign_bit = 0;
		printf("Sign: %d\n", sign_bit);
	}
	else
	{
		printf("Sign: -\n");
		sign_bit = 1;
		dec_number = dec_number * -1;
	}

	float mantissa = dec_number;
	int exponent_number = 0;

	while (mantissa >= 2)
	{
		mantissa = mantissa / 2.0;
		exponent_number++;
	}
	while (mantissa < 1)
	{
		mantissa = mantissa * 2.0;
		exponent_number--;
	}

	int exponent_bits = exponent_number + 127;

	int k = 0;
	int exponent[20];

	while(exponent_bits > 0)
	{
		exponent[k] = exponent_bits % 2;

		exponent_bits = exponent_bits/2;

		k++;

	}

	int myArray[20];
	printf("Biased exponent: ");
	for (int i = 0; i<=7; i++)
	{
		myArray[i] = exponent[7-i];
		printf("%d", myArray[i]);
	}

	(int)pow(2, exponent_number);
	printf("\nMantissa: ");

	mantissa = mantissa -1;

	int signficand[50];


	for(int i = 0; i <= 22; i++)
	{

	float currentDigit = pow(2,i+1);
	currentDigit = 1/currentDigit;

		if(mantissa >= currentDigit)
		{
			signficand[i] = 1;
			mantissa = mantissa - currentDigit;
			printf("1");
		}
		else
		{
			printf("0");
			signficand[i] = 0;
		}

	}

	printf("\n");

	for(int i = 0; i <= 7; i++)
	{
		exponent_bits = exponent_bits + myArray[i]*pow(2,30-i);
	}
int mantissa_bits = 0;
	for(int i = 0; i <= 22; i++)
	{
		mantissa_bits = mantissa_bits + signficand[i]*pow(2,22-i);
	}

	int ieee_number = exponent_bits + mantissa_bits;

	printf("IEEE-754: %x\n", ieee_number);
  return;
}


void IEEEToDec()
{
	int ieee_number;

	printf("Enter the IEEE-754 representation: \n");
	scanf("%x", &ieee_number);

	if(ieee_number == 0x00000000)
	{
		printf("Special case: 0\n");
		return;
	}

	if(ieee_number == 0x80000000)
	{
		printf("Special case: -0\n");
		return;
	}

	if(ieee_number == 0x7F800000)
	{
		printf("Special case: + infinity\n");
		return;
	}

	if(ieee_number == 0xFF800000)
	{
		printf("Special case: - infinity\n");
		return;
	}

	if(ieee_number == 0x7FBFFFFF)
	{
		printf("Special case: NaN\n");
		return;
	}

	if(ieee_number == 0xFFFFFFFF)
	{
		printf("Special case: NaN\n");
		return;
	}

	int sign;

	if(sign == 0)
	{
		printf("Sign: +\n");
	}
	else
	{
		printf("Sign: -\n");
	}

	int sign_bit = (ieee_number & 0x80000000) / ((int)pow(2,31));

	int unbiased_exp = (sign_bit * -2) + 1;

	printf("Unbiased exponent: %x\n", unbiased_exp);

	int exponent_bits = (ieee_number & 0x7F800000) / ((int)pow(2,23));

	int exponent = (int)pow(2, exponent_bits - 127);

	int mantissa_bits = (ieee_number & 0x007FFFFF);

	float mantissa = (mantissa_bits * pow(2, -23)) + 1;
	printf("Normalized Decimal: %f\n", mantissa);

	float dec_number = unbiased_exp * exponent * mantissa;
	printf("Decimal: %f\n", dec_number);
	 return;
}

int main()
{

	int choice = 0;

	while(choice != 3)
	{
		printf("\nFloating-point conversion:\n");
		printf("--------------------------\n");
		printf("1) Decimal to IEEE-754 conversion\n");
		printf("2) IEEE-754 to Decimal conversion\n");
		printf("3) Exit\n");
		printf("\nEnter selection: ");
		scanf("%x", &choice);
		printf("\n");

		switch(choice)
		{
			case 1: DecToIEEE(); break;
			case 2: IEEEToDec(); break;

			default:
			break;
		}
	}

  return 0;
}
