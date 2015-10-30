/**
 * Copyright 2015 Eric Vestfals
 * esv5@zips.uakron.edu
 *
 * AST.cpp
 *
 * For each class that is part of the AST, we define the three functions
 * evaluate(), printPostfix() and printSExpr().
 *
 * For evaluate():
 *
 * For each class that represents a binary node (Addition, Subtraction, ...),
 * the evaluate function calls evaluate on the left node which will keep calling
 * evaluate() recursively until eventually reaching a Number node which will return
 * an int. The same is done for the right node.
 *
 * printPostfix() performs a post-order traversal of the generated AST to print out
 * the postfix version of the expression.
 *
 * printSExpr() performs a pre-order traversal of the generated AST to print out
 * the S-expression.
 */

//#include "AST.hpp"
//#include <iostream>