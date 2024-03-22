# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def mergeTwoLists(
        self, list1: ListNode, list2: ListNode
    ) -> ListNode:
        if list1 is None:
            return list2

        if list2 is None:
            return list1

        # Initialize
        head = ListNode()

        if list1.val < list2.val:
            head.val = list1.val
            iter1 = list1.next
            iter2 = list2
        else:
            head.val = list2.val
            iter1 = list1
            iter2 = list2.next

        iter = head

        while True:
            if iter1 is None:
                # Assign iter2 to iter.next and exit.
                iter.next = iter2
                break

            if iter2 is None:
                # Assign iter1 to iter.next and exit.
                iter.next = iter1
                break

            # Create a New Node
            newNode = ListNode()
            if iter1.val < iter2.val:
                newNode.val = iter1.val
                iter1 = iter1.next
            else:
                newNode.val = iter2.val
                iter2 = iter2.next

            # Attach the new node to the result node.
            newNode.next = None
            iter.next = newNode
            iter = newNode

        return head
