// Allen Zohrabians
// Comp 222
// Assignment #1 - Measuring Performance

#include <stdio.h>

int totalCycles;
int totalInstructionCount;
int numberOfClasses;
float clockCycleRate;
float cyclesPerInstruction;
int instructionCount;

void EnterParameters()
{

	int numberOfClasses;

	printf("\nEnter the number of instruction classes: \n");
	scanf("%d", &numberOfClasses);

	printf("\nEnter the frequencey of the machine (GHz):\n");
	scanf("%f", &clockCycleRate);

	for (int i = 0; i < numberOfClasses; i++)
	{
		printf("\nEnter the CPI of the class:\n");
		scanf("%f", &cyclesPerInstruction);

		printf("\nEnter the instruction count of the class (billions):\n");
		scanf("%d", &instructionCount);

		totalInstructionCount += instructionCount;

		totalCycles += cyclesPerInstruction * instructionCount;
	}
	return;
}

void CalculateCPI()
{

	float averageCPI;

  averageCPI = (float)totalCycles/(float)totalInstructionCount;

	printf("\nThe average CPI of the sequence is:  %.2f \n", averageCPI);

	return;
}

void CalculateExecutionTime()
{

	float executionTime;

	executionTime = totalCycles/clockCycleRate;

	printf("\nThe execution time of the sequence is: %.2f seconds\n", executionTime);

	return;
}

void CalculateMIPS()
{

	float mips;

	mips = 1000 * (totalInstructionCount/(totalCycles/clockCycleRate));

	printf("\nThe total MIPS of the sequence is: %.2f \n", mips);

	return;
}

int main()
{

	int choice = 0;

	while(choice != 5)
	{
		printf("\nMeasuring Performance:\n");
		printf("----------------------\n");
		printf("1) Enter parameters\n");
		printf("2) Calculate CPI of a sequence\n");
		printf("3) Calculate Execution time of a sequence\n");
		printf("4) Calculate MIPS of a sequence\n");
		printf("5) Exit program\n");
		printf("\nEnter selection: ");
		scanf("%d", &choice);
		printf("\n");

		switch(choice)
		{
			case 1: EnterParameters(); break;
			case 2: CalculateCPI(); break;
			case 3: CalculateExecutionTime(); break;
			case 4: CalculateMIPS(); break;

			default:
			break;
		}
	}
	return 0;
}
