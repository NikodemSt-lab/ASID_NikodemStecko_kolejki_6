#include <cassert>
#include <initializer_list>
#include <iostream>
#include <sstream>

#include "mydeque.hpp"

int main() {
    MyDeque<int> queue(4);
    assert(queue.empty() && !queue.full());
    assert(queue.size() == 0 && queue.max_size() == 4);

    queue.push_back(11);
    queue.push_back(22);
    queue.push_front(33);
    queue.push_front(44);

    assert(queue.full() && queue.size() == 4);
    assert(queue.front() == 44 && queue.back() == 22);

    std::ostringstream output;
    std::streambuf* old = std::cout.rdbuf(output.rdbuf());

    queue.display();
    queue.display_reversed();

    std::cout.rdbuf(old);
    assert(output.str() == "44 33 11 22 \n22 11 33 44 \n");

    MyDeque<int> copy(queue);
    MyDeque<int> assigned;

    assert(assigned.max_size() == 10);
    assigned.push_back(99);

    MyDeque<int>& result = (assigned = queue);

    assert(&result == &assigned && assigned.max_size() == 4);

    assigned = assigned;
    assert(assigned.full());

    queue.front() = 45;
    queue.back() = 23;

    for (int item : {44, 33, 11, 22}) 
    {
        assert(copy.front() == item && assigned.front() == item);
        copy.pop_front();
        assigned.pop_front();
    }
    assert(copy.empty() && assigned.empty());

    queue.pop_front();
    assert(queue.front() == 33);

    queue.pop_front();
    assert(queue.front() == 11);

    queue.pop_front();
    assert(queue.size() == 1 && queue.front() == 23);

    queue.push_back(55);
    queue.push_back(66);
    queue.push_back(77);

    assert(queue.full() && queue.front() == 23 && queue.back() == 77);

    queue.pop_back();
    assert(!queue.full() && queue.size() == 3 && queue.back() == 66);

    queue.clear();
    assert(queue.empty() && queue.size() == 0 && queue.max_size() == 4);

    queue.push_front(8);
    assert(queue.front() == 8 && queue.back() == 8);

    queue.pop_back();
    assert(queue.empty());

    std::cout << "Wszystkie testy zakonczone sukcesem\n";
}
