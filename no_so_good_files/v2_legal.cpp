#include <iostream>
#include<fstream>
#include <queue>
#include<stack>
#include<cmath>
#include<cstring>
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

int main(){
	ifstream input_file;
	input_file.open("Lesson\\DataStructure\\lab2-stack\\expression_evaluation\\input.txt", ios::in);
	if (!input_file.is_open())
	{
		cout << "读取文件失败" << endl;
		return 0;
	}

    queue<char> infix, postfix;   //前缀表达式、后缀表达式
	string str;
    int i = 1;
    while (getline(input_file,str)){
		str += '\n';
		for (const char *p = str.c_str(); *p != '\n'; p++)
			infix.push(*p);
		if(!isLegal(infix))
            cout << i++ << ':' << "ERROR IN INFIX NOTATION\n";
        else
            cout << i++ << ':' <<"yes!\n";
        while(!infix.empty())
            infix.pop();
    }
}