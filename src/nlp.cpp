#include <iostream>
#include <spacy/spacy.h>
#include <spacy/nlp.h>
#include <spacy/doc.h>
#include <spacy/token.h>


int main(int argc, char* argv[])
{
    Spacy::Spacy spacy;
    auto nlp = spacy.load("en");
    auto doc = nlp.parse("This is a sentence.");
    for (auto& token : doc.tokens())
        std::cout << token.text() << " [" << token.pos_() << "]\n";
    return 0;
}
