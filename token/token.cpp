#include "../common.h"

void exitOnError() {
    std::cout << "Use: token " TIME_OPTION "\n"
                 "     token " REQUEST_OPTION "\n"
                 "     token " RECURSION_OPTION "\n"
                 "     token " EVENT_OPTION "\n";
    exit(ERROR);
}

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

    std::string secretKey;
    std::cout << "Secret key: ";
    std::cin >> secretKey;

    if (argument == TIME_OPTION) {
        auto previousTimePoint = getLastTimePoint();
        std::cout << generateOTP(secretKey, std::to_string(previousTimePoint)) << "\n";
        while (1) {
            auto timePoint = getLastTimePoint();
            if (timePoint == previousTimePoint) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            } else {
                previousTimePoint = timePoint;
                std::cout << generateOTP(secretKey, std::to_string(timePoint)) << "\n";
            }
        }
    } else if (argument == REQUEST_OPTION) {
        std::string request;
        do {
            std::cout << "Request: ";
            std::cin >> request;
            std::cout << generateOTP(secretKey, request) << "\n";
        } while (1);
    } else if (argument == RECURSION_OPTION) {
        std::string init;
        std::cout << "Init code: ";
        std::cin >> init;
        do {
            init = generateOTP(secretKey, init);
            std::cout << init << "\n";
            for (char ch = '\0'; ch != 'y'; ) {
                std::cout << "Get new code (y): ";
                std::cin >> ch;
            }
        } while (1);
    } else if (argument == EVENT_OPTION) {
        uint64_t counter{0};
        do {
            std::cout << generateOTP(secretKey, std::to_string(counter++)) << "\n";
            for (char ch = '\0'; ch != 'y'; ) {
                std::cout << "Get new code (y): ";
                std::cin >> ch;
            }
        } while (1);
    }
}
