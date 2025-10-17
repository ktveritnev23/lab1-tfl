#include "../include/srs_test.h"

namespace SRS {

srs::srs(std::string alphabet, std::string filename) : alphabet(alphabet){
    std::ifstream input_file(filename);
        std::string current_line;
        if (input_file.is_open()) {
            while (std::getline(input_file,current_line)) {
                std::string from, to;
                std::istringstream splitter(current_line);
                splitter >> from >> to;
                
                rules.emplace_back(from, to);
            }
        }
        input_file.close();
}

std::string srs::rand_str(size_t min_len, size_t max_len) const {
    size_t random_length = min_len + rand() % (max_len - min_len + 1);
    size_t alphabet_length = alphabet.size();
    std::string s(random_length, '\0');
    for (auto& c : s) c = alphabet[rand() % alphabet_length];
    return s;
}

std::ostream& operator<<(std::ostream& os, const srs& s) {
    os << "Alphabet: " << "{ ";
    for (const char& letter : s.alphabet)
        os << letter << ' ';
    os << "}";
    os << "\nRules:\n";
    for (const auto& rule : s.rules)
        os << rule.first << " -> " << (rule.second.empty() ? "ε" : rule.second) << '\n';
    return os;
}

std::ostream& operator<<(std::ostream& os, const fuzz_success& f) {
    os << "{";
    os << "\n\tsource: " << f.src;
    os << "\n\tdestination: " << f.dest;
    os << "\n\toriginal chain: ";
    for (auto it = f.first_chain.begin(); it != f.first_chain.end(); it++) {
        if (it != f.first_chain.begin()) os << " -> ";
        os << *it;
    }
    os << "\n\talternative chain: ";
    for (auto it = f.second_chain.begin(); it != f.second_chain.end(); it++) {
        if (it != f.second_chain.begin()) os << " -> ";
        os << *it;
    }
    os << "\n}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const fuzz_failure& f) {
    os << "{";
    os << "\n\tsource: " << f.src;
    os << "\n\tdestination: " << f.dest;
    os << "\n}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const fuzz_result& f) {
    os << "Successes: " << f.success;
    os << "\nFailures: " << f.failure;
    os << "\nExamples of successful rewritings: \n";
    for (const fuzz_success& ff : f.examples) {
        os << ff << '\n';
    }
    os << "\nExamples of failed rewritings: \n";
    for (const fuzz_failure& ff : f.examples_fail) {
        os << ff << '\n';
    }
    return os;
}

std::vector<std::string> all_possible_rewrites(const srs& srs, std::string input) {
    std::vector<std::string> result;
    const size_t start_pos = 0;

    for (const auto& rule : srs.rules) {
        size_t current_pos = input.find(rule.first, start_pos);
        size_t lhs_len = rule.first.size();
        while (current_pos != std::string::npos) {
            result.push_back(input.substr(0, current_pos) + rule.second + input.substr(current_pos+lhs_len));
            current_pos = input.find(rule.first, current_pos+1);
        }
    }
    return result;
}

std::vector<std::string> all_possible_rewrites_bidirectional(const srs& srs, std::string input) {
    std::vector<std::string> result;
    const size_t start_pos = 0;

    for (const auto& rule : srs.rules) {
        size_t current_pos = input.find(rule.first, start_pos);
        size_t lhs_len = rule.first.size();
        while (current_pos != std::string::npos) {
            result.push_back(input.substr(0, current_pos) + rule.second + input.substr(current_pos+lhs_len));
            current_pos = input.find(rule.first, current_pos+1);
        }
    }

    for (const auto& rule : srs.rules) {
        size_t current_pos = input.find(rule.second, start_pos);
        size_t lhs_len = rule.second.size();
        while (current_pos != std::string::npos) {
            result.push_back(input.substr(0, current_pos) + rule.first + input.substr(current_pos+lhs_len));
            current_pos = input.find(rule.second, current_pos+1);
        }
    }
    return result;
}

std::vector<std::string> random_chain(const srs& srs, std::string input, size_t min_steps, size_t max_steps) {
    std::vector<std::string> chain = {input};
    size_t random_num_rules = min_steps + rand() % (max_steps - min_steps + 1);
    std::string output;
    for(size_t i = 0; i < random_num_rules; i++) {
        std::vector<std::string> next_steps = all_possible_rewrites(srs,chain.back());
        if (next_steps.empty())
            break;
        chain.push_back(next_steps[rand() % next_steps.size()]);
    }
    return chain;
}



}