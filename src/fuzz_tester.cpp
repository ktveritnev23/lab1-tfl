#include "include/srs_test.h"

#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace SRS;
using namespace std;

static vector<string> build_forward_path(
        const unordered_map<string, pair<string,size_t>>& parent,
        const string& src,
        const string& meet)
{
    vector<string> p;
    string cur = meet;
    while (true) {
        p.push_back(cur);
        if (cur == src) break;               
        auto it = parent.find(cur);
        cur = it->second.first;             
    }
    reverse(p.begin(), p.end());        
    return p;
}


static vector<string> build_backward_path(
        const unordered_map<string, pair<string,size_t>>& parent,
        const string& dest,
        const string& meet)
{
    vector<string> p;
    string cur = meet;                       
    while (cur != dest) {
        auto it = parent.find(cur);
        
        cur = it->second.first;              
        p.push_back(cur);                    
    }
    // only forward path needs to be reversed
    return p;                                 
}


pair<bool, vector<string> > is_reachable_bidirectional(const srs& srs, string src, string dest, size_t max_depth = 60, size_t max_nodes = 2000000){
    if (src == dest)
        return {true, {src}};


    unordered_set<string> visitedF;
    unordered_set<string> visitedB;
    visitedF.insert(src);
    visitedB.insert(dest);

    size_t system_size = 0;
    
    unordered_map<string, pair<string, size_t> > parentF, parentB;

    struct Node {
        string str;
        size_t depth;
    };

    queue<Node> qF, qB;
    qF.push({src, 0});
    qB.push({dest, 0});

    while (!qF.empty() && !qB.empty() && system_size < max_nodes) {

        bool cur_dir = qF.size() <= qB.size();

        // balance the BFS
        queue<Node>& curQ = cur_dir ? qF : qB;
        unordered_set<string>& curVisited = cur_dir ? visitedF : visitedB;
        unordered_set<string>& otherVisited = cur_dir ? visitedB : visitedF;
        unordered_map<string, pair<string,size_t> >& curParent = cur_dir ? parentF : parentB;

        Node current = curQ.front();
        curQ.pop();

        if (current.depth >= max_depth)
            continue;

        const vector<string> succ_step = all_possible_rewrites_bidirectional(srs,current.str);

        for (size_t i = 0; i < succ_step.size(); i++) {
            const string& nxt = succ_step[i];
            system_size++;
            if (!curVisited.insert(nxt).second)
                continue;

            curParent[nxt] = {current.str, i};
            
            // meeting point of searching from two sides
            if (otherVisited.find(nxt) != otherVisited.end()) {
                vector<string> forward_path;
                vector<string> backward_path;

                if (cur_dir) {
                    forward_path  = build_forward_path(parentF, src, nxt);
                    backward_path = build_backward_path(parentB, dest, nxt);
                } else {
                    forward_path  = build_forward_path(parentF, src, nxt);
                    backward_path = build_backward_path(parentB, dest, nxt);
                }

                // concatenate
                forward_path.insert(forward_path.end(),
                                    backward_path.begin(),
                                    backward_path.end());

                return {true, forward_path};
            }

            curQ.push({nxt, current.depth + 1});
        }
    }
    return {false, {}};
}



fuzz_result fuzzer(const srs& t1, const srs& t2, 
                   size_t min_len, size_t max_len, 
                   size_t number_of_words = 1000, 
                   size_t min_steps = 1, size_t max_steps = 60) {
    size_t example_limit = 10;
    size_t success = 0, failure = 0;
    vector<fuzz_success> examples;
    vector<fuzz_failure> fails;
    vector<string> rewrite_chain;
    for(size_t i = 0; i < number_of_words; i++) {
        string src = t1.rand_str(min_len, max_len);
        
        rewrite_chain = random_chain(t1, src, min_steps, max_steps);

        string dest = rewrite_chain.back();

        pair<bool, vector<string> > test_line = is_reachable_bidirectional(t2, src, dest);
        if (test_line.first){
            success++;
            if (examples.size() < example_limit)
                examples.push_back(fuzz_success{src, dest,rewrite_chain,test_line.second});
        }
        else {

            failure++;
            if (fails.size() < example_limit)
                fails.push_back(fuzz_failure{src, dest});
        }
        
    }
    return fuzz_result{success, failure, examples, fails};
}



int main() {
    srand(time(0));
    const string alphabet = "ab";
    const size_t min_fuzz_length = 6;
    const size_t max_fuzz_length = 12;

    srs old_srs(alphabet, "../trs/trs.txt");
    srs new_srs(alphabet, "../trs/trs_triv.txt");
    // or you can also test T without baaabb -> epsilon against completed T'' (not trivial)
    srs srs_el(alphabet, "../trs/trs_epsilonless.txt");
    srs srs_comp(alphabet, "../trs/trs_completed.txt");

    // if some strings fail, raise limits
    fuzz_result result = fuzzer(old_srs, new_srs, min_fuzz_length, max_fuzz_length);

    fuzz_result result_el = fuzzer(srs_el, srs_comp, min_fuzz_length, max_fuzz_length);

    cout << result;

    cout << result_el
}