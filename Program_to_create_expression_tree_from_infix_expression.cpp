#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <exception>
 
using namespace std;
 
class ExpressionElementNode
{
    public:
        virtual double value() = 0;
};
 
class NumericElementNode: public ExpressionElementNode
{
 
    private:
        double number;
        NumericElementNode(const NumericElementNode& n);
        NumericElementNode();
        NumericElementNode&operator=(const NumericElementNode& n);
    public:
 
        NumericElementNode(double val);
        virtual double value();
};
 
inline NumericElementNode::NumericElementNode(double val) :
    number(val)
{
}
 
inline double NumericElementNode::value()
{
    return number;
}
 
class BinaryOperationNode: public ExpressionElementNode
{
 
    private:
 
        char binary_op;
 
        ExpressionElementNode *left;
        ExpressionElementNode *right;
 
        BinaryOperationNode(const BinaryOperationNode& n);
        BinaryOperationNode();
        BinaryOperationNode &operator=(const BinaryOperationNode& n);
 
    public:
        BinaryOperationNode(char op, ExpressionElementNode *l,
                ExpressionElementNode *r);
 
        virtual double value();
};
 
inline BinaryOperationNode::BinaryOperationNode(char op,
        ExpressionElementNode *l, ExpressionElementNode *r) :
    binary_op(op), left(l), right(r)
{
}
double BinaryOperationNode::value()
{
    double leftVal = left->value();
 
    double rightVal = right->value();
 
    double result;
 
    switch (binary_op)
    {
 
        case '+':
            result = leftVal + rightVal;
            break;
 
        case '-':
            result = leftVal - rightVal;
            break;
 
        case '*':
            result = leftVal * rightVal;
            break;
 
        case '/':
            result = leftVal / rightVal;
            break;
    }
 
    return result;
}
class ExpressionElementNode;
class BinaryOperationNode;
 
class BinaryExpressionBuilder
{
 
    private:
        std::stack<char> operatorStack;
 
        std::stack<ExpressionElementNode *> operandStack;
 
        void processOperator(char op);
        void processRightParenthesis();
 
        void doBinary(char op);
 
        int precedence(char op);
 
    public:
 
        class NotWellFormed: public std::exception
        {
 
            public:
                virtual const char* what() const throw ()
                {
                    return "The expression is not valid";
                }
        };
 
        BinaryOperationNode *parse(std::string& istr) throw (NotWellFormed);
};
int BinaryExpressionBuilder::precedence(char op)
{
    enum
    {
        lowest, mid, highest
    };
 
    switch (op)
    {
 
        case '+':
        case '-':
            return mid;
 
        case '/':
        case '*':
            return highest;
 
        default:
            return lowest;
    }
}
 
BinaryOperationNode *BinaryExpressionBuilder::parse(std::string& str)
        throw (NotWellFormed)
{
    istringstream istr(str);
    char token;
 
    while (istr >> token)
    {
 
        switch (token)
        {
 
            case '+':
            case '-':
            case '*':
            case '/':
                processOperator(token);
                break;
 
            case ')':
                processRightParenthesis();
                break;
 
            case '(':
                operatorStack.push(token);
                break;
 
            default:

                istr.putback(token);
                double number;
 
                istr >> number;
 
                NumericElementNode *newNode = new NumericElementNode(number);
                operandStack.push(newNode);
 
                continue;
        } 
    }
 
    while (!operatorStack.empty())
    {
 
        doBinary(operatorStack.top());
        operatorStack.pop();
    }

    if (operandStack.size() != 1)
    {
 
        throw NotWellFormed();
    }
 
    ExpressionElementNode *p = operandStack.top();
 
    return static_cast<BinaryOperationNode *> (p);
}
 
void BinaryExpressionBuilder::processOperator(char op)
{
    int opPrecedence = precedence(op);
 
    while ((!operatorStack.empty()) && (opPrecedence <= precedence(
            operatorStack.top())))
    {
 
        doBinary(operatorStack.top());
        operatorStack.pop();
    }
 
    operatorStack.push(op);
}
 
void BinaryExpressionBuilder::processRightParenthesis()
{
    while (!operatorStack.empty() && operatorStack.top() != '(')
    {
 
        doBinary(operatorStack.top());
        operatorStack.pop();
    }
 
    operatorStack.pop();
}

void BinaryExpressionBuilder::doBinary(char op)
{
    ExpressionElementNode *right = operandStack.top();
 
    operandStack.pop();
 
    ExpressionElementNode *left = operandStack.top();
 
    operandStack.pop();
 
    BinaryOperationNode *p = new BinaryOperationNode(operatorStack.top(), left,
            right);
 
    operandStack.push(p);
}
int main(int argc, char** argv)
{
 
    NumericElementNode num1(10);
    NumericElementNode num2(20);
    BinaryOperationNode n('+', &num1, &num2);
 
    BinaryExpressionBuilder b;
 
    cout << "Enter expression" << endl;
 
    string expression;
    getline(cin, expression);
 
    BinaryOperationNode *root = b.parse(expression);
 
    cout << " result = " << root->value();
    return 0;
}
