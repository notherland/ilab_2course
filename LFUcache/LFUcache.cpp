#include <iostream>
#include <list>
#include <unordered_map>

struct page_t {
    page_t() {
        nreq = 1;
        data = 0;
    }

    int nreq;
    int data;
};

class LFUcache {
public:
    LFUcache(size_t sz) { //Constructor
        capacity = sz;
    }

    bool lookup(int index);

    void print() {
        std::cout << "Cache :" << std::endl;
        for (auto i : hash) {
            std::cout << "index = " << i.first << "  nreq = " << i.second->nreq << std::endl;
        }
    }

    ~LFUcache(){ //Destructor
        cache.clear();
        hash.clear();
        capacity = 0;
    }

private:
    size_t capacity;
    std::list<page_t> cache;
    typedef typename std::list<page_t>::iterator it;
    std::unordered_map<int, it> hash;

    bool isfull() const // проверяет полон ли кэщ
    {
        return cache.size() + 1 > capacity;
    }
};

bool Comparator(const page_t &el1, const page_t &el2) {
    return el1.nreq > el2.nreq;
}

bool LFUcache::lookup(int index) {
    auto elem = hash.find(index);

    if (elem == hash.end()) // there is no element with index in cache
    {
        page_t newelem;
        std::cout << "New elem: " << index << std::endl;
        if (isfull()) // if cache is full create or ignore new element
        {
            //std::cout << newelem.nreq;
            if (newelem.nreq >= cache.end()->nreq) {

                cache.erase(cache.end());
                cache.insert(cache.end(), newelem);
                std::pair<int, it> newhashnode(index, cache.end());
                hash.insert(newhashnode);
            }
        } else // if cache is not full create new element
        {
            std::cout << "newelem.nreq  = " << newelem.nreq << std::endl;
            cache.push_back(newelem);
            std::pair<int, it> newhashnode(index, cache.end());
            hash.insert(newhashnode);
            //print();
            std::cout << "Newelem.nreq in cache and in hash: " << cache.end()->nreq << " " << hash[index]->nreq << std::endl;
        }
        return true;
    } else {//increasing number of requests for element which is already existed in cache
        std::cout << "Old elem: " << index << std::endl;
        elem->second->nreq += 1;
        //std::cout << "Old elem requests : " << elem->second->nreq << " " << std::endl;
        //print();
        cache.sort(Comparator);
        return false;
    }
}

int main() {
    size_t sz = 0;
    int n = 0;
    int index = 0;

    std::cout << "Cache size : " << std::endl;
    std::cin >> sz;
    LFUcache cache{sz};

    std::cout << "Number of requests : " << std::endl;
    std::cin >> n;
    int hits = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> index;
        hits += cache.lookup(index);
        //cache.print();
    }

    std::cout << std::endl<< "End" << std::endl << "hits : " << hits << std::endl;
    cache.print();

    return 0;
}
