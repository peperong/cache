#ifndef CACHE_H
#define CACHE_H

#include <string>

#define CACHE_SIZE 10

class Cache {
  
private:
struct Node {
    std::string key;
    double value;
    Node* next;
    Node* prev;
};
  Node* head; 
  Node* tail;
  int capacity;
  void remove(Node* node);
  void insertFront(Node* node);
  bool isFull();
  int cacheSize();
struct Bucket {
        std::string key;
        int value;
        Bucket* next;
    };

  static const int tableSize = 1000; // 해시 테이블의 크기
  Bucket* hashTable[tableSize]; // 해시 테이블 배열

  // 해시 함수
  unsigned int hashFunction(const std::string& key);

  // 버킷 생성 및 초기화
  Bucket* createBucket(const std::string& key, int value);

  // 해시 테이블에서 키에 해당하는 버킷을 찾는다
  Bucket* findBucket(const std::string& key);

  // 해시 테이블에 버킷을 추가한다
  void addToHashTable(const std::string& key, int value);

public:
  Cache();
  ~Cache();
  // int를 cache에 추가한다
  void add(std::string key, int value);
  // double을 cache에 추가한다
  void add(std::string key, double value);
  // key에 해당하는 value를 cache에서 가져온다
  // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
  bool get(std::string key, int &value);
  // key에 해당하는 value를 cache에서 가져온다.
  // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
  bool get(std::string key, double &value);

  // 디버그 및 채점 용: 연결 리스트를 문자열로 표현하여 반환한다
  // 다음과 같이 표현된 문자열을 반환한다
  // [key1: value1] -> [key2: value2] -> ... -> [keyN: valueN]
  std::string toString();
};

#endif