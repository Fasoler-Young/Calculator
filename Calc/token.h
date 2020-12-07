#pragma once

enum TokenType
{
    Number, Operation, BracketOpen, BracketClose
};

// Token - базовый класс, все его методы мы сделаем виртуальными.
// Мы сделаем много наследников, в которых переопределим эти методы.
class Token
{
public:
    // Чтобы метод можно было переопределить в наследнике,
    // надо сделать его виртуальным, т.е. пометить словом virtual
    
    // Метод getType сделаем *абстрактным* - то есть без реализации
    virtual TokenType getType() = 0;

    // Number: getValue
    virtual double getValue() { throw "Method not supported"; }

    // Operation: getPriority, isLeftAssociative, apply
    virtual int getPriority() { throw "Method not supported"; }
    virtual bool isLeftAssociative() { throw "Method not supported"; }
    virtual double apply(double op1, double op2) { throw "Method not supported"; }
    virtual char getSymbol() { throw "Method not supported"; }

};

// TokenNumber - хранит в себе числовое значение
class TokenNumber : public Token
{
private:
    double value;
    
public:
    TokenNumber(double value) { this->value = value; }
    
    // Мы переопределяем в наследнике метод getType. Пометим переопределенный метод словом override.
    // Вообще это необязательно, можно и без него. Но слово override все же полезно:
    // 1) Наличие override помогает читателю кода понять, что метод переопределяется.
    // 2) Наличие override помогает компилятору отловить ошибку, когда автор кода считает,
    //    что он переопределяет метод, а в базовом классе такого метода нет.
    TokenType getType() override { return TokenType::Number; }
    double getValue() override { return value; }
    
    // Методы getPriority, isLeftAssociative, apply не переопределяем.
    // Если их вызвать у экземпляра класса TokenNumber, то они также бросят исключение.
};

// TokenBracketOpen/Close - скобки
class TokenBracketOpen : public Token
{
public:
    TokenType getType() override { return TokenType::BracketOpen; }
};

class TokenBracketClose : public Token
{
public:
    TokenType getType() override { return TokenType::BracketClose; }
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
    bool isLeftAssociative() override { return true; }
    char getSymbol() override { return '+'; }
    double apply(double op1, double op2) { return op1 + op2; }
};

class TokenMinus : public TokenOperation
{
public:
    int getPriority() override { return 1; }
    bool isLeftAssociative() override { return true; }
    char getSymbol() override { return '-'; }
    double apply(double op1, double op2) { return op1 - op2; }
};

class TokenMultiply : public TokenOperation
{
public:
    int getPriority() override { return 2; }
    char getSymbol() override { return '*'; }
    bool isLeftAssociative() override { return true; }
    double apply(double op1, double op2) { return op1 * op2; }
};

class TokenDivide : public TokenOperation
{
public:
    int getPriority() override { return 2; }
    bool isLeftAssociative() override { return true; }
    char getSymbol() override { return '/'; }
    double apply(double op1, double op2) { return op1 / op2; }
};
