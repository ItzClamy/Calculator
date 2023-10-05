#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "Tokenizer.h"
#include "Parser.h"
#include "Evaluator.h"
#include "Token.h"
#include "Utility.h"

// Constants
const std::string CMD_HELP = "help";
const std::string CMD_EXIT = "exit";

void evaluateExpression(const std::string& expression, std::unordered_map<std::string, double>& variables) {
    // Tokenize the expression
    Tokenizer tokenizer(expression);
    auto tokens = tokenizer.tokenize();

    // Convert tokens into an abstract syntax tree (AST)
    Parser parser(tokens);
    auto ast_list = parser.parse();

    // Evaluate the AST and print the result
    Evaluator evaluator(variables);
    double result = evaluator.evaluate(ast_list.back());
    std::cout << result << std::endl;
}

void assignVariable(const std::string& input, std::unordered_map<std::string, double>& variables, Utility& utilities) {
    // Split the input into variable name and expression
    auto extraction = utilities.extract_variable_and_expression(input);
    std::string variable_name = extraction.first;
    std::string expression = extraction.second;

    // Tokenize the expression
    Tokenizer tokenizer(expression);
    auto tokens = tokenizer.tokenize();

    // Convert tokens into an abstract syntax tree (AST)
    Parser parser(tokens);
    auto ast_list = parser.parse();

    // Evaluate the AST and assign the result to the variable
    Evaluator evaluator(variables);
    double value = evaluator.evaluate(ast_list.back());
    variables[variable_name] = value;
    //std::cout << variable_name << " = " << value << std::endl;
}


int main() {
    Utility utilities;

    // Holds variable names and their values for lookup and assignment
    std::unordered_map<std::string, double> variables;

    // Welcome the user to the application
    utilities.print_welcome_message();

    // Main loop to keep reading input until user decides to exit
    while (true) {
        std::string input = utilities.prompt_input();

        // Convert input to lowercase for easier comparison
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == CMD_HELP) {
            utilities.print_help();
            continue;
        }
        if (input == CMD_EXIT) {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        if (input.empty()) continue;

        // Replace variables in the input with their current values
        input = utilities.substitute_variables(input, variables);

        try {
            if (input.find('=') != std::string::npos) {
                assignVariable(input, variables, utilities);
            }
            else {
                evaluateExpression(input, variables);
            }
        }
        catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}


