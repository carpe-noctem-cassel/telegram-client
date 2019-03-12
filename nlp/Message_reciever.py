import time
import zmq
import sys
import os
from pathlib import Path
mypath = Path(os.getcwd()).joinpath("../msg").absolute()
sys.path.append(str(mypath))
import capnp
import message_capnp

rcv_topic = "voice"
snd_topic = "msg_source"
context = zmq.Context()
socket_down = context.socket(zmq.SUB)
socket_up = context.socket(zmq.PUB)
socket_down.bind("tcp://127.0.0.1:5555")
socket_down.setsockopt(zmq.SUBSCRIBE, rcv_topic.encode("ascii"))


while True:
    topic, message = socket_down.recv()
    msg = message_capnp.Message.from_bytes(message)
    print(msg.text)
    time.sleep(1)
    socket_up.send_multipart([snd_topic.encode("ascii"), b"World"])
