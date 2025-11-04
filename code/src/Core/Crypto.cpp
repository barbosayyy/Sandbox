#include "Crypto.h"
#include "Utils.h"
#include "smhasher/MurmurHash3.h"
#include <iomanip>
#include <sstream>
#include <random>

namespace Sb {
    const SbGUID Crypto::NewGUID() {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        SbGUID guid;
        guid.h1 = ((u64)gen()<< 32) ^ gen();
        guid.h2 = ((u64)gen()<< 32) ^ gen();
        return guid;
    };

    const SbGUID Crypto::GetGUIDFromHashedInput(const String& input, GUIDDomain domain) {
        String domainedInput = std::to_string(static_cast<int>(domain)) + ":" + std::string(input);
        SbGUID guid{};
        MurmurHash3_x64_128(domainedInput.data(), static_cast<int>(domainedInput.size()), 0xDEADBEEF, &guid);

        return guid;
    }

    String Crypto::GetStringFromGUID(const SbGUID& guid) {
        std::ostringstream oss;
        oss << std::hex << std::setfill('0')
        << std::setw(16) << guid.h1
        << std::setw(16) << guid.h2;
        
        return oss.str();
    }

    // TODO - Could also parse braced+dashed guid strings?
    SbGUID Crypto::GetGUIDFromString(const String& string) {
        if(string.size() != 32) {
            assert("Crypto: Invalid GUID string size");
        }
        SbGUID guid{};
        guid.h1 = StringParser::HexToU64(string.substr(0, 16));
        guid.h1 = StringParser::HexToU64(string.substr(0, 16));

        return guid;
    }
}