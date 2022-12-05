
#define HAVE_STRUCT_TIMESPEC
#include <iostream>


#define _RW_LOCK_LINKED_LIST_PT_H_
#define DEFAULT_NUM_THREADS 1
#define DEFAULT_DURATION 1000
#define DEFAULT_RANGE 2048
#define DEFAULT_READS 80
#define DEFAULT_UPDATES 20

static uint32_t finds;
static uint32_t max_key;

#include <atomic>
#include <thread>
#include <pthread.h>







template<typename T> class LinkedListSet {

private:
    struct Node {
        T key;
        Node* next;
    };

    Node* _head;
    Node* _tail;

public:

    LinkedListSet() {
        _head = new Node();
        _tail = new Node();
        _head->next = _tail;
    }

    ~LinkedListSet() {
        clear();
        delete _head;
        delete _tail;
    }


    bool add(T key) {
        Node* newNode = new Node();
        newNode->key = key;
        Node* node = _head->next;
        Node* prev = _head;
        while (node != _tail) {
            if (key == node->key) {

                return false;
            }
            if (key < node->key) {

                break;
            }
            prev = node;
            node = node->next;
        }

        newNode->next = node;
        prev->next = newNode;
        return true;
    }



    bool remove(T key) {
        Node* node = _head->next;
        Node* prev = _head;
        while (node != _tail) {
            if (key == node->key) {

                prev->next = node->next;
                delete node;
                return true;
            }
            if (key < node->key) {

                return false;
            }
            prev = node;
            node = node->next;
        }
        return false;
    }


    bool contains(T key) {
        Node* node = _head->next;
        while (node != _tail) {
            if (key == node->key) {

                return true;
            }
            if (key < node->key) {

                return false;
            }
            node = node->next;
        }
        return false;
    }


    void clear(void) {
        Node* node = _head->next;
        Node* prev = _head->next;
        while (node != _tail) {
            prev = node;
            node = node->next;
            delete prev;
        }
        _head->next = _tail;
    }


    long size(void) {
        Node* node = _head->next;
        long size = 0;
        while (node != _tail) {
            size++;
            node = node->next;
        }
        return size;
    }
};



template<typename T> class LLinkedList {

private:
    LinkedListSet<T> _set;
    pthread_rwlock_t _rwlock = PTHREAD_RWLOCK_INITIALIZER;

public:


    bool add(T key) {
        pthread_rwlock_wrlock(&_rwlock);
        bool retValue = _set.add(key);
        pthread_rwlock_unlock(&_rwlock);
        return retValue;
    }



    bool remove(T key) {
        pthread_rwlock_wrlock(&_rwlock);
        bool retValue = _set.remove(key);
        pthread_rwlock_unlock(&_rwlock);
        return retValue;
    }



    bool contains(T key) {
        pthread_rwlock_rdlock(&_rwlock);
        bool retValue = _set.contains(key);
        pthread_rwlock_unlock(&_rwlock);
        return retValue;
    }
};



int main()
{
    pthread_t* threads;
    pthread_attr_t attr;
    int n_threads = DEFAULT_NUM_THREADS;
    max_key = DEFAULT_RANGE;
    uint32_t updates = DEFAULT_UPDATES;
    finds = DEFAULT_READS;
    int duration = DEFAULT_DURATION;
    //thread_data_t* data;

    //INCOMPLETO, FALTO TIEMPO :c
    /*for (int i = 0; i < n_threads; i++) {
        data[i].id = i;
        data[i].n_ops = 0;
        data[i].n_insert = 0;
        data[i].n_remove = 0;
        data[i].n_search = 0;
        data[i].n_add = max_key / (2 * n_threads);
        if (i < ((max_key / 2) % n_threads))
            data[i].n_add++;
        //data[i].barrier = &barrier;
        if (pthread_create(&threads[i], &attr, test, (void*)(&data[i])) !=
            0) {
            fprintf(stderr, "Error creating thread\n");
            exit(1);
        }
    }*/
}

