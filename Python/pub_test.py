#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import itertools
import sys
import time

import zmq

def main():
    if len (sys.argv) != 2:
        print('usage: publisher <bind-to>')
        sys.exit (1)

    bind_to = sys.argv[1]

    all_topics = [b'sports.general', b'sports.football', b'sports.basketball',
                  b'stocks.general', b'stocks.GOOG', b'stocks.AAPL',
                  b'weather']

    ctx = zmq.Context()
    s = ctx.socket(zmq.PUB)
    s.bind("tcp://*:5563")

    print("Starting broadcast on topics:")
    print("   %s" % all_topics)
    print("Hit Ctrl-C to stop broadcasting.")
    print("Waiting so subscriber sockets can connect...")
    print("")
    time.sleep(5.0)

    msg_counter = itertools.count()
    try:
        for topic in itertools.cycle(all_topics):
            msg_body = bytes(str(msg_counter.__next__()).encode())
            print('   Topic: %s, msg:%s' % (topic, msg_body))
            s.send_multipart([topic, msg_body])
            # short wait so we don't hog the cpu
            time.sleep(0.1)
    except KeyboardInterrupt:
        pass

    print("Waiting for message queues to flush...")
    time.sleep(0.5)
    print("Done.")

if __name__ == "__main__":
    main()