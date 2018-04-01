/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
    var carry int
    var head, tail *ListNode
    for l1 != nil || l2 != nil || carry > 0 {
        n := new(ListNode)
        n.Val = carry
        carry = 0
        if l1 != nil {
            n.Val += l1.Val
            l1 = l1.Next
        }
        if l2 != nil {
            n.Val += l2.Val
            l2 = l2.Next
        }
        if n.Val > 9 {
            n.Val -= 10
            carry = 1
        }
        if tail == nil {
            // head points to least significant (first) digit
            head = n
        } else {
            tail.Next = n
        }
        tail = n
    }
    return head
}
