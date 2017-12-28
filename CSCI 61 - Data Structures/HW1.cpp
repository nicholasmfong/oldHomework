#include <iostream>
#include <sstream>      //Nicholas Fong CSCI 61 HW 1
#include <string>
#include <vector>
#include <stack>
#include <cassert>
using namespace std;
vector<string> tokenize(const string & s){
    vector<string> ans;
    istringstream ss(s);
    string temp;
    while (ss  >> temp)
        ans.push_back(temp);
    return ans;
}
int evaluate_prefix(string input){
         vector<string> tokens = tokenize(input);
         stack<int> operands;
         int op1, op2;
         for (vector<string>::size_type i = tokens.size(); i > 0; --i){
               switch(tokens[i-1][0]){
                      case '+':
                                 op1 = operands.top();
                                 operands.pop();
                                 op2 = operands.top();
                                 operands.pop();
                                 operands.push(op1 + op2);
                                 break;


                     case '-':
                                 op1 = operands.top();
                                 operands.pop();
                                 op2 = operands.top();
                                 operands.pop();
                                 operands.push(op1 - op2);
                                 break;

                     case '*':
                                 op1 = operands.top();
                                 operands.pop();
                                 op2 = operands.top();
                                 operands.pop();
                                 operands.push(op1 * op2);
                                 break;

                     case '/':
                                 op1 = operands.top();
                                 operands.pop();
                                 op2 = operands.top();
                                 operands.pop();
                                 operands.push(op1 / op2);
                                 break;
                   case '%':
                                 op1 = operands.top();
                                 operands.pop();
                                 op2 = operands.top();
                                 operands.pop();
                                 operands.push(op1 % op2);
                                 break;
                   default:
                                 int v(0);
                                 istringstream stream(tokens[i-1]);
                                 stream >> v;
                                 operands.push(v);
                                 break;
        }
     }
         return operands.top();
}
unsigned precedence(char op){
    switch(op)
   {
        case '*' : case '/' : case '%' :
            return 2;

        case '+' : case '-' :
            return 1;

        default:
            return 0;
    }
}
int main(){
    string input, postfix;
    cout << "Enter an prefix expression: ";
    getline(cin, input);
    cout << " = " << evaluate_prefix(input) << endl;
}
