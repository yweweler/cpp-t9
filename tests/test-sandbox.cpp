#include "gtest/gtest.h"

TEST(basic_check, test_eq) {
    EXPECT_EQ(1, 0);
}

//        auto test = corpus.ktoc('0');
//        std::cout << "corpus.ktoc('0') = \"" << test << "\"" << std::endl;
//        test = corpus.ktoc('9');
//        std::cout << "corpus.ktoc('9') = \"" << test << "\"" << std::endl;
//        test = corpus.ktoc('*');
//        std::cout << "corpus.ktoc('*') = \"" << test << "\"" << std::endl;
//        test = corpus.ktoc('#');
//        std::cout << "corpus.ktoc('#') = \"" << test << "\"" << std::endl;
//        test = corpus.ktoc('}');
//        std::cout << "corpus.ktoc('}') = \"" << test << "\"" << std::endl;

//        auto test = corpus.ctok('0');
//        std::cout << "corpus.ctok('0') = \'" << test << "\'" << std::endl;
//        test = corpus.ctok('t');
//        std::cout << "corpus.ctok('t') = \'" << test << "\'" << std::endl;
//        test = corpus.ctok(' ');
//        std::cout << "corpus.ctok(' ') = \'" << test << "\'" << std::endl;
//        test = corpus.ctok('A');
//        std::cout << "corpus.ctok('A') = \'" << test << "\'" << std::endl;
//        test = corpus.ctok('@');
//        std::cout << "corpus.ctok('@') = \'" << test << "\'" << std::endl;

//        std::string test;
//        bool ret;
//        test = "123122*##";
//        ret = corpus.validate_t9_keys(test);
//        std::cout << "corpus.validate_t9_keys(" << test << ") => " << ret << std::endl;
//        test = "123122*##@";
//        ret = corpus.validate_t9_keys(test);
//        std::cout << "corpus.validate_t9_keys(" << test << ") => " << ret << std::endl;
//        test = "89";
//        ret = corpus.validate_t9_keys(test);
//        std::cout << "corpus.validate_t9_keys(" << test << ") => " << ret << std::endl;
//        test = "8";
//        ret = corpus.validate_t9_keys(test);
//        std::cout << "corpus.validate_t9_keys(" << test << ") => " << ret << std::endl;
//        test = "#";
//        ret = corpus.validate_t9_keys(test);
//        std::cout << "corpus.validate_t9_keys(" << test << ") => " << ret << std::endl;

//        std::string test;
//        bool ret;
//        test = "12312290";
//        ret = corpus.validate_corpus_symbols(test);
//        std::cout << "corpus.validate_corpus_symbols(" << test << ") => " << ret << std::endl;
//        test = "12aAselikfh";
//        ret = corpus.validate_corpus_symbols(test);
//        std::cout << "corpus.validate_corpus_symbols(" << test << ") => " << ret << std::endl;
//        test = "45,., 34 asda d";
//        ret = corpus.validate_corpus_symbols(test);
//        std::cout << "corpus.validate_corpus_symbols(" << test << ") => " << ret << std::endl;
//        test = "#";
//        ret = corpus.validate_corpus_symbols(test);
//        std::cout << "corpus.validate_corpus_symbols(" << test << ") => " << ret << std::endl;
//        test = "awd , awd:";
//        ret = corpus.validate_corpus_symbols(test);
//        std::cout << "corpus.validate_corpus_symbols(" << test << ") => " << ret << std::endl;

//        t9::t9_symbol_sequence seq1;
//        t9::t9_symbol_sequence seq2;
//        size_t ret;
//        seq1 = "123asdawd2";
//        seq2 = "123asdawd2";
//        ret = corpus.sequence_diff(seq1, seq2);
//        std::cout << "corpus.sequence_diff(" << seq1 << ", " << seq2 << ") => " << ret << std::endl;
//        seq1 = "123asdawd2";
//        seq2 = "123asdawd1";
//        ret = corpus.sequence_diff(seq1, seq2);
//        std::cout << "corpus.sequence_diff(" << seq1 << ", " << seq2 << ") => " << ret << std::endl;
//        seq1 = "";
//        seq2 = "";
//        ret = corpus.sequence_diff(seq1, seq2);
//        std::cout << "corpus.sequence_diff(" << seq1 << ", " << seq2 << ") => " << ret << std::endl;
//        seq1 = "  123";
//        seq2 = "1231 123";
//        ret = corpus.sequence_diff(seq1, seq2);
//        std::cout << "corpus.sequence_diff(" << seq1 << ", " << seq2 << ") => " << ret << std::endl;
