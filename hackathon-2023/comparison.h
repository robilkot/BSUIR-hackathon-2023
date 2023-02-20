#include <boost/python.hpp>
#include <iostream>
#include <string>

// This requires built Boost libraries and dll in the project folder.
// Python 3.9 and spaCy are also needed
// 
// TODO: rewrite using FastText library?
float meaningSimilarity(std::string sentence1, std::string sentence2)
{
    using namespace std;
    using namespace boost::python;

    object spacy = import("spacy");

    // Load the language model
    object nlp = spacy.attr("load")("en_core_web_sm");

    // Process the sentences
    object doc1 = nlp(sentence1);
    object doc2 = nlp(sentence2);

    // Compare using spaCy's similarity metric
    object similarity_obj = doc1.attr("similarity")(doc2);
    // Convert python object to float
    return extract<float>(similarity_obj);
}
