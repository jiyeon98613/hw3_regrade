#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <iostream>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

  size_t height(int size) const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> heap_;
  int m_ = 2;
  size_t size_ = 0;
  PComparator comp_;
  void print();
  void heapify(size_t idx);
  void heapify_helper(size_t idx, size_t leaf);
  void trickle_up(size_t loc);
  


};

template <typename T, typename PComparator>
void Heap<T,PComparator>::print()
{
  size_t i = 0;
  std::cout<<heap_[i];
  ++i;
  while(i != size_)
  {
    std::cout<<" - "<<heap_[i];
    ++i;
  }
  std::cout<<std::endl;
}

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
: m_(m), size_(0), comp_ (c)
{}
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
  heap_.clear();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  heap_.push_back(item);
  ++size_;
  //trickle up
  //if(size_ == 1){return;}
  trickle_up(size_ -1);
  print();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickle_up(size_t loc)
{
  size_t parent = (loc-1)/m_;
  std::cout<<"comp:"<<comp_(heap_[parent], heap_[loc])<<std::endl;
  while(parent >= 0 && comp_(heap_[loc], heap_[parent])) //while child is better than parent
  { 
    std::cout<<"heap_loc="<<heap_[loc]<<" is better than heap[parent]="<< heap_[parent]<<std::endl;
    std::cout<<"heap.h:125: comp worked trickle_up"<<std::endl;
    std::swap(heap_[loc], heap_[parent]);
    loc = parent;
    parent= loc/m_;
  } 
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return heap_.empty();
}


template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return heap_.size();
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("The stack is empty.");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  std::cout<<"top function called::"<<heap_.front()<<std::endl;
  //print();
  return heap_.front();


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{ std::cout<<"pop function called."<<std::endl;
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("The stack is empty.");

  }
  //switch the item
  if(size_ == 1) 
  {
    heap_.pop_back(); 
      --size_;
      std::cout<<"pop function: size = 1"<<std::endl;
    return;
    
  }
  std::swap(heap_[0], heap_[size_-1]);
  std::cout<<"under pop function, after swap the top: ";
  print();
  heap_.pop_back();
  --size_;
  std::cout<<"under pop function, after popback: ";
  print();
  //heapify
  heapify(0);
  std::cout<<"under pop function, after heapify: ";
  print();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(size_t index)
{
  //find the start index of the leaf node -assuming that the size_ > 1
  size_t i = 0;
  size_t leaf_start = 0 ; //leaf_end=0;
  if((size_) > 1) 
  {
    while (i < height(size_)-1) 

    {
      
      leaf_start += pow(m_, i);
      ++i;
      //leaf_end = (leaf_start + pow(m_, i) -1);
      
    }
    std::cout<<"under heapify function, before heapify_helper: ";
    print();
    heapify_helper(index, leaf_start);
    std::cout<<"under heapify function, after heapify_helper: ";
    print();
  }

 
}
template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify_helper(size_t index, size_t l_s)
{
  std::cout<<"undere h_h function: index="<<index<<", l_s = "<<l_s<<std::endl;
  //recursion helper function starts here
  if(index >= l_s ) {return;} //base case: if the index is a leaf node 
  size_t best_ch = index * m_ +1;//start from the most left child
  size_t increment = 1;
  for(int i = 0 ; i < m_-1 ; ++i) //iterate through the possible m-th child
  {
    if((best_ch + increment) <= size_-1) //if there's right node exist
    {
      
      int rChild = best_ch + increment;
      if(comp_(heap_[rChild], heap_[best_ch])  )
      {
        best_ch = rChild;
        increment = 1;
      }
      else
      {
        ++increment;
      }
    } else {break;}
    //++best_ch;
  }
  std::cout<<"undere h_h function: bestchild="<<best_ch<<std::endl;
  //we found the best child now and so we need compare the parent and the child and swap 
  if(comp_(heap_[best_ch], heap_[index]))
  {

    std::swap(heap_[best_ch], heap_[index]);
    std::cout<<"under h_h function, after swap between best_ch:"<<best_ch <<", and index:"<<index <<std::endl;;
  print();
  }
  heapify_helper(best_ch,l_s );
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::height(int size) const
{
  int i = 1;
  int h = 1;
  while(size > i)
  {
    i += pow(m_, h);
    ++h;
  }
  if(size == 1) return 1;
  if (size == 0) return 0;
  return h;
}

#endif

