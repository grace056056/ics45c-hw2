// ------------------------- Your tests - student_gtests.cpp ----------------------------- //
// Your own GoogleTest suite for the word_count module. It is graded: the autograder runs it
// against a correct implementation and against several with one bug each. A test is worth
// something only when it passes on the correct implementation and fails on a broken one, so a
// test that always fails (or that tests nothing) earns nothing.
//
// Two examples are given. Add tests of your own for to_lowercase, load_stopwords, count_words
// and output_word_counts, and for the edges: an empty document, a document that is all stop
// words, stop words written in mixed case, and the same word in several cases.
// --------------------------------------------------------------------------------------- //

#include <gtest/gtest.h>

#include <sstream>

#include "word_count.hpp"

TEST(WordCountTests, StopwordsAreLoadedCaseInsensitively) {
    std::stringstream stopwords{"The OVER\n"};
    const auto loaded = load_stopwords(stopwords);
    EXPECT_TRUE(loaded.contains("the"));
    EXPECT_TRUE(loaded.contains("over"));
}

TEST(WordCountTests, WordsAreCountedCaseInsensitively) {
    std::stringstream document{"Apple apple APPLE pear"};
    const auto counts = count_words(document, {});
    EXPECT_EQ(counts.at("apple"), 3);
    EXPECT_EQ(counts.at("pear"), 1);
}

// ADD YOUR TESTS HERE:

TEST(StudentWordCount, ToLowercase) {
    std::string s = "HeLLo";
    to_lowercase(s);
    EXPECT_EQ(s, "hello");
}

TEST(StudentWordCount, LoadStopwordsLowercases) {
    std::istringstream in("The AND or");
    auto stops = load_stopwords(in);
    EXPECT_EQ(stops.size(), 3u);
    EXPECT_EQ(stops.count("the"), 1u);
    EXPECT_EQ(stops.count("and"), 1u);
    EXPECT_EQ(stops.count("or"), 1u);
}

TEST(StudentWordCount, CountIsCaseInsensitive) {
    std::istringstream doc("Apple apple APPLE banana");
    std::set<std::string> stops;
    auto counts = count_words(doc, stops);
    EXPECT_EQ(counts.size(), 2u);
    EXPECT_EQ(counts["apple"], 3);
    EXPECT_EQ(counts["banana"], 1);
}

TEST(StudentWordCount, StopwordsSkipped) {
    std::istringstream stop_in("THE");
    auto stops = load_stopwords(stop_in);
    std::istringstream doc("the cat The dog");
    auto counts = count_words(doc, stops);
    EXPECT_EQ(counts.size(), 2u);
    EXPECT_EQ(counts.count("the"), 0u);
    EXPECT_EQ(counts["cat"], 1);
}

TEST(StudentWordCount, EmptyDocument) {
    std::istringstream doc("");
    std::set<std::string> stops;
    EXPECT_TRUE(count_words(doc, stops).empty());
}

TEST(StudentWordCount, AllStopwords) {
    std::istringstream doc("a an a");
    std::set<std::string> stops{"a", "an"};
    EXPECT_TRUE(count_words(doc, stops).empty());
}

TEST(StudentWordCount, OutputFormat) {
    std::map<std::string, int> counts{{"zebra", 1}, {"apple", 7}};
    std::ostringstream out;
    output_word_counts(counts, out);
    EXPECT_EQ(out.str(), "apple 7\nzebra 1\n");
}

TEST(StudentWordCount, OutputEmpty) {
    std::map<std::string, int> counts;
    std::ostringstream out;
    output_word_counts(counts, out);
    EXPECT_EQ(out.str(), "");
}
