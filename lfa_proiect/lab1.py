class Dfa:
	_alphabet = []
	_initial_state = -1
	_final_states = []
	_delta = {}
	_current_state = -1
	_token = ""

	def __init__(self,text):

		#initialize
		self._alphabet = []
		self._final_states = []
		self._delta = {}
		self._token = ""

		#split by '\n'
		rows = text.split('\n')
		split_rows = []

		#split each row by ','
		for x in rows[3:]:
			split_rows.append(x.split(','))

		#get token,alphabet and initial state	
		self._alphabet = rows[0]
		#self._alphabet = list(self._alphabet)
		self._token = rows[1]
		self._initial_state = int(rows[2])
		self._current_state = int(rows[2])

		
		i = 0
		while i < len(split_rows) - 1:
			if split_rows[i][1] == "'\\n'":
				split_rows[i][1] = '\n'
			elif split_rows[i][1] == "' '":
				split_rows[i][1] = ' '
			else:
				s = split_rows[i][1]
				s = s[1:-1]
				split_rows[i][1] = s
			self._delta[(int(split_rows[i][0]),split_rows[i][1])] = int(split_rows[i][2])
			i = i + 1
	
		for x in rows[-1].split(' '):
			self._final_states.append(int(x))

	def one_step(self,state,word):
		self._current_state = state
		if (state,word[0]) in self._delta and (word[0] in self._alphabet):
			self._current_state = self._delta[(state,word[0])]
		else:
			self._current_state = -1
		word = word[1:]
		return word

	def accepted(self,word):
		while word != "":
			word = self.one_step(self._current_state,word)
			if self._current_state == -1:
				break
			
		copy_of_current_state = self._current_state
		self._current_state = self._initial_state
		return copy_of_current_state in self._final_states

	def print_dfa(self):
		print(self._alphabet)
		print(self._initial_state)
		print(self._final_states)
		print(self._delta)
		print(self._token)

if __name__ == "__main__":
	info = "abcdef\nPATTERN1\n0\n0,'a',1\n0,'b',2\n0,'c',1\n0,'d',1\n0,'e',3\n0,'f',1\n2,'a',5\n2,'b',4\n2,'c',6\n2,'d',1\n2,'e',7\n2,'f',1\n3,'a',5\n3,'b',4\n3,'c',6\n3,'d',1\n3,'e',7\n3,'f',1\n4,'a',5\n4,'b',4\n4,'c',6\n4,'d',1\n4,'e',7\n4,'f',1\n5,'a',5\n5,'b',2\n5,'c',6\n5,'d',1\n5,'e',7\n5,'f',1\n6,'a',11\n6,'b',1\n6,'c',6\n6,'d',1\n6,'e',1\n6,'f',1\n7,'a',5\n7,'b',4\n7,'c',6\n7,'d',1\n7,'e',7\n7,'f',8\n8,'a',1\n8,'b',1\n8,'c',1\n8,'d',9\n8,'e',1\n8,'f',1\n9,'a',1\n9,'b',1\n9,'c',1\n9,'d',1\n9,'e',10\n9,'f',1\n10,'a',1\n10,'b',1\n10,'c',1\n10,'d',1\n10,'e',10\n10,'f',8\n11,'a',11\n11,'b',1\n11,'c',6\n11,'d',1\n11,'e',1\n11,'f',1\n3 9 4 7 11 6 5 2"
	info_2 = "\\n\nNEWLINE\n0\n0,'\\n',1\n1,'\\n',2\n1"
	info_3 = " \nSPACE\n0\n0,' ',1\n1,' ',2\n1"
	x = Dfa(info)
	y = Dfa(info_2)
	z = Dfa(info_3)
	t = Dfa()

	z.print_dfa()
	y.print_dfa()
	x.print_dfa()
	if y.accepted("\n"):
		print("bun1")

	if z.accepted(" "):
		print("bun2")

	if x.accepted("b"):
		print("bun3")
	# if(y.accepted("b")):
	# 	print("Bun")
	# else:
	# 	print("Nu")

	# if(x.accepted("0111")):
	# 	print("Bun")
	# else:
	# 	print("Nu")

	# if(x.accepted("01111")):
	# 	print("Bun")
	# else:
	# 	print("Nu")
	
	# if(y.accepted("bb")):
	# 	print("Bun")
	# else:
	# 	print("Nu")



		

