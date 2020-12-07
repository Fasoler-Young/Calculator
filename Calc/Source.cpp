#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include"token.h"


using namespace std;
class Calculator {
public:
    double calculate(vector <Token*> tokens) {
        stack<double > stack;
        for (Token* p : tokens) {
            if (p->getType() == TokenType::Number) {
                stack.push(p->getValue());
            }
            if (p->getType() == TokenType::Operation) {
                double op1 = stack.top();
                stack.pop();
                double op2 = stack.top();
                stack.pop();

                double mid_result = p->apply(op2, op1);
                stack.push(mid_result);

                cout << op2 << p->getSymbol() << op1 << "=" << mid_result << endl;
            }


        }
        return stack.top();
    }


    vector<Token*>transform(vector<Token*>tokens) {
        stack<Token*> stack;
        vector<Token*> result;
        for (Token* p : tokens) {
            if (p->getType() == TokenType::Number) {
                result.push_back(p);
            }
            if (p->getType() == TokenType::Operation) {
                while (!stack.empty()) {
                    if (stack.top()->getPriority() >= p->getPriority()) {
                        result.push_back(stack.top());
                        stack.pop();
                    }
                    else {
                        break;
                    }

                }
              
                
                stack.push(p);
            }
        }
        while (!stack.empty()) {
            result.push_back(stack.top());
            stack.pop();
        }
        return result;
    }

    vector<Token*>parse(string s) {
        vector<Token*> v;
        string buf;
        for (char c : s) {
            if ('0' <= c && c <= '9' || c == '.')
                buf += c;
            else {
                if (buf.size() != 0) {
                    double a = stod(buf);
                    buf = "";
                    v.push_back(new TokenNumber(a));
                }

                if (c == '+')
                    v.push_back(new TokenPlus());
                else if (c == '-')
                    v.push_back(new TokenMinus());
                else if (c == '*')
                    v.push_back(new TokenMultiply());
                else if (c == '/')
                    v.push_back(new TokenDivide());
            }

        }
        if (buf.size() != 0) {
            v.push_back(new TokenNumber(stod(buf)));
            buf = "";
        }
        return v;
    }
};
int main() {
    string s;
    cin >> s;
    Calculator calc;

    vector<Token*> v = calc.parse(s);
    //cout << 1;
    vector<Token*> u = calc.transform(v);
    cout << 1;
    for (Token* p : u) {
        if (p->getType() == TokenType::Number) {
            cout << p->getValue();
        }
        if (p->getType() == TokenType::Operation) {
            cout << p->getSymbol();
        }
    }
    cout << endl;
    double res = calc.calculate(u);
    cout << res;
    /*tokens.push_back (new TokenNumber(3));
    tokens.push_back (new TokenNumber(15));
    tokens.push_back (new TokenMinus());
    tokens.push_back (new TokenNumber(4));
    tokens.push_back (new TokenMultiply());*/

    /*tokens.push_back(new TokenNumber(3));
    tokens.push_back(new TokenMinus());
    tokens.push_back(new TokenNumber(15));
    tokens.push_back(new TokenMultiply());
    tokens.push_back(new TokenNumber(4));
    Calculator calc;
    tokens = calc.transform(tokens);
    cout << calc.calculate(tokens)<<endl;*/

    return 0;
}