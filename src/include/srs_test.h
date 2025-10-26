#ifndef SRS_TEST_H
#define SRS_TEST_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

namespace SRS {
struct srs {
    std::string alphabet;
    std::vector<std::pair<std::string, std::string> > rules;
    srs(std::string, std::string);
    std::string rand_str(size_t, size_t) const;
};

std::ostream& operator<<(std::ostream&, const srs&);

struct fuzz_success {
    std::string src;
    std::string dest;
    std::vector<std::string> first_chain;
    std::vector<std::string> second_chain;
};

std::ostream& operator<<(std::ostream&, const fuzz_success&);

struct fuzz_failure {
    std::string src;
    std::string dest;
};

std::ostream& operator<<(std::ostream&, const fuzz_failure&);

struct fuzz_result {
    size_t success;
    size_t failure;
    std::vector<fuzz_success> examples;
    std::vector<fuzz_failure> examples_fail;
};

std::ostream& operator<<(std::ostream&, const fuzz_result&);

std::vector<std::string> all_possible_rewrites(const srs&, std::string);
std::vector<std::string> all_possible_rewrites_bidirectional(const srs&, std::string);
std::vector<std::string> random_chain(const srs&, std::string, size_t, size_t);

}

#endif // SRS_TEST_H