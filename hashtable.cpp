#include "hashtable.h"

/************************************
 * Constructor / Destructor
 ************************************/

Hashtable::Hashtable() {
    count = 0;
    for (int i = 0; i < HASHTABLESIZE; i++) {
        hashtable[i] = nullptr;
    }
}

Hashtable::~Hashtable() {
    for (int i = 0; i < HASHTABLESIZE; i++) {
        if (hashtable[i]) {
            delete hashtable[i];
        }
    }
}


/************************************
 * Private
 ************************************/
int Hashtable::hash(int id) {
    // guarantees a position between 0 and HASHTABLESIZE - 1
    return id % HASHTABLESIZE;
}


/************************************
 * Public
 ************************************/

bool Hashtable::insertEntry(int id, string data) {
    bool inserted = false;
    int position = hash(id);

    cout << id << " initial position: " << position << ", ";
    // if the space is occupied, search for the next space
    // this is a linear probe
    if (hashtable[position]) {
        for (int i = 0; i < HASHTABLESIZE && hashtable[position]; i++) {
            if (position == HASHTABLESIZE - 1) {
                position = 0;
            } else {
                position++;
            }
            cout << position << ", ";
        }
    }
    cout << "final: " << position << endl;

    // if the space is empty, insert, otherwise the table was full
    if (!hashtable[position]) {
        Data *entry = new Data;
        entry->id = id;
        entry->data = data;
        hashtable[position] = entry;
        count++;
        inserted = true;
    }

    return inserted;
}

bool Hashtable::deleteEntry(int id) {
    bool del = false;
    int position = hash(id);

    /*
     * Start at the hashed position and then linear probe
     */
    for (int i = 0; i < HASHTABLESIZE && !del; i++) {
        if (hashtable[position] && hashtable[position]->id == id) {
            delete hashtable[position];
            hashtable[position] = nullptr;
            del = true;
            count--;
        } else {
            if (position == HASHTABLESIZE - 1) {
                position = 0;
            } else {
                position++;
            }
        }
    }

    return del;
}

string Hashtable::getData(int id) {
    string ret = "";
    int position = hash(id);

    /*
     * Start at the hashed position and then linear probe
     */
    for (int i = 0; i < HASHTABLESIZE && ret == ""; i++) {
        if (hashtable[position] && hashtable[position]->id == id) {
            ret = hashtable[position]->data;
        } else {
            if (position == HASHTABLESIZE - 1) {
                position = 0;
            } else {
                position++;
            }
        }
    }

    return ret;
}

void Hashtable::printTable() {
    for (int i = 0; i < HASHTABLESIZE; i++) {
        if (hashtable[i]) {
            cout << "Table Entry " << i << ": " << hashtable[i]->id << ": " << hashtable[i]->data << endl;
        } else {
            cout << "Table Entry " << i << ": EMPTY" << endl;
        }
    }
}

int Hashtable::getCount() {
    return count;
}