#include "ConsoleCalculator.h"
#include <iostream>
#include <limits>

using namespace Console;

namespace Console
{


	ConsoleCalculator::ConsoleCalculator()
	{
		arithmaticType.push_back("Addition");
		arithmaticType.push_back("Subtraction");
		arithmaticType.push_back("Multiplication");
		arithmaticType.push_back("Division");

		arithmaticSign[0] = '+';
		arithmaticSign[1] = '-';
		arithmaticSign[2] = '*';
		arithmaticSign[3] = '/';

		std::cout << "Your using Console Calculator\n";
	}


	ConsoleCalculator::~ConsoleCalculator()
	{
		std::cout << std::endl;
		std::cout << "Thank you for using the calculator \n";
	}

	void ConsoleCalculator::SelectOperation()
	{
		std::string dummy;

		int selection;

		std::cout << "\n \n";
		std::cout << "Please select arithmathic operations\n";
		std::cout << "1. Addition\n";
		std::cout << "2. Subtraction\n";
		std::cout << "3. Multiplication\n";
		std::cout << "4. Division\n";

		std::cout << "\n";
		std::cout << "Enter Selection : ";
		std::cin >> selection;

		if (std::cin.fail())
		{
			std::cin.clear();
			//std::cin >> dummy;
			std::cin.ignore();
			//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << std::endl;
			std::cout << "You entered wrong input";

			SelectOperation();

			return;
		}

		OperateArithmatic(selection);

	}

	void ConsoleCalculator::OperateArithmatic(int selection)
	{

		if (selection > arithmaticSign.size() || selection < 0)
		{
			std::cout << std::endl;
			std::cout << "Invaid input";
			SelectOperation();
			return;
		}
		//std::string type = arithmaticType.at(selection - 1);
		char type = arithmaticSign[selection - 1];

		int select;

		float number1, number2;
		float result;


		InputNumberHandling(number1);
		std::cout << type;
		InputNumberHandling(number2);

		switch (selection)
		{
		case 1:
			result = Addition(number1, number2);
			break;
		case 2:
			result = Subtraction(number1, number2);
			break;
		case 3:
			result = Multiplacation(number1, number2);
			break;
		case 4:
			result = Division(number1, number2);
			break;
		default:
			std::cout << "Invalid selection";
			SelectOperation();
			return;
		}

		std::cout << std::endl;
		std::cout << "Result : " << result << std::endl << std::endl;

		std::cout << "Enter new number(1) or select another operation(2)? : ";

		while (true)
		{

			std::cin >> select;


			if (std::cin.fail())
			{

				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				continue;
			}

			switch (select)
			{
			case 1:
				OperateArithmatic(selection);
				return;
			case 2:
				SelectOperation();
				return;
			case 3:
				return;
			default:
				std::cout << std::endl;
				std::cout << "Invalid input";
				std::cout << std::endl;
				continue;
			}


		}


	}

	template <typename T>
	T ConsoleCalculator::InputNumberHandling(T& inputType)
	{


		while (true)
		{
			std::cout << std::endl;
			std::cout << "Enter Number : ";
			std::cin >> inputType;

			if (std::cin.fail()) {

				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				std::cout << "Invalid input try again : " << std::endl;

				continue;
			}

			break;

		}

		return inputType;
	}


}