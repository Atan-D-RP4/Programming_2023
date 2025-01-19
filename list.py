class Node:
    def __init__(self, data):
        self.data = data
        self.next = None


class LinkedList:
    def __init__(self, elements=None):
        self.head = None
        if elements is not None:
            for element in elements:
                self.insert(element)

    def insert(self, data):
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node

    def reverse(self):
        prev = None
        current = self.head
        while current:
            next = current.next
            current.next = prev
            prev = current
            current = next
        self.head = prev

    def __str__(self):
        result = []
        current = self.head
        while current:
            result.append(current.data)
            current = current.next
        return ' -> '.join(map(str, result))

    def __add__(self, other):
        result = LinkedList()
        current = other.head
        while current:
            result.insert(current.data)
            current = current.next
        current = self.head
        while current:
            result.insert(current.data)
            current = current.next
        return result

l1 = LinkedList([1, 2, 3])
l2 = LinkedList([4, 5, 6])
print(l1)
print(l2)
l3 = l1 + l2
print(l3)
