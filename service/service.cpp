#include "../common.h"

void exitOnError() {
    std::cout << "Use: service " TIME_OPTION "\n"
                 "     service " REQUEST_OPTION "\n"
                 "     service " RECURSION_OPTION "\n"
                 "     service " EVENT_OPTION "\n";
    exit(ERROR);
}

struct User {
    std::string password;
    std::string secretKey;
    std::string initCode;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        exitOnError();
    }

    std::string argument(argv[1]);
    if (argument != TIME_OPTION &&
        argument != REQUEST_OPTION &&
        argument != RECURSION_OPTION &&
        argument != EVENT_OPTION) {
        exitOnError();
    }

    std::unordered_map<std::string, User> dataBase;
    dataBase["admin"] = {"AdMiN", "QwertY123", "112233"};

    while(1) {
        std::cout << "\n\nNew round of authentication\n";
        std::string str;
        std::cout << "login: ";
        std::cin >> str;
        auto user = dataBase.find(str);
        if (user == dataBase.end()) {
            std::cout << "Wrong login!\n";
            continue;
        }
        std::cout << "password: ";
        std::cin >> str;
        if (user->second.password != str) {
            std::cout << "Wrong password!\n";
            continue;
        }

        if (argument == TIME_OPTION) {
            std::cout << "OTP key: ";
            std::cin >> str;
            auto timePoint = getLastTimePoint();
            if (str == generateOTP(user->second.secretKey, std::to_string(timePoint))) {
                std::cout << "Access granted\n";
            } else {
                std::cout << "Access denied\n";
            }
        } else if (argument == REQUEST_OPTION) {
            std::random_device rd;
            std::mt19937 g(rd());
            std::uniform_int_distribution<> a(33, 126);
            std::string request;
            for (size_t i = 0; i < 10; ++i) {
                request.push_back(static_cast<char>(a(g)));
            }

            std::cout << "OTP key for " << request << " : ";
            std::cin >> str;
            if (str == generateOTP(user->second.secretKey, request)) {
                std::cout << "Access granted\n";
            } else {
                std::cout << "Access denied\n";
            }
        } else if (argument == RECURSION_OPTION) {
            std::cout << "OTP key: ";
            std::cin >> str;
            std::string tmp = generateOTP(user->second.secretKey, user->second.initCode);
            if (str == tmp) {
                user->second.initCode = tmp;
                std::cout << "Access granted\n";
            } else {
                std::cout << "Access denied\n";
            }
        } else if (argument == EVENT_OPTION) {
            static uint64_t counter{0};
            std::cout << "OTP key: ";
            std::cin >> str;
            if (str == generateOTP(user->second.secretKey, std::to_string(counter++))) {
                std::cout << "Access granted\n";
            } else {
                std::cout << "Access denied\n";
            }
        }
    }
}
