#include <iostream>
#include<string>
#include <stdlib.h>
#include <cstdlib>
using namespace std;


int mcd(int x, int y){
    int z = y;
    while(x%y!=0){
        z = x%y;
        x = y;
        y = z;
    }
    return z;
}


class Rational{
    private :
    int p, q, minus = 0;
    
    public :
    
    //some constructers
    Rational(){
        p = 0;
        q = 1;
    };
    Rational(int wholeNumber){
        p = wholeNumber;
        q = 1;
    };
    Rational(int a, int b){
        if (b==0)
            cout << "denominator is 0" << endl;
        
        normalisation(a, b);
    };
    Rational(Rational & R){
        minus = R.get_sign();
        p = R.get_p();
        q = R.get_q();
    }
    Rational(string s){
        minus = 0;
        int loc = s.find('/');
        if (s[0] == '-'){
            minus = 1;
        }
        
        if (!loc < 0){
            string tmp1 = s.substr(minus,loc);
            p = atof(tmp1.c_str());
            string tmp2 = s.substr(loc+1,s.length());
            q = atof(tmp2.c_str());
            cout<<q;
        }
        else {
            string tmp1 = s.substr(minus,s.length());
            p = atof(tmp1.c_str());
            q = 1;
        }
        
    };
    
    //stream operators overload
    friend ostream & operator<<(ostream & o,Rational & A) {
        int sign,head,bottom;
        sign = A.get_sign();
        head = A.get_p();
        bottom = A.get_q();
        if (sign == 0){
            o << head << '/' << bottom << endl;
        }
        else {
            o << "-" << head << '/' << bottom << endl;
        }
        return o;
    }
    friend istream & operator>>(istream & i,Rational & A) {
        string s;
        int sign,head,bottom,loc;
        string tmp1,tmp2;
        i >> s;
        sign = 0;
        if (s[0] == '-'){
            sign = 1;
        }
        
        loc = s.find('/');
        if (loc > 0){
            tmp1 = s.substr(sign,loc);
            head = atof(tmp1.c_str());
            tmp2 = s.substr(loc+1,s.length());
            bottom = atof(tmp2.c_str());
        }
        else{
            head = atof(s.c_str());
            bottom = 1;
        }
        A.change_p(head);
        A.change_q(bottom);
        A.change_sign(sign);
        return i;
    }
    
    
    //display item
    void show(){
        if (minus > 0)
            cout << '-';
        cout << p <<' '<< q << endl;
    }
    //supplemental functions
    void checkminus(int & a, int & b){
        if (a*b < 0){
            minus = 1;
        }
        
        a = abs(a);
        b = abs(b);
    }
    void normalisation(int a, int b){
        int c;
        checkminus(a,b);
        if (a == 0){
            c = 1;
        }
        else {
            if (a-b > 0){
                c = mcd(a,b);
            }
            else {c = mcd(b,a);}
        }
        p = a/c;
        q = b/c;
    }
    int get_p(){
        return p;
    }
    int get_q(){
        return q;
    }
    int get_sign(){
        return minus;
    }
    void change_p(int a){
        p = a;
    }
    void change_q(int a){
        q = a;
    }
    void change_sign(int a){
        minus = a;
    }
    
    ~Rational();
};

Rational :: ~Rational(){
}
// operators overload
Rational operator+(Rational & A, Rational & B){
    int pa,pb,qa,qb,p,q;
    
    pa = A.get_p();
    pb = B.get_p();
    qa = A.get_q();
    qb = B.get_q();
    
    if (A.get_sign() > 0 ){
        if (B.get_sign() > 0){
            p = - pa * qb - pb * qa;
            q = qa * qb;
        }
        else{
            p = - pa * qb + pb * qa;
            q = qa * qb;
        }
    }
    else{
        if(B.get_sign() > 0){
            p = pa * qb - pb * qa;
            q = qa * qb;
        }
        else{
            p = pa * qb + pb * qa;
            q = qa * qb;
        }
    }
    Rational C(p,q);
    return C;
}

