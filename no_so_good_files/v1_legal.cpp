#include<queue>
using std::queue;
/**next_tyoe:
 * 0. start = {'(', digit}
 * 1. digit.next = {op, ')', '\n'}
 * 2. op.next = {digit, '('}
 * 3. '('.next = {digit}
 * 4. ')'.next = {op, '\n'}
 * 
 * 补充：
 * * 当字符起始位为0时，下一字符必须是'.'；
 * * '.'在一个数中不得重复出现。
 * */

bool isLegal(queue<char> q){
    int matches = 0, next_type = 0;     //matches：匹配括号；next_type：规定下一字符类型
    bool pointed = false;               //小数点标记
    while(!q.empty()){
        switch (q.front()){
        case '0':
            
        case '1' ... '9':
        
        default:
            break;
        }
    }
    while(!q.empty()){
        if(q.front() == '('){
            if(next_type != 0 && next_type != 2)
                return false;
            matches++;
            next_type = 3;
        }
        else if(q.front() == ')'){
            if(matches <= 0 || next_type != 1)
                return false;
            matches--;
            next_type = 4;
        }
        else if(q.front() == '0'){
            // if(before <= '9' && before >= '0')
            //     return false;

        }
        else if(q.front() <= '9' && q.front() > '0'){
            if(next_type != 0 && next_type != 2 && next_type != 3)
                return false;
            next_type = 1;
        }
        else if(q.front() == '+' || q.front() == '-' || q.front() == '*' || q.front() == '/' || q.front() == '^' || q.front() == '%'){
                if(next_type != 1 && next_type != 4)
                    return false;
            next_type = 2;
        }
        else
            return false;
        //before = q.front();
        q.pop();
    }
    if(matches != 0 || (next_type != 1 && next_type != 4))
        return false;
    return true;
}