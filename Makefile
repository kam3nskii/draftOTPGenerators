FLAGS= -O2 -Wall -std=c++17 -fsanitize=undefined -fsanitize=address

all: draft/token base32/base service/service token/token

draft/token: draft/draftToken.cpp
	$(CXX) -o $@ $(FLAGS) $^

base32/base: base32/base32.cpp
	$(CXX) -o $@ $(FLAGS) $^

service/service: service/service.cpp
	$(CXX) -o $@ $(FLAGS) $^

token/token: token/token.cpp
	$(CXX) -o $@ $(FLAGS) $^

clean:
	rm draft/token
	rm base32/base
	rm token/token
	rm service/service
