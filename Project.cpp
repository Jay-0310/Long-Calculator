#include <bits/stdc++.h>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Convert infix to postfix using Shunting Yard Algorithm
vector<string> infixToPostfix(const string& expression) {
    vector<string> postfix;
    stack<char> operators;
    istringstream ss(expression);
    string token;

    while (ss >> token) {
        if (isdigit(token[0])) {
            postfix.push_back(token);
        }
        else if (token == "(") {
            operators.push('(');
        } 
        else if (token == ")") {
            while (!operators.empty() && operators.top() != '(') {
                postfix.push_back(string(1, operators.top()));
                operators.pop();
            }
            if (!operators.empty()) operators.pop(); // Pop '('
            else throw runtime_error("Mismatched parentheses");
        } 
        else { 
            while (!operators.empty() && precedence(operators.top()) >= precedence(token[0])) {
                postfix.push_back(string(1, operators.top()));
                operators.pop();
            }
            operators.push(token[0]);
        }
    }
    // Pop remaining operators
    while (!operators.empty()) {
        if (operators.top() == '(') throw runtime_error("Mismatched parentheses");
        postfix.push_back(string(1, operators.top()));
        operators.pop();
    }
    return postfix;
}

// Evaluate a postfix expression
double evaluatePostfix(const vector<string>& postfix) {
    stack<double> values;

    for (const string& token : postfix) {
        if (isdigit(token[0])) {
            values.push(stod(token));
        } 
        else {
            if (values.size() < 2) throw runtime_error("Invalid postfix expression");
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            if (token == "+") values.push(a + b);
            else if (token == "-") values.push(a - b);
            else if (token == "*") values.push(a * b);
            else if (token == "/") {
                if (b == 0) throw runtime_error("Division by zero");
                values.push(a / b);
            }
        }
    }
    if (values.size() != 1) throw runtime_error("Invalid postfix expression");
    return values.top();
}

// Main function
int main() {
    string expression;
    cout << "Enter a mathematical expression: ";
    getline(cin, expression);
    try {
        vector<string> postfix = infixToPostfix(expression);
        double result = evaluatePostfix(postfix);
        cout << "Result: " << result << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
