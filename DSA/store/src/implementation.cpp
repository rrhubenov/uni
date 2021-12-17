#include "../headers/interface.h"
#include <vector>
#include <iostream>
#include "../headers/llist.hh"
#include "../headers/queue.hh"


struct MyClient {
    int id;
    int arriveMinute;
    int bananas;
    int schweppes;
    int maxWaitTime;

    MyClient(int id, int am, int b, int s, int mwt):
        id(id), arriveMinute(am), bananas(b), schweppes(s), maxWaitTime(mwt) {}

    MyClient() {
        this->id = 0;
        this->arriveMinute = 0;
        this->bananas = 0;
        this->schweppes = 0;
        this->maxWaitTime = 0;
    }
};

struct MyStore : Store {
	ActionHandler *actionHandler = nullptr;

    struct Event {
        enum Type {
            CARRIVE, CLEAVE, DELIVERY, NONE
        };

        Type type;
        int id, min, bananas, schweppes, waitTime;

        Event(Type type, int id, int min, int bananas, int schweppes, int waitTime)
            : type(type), id(id), min(min), bananas(bananas), schweppes(schweppes), waitTime(waitTime) {}

        Event() {
            this->type = NONE;
            this->id = INT_MAX;
            this->min = INT_MAX;
            this->bananas = 0;
            this->schweppes = 0;
            this->waitTime = 0;
        }

        bool operator<(Event other) {
            return this->min < other.min;
        }

        bool operator>(Event other) {
            return this->min > other.min;
        }

        bool operator==(Event other) {
            return this->min == other.min;
        }

        bool operator>=(Event other) {
            return *this > other || *this == other;
        }

        bool operator<=(Event other) {
            return *this < other || *this == other;
        }

    };


    int wc;
    int bananas;
    int schweppes;
    LList<Event> clientsArrive;
    LList<Event> clientsLeave;
    LList<Event> deliveries;
    LList<MyClient> clientsWaiting;
    vector<bool> clientsInShop;

    int currMin;
    int bananasInDelivery;
    int schweppesInDelivery;

    MyStore() {
        this->clientsArrive = LList<Event>();
        this->clientsLeave = LList<Event>();
        this->deliveries = LList<Event>();
        this->clientsWaiting = LList<MyClient>();

        this->currMin = 0;
        this->bananasInDelivery = 0;
        this->schweppesInDelivery = 0;

        this->bananas = 0;
        this->schweppes = 0;
    }

	void setActionHandler(ActionHandler *handler) override {
		actionHandler = handler;
	}

	void init(int workerCount, int startBanana, int startSchweppes) override {
        this->wc = workerCount;	
        this->bananas = startBanana;
        this->schweppes = startSchweppes;
	}

	void addClients(const Client *clients, int count) override {
        for(int i = 0; i < count; ++i) {
            Client client = clients[i];
            Event clientArrive = Event(Event::CARRIVE, i, client.arriveMinute, client.banana, client.schweppes, client.maxWaitTime);
            Event clientLeaves = Event(Event::CLEAVE, i, client.arriveMinute + client.maxWaitTime, client.banana, client.schweppes, client.maxWaitTime);
            
            clientsArrive.insertBack(clientArrive);
            clientsLeave.insertSorted(clientLeaves);
            clientsInShop.push_back(false);
        }
	}

	void advanceTo(int minute) override {
		solution(minute);
	}

	virtual int getBanana() const {
		return bananas;
	}

	virtual int getSchweppes() const {
		return schweppes;
	}

