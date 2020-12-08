#pragma once
#include <math.h>

enum TokenType
{
    Number, Operation, BracketOpen, BracketClose
};

// Token - базовый класс, все его методы мы сделаем виртуальными.
class Token
{
public:
    
    // Метод getType сделаем *абстрактным* - то есть без реализации
    virtual TokenType getType() = 0;

    // Number: getValue
    virtual double getValue() { throw "Method not supported"; }

    // Operation: getPriority, isLeftAssociative, apply, getSymbol, isUnary
    virtual int getPriority() { throw "Method not supported"; }
    virtual bool isUnary() { throw "Method not supported"; }
    virtual bool isLeftAssociative() { throw "Method not supported"; }
    virtual double apply(double op1, double op2=0.) { throw "Method not supported"; }
    virtual char getSymbol() { throw "Method not supported"; }

};

// TokenNumber - хранит в себе числовое значение
class TokenNumber : public Token
{
private:
    double value;
    
public:
    TokenNumber(double value) { this->value = value; }
    TokenType getType() override { return TokenType::Number; }
    double getValue() override { return value; }
    
};

// TokenBracketOpen/Close - скобки
class TokenBracketOpen : public Token
{
public:
    TokenType getType() override { return TokenType::BracketOpen; }
    int getPriority() override { return 0; }
    char getSymbol() override { return '('; }
};

class TokenBracketClose : public Token
{
public:
    TokenType getType() override { return TokenType::BracketClose; }
    int getPriority() override { return 0; }
    char getSymbol() override { return ')'; }
};

// TokenOperation и наследники
class TokenOperation : public Token
{
public:
    TokenType getType() override { return TokenType::Operation; }
};

class TokenPlus : public TokenOperation
{
public:
    int getPriority() override { return 1; }
    bool isUnary() override { return false; }
    bool isLeftAssociative() override { return true; }
    char getSymbol() override { return '+'; }
    double apply(double op1, double op2) { return op1 + op2; }
};

class TokenMinus : public TokenOperation
{
public:
    int getPriority() override { return 1; }
    bool isUnary() override { return false; }
    bool isLeftAssociative() override { return true; }
    char getSymbol() override { return '-'; }
    double apply(double op1, double op2) { return op1 - op2; }
};

class TokenUnaryMinus : public TokenOperation
{
public:
    int getPriority() override { return 1; }
    bool isUnary() override { return true; }
    bool isLeftAssociative() override { return true; }
    char getSymbol() override { return '-'; }
    double apply (double op1, double op2) override { return -op1; }
};

class TokenMultiply : public TokenOperation
{
public:
    int getPriority() override { return 2; }
    char getSymbol() override { return '*'; }
    bool isUnary() override { return false; }
    bool isLeftAssociative() override { return true; }
    double apply(double op1, double op2) { return op1 * op2; }
};

class TokenDivide : public TokenOperation
{
public:
    int getPriority() override { return 2; }
    bool isUnary() override { return false; }
    bool isLeftAssociative() override { return true; }
    char getSymbol() override { return '/'; }
    double apply(double op1, double op2) { return op1 / op2; }
};

class TokenPower : public TokenOperation
{
public:
    int getPriority() override { return 3; }
    bool isUnary() override { return false; }
    bool isLeftAssociative() override { return true; }
    char getSymbol() override { return '^'; }
    double apply(double op1, double op2) { return pow(op1, op2); }
};

class TokenFactorial : public TokenOperation
{
public:
    int getPriority() override { return 3; }
    bool isUnary() override { return true; }
    bool isLeftAssociative() override { return true; }
    char getSymbol() override { return '!'; }
    double apply(double op1, double op2=0.) { return op1 > 0? op1 * apply(op1 - 1) : 1; }
};
