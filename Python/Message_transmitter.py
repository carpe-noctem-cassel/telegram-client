#!/usr/bin/env python3
import time

import zmq
import sys
sys.path.append("/home/stefan/teamwork-ws/src/telegram-client/msg")
import capnp
import message_capnp


context = zmq.Context()
print("Connecting to hello world server...")
socket = context.socket(zmq.PUB)
socket.connect("tcp://localhost:5555")
# socket.bind("tcp://*:5555")

for request in range(10):
    print("Sending request {} ...".format(request))
    msg = message_capnp.Message.new_message()
    msg.chatId = 1
    msg.text = "hallo"
    socket.send_multipart([b"msg_sink", msg.to_bytes()])
    time.sleep(1.0)
    # message = socket.recv()
    # print("Received reply {} [ {} ]".format(request, message))
