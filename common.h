#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <thread>
#include <unordered_map>
#include <vector>

enum { ERROR = 1 };
constexpr size_t Interval = 15;
constexpr size_t BUFFER_SIZE = 20;

void execute(const char* str, const char* arg1, const char* arg2) {
    int child = fork();
    if (child < 0) {
        fprintf(stderr, "fork error: %s\n", strerror(errno));
        exit(ERROR);
    }
    if (child == 0) {
        execlp(str, str, arg1, arg2, NULL);
        fprintf(stderr, "execlp error: %s\n", strerror(errno));
        exit(ERROR);
    }
    int wstatus;
    waitpid(child, &wstatus, 0);
}

std::time_t getLastTimePoint() {
    std::time_t result = std::time(nullptr);
    return result / Interval;
}

std::string getOTP(std::vector<uint8_t>& bytes) {
    int offset = bytes[19] & 0xf;
    int code = (bytes[offset] & 0x7f) << 24;
    code |= (bytes[offset + 1] & 0xff) << 16;
    code |= (bytes[offset + 2] & 0xff) << 8;
    code |= (bytes[offset + 3] & 0xff);
    code &= 0x7fffffff;
    code %= 1000000;
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(6) << code;
    return ss.str();
}

std::string generateOTP(const std::string& secretKey,
                        const std::string& request) {
    std::vector<uint8_t> bytes(BUFFER_SIZE);
    execute("./hmac_sha1.py", secretKey.c_str(), request.c_str());
    std::ifstream input("./hash", std::ios::binary);
    input.read(reinterpret_cast<char*>(bytes.data()), BUFFER_SIZE);
    input.close();
    return getOTP(bytes);
}

#define TIME_OPTION "--time"
#define REQUEST_OPTION "--request"
#define RECURSION_OPTION "--recursion"
#define EVENT_OPTION "--event"
