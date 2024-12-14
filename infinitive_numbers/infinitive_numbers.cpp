#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

const int MOD = 10000000;
const int MOD_SIZE = 7;

class big_int {
private:
    vector<int> val;
    bool negative;
public:
    big_int(string num,bool n=false):negative(n) {
        int l = num.size() - MOD_SIZE;
        while (l > 0) {
            val.push_back(stoi(num.substr(l, MOD_SIZE)));
            l -= MOD_SIZE;
        }
        val.push_back(stoi(num.substr(0, MOD_SIZE + l)));
        reverse(val.begin(), val.end());
    }

    big_int(vector<int>& a,bool n = false) : val(a),negative(n) {}

    big_int(int a, bool n = false) :negative(n),val({a}){}


    string print() const {
        string res = to_string(val[0]);
        if (negative) 
            res = "-" + res;
        for (int i = 1; i < val.size(); i++) {
            string a = to_string(val[i]);
            while (a.size() < MOD_SIZE)
                a = "0" + a;
            res += a;
        }
        return res;
    }

    vector<int> get_val()const { return val; }

    void set_val(const vector<int>& a) { val = a; }

    bool is_negative() const { return negative; }

    void set_negative(bool v) { negative = v; }


    bool operator>(const big_int& a)const {
        if (val.size() > a.get_val().size())
            return true;
        else if (val.size() < a.get_val().size())
            return false;
        else {
            for (int i = 0; i < val.size(); i++) {
                if (val[i] > a.get_val()[i])
                    return true;
            }
            return false;
        }
    }

    bool operator<(const big_int& a)const {
        return a > *this;
    }

    bool operator==(const big_int& a)const {
        if (val.size() != a.get_val().size())
            return false;
        for (int i = 0; i < val.size(); i++) {
            if (a.get_val()[i] != val[i])
                return false;
        }
        return true;
    }

    big_int operator+(const big_int& a)const {
        if (a.is_negative()) {
            if (!negative) {
                big_int c = a;
                c.set_negative(false);
                return *this - c;
            }
            else {
                big_int c = a;
                c.set_negative(false);
                big_int b = *this;
                b.set_negative(false);
                big_int r = c + b;
                r.set_negative(true);
                return r;
            }
        }
        else if (negative) {
            big_int b = *this;
            b.set_negative(false);
            return a - b;
        }
        vector<int> n2 = a.get_val();
        vector<int> n1 = val;
        vector<int> res(max(n1.size(), n2.size()), 0);
        while (n1.size() < n2.size())
            n1.insert(n1.begin(), 0);
        while (n2.size() < n1.size())
            n2.insert(n2.begin(), 0);
        int addition = 0;
        for (int i = n1.size() - 1; i >= 0; i--) {
            res[i] = (n2[i] + n1[i] + addition) % MOD;
            addition = (n2[i] + n1[i] + addition) / MOD;
        }
        if (addition)
            res.insert(res.begin(), addition);
        big_int r(res);
        return r;
    }

    big_int operator-(const big_int& a)const {
        if (negative) {
            if (a.is_negative()) {
                big_int b = a;
                b.set_negative(false);
                return b - *this;
            }
            else {
                big_int c = a;
                c.set_negative(false);
                big_int b = *this;
                b.set_negative(false);
                big_int r = (c + b);
                r.set_negative(true);
                return r;
            }
        }
        else if (a.is_negative()) {
            big_int c = a;
            c.set_negative(false);
            return c + *this;
        }
        if (*this < a) {
            big_int res = a - *this;
            res.set_negative(true);
            return res;
        }
        else if (*this == a)
            return big_int(0);
        else {
            vector<int> res(val.size());
            vector<int> k = a.get_val();
            bool take = 0;
            while (k.size() < val.size())
                k.insert( k.begin(),0);
            for (int i = val.size() - 1; i >= 0; i--) {
                res[i] = val[i] - k[i] - take;
                if (res[i] < 0) {
                    res[i] += MOD;
                    take = 1;
                }
            }
            if (take) {
                //error
                take = 0;
            }
            while (res.size() > 1 && res.front() == 0) { res.erase(res.begin()); }
            return big_int(res);
        }
    }
};

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    string a, b;
    cin >> a >> b;
    big_int num(a);
    big_int num2(b);
    cout << (num - num2).print();
    return 0;
}
