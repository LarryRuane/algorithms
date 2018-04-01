/*
Detect a cycle in a linked list. Note that the head pointer may be 'NULL' if the list is empty.

A Node is defined as: 
    struct Node {
        int data;
        struct Node* next;
    }
*/

bool has_cycle(Node* head) {
    if (!head) return 0; // empty list
    Node* fast = head->next;
    Node* slow = head;
    bool moveSlow = true;
    while (fast && fast != slow) {
        fast = fast->next;
        if (moveSlow) {
            slow = slow->next;
        }
        moveSlow = !moveSlow;
    }
    return fast == slow;
}
