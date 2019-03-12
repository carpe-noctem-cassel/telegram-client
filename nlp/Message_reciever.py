import time
import zmq
import sys
import os
from pathlib import Path
mypath = Path(os.getcwd()).joinpath("../msg").absolute()
sys.path.append(str(mypath))
import capnp
import message_capnp

rcv_topic = ""
snd_topic = "msg_source"
context = zmq.Context()
socket_down = context.socket(zmq.SUB)
socket_up = context.socket(zmq.PUB)
socket_down.connect("tcp://127.0.0.1:5555")
# socket_down.bind("ipc:///@capnzero.ipc")
socket_down.setsockopt_string(zmq.SUBSCRIBE, rcv_topic)

while True:
    print("Recieving . . .")
    message = socket_down.recv()
    # print(message)
    msg = message_capnp.Message.from_bytes(message)
    print(msg)
    print(msg.text)
    socket_up.send(message)
