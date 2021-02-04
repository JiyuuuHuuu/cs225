#pragma once

#include <cstddef>

class Queue
{
    public:
        Queue();
        int size() const;
        bool isEmpty() const;
        void enqueue(int value);
        int dequeue();
        ~Queue();

    private:
        class Node
        {
          public:
            Node(int val)
            {
              value = val;
              next = NULL;
            };
            int value;
            Node *next;
        };
        Node *front;
        Node *tail;
        int num;
        void _destroy();
};
