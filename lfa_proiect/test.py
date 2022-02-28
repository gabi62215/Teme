from functools import reduce

def concat(l):
	def convert(x,y):
		return str(x) + str(y)

	if l == []:
		return ""
	else:
		return reduce(convert,l)

def string_to_int_list(l):
	return map(int,l)

if __name__ == "__main__":
	l = ["1","2","3"]
	p = []

	print(concat(p))

	x = list(string_to_int_list(l))
	print(x)