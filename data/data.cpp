#include "data.h"

#include <QReadWriteLock>

QReadWriteLock lock;

#ifdef WIN32
/* windows specific - mingw32 */
#define SHARED __attribute__((section(".shr"), shared))

char exp[Data::expX][Data::expY][Data::expZ] SHARED = {{"", "", ""}};

bool standing SHARED = false;
bool sitting SHARED = false;
bool kneeling SHARED = false;
bool prone SHARED = false;
bool stunned SHARED = false;
bool bleeding SHARED = false;
bool hidden SHARED = false;
bool invisible SHARED = false;
bool webbed SHARED = false;
bool joined SHARED = false;
bool dead SHARED = false;

char inventory[Data::inventoryX] SHARED = "";

char container[Data::containerX] SHARED = "";

char wieldRight[Data::wieldX] SHARED = "";
char wieldRightNoun[Data::wieldX] SHARED = "";
char wieldLeft[Data::wieldX] SHARED = "";
char wieldLeftNoun[Data::wieldX] SHARED = "";

int health SHARED = 0;
int concentration SHARED = 0;
int spirit SHARED = 0;
int fatigue SHARED = 0;

char roomTitle[Data::roomTitleX] SHARED = "";
char roomDescription[Data::roomDescriptionX] SHARED = "";
char roomObjects[Data::roomObjectsX] SHARED = "";
char roomPlayers[Data::roomPlayersX] SHARED = "";
char roomExits[Data::roomExitsX] SHARED = "";

