import zmq
import capnp
import message_capnp

context = zmq.Context()
socket = context.socket(zmq.SUB)
socket.connect("tcp://224.0.0.2:5555")
socket.setsockopt(zmq.SUBSCRIBE, b"tgr")

while True:
    message = socket.recv()
    msg = message_capnp.Message.from_bytes(message)
    print(msg.text)
