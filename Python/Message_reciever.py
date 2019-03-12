import time
import zmq
import sys
sys.path.append("/home/stefan/teamwork-ws/src/telegram-client/msg")
import capnp
import message_capnp

rcv_topic = "msg_sink"
snd_topic = "msg_source"
context = zmq.Context()
socket_down = context.socket(zmq.SUB)
socket_up = context.socket(zmq.PUB)
socket_down.bind("tcp://127.0.0.1:5555")
socket_down.setsockopt(zmq.SUBSCRIBE, rcv_topic.encode("ascii"))


while True:
    topic, message = socket_down.recv_multipart()
    msg = message_capnp.Message.from_bytes(message)
    print(msg.text)
    time.sleep(1)
    socket_up.send_multipart([snd_topic.encode("ascii"), b"World"])
