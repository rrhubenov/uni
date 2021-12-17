#include "./src/implementation.cpp"

#define TESTING
#ifdef TESTING
#define CATCH_CONFIG_MAIN
#include "./headers/catch.hpp"
#include "./tests/tests.cpp"
#else


int main() {
    int wc, cc;
    cin >> wc >> cc;

    MyStore ms = MyStore();

    Client* clients = new Client[cc];

    for(unsigned i = 0; i < cc; ++i) {
        int arrives, waits, bananas, schw;
        cin >> arrives >> bananas >> schw >> waits;

        clients[i] = Client{arrives, bananas, schw, waits};
    }

    ms.addClients(clients, 4);

    ms.init(wc, 0, 0);
    ms.advanceTo(INT_MAX);

    delete[] clients;

    return 0;
}

#endif
