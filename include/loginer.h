#include "theNextThread.h"
#include "json.hpp"
#include <string>
namespace theNextChater {
using ::std::string;
class loginer {
    loginer(string nickname);
    virtual ~loginer(){}
private:
    ::theNextSocket::theNextThread check;
    ::theNextSocket::theNextThread accept;
};
}