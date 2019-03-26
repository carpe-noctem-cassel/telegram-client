#!/usr/bin/env python3
import time
import zmq
import sys
import spacy
import os
from pathlib import Path

mypath = Path(os.getcwd()).joinpath("../msg").absolute()
sys.path.append(str(mypath))
import capnp
import message_capnp
import spacy


rcv_topic = ""
snd_topic = "msg_source"
context = zmq.Context()
socket_down = context.socket(zmq.SUB)
socket_up = context.socket(zmq.PUB)
socket_down.connect("tcp://127.0.0.1:5555")
# socket_down.bind("ipc:///@capnzero.ipc")
socket_down.setsockopt_string(zmq.SUBSCRIBE, rcv_topic)

# nlp initializations
nlp = spacy.load('de')

while True:
    print("Recieving . . .")
    message = socket_down.recv()
    # print(message)
    msg = message_capnp.Message.from_bytes(message)
    # print(msg)


    print(msg.text)

    # nlp stuff
    doc = nlp(msg.text)
    root = ""
    subj = ""
    obj = ""
    print("\x1B[33m" + msg.text + "\x1B[0m")
    for token in doc:
        print("\x1B[41m", token.text, "\x1B[0m is a \x1b[41m", spacy.explain(token.dep_), "({})".format(token.dep_),
              "\x1B[0m <--", token.head.text, spacy.explain(token.head.pos_), [child for child in token.children])
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
    print("\x1B[32mTRIPLET: {}:({} | {})\x1B[0m".format(root, subj, obj))
    print("\x1B[31m===========================================================================\x1B[0m")

