#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...

    return eval(root);
}

double AbstractSyntaxTree::eval(AbstractSyntaxTree::Node* subRoot) const
{
    //base case
    if (subRoot->elem != "+" && subRoot->elem != "-" && subRoot->elem != "*" && subRoot->elem != "/")
      return std::stod(subRoot->elem);

    if (subRoot->elem == "+")
      return eval(subRoot->left) + eval(subRoot->right);
    if (subRoot->elem == "-")
      return eval(subRoot->left) - eval(subRoot->right);
    if (subRoot->elem == "*")
      return eval(subRoot->left) * eval(subRoot->right);
    else
      return eval(subRoot->left) / eval(subRoot->right);
}
