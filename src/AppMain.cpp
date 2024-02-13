//
// Created by mctrivia on 25/01/24.
// This class was created to provide a single point of getting classes that should
// have a single instance throughout the app
//

#include "AppMain.h"
#include "Log.h"

using namespace std;




AppMain* AppMain::_pinstance = nullptr;
mutex AppMain::_mutex;

AppMain* AppMain::GetInstance() {
    lock_guard<mutex> lock(_mutex);
    if (_pinstance == nullptr) {
        _pinstance = new AppMain();
    }
    return _pinstance;
}




void AppMain::setDatabase(Database* db) {
    //save database location
    _db = db;
}
Database* AppMain::getDatabase() {
    if (_db == nullptr) {
        Log* log = Log::GetInstance();
        log->addMessage("Tried to get Database without first loading", Log::CRITICAL);
        throw runtime_error("Not available");
    }
    return _db;
}

void AppMain::setIPFS(IPFS* ipfs) {
    //save database location
    _ipfs = ipfs;
}
IPFS* AppMain::getIPFS() {
    if (_ipfs == nullptr) {
        Log* log = Log::GetInstance();
        log->addMessage("Tried to get IPFS without first loading", Log::CRITICAL);
        throw runtime_error("Not available");
    }
    return _ipfs;
}
void AppMain::setDigiByteCore(DigiByteCore* dgb) {
    //save database location
    _dgb = dgb;
}
DigiByteCore* AppMain::getDigiByteCore() {
    if (_dgb == nullptr) {
        Log* log = Log::GetInstance();
        log->addMessage("Tried to get DigiByte Core without first loading", Log::CRITICAL);
        throw runtime_error("Not available");
    }
    //todo add check that wallet is connected
    return _dgb;
}
bool AppMain::isDigiByteCoreSet() {
    return (_dgb != nullptr);
}

/**
 * Called just before the objects stored in this object go out of scope
 */
void AppMain::reset() {
    _ipfs = nullptr;
    _dgb = nullptr;
    _db = nullptr;
}
void AppMain::setPermanentStoragePoolList(PermanentStoragePoolList* psp) {
    _psp = psp;
}
PermanentStoragePoolList* AppMain::getPermanentStoragePoolList() {
    if (_psp == nullptr) {
        Log* log = Log::GetInstance();
        log->addMessage("Tried to get Permanent Storage Pool List without first loading", Log::CRITICAL);
        throw runtime_error("Not available");
    }
    return _psp;
}
