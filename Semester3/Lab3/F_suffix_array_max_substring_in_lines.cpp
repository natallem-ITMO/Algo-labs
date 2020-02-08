#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
vector<int> index_start;


extern const int CHAR_AMOUNT = 256;

long long int recount_classes(std::vector<std::pair<long long int, std::pair<long long int, long long int >>> &suffixes,
                              long long int shift) {
    std::vector<long long int> class_of_suffix(suffixes.size());
    long long int current_class = 0;
    for (long long int i = 1; i < suffixes.size(); i++) {
        if (suffixes[i - 1].second != suffixes[i].second) ++current_class;
        class_of_suffix[suffixes[i].first] = current_class;
    }
    for (auto &triple : suffixes) {
        triple.second.second = class_of_suffix[triple.first];
        if (triple.first < shift) {
            triple.first = triple.first + suffixes.size() - shift;
        } else {
            triple.first -= shift;
        }
        triple.second.first = class_of_suffix[triple.first];
    }
    return current_class;
}

void count_sort(std::vector<std::pair<long long int, std::pair<long long int, long long int>>> &suffixes,
                long long int max_class) {
    std::vector<long long int> class_counter(max_class + 1, 0);
    for (auto triple : suffixes) {
        ++class_counter[triple.second.first];
    }
    long sum = 0;
    for (long long int i = 0; i < class_counter.size(); i++) {
        long prev = sum;
        sum += class_counter[i];
        class_counter[i] = prev;
    }
    std::vector<std::pair<long long int, std::pair<long long int, long long int>>> new_suffixes(suffixes.size());

    for (auto triple : suffixes) {
        new_suffixes[class_counter[triple.second.first]++] = triple;
    }
    suffixes = new_suffixes;
}


std::vector<int> circular_suffix_array(const std::string &input) {
    std::vector<int> indexes(input.size());
    std::vector<std::pair<long long int, std::pair<long long int, long long int>>> suffixes;
    for (long long int i = 0; i < input.size(); i++) {
        suffixes.push_back({i, {input[i], 0}});
    }
    count_sort(suffixes, 256);
    recount_classes(suffixes, 0);
    for (long long int i = 1; i <= input.size(); i = i << 1) {
        long long int max_class = recount_classes(suffixes, i);
        count_sort(suffixes, max_class);
    }
    for (long long int i = 0; i < suffixes.size(); i++) {
        indexes[i] = (suffixes[i].first);
    }
    return indexes;
}

vector<int> prefix(const vector<int> suff_array, const string &input) {
    vector<int> result(suff_array.size(), 0);
    vector<int> indexes(suff_array.size(), 0);
    for (int i = 0; i < suff_array.size(); i++) {
        indexes[suff_array[i]] = i;
    }
    int prev = 0;
    for (int i = 0; i < suff_array.size() - 1; i++) {
        if (prev != 0) prev--;
        int counter = prev;
        for (int ch1 = i + prev, ch2 = suff_array[indexes[i] - 1] + prev;
             ch1 < input.size() && ch2 < input.size(); ch1++, ch2++) {
            if (input[ch1] == input[ch2]) counter++;
            else break;
        }
        result[indexes[i]] = counter;
        prev = counter;
    }

    return result;
}


int firstIndex;
int MAX = INT32_MAX;
int amountOfLeafs = 1;


int get_number_of_string(int l);

int getRs(int node) {
    return node * 2 + 2;
}

int getLs(int node) {
    return getRs(node) - 1;
}

void push(vector<int> &vec, int node) {
    if (node >= firstIndex)
        return;
    int ls = node * 2 + 1;
    int rs = node * 2 + 2;
    vec[ls] = max(vec[ls], vec[node]);
    vec[rs] = max(vec[rs], vec[node]);
}


int findMin(vector<int> &vec, int node, int l, int r, int L, int R) {//l r исходные границы, L R текущие
    push(vec, node);
    if (L >= r || R <= l) {
        //int k = 0;
        return MAX;
    }

    if (L >= l && R <= r) {
        return vec[node];
    }

    int ls = getLs(node);
    int rs = getRs(node);
    int m = (L + R) / 2;
    int lsRes = findMin(vec, ls, l, r, L, m);
    int rsRes = findMin(vec, rs, l, r, m, R);
    return min(lsRes, rsRes);
}

int findMinIndex(vector<int> &vec, int node) {
    push(vec, node);
    if (node >= firstIndex) return node;
    if (vec[getLs(node)] == vec[node]) findMinIndex(vec, getLs(node));
    else findMinIndex(vec, getRs(node));
}

vector<int> create_tree_of_segments(const vector<int> & base){


    int n =base.size();
    int power = 0;
    int amountOfVertices = 0;
    while (n > amountOfLeafs) {
        amountOfVertices += amountOfLeafs;
        amountOfLeafs = (amountOfLeafs << 1);
        power++;
    }
    amountOfVertices += amountOfLeafs;
    firstIndex = (1 << (power)) - 1;
//   int  lastIndex = firstIndex + n - 1;
    vector<int> vec(amountOfVertices, MAX);
    for (int i = firstIndex,j=0; j < base.size(); i++, j++) {
        vec[i] = base[j];
    }

    for (int i = firstIndex - 1; i >= 0; i--) {
        vec[i] = min(vec[2 * i + 1], vec[2 * i + 2]);
    }
    return vec;
}



int main() {

#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");

#endif
//    std::ofstream cout("log.out");

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    string input;
    index_start.resize(n);
    for (int i = 0; i < n; i++) {
        index_start[i] = input.size();
        string s;
        cin >> s;
//        cout << s << "\n";
        input += s + (char) (45 - i);
    }
    index_start.push_back(input.size());
//    cout << input << "\n";
    auto suffixArray = circular_suffix_array(input);
//    cout << "size=" << suffixArray.size() << "\n";
//    int t = 0;
//    for (auto c:suffixArray) {
//        cout <<t++ << ") "<< c << "-" << input.substr(c) <<"\n";
//    }
    auto prefixArray = prefix(suffixArray, input);
    auto tree = create_tree_of_segments(prefixArray);


    int flag = (1 << n) -1;
    vector<int> amount(n,0);
    int max_length = -1;
    int index_result = -1;
    for (int l = n, r = n-1; l < suffixArray.size(); l++){
        while(flag != 0  ){
            if (r == suffixArray.size()-1) break;
            r++;
            int k = suffixArray[r];
            int cur_index = get_number_of_string(suffixArray[r]);
            amount[cur_index]++;

            if ((flag & (1 << (cur_index)))!=0) flag = flag ^ (1 << (cur_index));
        }
        if (flag==0 ){
            int cur_max = findMin(tree, 0, l+1 , r+1, 0, amountOfLeafs);
            if (cur_max > max_length ){
                max_length = cur_max;
                index_result = suffixArray[l];
            } else {}
            int x = 10;
        }
        int l_index = suffixArray[l];
        int cur_l_string = get_number_of_string(l_index);
        amount[cur_l_string]--;
        if (amount[cur_l_string]==0)         flag |= (1 << (cur_l_string));
    }
    cout << input.substr(index_result, max_length);

    return 0;
}

int get_number_of_string(int l) {

    for (int i = 0; i < index_start.size()-1; i++){
        if (index_start[i+1] > l) return i;
    }
    return index_start.size()-1;
}
