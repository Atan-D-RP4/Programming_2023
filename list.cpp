#include <iostream>
#include <vector>

using namespace std;

class ListNode {
public:
    int val;
    ListNode *next;
    ListNode(int val) : val(val), next(nullptr) {}
    ListNode(int val, ListNode *next) : val(val), next(next) {}
};

class LinkedList {
private:
    ListNode *head;
    ListNode *tail;
public:
    LinkedList() {
        head = new ListNode(-1);
        tail = head;
    }

    int get(int index) {
        ListNode *crsr = head->next;
        int i = 0;
        for ( ; crsr != nullptr; crsr = crsr->next) {
            if (i == index)
                return crsr->val;
            ++i;
        }
        return -1;
    }

    void insertHead(int val) {
        ListNode *newHead = new ListNode(val, head->next);
        head->next = newHead;
        if (newHead->next == nullptr)
            tail = newHead;
    }

    void insertTail(int val) {
        ListNode *newHead = new ListNode(val);
         if (head == nullptr) {
            head = newHead;
            return;
        }
        tail->next = newHead;
        tail = tail->next;
    }

    bool remove(int index) {
        if (head == nullptr || index < 0)
            return false;

        if (index == 0) {  // If removing the first node
            ListNode *toDelete = head->next;  // Store the node to be deleted
            head->next = head->next->next;  // Update head to skip the first node
            delete toDelete;  // Free the memory of the node to be deleted
            return true;
        }

        ListNode *crsr = head;  // Start from the head
        int i = 0;
        while (crsr->next != nullptr && i < index - 1) {
            crsr = crsr->next;
            ++i;
        }

        if (crsr->next == nullptr || i != index - 1)  // Check if index is out of bounds
            return false;

        ListNode *toDelete = crsr->next;  // Store the node to be deleted
        crsr->next = crsr->next->next;  // Adjust the pointers to bypass the node to be deleted
        if (crsr->next == nullptr)  // If the node to be deleted was the last node
            tail = crsr;  // Update tail
        delete toDelete;  // Free the memory of the node to be deleted
        return true;
    }

    vector<int> getValues() {
        vector<int> res;
        ListNode *crsr = head->next;
        for ( ; crsr != nullptr; crsr = crsr->next)
            res.push_back(crsr->val);
        return res;
    }
};

int main() {
    LinkedList list;
    list.insertHead(1);
    list.insertHead(2);
    list.insertHead(3);
    list.insertTail(4);
    list.insertTail(5);

    cout << "Initial List: ";
    for (int val : list.getValues()) {
        cout << val << " ";
    }
    cout << endl;

    list.remove(0); // Remove the first element
    list.remove(3); // Remove the last element

    cout << "Modified List: ";
    for (int val : list.getValues()) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