Rational operator-(Rational & A, Rational & B){
    
    int pa,pb,qa,qb,p,q;
    
    pa = A.get_p();
    pb = B.get_p();
    qa = A.get_q();
    qb = B.get_q();
    
    if (A.get_sign() > 0 ){
        if (B.get_sign() > 0){
            p = - pa * qb + pb * qa;
            q = qa * qb;
        }
        else{
            p = - pa * qb - pb * qa;
            q = qa * qb;
        }
    }
    else{
        if(B.get_sign() > 0){
            p = pa * qb + pb * qa;
            q = qa * qb;
        }
        else{
            p = pa * qb - pb * qa;
            q = qa * qb;
        }
    }
    Rational C(p,q);
    return C;
}
Rational operator-(Rational & A){
    int pa,qa,p,q;
    
    pa = A.get_p();
    qa = A.get_q();
    
    p = - pa;
    q = qa;
    
    Rational C(p,q);
    return C;
}
Rational operator*(Rational & A, Rational & B){
    int pa,pb,qa,qb,p,q,tmp;
    
    pa = A.get_p();
    pb = B.get_p();
    qa = A.get_q();
    qb = B.get_q();
    
    tmp = A.get_sign() + B.get_sign();
    if (tmp%2 > 0){
        p = - pa * pb;
        q = qa * qb;
    }
    else {
        p = pa * pb;
        q = qa * qb;
    }
    
    Rational C(p,q);
    return C;
}
Rational operator/(Rational & A, Rational & B){
    int pa,pb,qa,qb,p,q,tmp;
    
    pa = A.get_p();
    pb = B.get_p();
    qa = A.get_q();
    qb = B.get_q();
    
    tmp = A.get_sign() + B.get_sign();
    if (tmp%2 > 0){
        p = - pa * qb;
        q = qa * pb;
    }
    else {
        p = pa * qb;
        q = qa * pb;
    }
    
    Rational C(p,q);
    return C;
}
bool operator==(Rational & A, Rational & B){
    int pa,pb,qa,qb,tmp;
    
    pa = A.get_p();
    pb = B.get_p();
    qa = A.get_q();
    qb = B.get_q();
    
    tmp = A.get_sign() - B.get_sign();
    if (tmp%2 == 0 && pa*qb == pb*qa){
        return true;
    }
    else {return false;}
}
bool operator<(Rational & A, Rational & B){
    int pa,pb,qa,qb,s1,s2;
    
    pa = A.get_p();
    pb = B.get_p();
    qa = A.get_q();
    qb = B.get_q();
    
    s1 = A.get_sign();
    s2 = B.get_sign();
    if (s1 > 0){
        if (s2 > 0){
            if (pa * qb < pb * qa){
                return false;
            }
            else {
                return true;
            }
        }
        else return true;
    }
    else {
        if (s2 > 0){
            return false;
        }
        else {
            if (pa * qb < pb * qa){
                return true;
            }
            else {
                return false;
            }
        }
    }
    
}

bool operator>(Rational & A, Rational & B){
    return !(A<B);
}




int main(int argc, const char * argv[]) {
    Rational X(1,2), Y(-8,-10),Z;
    string s;
    
    Z = -X;
    cout << "-X =" << Z;
    Z = -Y;
    cout << "-Y =" << Z << endl;
    
    Z = X+Y;
    cout << "X+Y =" << Z;
    Z = X-Y;
    cout << "X-Y =" << Z;
    Z = X*Y;
    cout << "X*Y =" << Z;
    Z = X/Y;
    cout << "X/Y =" << Z << endl;
    
    cout << (X<Y) << endl;
    if (X<Y){
        cout << "X < Y" << endl;
    }
    else {
        cout << "Y < X" << endl;
    }
    if (X>Y){
        cout << "X > Y" << endl;
    }
    else {
        cout << "Y > X" << endl;
    }
    
    Rational x;
    cin>>x;
    
    cout << x << endl;
    
    return 0;
}

