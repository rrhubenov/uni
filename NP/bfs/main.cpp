#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <future>
#include <vector>
#include <string>
#include <sstream>

int THRESHHOLD = 3000;

void swap(int* arr, int first, int second) {
    int temp = arr[first];
    arr[first] = arr[second];
    arr[second] = temp;
}

int _partition(int* arr, int l, int h) {
    int pivot = arr[h];
    int i = l - 1;
    for(int j = l; j < h; j++) {
        if(arr[j] < pivot) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, h);
    return i + 1;
}

void _sort(int* arr, int l, int h) {
    if(l < h) {
        int q = _partition(arr, l, h);
        if((h - l) <= THRESHHOLD) {
            _sort(arr, l, q - 1);
            _sort(arr, q + 1, h);
        } else {
            std::thread lower(&_sort, arr, l, q - 1);
            _sort(arr, q + 1, h);
            lower.join();
        }
    }
}

void quicksort_inplace(int* arr, int len) {
    _sort(arr, 0, len-1);
}

void qs() {

    int* arr = new int[1000000];

    for(int i = 0; i < 1000000; ++i) {
        arr[i] = rand() % 2000000;
    }

    auto start = std::chrono::high_resolution_clock::now();
    quicksort_inplace(arr, 1000000);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Time: " << duration.count() << std::endl;
    for(size_t i = 0; i < 20; ++i) {
        std::cout << arr[i] << std::endl;
    }
}

int main(int argc, char **argv) {
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << " <port number>" << std::endl;
        return 0;
    }

    int port = atoi(argv[1]);

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    int bind_value = bind(sock, (struct sockaddr*)&address, sizeof(address));
    if(bind_value < 0) {
        perror("Could not bind");
        return -1;
    }

    int listen_value = listen(sock, 1);
    if(listen_value < 0) {
        perror("Could not listen");
        return -2;
    }
    
    struct sockaddr_in remote_address;
    socklen_t remote_addrlen = sizeof(address);

    std::cout << "Waiting for new connection" << std::endl;
    int client_socket = accept(sock, (struct sockaddr*)&remote_address, &remote_addrlen);

    std::string client_ip = inet_ntoa(remote_address.sin_addr);
    int remote_port = ntohs(remote_address.sin_port);

    std::cout << "Accepted new client @ " << client_ip << ":" << remote_port << std::endl;

    int BUFFLEN = 1024;
    char buffer[BUFFLEN];

    std::vector<int> target;

    while(1) {
        memset(buffer, 0, BUFFLEN);
        int bytes_received = recv(client_socket, buffer, BUFFLEN-1, 0);
        buffer[BUFFLEN - 1] = '\0';
        if(bytes_received < 0) {
            perror("error receiving");
            return -3;
        }
        if(bytes_received == 0) {
            std::cout << "Client @ " << client_ip << ":" << remote_port << " has disconnected." << std::endl;
            break;
        }

        char* pch = strtok(buffer, " ");

        while(pch != NULL) {
            target.push_back(atoi(pch));
            pch = strtok(NULL, " ");
        }

        if(bytes_received < BUFFLEN - 1) {
            quicksort_inplace(target.data(), target.size());
            std::stringstream result;
            std::copy(target.begin(), target.end(), std::ostream_iterator<int>(result, " "));
            send(client_socket, result.str().c_str(), result.str().length(), 0);
            target.clear();
        }
    }

    std::cout << "Shutting down socket." << std::endl;
    shutdown(client_socket, SHUT_RDWR);

    return 0;
}


