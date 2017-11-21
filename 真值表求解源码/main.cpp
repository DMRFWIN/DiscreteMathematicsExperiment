//
// Created by dmrf on 17-10-21.
//

#include<iostream>

#include<string>
#include<map>

using namespace std;
map<char, int> value_map;
map<string, int> v_map;
int value = 0;
string expr; //真值转换函数

void change_val(int &s) { if (0 == s) s = 1; else s = 0; } //处理基本连接词的函数

int deal_cal(int par1, char par2,
             int par3) {

    switch (par2) {
        case '&'://合取
            return par1 && par3;

        case '|'://析取
            return par1 || par3;

     /*   case '-'://条件
            return !(par1 == 1 && par3 == 0);

        case '~'://双条件
            return (par1 == par3);*/

        default:
            cout << "有某些命题的真值错误" << endl;
            break;
    }
}


//没有括号的表达式处理函数
int run_unkh_expr(string &str) {
    int a;
    int par_value;//该部分表达式的值
    string::size_type l = str.length();
    string::const_iterator it = str.begin();
    for (; it != str.end(); it++) {
        if (*it == '!') {
            string::const_iterator init_it = it + 1;//保存！符后的下一个位置
            change_val(value_map[*(init_it)]);//转换真值
            str.erase(it);//删除否定符号
        }
    }
    it = str.begin();
    par_value = value_map[*it];
    if (l == 1)//如果该部分只有一个命题则返回该命题的真值
    { return par_value; }
    else {
        for (; it != str.end() - 1;) {
            ++it;
            char b = *it;
            par_value = deal_cal(par_value, b, value_map[*(++it)]);
        }
    }

    return par_value;
}

int run_expr(string &Expr) { //扫描括号
    int sum_kh = 0;//括号数
    string::const_iterator iter;
    string::const_iterator addr_kh[50];//用于记录括号的位置
    char kind_kh[50];//用于记录括号的类型
    for (iter = Expr.begin();
         iter != Expr.end(); iter++) {
        if (*iter == '(' || *iter == ')') {
            addr_kh[sum_kh] = iter;
            kind_kh[sum_kh] = *iter;
            sum_kh++;
        }
    }
    if (0 == sum_kh)//如果没有括号
    {
        value = run_unkh_expr(Expr);
        return value;
    } else {
        int i = 0;
        for (; i <= sum_kh; i++) {
            if (kind_kh[i] == ')')//找到最内级的括号并跳出循环
                break;
        } //取出最内层没有括号的字符串
        string in_str = string(addr_kh[i - 1] + 1, addr_kh[i]); //算出最内层表达式的值
       //((!p&q)|(p|q))&(p|v)
        value = run_unkh_expr(in_str);
        v_map[in_str] = value;


        static char var = '1';
        value_map[var] = value;//将括号整体设为一个字符‘1’
        string::const_iterator ite = addr_kh[i - 1];//"字符(的位置" //判断（是不是表达式的开头
        string::const_iterator init_i;
        bool is_begin = false;
        if (ite == expr.begin()) { is_begin = true; }
        else { init_i = addr_kh[i - 1] - 1; }
        {
            expr.erase(ite, addr_kh[i] + 1);//删除掉最内层表达式包括括号在内
        }   //再在删除的地方插入新的字符‘1’


        if (is_begin == true) { expr = var + expr; }
        else { expr.insert(init_i + 1, var); }
        var = var + 1;
        value = run_expr(expr);
        return value;
    }
} //求主析取范式和主合取范式的函数




int main() {
    cout << "请先输入合式公式表达式" << endl;
    cin >> expr;
    string expr2=expr;
    string::const_iterator iter = expr.begin();
    for (; iter != expr.end(); iter++) {
        if (*iter != '!' && *iter != '&' && *iter != '~' && *iter != '-' && *iter != '|' && *iter != '(' &&
            *iter != ')') {
            value_map[*iter] = 1;//为每一个原子命题默认为真
        }
    }
    cout << "请依次再输入各个原子命题的真值选项：" << endl;
    cout << "1 :true" << endl;
    cout << "0 :false" << endl;
    for (map<char, int>::const_iterator it = value_map.begin();
         it != value_map.end(); ++it)//为每个原子命题赋真值
    {
        cout << "请输入" << it->first << "的真值：" << endl;
        int c;
        cin >> c;
        if (c != 1 && c != 0) { cout << "您的输入有误。" << endl; }
        else {
            value_map[it->first] = c;
        }
    }
    /*  for (map<char, int>::iterator yy = value_map.begin(); yy != value_map.end(); yy++) {
          cout << "value_map  " << yy->first <<" "<< yy->second << endl;
      }*/

    int val = run_expr(expr);
    v_map[expr2] = val;

    for (map<char , int>::iterator yy = value_map.begin(); yy != value_map.end(); yy++) {
        if (yy->first>='a'&&yy->first<='z'){
            cout << yy->first << "\t"<<yy->second<<endl;
        }

    }

    cout<<expr2<<"\t"<<val<<endl;

}
