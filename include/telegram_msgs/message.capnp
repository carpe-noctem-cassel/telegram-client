@0xbbcab1e12c72fc7a;
using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("telegram_msgs");
using IDMsg = import "/capnzero/ID.capnp";

struct Message {
	timestamp @0 :UInt32;
	chatId @1 :Int64;
	userId @2 :Int32;
	messageId @3 :Int32;
	userName @4 :Text;
	firstName @5 :Text;
	lastName @6 :Text;
	languageCode @7 :Text;
	text @8 :Text;
	type @9 :UInt8;
}
