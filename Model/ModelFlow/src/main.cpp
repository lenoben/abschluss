/**
 * @file main.cpp
 * @author John Obi (johnobi2003@gmail.com)
 * @brief Testing and configuring cmake for this directory
 * @version 0.1
 * @date 2024-01-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <mlpack.hpp>
using namespace mlpack;
using namespace mlpack::data;

int main()
{
    /**
     * @brief Corpus is a collection or vector of strings to be used
     * 
     */
    std::vector<std::string> corpus = {
        "This is document 1.",
        "Another document for testing.",
        "Final document.",
        "Final document for testing",
        "This is document 1.",
        "Another document for testing Final document.",
        "The quick brown fox jumps over the lazy dog.",
        "Jinxed wizards pluck ivy from the big quilt.",
        "Crazy Fredrick bought many very exquisite opal jewels.",
        "We promptly judged antique ivory buckles for the next prize.",
        "A mad boxer shot a quick, gloved jab to the jaw of his dizzy opponent.",
        "Jaded zombies acted quaintly but kept driving their oxen forward.",
        "The job requires extra pluck and zeal from every young wage earner.",
        "Mr. Jock, TV quiz PhD., bags few lynx.",
        "Two driven jocks help fax my big quiz.",
        "Waltz, nymph, for quick jigs vex Bud."};

    /// Define the tokenizer type (char tokenizer in this case)
    using TokenizerType = CharExtract;

    /**
     * @brief A variable of TfIdf encoding policy
     * 
     */
    StringEncoding<TfIdfEncodingPolicy, StringEncodingDictionary<int>> encoder;

    /**
     * @brief an arma matrix that will store the encoded data matrix
     * 
     */
    arma::mat encodedData;

    encoder.Encode(corpus, encodedData, TokenizerType());

    std::cout << encodedData << std::endl;
    std::cout << encodedData.n_cols << std::endl;
    std::cout << encodedData.n_rows << std::endl;

    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "----NEW STRİNG CORPUS FROM NEW PREDİCT---" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    /**
     * @brief A new collection of string to be vectorize
     * 
     */
    std::vector<std::string> corpus2 = {"Final document."};

    /**
     * @brief arma matrix to collect the matrix made from vectorizing the new corpus
     * 
     */
    arma::mat encodedData2;
    
    encoder.Encode(corpus2, encodedData2, TokenizerType());

    std::cout << encodedData2 << std::endl;
    std::cout << encodedData2.n_cols << std::endl;
    std::cout << encodedData2.n_rows << std::endl;

    return 0;
}