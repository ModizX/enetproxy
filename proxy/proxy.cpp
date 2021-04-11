#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include "enet/include/enet.h"
#include "http.h"
#include "server.h"
#include "gt.hpp"

server* g_server = new server();

int main() {
#ifdef _WIN32
    SetConsoleTitleA("Proxy made by Modiz");
#endif
    printf("Enet proxy by Modiz And King\n");

    std::ifstream vr;
    vr.open("version.txt");
    if (!vr) {
    	printf("version.txt not found, creating...\n");
        std::ofstream vw;
        vw.open("version.txt");
        vw << gt::version;
        vw.close();
        printf("version.txt has been created!\n");
    }
    vr >> gt::version;
    vr.close();

    std::thread http(http::run, "127.0.0.1", "17191");
    http.detach();
    printf("Server is running.\n");

    enet_initialize();
    if (g_server->start()) {
        printf("Server & client proxy is running.\n");
        while (true) {
            g_server->poll();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }   
    else
        printf("Failed to start server or proxy.\n");
}
