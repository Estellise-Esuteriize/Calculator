#pragma once
#include "BaseCalculator.h"
#include <vector>
#include <array>
#include <string>

namespace Console
{

	class ConsoleCalculator : public BaseCalculator
	{

	public:
		ConsoleCalculator();
		~ConsoleCalculator();
		void SelectOperation();

	private:
		std::array<int, 4> arithmaticSign;
		std::vector<std::string> arithmaticType;
		void OperateArithmatic(int selection);
		template <typename T>
		T InputNumberHandling(T& inputType);
	};

}