#define INV_PTR size_t(*)(const string&)
#define INV_PAIR pair<size_t, size_t>(*)(const string&)
#include "include/srs_test.h"

using namespace SRS;
using namespace std;

// длина
size_t len_adapter(const string& s) {
    return s.size();
}

// сумма весов a и b (a/b от 1/3 до 1)
size_t weights(const string& s) {
    size_t cnt = 0;
    const size_t char_w[] = {1,3};
    for(char c : s) {
        cnt += (size_t)(c=='a')*char_w[0];
        cnt += (size_t)(c=='b')*char_w[1];
    }
    return cnt;
}


// Лексикографическая пара из (длины, суммы весов {a,b} -> {1,2})
pair<size_t, size_t> len_and_weight(const string& s) {
    pair<size_t, size_t> cnt = {0,0};
    for(char c : s) {
        cnt.first++;
        cnt.second+=(1*(c=='a'))+(2*(c=='b'));
    }
    return cnt;
}

struct invariant_test {
    size_t succ = 0;
    size_t fail = 0;
    vector<string> examples;
};

ostream& operator<<(ostream& os, const invariant_test& i) {
    os << "Successes: " << i.succ << '\n';
    os << "Failures: " << i.fail << '\n';
    if(i.fail) {
        os << "Examples of failures: \n";
        for (const string& s : i.examples) {
            os << s << '\n';
        }
    } else {
        os << "Test successful\n";
    }
    return os;

}

invariant_test invariant_tester(const srs& s, 
                                const vector<pair<INV_PTR, string> >& invariants, 
                                const vector<pair<INV_PAIR,string> >& invariant_pairs, 
                                size_t min_length, size_t max_length, size_t num_words = 1000) {
    size_t min_steps = 1, max_steps = 15;
    size_t max_examples = 20;
    bool failed = false;
    //vector<string> examples;
    invariant_test result;
    for(size_t i = 0; i < num_words; i++) {
        string src = s.rand_str(min_length, max_length);
        vector<string> dest = random_chain(s, src, min_steps, max_steps);

        vector<size_t> first_ivs(invariants.size());

        vector<pair<size_t, size_t> > first_pairs(invariant_pairs.size());

        for(size_t j = 0; j < invariants.size(); j++){
            first_ivs[j] = invariants[j].first(src);
        }

        for(size_t j = 0; j < invariant_pairs.size(); j++){
            first_pairs[j] = invariant_pairs[j].first(src);
        }

        failed = false;

        string prev = src;

        for(const auto& a : dest) {
            for(size_t j = 0; j < invariants.size(); j++){
                size_t curr_invar = invariants[j].first(a);
                if(curr_invar > first_ivs[j]) {
                    result.fail++;
                    failed = true;
                    if(result.examples.size() < max_examples){
                        ostringstream answer;
                        answer << prev << " -> " << a << ": "
                               << '(' << invariants[j].second << ") " 
                               << first_ivs[j] << " < " << curr_invar;
                        result.examples.push_back(answer.str());
                    }
                    break;
                }
                
                first_ivs[j] = curr_invar;
            }
            if (failed) break;
            for(size_t j = 0; j < invariant_pairs.size(); j++){
                pair<size_t, size_t> curr_pair = invariant_pairs[j].first(a);
                if (curr_pair > first_pairs[j]){
                    result.fail++;
                    failed = true;
                    if(result.examples.size() < max_examples){
                        ostringstream answer;
                        answer << prev << " -> " << a << ": "
                               << '(' << invariants[j].second << ") " 
                               << '(' << first_pairs[j].first << ',' << first_pairs[j].second << ')'
                               << " < " << '(' << curr_pair.first << ',' << curr_pair.second << ')';
                        result.examples.push_back(answer.str());
                    }
                }

                first_pairs[j] = curr_pair;
            }

            prev = a;
        }
        if(!failed) result.succ++;
    }
    return result;
}

int main() {
    srand(time(0));
    const string alphabet = "ab";
    const size_t min_length = 6;
    const size_t max_length = 12;

    // terminable version of T with flipped rule
    srs old_srs(alphabet, "../trs/trs_eps.txt");
    srs new_srs(alphabet, "../trs/trs_triv.txt");


    vector<pair<INV_PTR, string> > invariants = {
        {len_adapter, "length"},
        {weights, "sum of weights {a,b} -> {1,3}"},
    };

    vector<pair<INV_PAIR, string> > invariant_pairs = {
        {len_and_weight, "pair of |w| and sum of weights {a,b} -> {1,2}"},
    };

    invariant_test result_old = invariant_tester(old_srs, invariants, invariant_pairs, min_length, max_length);
    invariant_test result_new = invariant_tester(new_srs, invariants, invariant_pairs, min_length, max_length);


    cout << "SRS T: " << endl;
    cout << result_old;

    cout << "SRS T': " << endl;
    cout << result_new;
}