**Algebra Calculator** <br/>
Verison 1.1

**Introduction:**
This calculator is a C++ program designed to solve equations. It utilizes a binary tree structure and token system to parse and evaluate algebraic expressions

**Functionality**
My calculator is geared towards handling a wide range of mathematical expressions. I built it so that when you input an expression, it breaks it down into 'tokens.' These tokens are the individual characters like numbers, math operators, and functions like square root. Once it's tokenized, I use a binary tree to represent the entire expression. This ensures that the math is done in the right order, like multiplication before addition.

**How it works**
The system uses a binary tree structure, termed the expression tree, to represent algebraic expressions. Each node in this tree corresponds to an element of the equation — be it an operator or an operand. The 'ExpressionNode' class encapsulates these nodes, with tokens inside each node conveying the specifics about the type and value associated w
ith them.

**Tokenizer:** 
<br />-> What it does: Its primary responsibility is to break down your input into more manageable pieces, termed tokens.
<br />-> How it works: It cans the input string character by character, categorizing them as numbers, operators, or other constructs. For instance, the expression "3+5" gets dissected into the tokens "3, "+", and "5."

**Parser:**
<br />-> What it does: The main task of the parser is to interpret the order and structure of tokens to ensure they follow mathematical and syntactical rules.
<br />-> How it works: Using the token outputs from the Tokenizer, the Parser arranges them into an Abstract Syntax Tree (AST). This tree structure allows for the proper order of operations (like multiplication before addition) to be adhered to, ensuring accurate evaluations.

**Evaluator:**
<br />-> What it does: It computes the final result by traversing the expression tree.
<br />-> How it works: Beginning at the root of the AST, the Evaluator processes the tree nodes in the correct order. If it encounters operations, it evaluates them using their child nodes. If a node represents a variable, the Evaluator fetches its value from an internal map. Once the entire tree has been navigated, the final result of the expression is obtained.

**Usage and Examples**
The Algebra Calculator is designed to parse and evaluate a variety of algebraic expressions.

Addition: '2 + 3' -> Result = 5 <br />
Subtraction: '2 - 10' -> Result = -8 <br />
Multiplication: '4 * 126' -> Result = 504 <br />
Division: '24 / 5' -> Result = 4.8 <br />

Power and Roots: <br />
&nbsp;&nbsp;&nbsp;&nbsp;Power: '3^5' -> Result = 243 <br />
&nbsp;&nbsp;&nbsp;&nbsp;Square root: 'sqrt(10)' -> Result = 4.8 <br />

Complex Expressions: <br />
&nbsp;&nbsp;&nbsp;&nbsp;Mixed Operations: '3^2 * sqrt(20)' -> Result = 40.249 <br />
&nbsp;&nbsp;&nbsp;&nbsp;Nested Operations: '3^2 * (2 - 10 + 3) * (sqrt(4) / 4)' -> Result = -22.5 <br />
&nbsp;&nbsp;&nbsp;&nbsp;Deeply Nested: '((2^3 + sqrt(25)) * (10 - 2 * 5)) / (3 + 1)' -> Result = 0 <br />

Advanced Usage: <br />
&nbsp;&nbsp;&nbsp;&nbsp;Long Expressions: 'sqrt(2^5) * (10 -3 * 4) / (1 + 0.5) + 3 * 4^2 - (6 + 2)' -> Result = 32.4575 <br />

Solving with known variables: '(x = 10), (y = 5) <br />
&nbsp;&nbsp;&nbsp;&nbsp;Direct Utilization: '2x' -> Result = 20 'y^2' -> Result = 25 <br />
&nbsp;&nbsp;&nbsp;&nbsp;Combined Variables: 'x + y' -> Result = 15 'x * y' -> Result = 50 <br />
&nbsp;&nbsp;&nbsp;&nbsp;Multiple Variables: '2x + 3y' -> Result = 35 '(x^2) / y -> Result = 20 <br />
&nbsp;&nbsp;&nbsp;&nbsp;Nested Variables: 'x * (y + 2) -> Result = 70 'sqrt(y) * (x - 3) -> Result = 35 <br />
&nbsp;&nbsp;&nbsp;&nbsp;Variable Reassignment: 'x = x + y' -> Result = x = 15 <br /> <br />
Note: Always ensure to verify variable assignments before solving complex expressions. Incorrect or overlooked assignments can lead to unintended results.

**INCORRECT EXAMPLES**<br/>
2 / 0 -- Invaild syntax, cannot divide by 0<br/>
2 * (3 + sqrt(16)) - 4 / 2 ^ 3) -- Invaild syntax, There is one too many closing parenthesis

**GOODBYE**
The calculated solution will be returned by the calculator. Feel free to modify and enhance the calculator as you feel, I just created as a test of my abilities.
