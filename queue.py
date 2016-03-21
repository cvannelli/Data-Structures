# A simple Queue implementation


class Queue():
	def __init__(self):
		self.queue = []

	def enqueue(self, value):
		self.queue.insert(0, value)

	def dequeue(self, value):
		try:
			return self.queue.pop()
		except IndexError:
			print("Cannot dequeue an empty queue")

	def size(self):
		return len(self.queue)

	def isEmpty(self):
		return len(self.queue) == 0