int rt SHARED = 0;
#else
/* other platforms - gcc ??*/
char exp[Data::expX][Data::expY][Data::expZ] __attribute__((section(".SHARED")) = {{"", "", ""}};

bool standing __attribute__((section(".SHARED")) = false;
bool sitting __attribute__((section(".SHARED")) = false;
bool kneeling __attribute__((section(".SHARED")) = false;
bool prone __attribute__((section(".SHARED")) = false;
bool stunned __attribute__((section(".SHARED")) = false;
bool bleeding __attribute__((section(".SHARED")) = false;
bool hidden __attribute__((section(".SHARED")) = false;
bool invisible __attribute__((section(".SHARED")) = false;
bool webbed __attribute__((section(".SHARED")) = false;
bool joined __attribute__((section(".SHARED")) = false;
bool dead __attribute__((section(".SHARED")) = false;

char inventory[Data::inventoryX] __attribute__((section(".SHARED"))  = "";

char container[Data::containerX] __attribute__((section(".SHARED"))  = "";

char wieldRight[Data::wieldX] __attribute__((section(".SHARED"))  = "";
char wieldRightNoun[Data::wieldX] __attribute__((section(".SHARED"))  = "";
char wieldLeft[Data::wieldX] __attribute__((section(".SHARED"))  = "";
char wieldLeftNoun[Data::wieldX] __attribute__((section(".SHARED"))  = "";

int health __attribute__((section(".SHARED"))  = 0;
int concentration __attribute__((section(".SHARED"))  = 0;
int spirit __attribute__((section(".SHARED"))  = 0;
int fatigue __attribute__((section(".SHARED"))  = 0;

char roomTitle[Data::roomTitleX] __attribute__((section(".SHARED"))  = "";
char roomDescription[Data::roomDescriptionX] __attribute__((section(".SHARED"))  = "";
char roomObjects[Data::roomObjectsX] __attribute__((section(".SHARED"))  = "";
char roomPlayers[Data::roomPlayersX] __attribute__((section(".SHARED"))  = "";
char roomExits[Data::roomExitsX] __attribute__((section(".SHARED"))  = "";

int rt __attribute__((section(".SHARED"))  = 0;

#endif


/* exp */

extern "C" EXPORT_FUNCTION int getExpIndex(const char name[]) {
    size_t expSize = sizeof(exp) / sizeof(exp[0]);
    size_t nameSize = strlen(name);

    for(unsigned int i = 0; i < expSize; i++) {
        if(exp[i][0][0] == 0) {
            return -1;
        }
        for(unsigned int j = 0; j < nameSize; j++) {
            if(exp[i][0][j] != name[j]) {
                break;
            } else {
                if(j == nameSize - 1) {
                    return i;
                }
            }
        }
    }
    return -1;
}

int getLastFreeIndex() {
    size_t expSize = sizeof(exp) / sizeof(exp[0]);

    for(unsigned int i = 0; i < expSize; i++) {
        if(exp[i][0][0] == 0) {
            return i;
        }
    }
    return -1;
}

void setExp(int index, const char name[], const char rank[], const char state[]) {
    strcpy(exp[index][0], name);
    strcpy(exp[index][1], rank);
    strcpy(exp[index][2], state);
}

void removeExp(int index) {
    strcpy(exp[index][0], "");
    strcpy(exp[index][1], "");
    strcpy(exp[index][2], "");
}

extern "C" EXPORT_FUNCTION void addExpField(const char name[], const char rank[], const char state[]) {
    int index = getExpIndex(name);

    if(index == -1) {
        int free = getLastFreeIndex();
        if(free != -1) {
            setExp(free, name, rank, state);
        }
    } else {
        setExp(index, name, rank, state);
    }
}

extern "C" EXPORT_FUNCTION void removeExpField(const char name[]) {
    int index = getExpIndex(name);

    if(index != -1) {
        removeExp(index);
    }
}

extern "C" EXPORT_FUNCTION int getExpRank(int index) {
    QReadLocker locker(&lock);
    if(index >= 0 && index < Data::expX) {
        return atoi(exp[index][1]);
    }
    return 0;
}

extern "C" EXPORT_FUNCTION int getExpState(int index) {
    QReadLocker locker(&lock);
    if(index >= 0 && index < Data::expX) {
        return atoi(exp[index][2]);
    }
    return 0;
}

/* status getters/setters */

extern "C" EXPORT_FUNCTION bool getStanding() {
    QReadLocker locker(&lock);
    return standing;
}

extern "C" EXPORT_FUNCTION void setStanding(bool _standing) {
    standing = _standing;
}

extern "C" EXPORT_FUNCTION bool getSitting() {
    QReadLocker locker(&lock);
    return sitting;
}

extern "C" EXPORT_FUNCTION void setSitting(bool _sitting) {
    sitting = _sitting;
}

extern "C" EXPORT_FUNCTION bool getKneeling() {
    QReadLocker locker(&lock);
    return kneeling;
}

extern "C" EXPORT_FUNCTION void setKneeling(bool _kneeling) {
    kneeling = _kneeling;
}

extern "C" EXPORT_FUNCTION bool getProne() {
    QReadLocker locker(&lock);
    return prone;
}

extern "C" EXPORT_FUNCTION void setProne(bool _prone) {
    prone = _prone;
}

extern "C" EXPORT_FUNCTION bool getStunned() {
    QReadLocker locker(&lock);
    return stunned;
}

extern "C" EXPORT_FUNCTION void setStunned(bool _stunned) {
    stunned = _stunned;
}

extern "C" EXPORT_FUNCTION bool getBleeding() {
    QReadLocker locker(&lock);
    return bleeding;
}

extern "C" EXPORT_FUNCTION void setBleeding(bool _bleeding) {
    bleeding = _bleeding;
}

extern "C" EXPORT_FUNCTION bool getHidden() {
    QReadLocker locker(&lock);
    return hidden;
}

extern "C" EXPORT_FUNCTION void setHidden(bool _hidden) {
    hidden = _hidden;
}

extern "C" EXPORT_FUNCTION bool getInvisible() {
    QReadLocker locker(&lock);
    return invisible;
}

extern "C" EXPORT_FUNCTION void setInvisible(bool _invisible) {
    invisible = _invisible;
}

extern "C" EXPORT_FUNCTION bool getWebbed() {
    QReadLocker locker(&lock);
    return webbed;
}

extern "C" EXPORT_FUNCTION void setWebbed(bool _webbed) {
    webbed = _webbed;
}

extern "C" EXPORT_FUNCTION bool getJoined() {
    QReadLocker locker(&lock);
    return joined;
}

extern "C" EXPORT_FUNCTION void setJoined(bool _joined) {
    joined = _joined;
}

extern "C" EXPORT_FUNCTION bool getDead() {
    QReadLocker locker(&lock);
    return dead;
}

extern "C" EXPORT_FUNCTION void setDead(bool _dead) {
    dead = _dead;
}

/* inventory */

extern "C" EXPORT_FUNCTION char* getInventory() {
    QReadLocker locker(&lock);
    return inventory;
}

extern "C" EXPORT_FUNCTION void setInventory(const char inv[]) {
    strcpy(inventory, inv);
}

/* container */

extern "C" EXPORT_FUNCTION char* getContainer() {
    QReadLocker locker(&lock);
    return container;
}

extern "C" EXPORT_FUNCTION void setContainer(const char cont[]) {
    strcpy(container, cont);
}

/* wield */

extern "C" EXPORT_FUNCTION char* getWieldRight() {
    QReadLocker locker(&lock);
    return wieldRight;
}

extern "C" EXPORT_FUNCTION void setWieldRight(const char wield[]) {
    strcpy(wieldRight, wield);
}

extern "C" EXPORT_FUNCTION char* getWieldRightNoun() {
    QReadLocker locker(&lock);
    return wieldRightNoun;
}

extern "C" EXPORT_FUNCTION void setWieldRightNoun(const char wield[]) {
    strcpy(wieldRightNoun, wield);
}

extern "C" EXPORT_FUNCTION char* getWieldLeft() {
    QReadLocker locker(&lock);
    return wieldLeft;
}

extern "C" EXPORT_FUNCTION void setWieldLeft(const char wield[]) {
    strcpy(wieldLeft, wield);
}

extern "C" EXPORT_FUNCTION char* getWieldLeftNoun() {
    QReadLocker locker(&lock);
    return wieldLeftNoun;
}

extern "C" EXPORT_FUNCTION void setWieldLeftNoun(const char wield[]) {
    strcpy(wieldLeftNoun, wield);
}

/* vitals */

extern "C" EXPORT_FUNCTION int getHealth() {
    QReadLocker locker(&lock);
    return health;
}

extern "C" EXPORT_FUNCTION void setHealth(int _health) {
    health = _health;
}

extern "C" EXPORT_FUNCTION int getConcentration() {
    QReadLocker locker(&lock);
    return concentration;
}

extern "C" EXPORT_FUNCTION void setConcentration(int _concentration) {
    concentration = _concentration;
}

extern "C" EXPORT_FUNCTION int getSpirit() {
    QReadLocker locker(&lock);
    return spirit;
}

extern "C" EXPORT_FUNCTION void setSpirit(int _spirit) {
    spirit = _spirit;
}

extern "C" EXPORT_FUNCTION int getFatigue() {
    QReadLocker locker(&lock);
    return fatigue;
}

extern "C" EXPORT_FUNCTION void setFatigue(int _fatigue) {
    fatigue = _fatigue;
}

/* room */

extern "C" EXPORT_FUNCTION char* getRoomTitle() {
    QReadLocker locker(&lock);
    return roomTitle;
}

extern "C" EXPORT_FUNCTION void setRoomTitle(const char title[]) {
    strcpy(roomTitle, title);
}

extern "C" EXPORT_FUNCTION char* getRoomDescription() {
    QReadLocker locker(&lock);
    return roomDescription;
}

extern "C" EXPORT_FUNCTION void setRoomDescription(const char desc[]) {
    strcpy(roomDescription, desc);
}

extern "C" EXPORT_FUNCTION char* getRoomObjects() {
    QReadLocker locker(&lock);
    return roomObjects;
}

extern "C" EXPORT_FUNCTION void setRoomObjects(const char obj[]) {
    strcpy(roomObjects, obj);
}

extern "C" EXPORT_FUNCTION char* getRoomPlayers() {
    QReadLocker locker(&lock);
    return roomPlayers;
}

extern "C" EXPORT_FUNCTION void setRoomPlayers(const char players[]) {
    strcpy(roomPlayers, players);
}

extern "C" EXPORT_FUNCTION char* getRoomExits() {
    QReadLocker locker(&lock);
    return roomExits;
}

extern "C" EXPORT_FUNCTION void setRoomExits(const char exits[]) {
    strcpy(roomExits, exits);
}

extern "C" EXPORT_FUNCTION int getRt() {
    QReadLocker locker(&lock);
    return rt;
}

extern "C" EXPORT_FUNCTION void setRt(int _rt) {
    rt = _rt;
}
