#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm
{
    template <typename T>
    class SortedList
    {
        struct  Node
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
        class ConstIterator
        {
            const Node* node;
            friend class SortedList;

            explicit ConstIterator(const Node* node) : node(node)
            {
            }

        public:
            ConstIterator(const ConstIterator& other) = default;

            ConstIterator& operator=(const ConstIterator& other) = default;

            ~ConstIterator() = default;

            ConstIterator& operator++()
            {
                if (node == nullptr)
                {
                    throw std::out_of_range("Out of Range");
                }
                node = node->next;
                return *this;
            }
            bool operator !=(const ConstIterator& other) const{
              return node != other.node;
            }

            const T& operator*() const
            {
                if (node == nullptr)
                {
                    throw std::out_of_range("Out of Range");
                }
                return node->value;
            }

            bool operator!=(const ConstIterator& it) const
            {
                return node != it.node;
            }
        };

        SortedList() : size(0), head(nullptr)
        {
        }

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

        SortedList& operator=(const SortedList& other)
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

        ~SortedList()
        {
            while (this->head != nullptr)
            {
                Node* temp = this->head;
                this->head = this->head->next;
                delete temp;
            }
        }

        void insert(const T& value)
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

        int length() const
        {
            return size;
        }

        ConstIterator begin() const
        {
            return ConstIterator(head);
        }

        ConstIterator end() const
        {
            return ConstIterator(nullptr);
        }

        template <class Predicate>
        SortedList filter(Predicate func) const
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

        SortedList apply(T (*operation)(const T&)) const
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
    };
}

