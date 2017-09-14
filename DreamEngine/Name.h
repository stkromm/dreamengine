#pragma once

class Name {
private:
	const char* string;
	const int hash;
	const int size;
public:
	constexpr int generateHash(const char* val, int size) {
		return 0;
	}
	constexpr Name(const char* val, int size) : size(size), string(val), hash(generateHash(val, size)) {};

	bool operator==(const Name& other) const {
		return other.hash == hash;
	}
};