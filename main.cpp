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
        
        if(isalnum(str[i]) || str[i] == '.') {
            string output = "";
            while (isalnum(str[i]) || str[i] == '.') {
                output += str[i++];
            }
            s.push(stof(output));
        }

        else {
            float op1, op2;
            s.pop(op2);
            if(s.isEmpty() || str[i] == '&') {
                s.push(-op2);
                continue;
            }
            s.pop(op1);

            switch (str[i]) {
                case '+': s.push(op1+op2);
                    break; 
                case '-': s.push(op1-op2);
                    break; 
                case '*': s.push(op1*op2);
                    break; 
                case '/':  s.push(op1/op2);
                    break;
            }
        }
    }
    return s.top();
}

string infixToPostfix(string str) {

    string output = "";
    stack<char> s;
    char c;

    for (int i = 0; i < str.length(); i++) {
        if(str[i] == ' ' || str[i] == '+' && str[i+1] != '(' && isalnum(str[i+1]) && !isalnum(str[i-1]) && str[i] != '.') continue;
        output += str[i]; 
    }
    str = output;

    output.clear();

    for (int i = 0; i < str.size(); i++) {
        if(isalnum(str[i])  || str[i] == '.') {
            output += str[i];
            while (isalnum(str[i+1]) && i < str.size()-1  || str[i+1] == '.') {
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
            while (isalnum(str[i+1]) || str[i+1] == '.') {
                output += str[++i]; 
            }
            output += '#';
            output += '&';
        }       
        else {
            while (!s.isEmpty() && prec(str[i]) <= prec(s.top())) {
                s.pop(c);   
                output += c;
            }
            s.push(str[i]);
        }
    }

    while (!s.isEmpty()) {
        s.pop(c);
        output += c;
    }
    return output;
}

int main() {
    // string s = "((9876 +  5432) * (8765 - 4321) + 25000 / 5000) * (987 - 123) + 15000 / 3 - 8000 * (6000 / 2000)"; // 5.87768e+010 = 58776827048
    string s = "-5.31 + (-2.4) - (+743.13) + (-0.3) + 10.49 - (-401.3) + 643.331";  // 3D


    string temp = infixToPostfix(s);
    cout << temp << endl;
    cout << s << " = " << Evaluation(temp);
}
