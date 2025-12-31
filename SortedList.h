#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    class SortedList {
      struct Node{
        T value;
        Node* next;
        Node(const T& value, Node* next = nullptr) : value(value), next(next) {}
      };
    int size;
    Node* head;

    public:
        SortedList(const SortedList<T> &other) : head(nullptr), size(0) {
            if(other.head==nullptr){
                return;
            }
            try {
                this->head = new Node(other.head->value);
                this->size++;
                Node* current = this->head;
                Node* otherCurrent= other.head->next;
                while(otherCurrent!=nullptr){
                    current->next = new Node(otherCurrent->value);
                    current = current->next;
                    otherCurrent = otherCurrent->next;
                    this->size++;
                }
            }
            catch(...){
                while(this->head!=nullptr){
                    Node* temp = this->head;
                    this->head = this->head->next;
                    delete temp;
                }
                throw;
            }
        }

        SortedList<T>& operator=(const SortedList<T> &other) {
            if (this == &other){
                return *this;
            }
            SortedList<T> temp(other);
            Node* old = this->head;
            this->head = temp.head;
            temp.head = old;
            temp.size = this->size;
            this->size = other.size;
            return *this;
        }
        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
     */
         SortedList();
     /**
         * 2. copy constructor
         * 3. operator= - assignment operator
     */
         void SortedList<T>::insert(const T& value){
         if(head == nullptr || head->value  > value){
            head = new Node(value, head);
            size++;
            return;
         }
          Node* current = head;
          while((current-> next-> value) < value && current->next != nullptr){
           current = current->next;
          }
          current->next = new Node(value, current->next);
          size++;
         }
          
        /**
         * 4. ~SortedList() - destructor
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
     */
     const T& operator*() const {
          Node* current = head;
          while(current->next != nullptr){
           current = current->next;
          }
          return current;
         }
     /**
         * 7. end method
         *
         * functions:
         * 8. insert - inserts a new element to the list
         * 9. remove - removes an element from the list
     */
     int SortedList<T>::length(const T& value){
         return size;
     }

      /**   * 10. length - returns the number of elements in the list
         * 11. filter - returns a new list with elements that satisfy a given condition
     */
     SortedList<T> SortedList<T>::apply(T (*operation)(const T&)) const{
          SortedList<T> newList;
          Node* current = head;
          ;
          while(current != nullptr){
           T temp = operation(current->value);
           newList.insert(temp);
           current = current->next;
          }
          return newList;
     }
     /**
         * 12. apply - returns a new list with elements that were modified by an operation
         */

    };

    template <class T>
    class SortedList<T>::ConstIterator {
    /**
     * the class should support the following public interface:
     * if needed, use =defualt / =delete
     *
     * constructors and destructor:
     * 1. a ctor(or ctors) your implementation needs
     * 2. copy constructor
     * 3. operator= - assignment operator
     * 4. ~ConstIterator() - destructor
     *
     * operators:
     * 5. operator* - returns the element the iterator points to
     * 6. operator++ - advances the iterator to the next element
     * 7. operator!= - returns true if the iterator points to a different element
     *
     */
    };
}

