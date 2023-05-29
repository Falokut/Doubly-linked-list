#pragma once
#include <iostream>

template <typename T> class List
{
  public:
    List();
    ~List();
    T &operator[](const int index);

    int GetSize() const
    {
        return Size;
    }
    void Push_Front(T Data);
    void Push_Back(T Data);
    void Insert(T Data, const int index);

    void Pop_Front();
    void Pop_Back();
    void RemoveAt(const int index);
    void Clear();

    void Print_Forward() const;
    void Print_Backward() const;

  private:
    template <typename T> struct Node
    {
        Node *pNext;
        Node *pPrev;
        T Data;

        Node(T Data = T(), Node *pNext = nullptr, Node *pPrev = nullptr)
        {
            this->Data = Data;
            this->pNext = pNext;
            this->pPrev = pPrev;
        }
    };

    int Size;
    Node<T> *head;
    Node<T> *tail;
};

template <typename T> List<T>::List()
{
    Size = 0;
    head = nullptr;
    tail = nullptr;
}

template <typename T> List<T>::~List()
{
    Clear();
}
template <typename T> inline T &List<T>::operator[](const int index)
{
    if (index >= GetSize())
        throw -1;
    const bool IsFirstPart = index <= GetSize() / 2;
    int counter = IsFirstPart ? 0 : GetSize() - 1;
    Node<T> *current = IsFirstPart ? this->head : this->tail;

    while (current)
    {
        if (counter == index)
            return current->Data;

        if (IsFirstPart)
        {
            current = current->pNext;
            ++counter;
        }
        else
        {
            current = current->pPrev;
            --counter;
        }
    }
}

template <typename T> inline void List<T>::Push_Front(T Data)
{
    if (!head)
        head = new Node<T>(Data);

    else
    {
        Node<T> *OldHead = head;
        head = new Node<T>(Data);
        head->pNext = OldHead;
        OldHead->pPrev = head;
        if (Size == 1)
            tail = OldHead;
    }
    ++Size;
}

template <typename T> inline void List<T>::Push_Back(T Data)
{
    if (!head)
        head = new Node<T>(Data);

    else if (!tail)
    {
        tail = new Node<T>(Data, nullptr, head);
        head->pNext = tail;
    }

    else
    {
        Node<T> *OldTail = tail;
        tail = new Node<T>(Data, nullptr, tail);
        OldTail->pNext = tail;
    }
    ++Size;
}

template <typename T> inline void List<T>::Insert(T Data, const int index)
{
    if (index > GetSize())
        return;

    else if (index <= GetSize() / 2) 
    {
        Node<T> *PrevNode = head;
        for (int i = 0; i < index - 1; ++i)
        {
            PrevNode = PrevNode->pNext;
        }
        PrevNode->pNext = new Node<T>(Data, PrevNode->pNext, PrevNode);
    }
    else
    {
        Node<T> *PrevNode = tail;
        for (int i = GetSize() - 1; i >= index - 1; --i)
        {
            PrevNode = PrevNode->pPrev;
        }
        PrevNode->pNext = new Node<T>(Data, PrevNode->pNext, PrevNode);
    }
    ++Size;
}

template <typename T> inline void List<T>::Pop_Front()
{
    if (GetSize() == 0)
        return;

    Node<T> *OldHead = head;
    head = head->pNext;
    delete OldHead;
    --Size;
}

template <typename T> inline void List<T>::Pop_Back()
{
    if (Size == 0)
        return;

    Node<T> *OldTail = tail;
    tail = tail->pPrev;
    delete OldTail;
    --Size;
}

template <typename T> inline void List<T>::RemoveAt(const int index)
{
    if (index < 0 || index >= GetSize())
        return;

    else
    {
        const bool IsFirstPart = index <= GetSize() / 2;
        Node<T> *PrevNode = IsFirstPart ? head : tail;
        if (IsFirstPart)
            for (int i = 0; i < index - 1; ++i)
                PrevNode = PrevNode->pNext;

        else
            for (int i = GetSize() - 1; i >= index - 1; --i)
                PrevNode = PrevNode->pPrev;

        Node<T> *ToDelete = PrevNode->pNext;
        PrevNode->pNext = PrevNode->pNext->pNext;
        PrevNode->pPrev = PrevNode->pPrev->pPrev;
        delete ToDelete;
    }

    --Size;
}

template <typename T> void List<T>::Clear()
{
    while (head)
        Pop_Front();
}

template <typename T> inline void List<T>::Print_Forward() const
{
    Node<T> *current = head;

    for (int i = 0; i < GetSize(); ++i)
    {
        std::cout << "List [" << i << "] = " << current->Data << "\t";
        current = current->pNext;
    }
}

template <typename T> inline void List<T>::Print_Backward() const
{
    Node<T> *current = tail;

    for (int i = GetSize() - 1; i >= 0; --i)
    {
        std::cout << "List [" << i << "] = " << current->Data << "\t";
        current = current->pPrev;
    }
}
