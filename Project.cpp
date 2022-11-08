#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#define PI 3.14159265358979323
using namespace std;

void remove_whitespace(string &str){
    string res = "";
    for(auto i:str){
        if(i!=' ')
            res += i;
    }
    str = res;
}

// this functions gives a vector with format {num1, num2, operation}
vector<string> split(string querie){
    int spl, n = querie.size();
    for(int i=1; i<n; i++){
        int t = (int)querie[i];
        if(t==33 || t==42 || t==43 || t==45 || t==47 || t==94){
            spl = i;
            break;
        }
    }
    vector<string> ans(3);
    string temp = ""+querie[spl];
    ans[0] = querie.substr(0, spl);
    if(spl+1<n)
        ans[1] = querie.substr(spl+1, n-spl);
    else    
        ans[1] = "";
    // the else case is for when factorial function is inputed\
    // there will be no second number
    ans[2] = querie[spl];

    return ans;
}

long double pow(long double base, int exp){
    if(base == 1 || base == 0)
        return base;
    if(exp == 1)
        return base;
    if(exp == 0)
        return 1;
    
    long double t = pow(base, exp/2);
    long double t_2 = t*t;
    if(exp%2 != 0)
        return t_2*base;
    return t_2;
}

long long fac(int num){
    if(num == 0)
        return 1;
    return (long long)num*fac(num-1);
}

long double sin(long double x){
    long double res = 0;
    short sign = 1;
    for(int i=0; i<10; i++){
        long double ex = pow(x, (2*i+1)); 
        long long div = fac(2*i+1);
        res += sign*ex/div;
        sign *= -1;
    }
    return res;
}

long double cos(long double x){
    long double res = 0;
    short sign = 1;
    for(int i=0; i<10; i++){
        long double ex = pow(x, (2*i)); 
        long long div = fac(2*i);
        res += sign*ex/div;
        sign *= -1;
    }
    return res;
}

long double tan(long double x){
    long double s = sin(x), c = cos(x);
    if(c<10e-7 && c>-10e-7){
        cout << "NOT DEFINED" << endl;
        return 1;
    }
    return s/c;
}

long double csc(long double x){
    long double res = sin(x);
    if(res<10e-7 && res>-10e-7){
        cout << "NOT DEFINED" << endl;
        return 1;
    }
    return 1/res;
}

long double sec(long double x){
    long double res = cos(x);
    if(res<10e-7 && res>-10e-7){
        cout << "NOT DEFINED" << endl;
        return 1;
    }
    return 1/res;
}

long double cot(long double x){
    long double s = sin(x), c = cos(x);
    if(s<10e-7 && s>-10e-7){
        cout << "NOT DEFINED" << endl;
        return 1;
    }
    return c/s;
}

void lower(string &str){
    int n = str.length();
    for(int i=0; i<n; i++){
        if((int)str[i]>64 && (int)str[i]<91)
            str[i] += 32;
    }
}

int main(){
    while(true){
        // inputing the querie 
        cout << ">>";
        string querie;
        getline(cin, querie);
        lower(querie);

        // removes white space
        remove_whitespace(querie);

        // to exit the programme
        if(querie[0]=='q' || querie[0]=='Q')
            break;
        // this section deals with simple arithmatic queries
        if((((int)querie[0])>47 && ((int)querie[0])<58) || (int)querie[0]==45/*for negitive numbers*/){
            vector<string> ans = split(querie);
            double num1 = stod(ans[0]), num2;
            // factorial case (no second number)
            if(ans[1] != "")
                num2 = stod(ans[1]);
            // all the arithmatic operations
            if(ans[2] == "+")
                cout << num1+num2 << endl;
            else if(ans[2] == "-")
                cout << num1-num2 << endl;
            else if(ans[2] == "/")
                cout << num1/num2 << endl;
            else if(ans[2] == "*")
                cout << num1*num2 << endl;
            else if(ans[2] == "^")
                cout << pow(num1, num2) << endl;
            else if(ans[2] == "!")
                cout << fac(num1) << endl;
        }

        // this part deals with trig. functions
        else{
            string func = querie.substr(0, 3);
            long double num, x;
            // for the calculations like sin(pi/2), cos(3pi/2) etc
            if(querie.substr(4, 3) == "pi)")
                num = PI;
            else if(querie.substr(4, 4) == "pi/2")
                num = PI/2;
            else if(querie.substr(4, 5) == "3pi/2")
                num = 3*PI/2;
            else if(querie.substr(4, 4) == "pi/4")
                num = PI/4;
            else if(querie.substr(4, 5) == "3pi/4")
                num = 3*PI/4;
            else if(querie.substr(4, 5) == "5pi/4")
                num = 5*PI/4;
            else if(querie.substr(4, 5) == "7pi/4")
                num = -PI/4;
            else    
                num = stod(querie.substr(4, querie.length()-5));
            // trig. functions
            if(func == "sin")
                x = sin(num);
            else if(func == "cos")
                x = cos(num);
            else if(func == "tan")
                x = tan(num);
            else if(func == "cot")
                x = cot(num);
            else if(func == "sec")
                x = sec(num);
            else if(func == "csc")
                x = csc(num);
            // this is for the cases like sin(pi), as we can't take inf
            // taylor series terms, sin(pi) will not be equal to 0
            // this fixes it.
            if(x<10e-7 && x>-10e-7)
                cout << 0 << endl;
            else
                cout << x << endl;
        }
    }
}