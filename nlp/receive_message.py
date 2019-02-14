import zmq
import capnp

import message_capnp
import addressbook_capnp


class Server():

    def __init__(self, context, url):
        self.socket = context.socket(zmq.REP)
        self.socket.bind(url)
        self.running = False

    def run(self):
        self.running = True

        while self.running:
            encoded_msg = self.socket.recv()

            alice = addressbook_capnp.Person.from_bytes(encoded_msg)

            print(alice.name)

            #msg = message_capnp.Message.from_bytes(encoded_msg)

            #print(msg.text)

            #result = encoded_msg + b" received!"

            #print(result)

            #self.socket.send(result)


context = zmq.Context()
server = Server(context, "tcp://*:5555")
server.run()