    void solution(int toMin) {
        if(clientsLeave.isEmpty() && deliveries.isEmpty() && clientsArrive.isEmpty()) {
            return;
        }

        Event event = popNextEvent(toMin);

        if(event.type == Event::NONE) {
            return;
        }

        currMin = event.min;

        switch(event.type) {
            case Event::CARRIVE: {
                int bananasNeeded = 0;
                int schweppesNeeded = 0;

                if(bananas < event.bananas) {
                    bananasNeeded = event.bananas - bananas;
                }
                if(schweppes < event.schweppes) {
                    schweppesNeeded = event.schweppes - schweppes;
                }

                if(bananasNeeded == 0 && schweppesNeeded == 0) {
                    bananas -= event.bananas;
                    schweppes -= event.schweppes;
                    cout << event.id << " " << event.min << " " << event.bananas << " " << event.schweppes << endl;
                } else {
                    if(bananasNeeded > 0) {
                        if(bananasInDelivery < bananasNeeded) {
                            handleSendWorkersForBananas(bananasNeeded, event.id);
                        }
                    }
                    if(schweppesNeeded > 0) {
                        if(schweppesInDelivery < schweppesNeeded) {
                            handleSendWorkersForSchweppes(schweppesNeeded, event.id);
                        }
                    }

                    addClientToWaiting(MyClient(event.id, event.min, bananasNeeded, schweppesNeeded, event.waitTime));
                }

                break;
            }
            case Event::CLEAVE: {
                if(!clientsInShop[event.id])
                    break;

                int takenBananas = min(bananas, event.bananas);
                int takenSchweppes = min(schweppes, event.schweppes);

                if(actionHandler != nullptr) {
                    actionHandler->onClientDepart(event.id, event.min, takenBananas, takenSchweppes);
                }
                cout << event.id << " " << event.min << " " << takenBananas << " " << takenSchweppes << endl;

                Node<MyClient>* curr = clientsWaiting.head;
                int pos = 0;

                while(curr != nullptr) {
                    if(curr->data.id == event.id) {
                        clientsWaiting.remove(pos);
                        break;
                    }
                    pos++;
                    curr = curr->next;
                }

                bananas -= takenBananas;
                schweppes -= takenSchweppes;

                clientsInShop[event.id] = false;

                break;
            }
            case Event::DELIVERY: {
                bananas += event.bananas;
                schweppes += event.schweppes;
                bananasInDelivery -= event.bananas;
                schweppesInDelivery -= event.schweppes;

                //cout << "DELIVERY WITH ID: " << event.id << endl;

                for(int i = 0; i < event.bananas / 100; ++i) {
                    if(actionHandler != nullptr) {
                        actionHandler->onWorkerBack(0, ResourceType::banana);
                    }
                    cout << "D" << " " << event.min << " " << "banana" << endl;
                }
                for(int i = 0; i < event.schweppes / 100; ++i) {
                    if(actionHandler != nullptr) {
                        actionHandler->onWorkerBack(0, ResourceType::schweppes);
                    }
                    cout << "D" << " " << event.min << " " << "schweppes" << endl;
                }

                Node<MyClient>* curr = clientsWaiting.head;
                int pos = 0;

                while(curr != nullptr) {
                    if(curr->data.bananas <= bananas && curr->data.schweppes <= schweppes) {
                        if(actionHandler != nullptr) {
                            actionHandler->onClientDepart(curr->data.id, currMin, curr->data.bananas, curr->data.schweppes);
                        }
                        cout << curr->data.id << " " << currMin << " " << curr->data.bananas << " " << curr->data.schweppes << endl;
                        bananas -= curr->data.bananas;
                        schweppes -= curr->data.schweppes;
                        removeClientFromLeaving(curr->data.id);
                        clientsInShop[event.id] = false;

                        curr = curr->next;

                        clientsWaiting.remove(pos);
                    } else {
                        curr = curr->next;
                    }
                        pos++;
                }

                break;
            }
            default:
                break;
        }

        solution(toMin);
    }

    int min(int a, int b) {
        if(a <= b) {
            return a;
        } else {
            return b;
        }
    }

    enum Resource {
        BANANA, SCHWEPPES, NONE, BOTH
    };


    Event popNextEvent(int toMin) {
        Event next;

        if(!clientsArrive.isEmpty()) {
            next = clientsArrive.front();
        }
        if(!deliveries.isEmpty() && deliveries.front() < next) {
            next = deliveries.front();
        }
        if(!clientsLeave.isEmpty() && clientsLeave.front() < next) {
            next = clientsLeave.front();
        }

        if(next.min > toMin) {
            return Event();
        }

        switch(next.type) {
            case Event::CARRIVE:
                clientsArrive.removeFront();
                break;
            case Event::CLEAVE:
                clientsLeave.removeFront();
                break;
            case Event::DELIVERY:
                deliveries.removeFront();
                break;
            default:
                break;
        }

        return next;
    }

    void removeClientFromLeaving(int id) {
        Node<Event>* curr = clientsLeave.head;
        int pos = 0;

        while(curr != nullptr) {
            if(curr->data.id == id) {
                clientsLeave.remove(pos);
                break;
            }
            pos++;
            curr = curr->next;
        }
    }

    void addClientToWaiting(MyClient client) {
        clientsWaiting.insertBack(client);
        clientsInShop[client.id] = true;
    }

    void handleSendWorkersForSchweppes(int schweppes, int id) {
        int workersNeeded = (schweppes + 99) / 100;
        int workersToSend = min(workersNeeded, wc);

        deliveries.insertBack(Event(Event::DELIVERY, id, currMin + 60, 0, workersToSend * 100, 0));
        for(int i = 0; i < workersToSend; ++i) {
            cout << "W " << currMin << " " << "schweppes" << endl;
        }
        schweppesInDelivery += 100*workersToSend;
        wc -= workersToSend;

        if(actionHandler != nullptr) {
            actionHandler->onWorkerSend(currMin, ResourceType::schweppes);
        }
    }

    void handleSendWorkersForBananas(int bananas, int id) {
        int workersNeeded = (bananas + 99) / 100;
        int workersToSend = min(workersNeeded, wc);

        deliveries.insertBack(Event(Event::DELIVERY, id, currMin + 60, workersToSend * 100, 0, 0));
        for(int i = 0; i < workersToSend; ++i) {
            cout << "W " << currMin << " " << "banana" << endl;
        }
        bananasInDelivery += 100*workersToSend;
        wc -= workersToSend;
        
        if(actionHandler != nullptr) {
            actionHandler->onWorkerSend(currMin, ResourceType::banana);
        }
    }

};

Store *createStore() {
	return new MyStore();
}

