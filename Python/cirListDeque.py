# A circular linked list implementation of a Deque
class Link(object):
	def __init__(self, data, next, prev):
		self.data = data
		self.next = next
		self.prev = prev


class cirListDeque(object):
		sentinel = Link(None, None, None)
		sentinel.prev = sentinel.next = sentinel
		size = 0

		def _addLinkAfter(self, oldLink, data):
			newLink = Link(data, None, None)
			# creates a new link with the value from the parameter

			oldLink.next.prev = newLink
			# sets the link's next's previous to the new link

			newLink.next = oldLink.next
			# sets the new link's next to the existing link's next

			oldLink.next = newLink
			# sets the new link after the existing link

			newLink.prev = oldLink
			# sets the new link's previous to the existing link

			self.size += 1
			# increments the size of the deque

		def addFront(self, data):
			self._addLinkAfter(self.sentinel, data)

		def addBack(self, data):
			self._addLinkAfter(self.sentinel.prev, data)

		def front(self):
			return (self.sentinel.next.data)

		def back(self):
			return (self.sentinel.prev.data)

		def _removeLink(self, oldLink):
			oldLink.prev.next = oldLink.next
			# sets the removed link's previous link's next, to the removed link's next

			oldLink.next.prev = oldLink.prev
			# sets the removed link's next link's prev, to the removed link's prev

			self.size -= 1
			# decrements the size of the deque

		def removeFront(self):
				self._removeLink(self.sentinel.next)

		def removeBack(self):
				self._removeLink(self.sentinel.prev)

		def isEmpty(self):
			return self.size == 0

		def printList(self):
			tempLink = self.sentinel.next
			while (tempLink != self.sentinel):
				print(tempLink.data)
				# prints the value contained in tempLink

				tempLink = tempLink.next
				# increments tempLink to its next

		def reverseDeque(self):
			link = self.sentinel
			temp = self.sentinel.next

			for index in range(0, self.size + 1):
				link.next = link.prev
				link.prev = temp
				link = temp
				temp = temp.next
