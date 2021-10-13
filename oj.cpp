#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
#include <string>
using namespace std;

bool isOperator(char c){
    if(c == '+' || c == '-' || c == '*' ||
       c == '/' || c == '^' || c == '%')
        return true;
    else
        return false;
}

bool isLegal(queue<char> q){
    q.push('\n');
    int matches = 0, next_type = 0;     //matches：匹配括号；next_type：规定下一字符类型
    bool pointed = false;               //小数点标记
    while(!q.empty()){
        char now = q.front();                //记录当前字符
        switch (next_type){
        case 0:
            if(now == '0')
                next_type = 1;
            else if(now == '('){
                matches++;
                next_type = 5;
            }
            else if(now >= '1' && now <= '9')
                next_type = 2;
            else if(now == '\n' && !matches)
                return true;
            else
                return false;
            break;
        case 1:
            if(now == '.'){
                next_type = 3;
                pointed = true;
            }
            else if(now == ')'){
                next_type = 6;
                matches--;
            }
            else if (isOperator(now))
                next_type = 4;
            else if(now == '\n' && !matches)
                return true;
            else
                return false;
            break;
        case 2:
            if(now >= '0' && now <= '9')
                next_type = 2;
            else if(now == '.'){
                if(pointed)
                    return false;
                next_type = 3;
            }
            else if(isOperator(now))
                next_type = 4;
            else if(now == ')'){
                next_type = 6;
                matches--;
            }
            else if(now == '\n' && !matches)
                return true;
            else
                return false;
            break;
        case 3:
            if(!(now >= '0' && now <= '9'))
                return false;
            next_type = 2;
            break;
        case 4:
            if(now == '('){
                next_type = 5;
                matches++;
            }
            else if(now >= '1' && now <= '9')
                next_type = 2;
            else if(now == '0')
                next_type = 1;
            else
                return false;
            break;
        case 5:
            if(now == '0')
                next_type = 1;
            else if(now >= '1' && now <= '9')
                next_type = 2;
            else
                return false;
            break;
        case 6:
            if(isOperator(now))
                next_type = 4;
            else if(now =='\n' && !matches)
                return true;
            else
                return false;
            break;
        default:
            break;
        }
        q.pop();
    }
}

int priority(char c){
    if(c == '+' || c == '-')
        return 1;
    else if(c == '*' || c == '/' || c == '%')
        return 2;
    else if(c == '^')
        return 3;
    else if(c == '(')
        return 0;
    else
        return -1;
}

int main(){
    queue<char> infix;                  //前缀表达式
    queue<string> postfix;              //后缀表达式
    stack<char> op_stack;               //运算符栈
    stack<double> cal_result;           //结果计算栈
    char ch;
    while(cin.get(ch)){
        if(ch == '\n')
            break;
        infix.push(ch);
    }

    if(!isLegal(infix)){
        cout << "ERROR IN INFIX NOTATION";
        return 0;
    }

    string str = "";
    while (!infix.empty()){
        ch = infix.front();
        if((ch >= '0' && ch <= '9') || ch == '.'){
            str += ch;
            infix.pop();
            if(infix.empty() || (infix.front() != '.' && !(infix.front() >= '0' && infix.front() <= '9'))){
                postfix.push(str);
                str = "";
            }
            continue;
        }
        else if(ch == ')'){
            while(op_stack.top() != '('){
                str += op_stack.top();
                postfix.push(str);
                str = "";
                op_stack.pop();
            }
            op_stack.pop();
        }
        else if(ch == '^')
            op_stack.push('^');
        else{//operator (not '^')
            while(ch != '(' && !op_stack.empty() && priority(ch) <= priority(op_stack.top())){
                str += op_stack.top();
                postfix.push(str);
                str = "";
                op_stack.pop();
            }
            op_stack.push(ch);
        }
        infix.pop();
    }

    while(!op_stack.empty()){
        str += op_stack.top();
        postfix.push(str);
        str = "";
        op_stack.pop();
    }
    //get postfix

    double a, b;
    while(!postfix.empty()){
        str = postfix.front();
        if(str.length() > 1 || isdigit(str[0])){
            cal_result.push(stod(str));
            postfix.pop();
            continue;
        }
        else{
            b = cal_result.top();
            cal_result.pop();
            a = cal_result.top();
            cal_result.pop();
        }

        switch (str[0])
        {
        case '+': cal_result.push(a + b); break;
        case '-': cal_result.push(a - b); break;
        case '*': cal_result.push(a * b); break;
        case '/': cal_result.push(a / b); break;
        case '^': cal_result.push(pow(a, b)); break;
        case '%': cal_result.push(double(int(a) % int(b))); break;
        default: break;
        }
        postfix.pop();
    }
    printf("%.2f\n", cal_result.top());
    cal_result.pop();
}
