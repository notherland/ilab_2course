#include <iostream>
#include <list>
#include <unordered_map>

struct page_t {
    page_t(int index) {
        id = index;
        nreq = 1;
        data = 0;
    }

    int id;
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
        std::cout << "Cache :" << std::endl << "cache size = " << cache.size() << std::endl;
        for (auto i : cache) {
            std::cout << "index = " << i.id << "  nreq = " << i.nreq << std::endl;
        }
    }

    ~LFUcache() { //Destructor
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
    return el1.nreq < el2.nreq;
}

bool LFUcache::lookup(int index) {
    auto elem = hash.find(index);

    if (elem == hash.end()) // there is no element with index in cache
    {
        page_t newelem{index};
        //std::cout << "New elem: " << index << std::endl;
        //print();
        if ((isfull()))//create new element instead of elem with the least nreq
        {
            if (newelem.nreq >= cache.back().nreq) {
                //std::cout << "Full" << std::endl;
                hash.erase(cache.front().id);
                cache.pop_front();
                cache.push_front(newelem);
                hash[index] = cache.begin();
            }
        } else {
            //std::cout << "Not full" << std::endl;
            cache.push_front(newelem);
            hash[index] = cache.begin();
        }
        //print();
        return true;
    } else {//increasing number of requests for element which is already existed in cache
        //std::cout << "Old elem: " << index << std::endl;
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

    std::cout << "hits : " << hits << std::endl;
    cache.print();

    return 0;
}
