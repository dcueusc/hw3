#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <stdexcept>

template <typename T, typename Comparator = std::less<T>>
class Heap {
public:
    /// Constructs an m-ary heap for any m >= 2
    Heap(int m = 2, Comparator c = Comparator()) : ary(m), comper(c) {}

    // other stuff

    /**
     * @brief Push an item to the heap
     * 
     * @param item item to add to the heap
     */
    void push(const T& item) {
        heap.push_back(item);
        heapifyUp(heap.size() - 1);
    }

    /**
     * @brief Remove the top priority item
     * 
     * @throw std::underflow_error if the heap is empty
     */
    void pop() {
        if (empty()) {
            throw std::underflow_error("Heap underflow");
        }
        heap[0]=heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    /**
     * @brief Returns the top (priority) item
     * 
     * @return T const& top priority item
     * @throw std::underflow_error if the heap is empty
     */
    T const & top() const {
        if (empty()) {
            throw std::underflow_error("Heap underflow");
        }
        return heap.front();
    }

    /**
     * @brief Returns true if the heap is empty
     * 
     * @return true if the heap is empty, false otherwise
     */
    bool empty() const {
        return heap.empty();
    }

    /**
     * @brief Returns the size of the heap
     * 
     * @return size_t size of the heap
     */
    size_t size() const {
        return heap.size();
    }

private:
    int ary; 
    std::vector<T> heap; 
    Comparator comper; 

    void heapifyUp(int index) {
      int parent = (index-1)/ary;
        while (index > 0 && comper(heap[index], heap[parent])) {
            std::swap(heap[index], heap[parent]);
            index = parent;
            parent = (index-1)/ary;
        }
    }

    void heapifyDown(int index) {
        int highestChild = ary*index+1; //smallest child - set to first child for now
        while (highestChild<size()) { //while children are within list size
            
            int last;  //find the index of last child or the index of the last element if youre at the end
            if(ary*index+ary+1<static_cast<int>(heap.size())){
              last = ary*index+ary+1;
            }else{last=static_cast<int>(heap.size());}

            for (int i=ary*index+2; i<last;++i) { //for all the rest of the children find highest
                if (comper(heap[i], heap[highestChild])) {
                    highestChild=i; //if this child is high priority than the previous, set as new highest
                }
            }
            if (comper(heap[index], heap[highestChild])) { //if highest priority child is not higher priority than index, end 
                break;
            }
            std::swap(heap[index], heap[highestChild]); //otherwise swap them and update indexs and continue
            index = highestChild;
            highestChild = ary*index+1;
        }
    }



};

#endif
