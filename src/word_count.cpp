#include <cctype>
#include <iostream>

#include "word_count.hpp"

void to_lowercase(std::string& str) {
    for (char& c : str) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
}

std::set<std::string> load_stopwords(std::istream& stopwords) {
    std::set<std::string> result;
    std::string word;
    while (stopwords >> word) {
        to_lowercase(word);
        result.insert(word);
    }
    return result;
}

std::map<std::string, int> count_words(std::istream& document,
                                       const std::set<std::string>& stopwords) {
    std::map<std::string, int> counts;
    std::string word;
    while (document >> word) {
        to_lowercase(word);
        if (stopwords.count(word) == 0) {
            ++counts[word];
        }
    }
    return counts;
}

void output_word_counts(const std::map<std::string, int>& word_counts,
                        std::ostream& output) {
    for (const auto& entry : word_counts) {
        output << entry.first << ' ' << entry.second << '\n';
    }
}
