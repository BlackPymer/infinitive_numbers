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
public:
    big_int(string num) {
        int l = num.size() - MOD_SIZE;
        while (l > 0) {
            val.push_back(stoi(num.substr(l, MOD_SIZE)));
            l -= MOD_SIZE;
        }
        val.push_back(stoi(num.substr(0, MOD_SIZE + l)));
        reverse(val.begin(), val.end());
    }
    big_int(vector<int>& a) : val(a) {}

    string print() {
        string res = to_string(val[0]);
        for (int i = 1; i < val.size(); i++) {
            string a = to_string(val[i]);
            while (a.size() < MOD_SIZE)
                a = "0" + a;
            res += a;
        }
        return res;
    }
    vector<int> get_val() { return val; }
    void set_val(const vector<int>& a) { val = a; }
    big_int operator+(big_int& a) {
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
};

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    string a, b;
    cin >> a >> b;
    big_int num(a);
    big_int num2(b);
    cout << (num + num2).print();
    return 0;
}
