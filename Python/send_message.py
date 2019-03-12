import zmq
import capnp

import message_capnp
import addressbook_capnp


class Client():
    
    def __init__(self, context, url):
        self.socket = context.socket(zmq.REQ)
        self.socket.connect(url)
    
    def send(self, message):
        self.socket.send(message)


context = zmq.Context()
client = Client(context, "tcp://localhost:5555")
#msg = message_capnp.Message.new_message()
#msg.firstName = "Stefan"
#msg.text = "Piep"
#encoded_msg = msg.to_bytes()
person = addressbook_capnp.Person.new_message()
person.name = 'alice'
msg = person.to_bytes()
client.send(msg) #encoded_msg)

