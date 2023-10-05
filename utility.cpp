#include "Utility.h"
#include "Tokenizer.h"
#include <iostream>

/* print_welcome_message: Prints the welcome message for the user*/
void Utility::print_welcome_message() {

    std::cout << "--------------------------------\n";
    std::cout << "| Welcome To Justin's Calculator |\n";
    std::cout << "--------------------------------\n\n";

    std::cout << "To start enter the expression you would like to have solved. If you need help, type 'help' for " << std::endl << "the help menu to pop up or 'exit' to leave the program!";
    std::cout << std::endl;

}

/* print_help: prints the help menu if user specifies*/
void Utility::print_help() {
    std::cout << "\n========================================\n";
    std::cout << "| Justin's Scientific Calculator - Help |\n";
    std::cout << "========================================\n\n";

    std::cout << "Here's how to use the calculator:\n";
    std::cout << "\n1. BASIC OPERATIONS:\n";
    std::cout << "   For addition: 5 + 3\n";
    std::cout << "   For subtraction: 5 - 3\n";
    std::cout << "   For multiplication: 5 * 3\n";
    std::cout << "   For division: 5 / 3\n";
    std::cout << "   For power: 5 ^ 3\n";
    std::cout << "   For square root: sqrt(25)\n";

    std::cout << "\n2. USING VARIABLES:\n";
    std::cout << "   To assign a value to a variable, type: x = 5 and press Enter.\n";
    std::cout << "   IMPORTANT: After declaring a variable, hit Enter before using it in an expression.\n";
    std::cout << "   For instance, declare x first: x = 5 [Enter], then use: 2x + 3\n";
    std::cout << "   Similarly, for multiple variables: x = 2 + 5^2 [Enter], y = sqrt(x) [Enter].\n";
    std::cout << "   After declaring, you can use them together: 2x + y - 8\n";

    std::cout << "\n3. COMPLEX EXPRESSIONS:\n";
    std::cout << "   Group your expressions using parentheses: (2 + 3) * 4\n";
    std::cout << "   Combine multiple operations: 2x + 7 - 8\n";

    std::cout << "\n4. NOTES:\n";
    std::cout << "   - Ensure you've defined variables before using them in expressions.\n";
    std::cout << "   - Invalid syntax or undeclared variables will lead to errors.\n";

    std::cout << "\n5. EXITING:\n";
    std::cout << "   Type 'exit' to close the calculator.\n";

    std::cout << "\nHappy calculating!\n\n";

}

/* prompt_input: messaged used in main that prompts user for input expression*/
std::string Utility::prompt_input() {

    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);

    return input;
}

/* trim_string: lambda function that trims the string if needed */
std::string Utility::trim_string(const std::string& str) {
    size_t first = str.find_first_not_of(' ');

    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

/* substitue_variables: Substitue variable names with their corresponding values in a given string*/
std::string Utility::substitute_variables(const std::string& input, const std::unordered_map<std::string, double>& variables) {
    std::string modified_input = input;

    for (const auto& pair : variables) {
        const std::string& name = pair.first;
        const double& value = pair.second;

        size_t pos = 0;

        while ((pos = modified_input.find(name, pos)) != std::string::npos) {  // Check and replace every instance of the variable name
            bool addMultiplication = pos > 0 && std::isdigit(modified_input[pos - 1]);

            if (addMultiplication) {  // If variable follows a number, insert multiplication
                modified_input.insert(pos, "*");
                pos++;
            }

            modified_input.replace(pos, name.length(), std::to_string(value));  // Replace variable name with its value
            pos += std::to_string(value).length();
        }
    }
    return modified_input;
}

/* extract_variable_and_expression: Extract variable name and its corresponding expression from a string*/
std::pair<std::string, std::string> Utility::extract_variable_and_expression(const std::string& input) {

    size_t pos = input.find('=');
    std::string variable_name = trim_string(input.substr(0, pos));
    std::string expression = input.substr(pos + 1);

    return { variable_name, expression };
}