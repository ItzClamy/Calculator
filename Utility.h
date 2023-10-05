#pragma once
#include <string>
#include <unordered_map>

/*-------Utility.h---------------------------------------------------------
	This header file defines the Utility class, which offers a range of
	utility functions to support the operation of the mathematical parser
	and its user interface.

	Key functionalities include:
		- Printing a welcome message to the user.
		- Prints a help menu
		- Prompting the user for input.
		- Trimming extraneous white spaces from strings.
		- Substituting variables in an input string with their respective values.
		- Extracting a variable name and its expression from an input string.

	This class can be easily expanded to add more utility functions as needed.

----------------------------------------------------------------------------*/

class Utility { 

public:
	/* Prints a welcome message to greet the user at the start of the application. */
	void print_welcome_message();

	/* Prints the help text */
	void print_help(); 

	/* Prompts the user for an input string and returns it. */
	std::string prompt_input();

	/* Removes leading and trailing spaces from a given string. */
	std::string trim_string(const std::string& str);

	/* Replaces variable placeholders in an input string with their corresponding values from the provided map. */
	std::string substitute_variables(const std::string& input, const std::unordered_map<std::string, double>& variables);

	/* Extracts the name of a variable and its corresponding expression from a given input string. */
	std::pair<std::string, std::string> extract_variable_and_expression(const std::string& input);

};
