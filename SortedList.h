#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm
{
    template <typename T>
    class SortedList
    {
        struct Node
        {
            T value;
            Node* next;

            Node(const T& value, Node* next = nullptr) : value(value), next(next)
            {
            }
        };

        int size;
        Node* head;

    public:
        SortedList(const SortedList<T>& other) : head(nullptr), size(0)
        {
            if (other.head == nullptr)
            {
                return;
            }
            try
            {
                this->head = new Node(other.head->value);
                this->size++;
                Node* current = this->head;
                Node* otherCurrent = other.head->next;
                while (otherCurrent != nullptr)
                {
                    current->next = new Node(otherCurrent->value);
                    current = current->next;
                    otherCurrent = otherCurrent->next;
                    this->size++;
                }
            }
            catch (...)
            {
                while (this->head != nullptr)
                {
                    Node* temp = this->head;
                    this->head = this->head->next;
                    delete temp;
                }
                throw;
            }
        }

        SortedList<T>& operator=(const SortedList<T>& other)
        {
            if (this == &other)
            {
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

        SortedList();

        ~SortedList()
        {
            while (this->head != nullptr)
            {
                Node* temp = this->head;
                this->head = this->head->next;
                delete temp;
            }
        }

        void remove(ConstIterator it)
        {
            if (it.node == nullptr || head == nullptr) { return; }
            Node* current = head;
            if (it.node == head)
            {
                head = head->next;
                delete current;
                size--;
                return;
            }
            while (current->next != nullptr && it.node != current->next)
            {
                current = current->next;
            }
            if (it.node == current->next)
            {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                size--;
            }
        }

        /**
        */
        void mtm::SortedList<T>::insert(const T& value)
        {
            if (head == nullptr || head->value > value)
            {
                head = new Node(value, head);
                size++;
                return;
            }
            Node* current = head;
            while ((current->next->value) < value && current->next != nullptr)
            {
                current = current->next;
            }
            current->next = new Node(value, current->next);
            size++;
        }

        template <class Predicate>
        SortedList filter(Predicate func)
        {
            SortedList filtered;
            Node* current = this->head;
            while (current != nullptr)
            {
                if (func(current->value))
                {
                    filtered.insert(current->value);
                }
                current = current->next;
            }
            return filtered;
        }

        /**
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
     */
        const T& operator*() const
        {
            Node* current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            return current;
        }

        /**
            * 7. end method
            *
            * functions:
            * 8. insert - inserts a new element to the list
        */
        int mtm::SortedList<T>::length(const T& value)
        {
            return size;
        }

        /**   * 10. length - returns the number of elements in the list
       */
        SortedList<T> mtm::SortedList<T>::apply(T (*operation)(const T&)) const
        {
            SortedList<T> newList;
            Node* current = head;;
            while (current != nullptr)
            {
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
    class SortedList<T>::ConstIterator
    {
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

