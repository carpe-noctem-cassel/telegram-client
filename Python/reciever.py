import time
import zmq
import capnp
import test_capnp

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

while True:
    message = socket.recv()
    msg = test_capnp.Test.from_bytes(message)
    print(msg.text)
    time.sleep(1)
    socket.send(b"World")
