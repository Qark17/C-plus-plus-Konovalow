#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;
int main() {
    string name = "name.txt";
    string line = "10 20 34 76";
    ofstream out(name);
    if (!out) {
        return 1;
    }

    istringstream iss(line);

    istream_iterator<int> begin(iss);
    istream_iterator<int> end;
    ostream_iterator<int> out_numbers(out, " ");

    transform(begin, end, out_numbers, [](int x) {
        return x * 2;
        });
    return 0;
}