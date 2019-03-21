#!/usr/bin/env python3
import spacy, json
from spacy import displacy
nlp = spacy.load('en_core_web_sm')
commands = open("Commands.txt", "r")
result = {}
for command in commands:
    doc = nlp(command.strip("\n"))
    root = ""
    subj = ""
    obj = ""
    print("\x1B[33m" + command + "\x1B[0m")
    for token in doc:
        print("\x1B[41m", token.text, "\x1B[0m is a \x1b[41m", spacy.explain(token.dep_), "({})".format(token.dep_), "\x1B[0m <--", token.head.text, spacy.explain(token.head.pos_), [child for child in token.children])
        if token.dep_ in ["sb", "nsubj", "nsubjpass"]:
           subj = token.text
        elif token.dep_ == "ROOT" and token.pos_ == "VERB" and root == "":
            root = token.text
        elif token.dep_ in ["oa", "dobj", "pobj"] and obj == "":
            obj = token.text

    if root == "":
        root = doc[0].text

    print("\x1B[32m", doc.ents, "\x1B[0m")
    print("\x1B[34mROOT: " + root + "\x1B[0m")
    print("\x1B[34mSUBJECT: " + subj + "\x1B[0m")
    print("\x1B[34mOBJECT: " + obj + "\x1B[0m")
    print("\x1B[31m===========================================================================\x1B[0m")
