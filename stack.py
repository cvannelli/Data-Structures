# A simple Stack implementation


class Stack():
	def __init__(self):
		self.stack = []

	def push(self, value):
		self.stack.append(value)

	def isEmpty(self):
		return len(self.stack) == 0

	def pop(self):
		try:
			return self.stack.pop()
		except IndexError:
			print("Cannot pop an empty stack")

	def top(self):
		temp = self.pop()
		self.push(temp)
		return temp
