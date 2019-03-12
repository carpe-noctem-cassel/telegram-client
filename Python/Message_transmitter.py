import zmq
import capnp
import test_capnp

context = zmq.Context()
print("Connecting to hello world server...")
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")
for request in range(10):
    print("Sending request %s ..." % request)
    msg = test_capnp.Test.new_message()
    msg.id = 1
    msg.text = "hallo"
    socket.send(msg.to_bytes())
    message = socket.recv()
    print("Received reply %s [ %s ]" % (request, message))