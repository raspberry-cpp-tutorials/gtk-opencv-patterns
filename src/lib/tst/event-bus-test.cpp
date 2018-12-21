#include "event-bus.hpp"
#include "catch.hpp"

/** Any class can be used as an event. */
class AnyEvent {
public:
	AnyEvent(int id) {
		identity = id;
	}
	int getIdentity() {
		return identity;
	}
protected:
	int identity;
};

/** Let's have another event. */
class OtherEvent:public AnyEvent {
public:
	OtherEvent(int id):AnyEvent(id) {
		// Nothing to do.
	}
};

/** Any class can be a subscriber, as long as it
  * implements the ability to receive events. */
class SubscriberToAllEvents:public Subscriptor<AnyEvent>, public Subscriptor<OtherEvent> {
public:
	SubscriberToAllEvents(int id) {
		identityOfLastReceivedEvent = id;
	};
	void receive(AnyEvent event) override {
		identityOfLastReceivedEvent = event.getIdentity();
	}
	void receive(OtherEvent event) override {
		identityOfLastReceivedEvent = event.getIdentity();
	}
	int getIdentityOfLastReceivedEvent() {
		return identityOfLastReceivedEvent;
	}
	void setIdentityOfLastReceivedEvent(int id) {
		identityOfLastReceivedEvent = id;
	}
private:
	int identityOfLastReceivedEvent;
};

using namespace std::placeholders;
using namespace std;

SCENARIO("The Event Bus Service broadcasts to all subscribers of this event") {
	EventBus<AnyEvent> eventBus;

	GIVEN( "Two classes subscribed to the same event") {
		SubscriberToAllEvents subscriber1(10), subscriber2(20);
		eventBus.clear();
		eventBus.subscribe(&subscriber1);
		eventBus.subscribe(&subscriber2);

		WHEN( "When the event is fired") {
			eventBus.propagate(AnyEvent(1));
			THEN ( "All subscriptors are informed ") {
				REQUIRE( subscriber1.getIdentityOfLastReceivedEvent() == 1);
				REQUIRE( subscriber2.getIdentityOfLastReceivedEvent() == 1);
			}
		}
		
		WHEN( "One class unsubscribes") {
			eventBus.unsubscribe(&subscriber2);
			
			THEN ("It doesn't receive events any more") {
				eventBus.propagate(AnyEvent(2));
				REQUIRE( subscriber1.getIdentityOfLastReceivedEvent() == 2);
				REQUIRE( subscriber2.getIdentityOfLastReceivedEvent() == 20);
			}
		}
	}
}


SCENARIO("The Event Bus Service broatcasts only to subscribers of this event") {
	EventBus<AnyEvent> eventBus1;
	EventBus<OtherEvent> eventBus2;
	
	GIVEN( "Two classes subscribed to different event") {
		eventBus1.clear();
		eventBus2.clear();
		SubscriberToAllEvents subscriber1(10), subscriber2(20);
		eventBus1.subscribe(&subscriber1);
		eventBus2.subscribe(&subscriber2);
		
		WHEN( "When the event is fired") {
			eventBus1.propagate(AnyEvent(1));
			eventBus2.propagate(OtherEvent(2));

			THEN ( "Only subscribers to specific event are informed ") {
				REQUIRE( subscriber1.getIdentityOfLastReceivedEvent() == 1);
				REQUIRE( subscriber2.getIdentityOfLastReceivedEvent() == 2);
			}
		}
	}
}

SCENARIO("The Event Bus Service is a singleton") {
	EventBus<AnyEvent> eventBus1;
	EventBus<AnyEvent> eventBus2;
	
	GIVEN( "Two classes subscribed to same event using different instances of same event bus") {
		eventBus1.clear();
		eventBus2.clear();
		SubscriberToAllEvents subscriber1(10), subscriber2(20);
		eventBus1.subscribe(&subscriber1);
		eventBus2.subscribe(&subscriber2);
		
		WHEN( "When the event is fired") {
			eventBus1.propagate(AnyEvent(1));
			
			THEN ( "All subscriptors are informed") {
				REQUIRE( subscriber1.getIdentityOfLastReceivedEvent() == 1);
				REQUIRE( subscriber2.getIdentityOfLastReceivedEvent() == 1);
			}
		}
	}
}
