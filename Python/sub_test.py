#!/usr/bin/env python3
import sys
import time
import zmq
import numpy


def main():
    if len (sys.argv) < 2:
        print('usage: subscriber <connect_to> [topic topic ...]')
        sys.exit (1)

    topics = sys.argv[2:]

    ctx = zmq.Context()
    s = ctx.socket(zmq.SUB)
    s.connect("tcp://localhost:5563")

    # manage subscriptions
    if not topics:
        print("Receiving messages on ALL topics...")
        s.setsockopt(zmq.SUBSCRIBE,'')
    else:
        print("Receiving messages on topics: %s ..." % topics)
        for t in topics:
            s.setsockopt(zmq.SUBSCRIBE,t.encode("ascii"))
    try:
        while True:
            topic, msg = s.recv_multipart()
            print('   Topic: %s, msg:%s' % (topic, msg))
    except KeyboardInterrupt:
        pass
    print("Done.")


if __name__ == "__main__":
    main()
