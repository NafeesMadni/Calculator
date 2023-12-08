#include "stack.h"

int prec(char c) {
    if(c == '-' || c == '+') return 1;
    if(c == '*' || c == '/') return 2;
    return 0;
}

bool isUnary(int i, string str) {
    return ( i == 0 || i > 0 && !isalnum(str[i-1]) && isalnum(str[i+1]) && str[i-1] != ')');
}

float Evaluation(string str) {
    stack<float> s;
    for (int i = 0; i < str.size(); i++) {
        
        if(isalnum(str[i])) {
            string output = "";
            while (isalnum(str[i])) {
                output += str[i++];
            }
            s.push(stof(output));
        }

        else {
            float op1, op2;
            s.pop(op2);
            if(s.isEmpty() || str[i] == '-' && str[i+1] == '_') {
                s.push(-op2);
                i++;
                continue;
            }
            s.pop(op1);

            switch (str[i]) {
                case '+':
                    cout << op1 << "+" << op2 << endl;
                    s.push(op1+op2);
                    break;
                
                case '-':
                    cout << op1 << "-" << op2 << endl;
                    s.push(op1-op2);
                    break;
                
                case '*':
                    cout << op1 << "*" << op2 << endl;
                    s.push(op1*op2);
                    break;
                
                case '/':
                    cout << op1 << "/" << op2 << endl;
                    s.push(op1/op2);
                    break;
            }
        }
    }
    return s.top();
}

string infixToPostfix(string str) {

    string temp = "";
    for (int i = 0; i < str.length(); i++) {
        if(str[i] == ' ' || str[i] == '+' && str[i+1] != '(' && isalnum(str[i+1]) && !isalnum(str[i-1])) {
            continue;
        }
        temp += str[i]; 
    }
    str = temp;

    stack<char> s;
    string output = "";

    for (int i = 0; i < str.size(); i++) {
        if(isalnum(str[i])) {
            output += str[i];
            while (isalnum(str[i+1]) && i < str.size()-1) {
                output += str[++i];
            } output += '#';
        }
        
        else if(str[i] == '(') s.push(str[i]);   

        else if(str[i] == ')') {
            char temp;
            while(!s.isEmpty() && s.top() != '(') {
                s.pop(temp);
                output += temp;
            } s.pop(temp);
        }

        else if(str[i] == '-' && isUnary(i, str)) {
            int j = i;
            while (isalnum(str[i+1])) {
                output += str[++i]; 
            }
            output += '#';
            output += str[j];
            output += '_';
        }       
        else {
            while (!s.isEmpty() && prec(str[i]) <= prec(s.top())) {
                char c;
                s.pop(c);   
                output += c;
            }
            s.push(str[i]);
        }
    }

    while (!s.isEmpty()) {
        char c;
        s.pop(c);
        output += c;
    }
    return output;
}

int main() {
    // string s = "5*2--3+5"; // 8
    // string s = "(((1 + 2) * 3) / 4 - 5) + 6 - ((7 * 8) / 9) - 10"; // -12.9722
    // string s = "2*(-4+5*2)-3";  // 9
    // string s = "((9876 +  5432) * (8765 - 4321) + 25000 / 5000) * (987 - 123) + 15000 / 3 - 8000 * (6000 / 2000)"; // 5.87768e+010 = 58776827048
    // string s = "(((10 + 2) * (7 - 3) + 25 / 5) * (9 - 2) + 15) / 3 - 8 * (6 / 2)"; //104.667
    // string s = "((4 * 5) + (12 / 3)) - (8 + 2)"; // 14
    // string s = "-5 + (-2) - (+7) + (-3) + 10 - (-4) + 6";  // 3D
    string s = "6*-8+21--21+4/(3+-2)";

    string temp = infixToPostfix(s);
    cout << s << " = " << Evaluation(temp);
}