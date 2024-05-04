#include "cached_runner.h"
#include "task_runner.h"
#include "task.h"

CachedRunner::CachedRunner(Cache& cache) : cache(cache), hitCount(0), missCount(0) {}

double CachedRunner::multiply(std::string filename) {
    double result;
    if (cache.get(filename, result)) {
        hitCount++;
        return result;
    } else {
        missCount++;
        result = TaskRunner::multiply(filename);
        cache.add(filename, result);
        return result;
    }
}

int CachedRunner::palindrome(std::string filename) {
    int result;
    if (cache.get(filename, result)) {
        hitCount++;
        return result;
    } else {
        missCount++;
        result = TaskRunner::palindrome(filename);
        cache.add(filename, result);
        return result;
    }
}

int CachedRunner::hits() {
    return hitCount;
}

int CachedRunner::misses() {
    return missCount;
}
