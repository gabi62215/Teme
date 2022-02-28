"""
Sfaturi de implementare:
- from lab2 import Dfa
- creati 3 obiecte Dfa pentru A3, A4 si A5, incepand de la string
- creati o clasa Lexer care primeste o lista de Dfa-uri si pentru fiecare un
nume
- creati metoda Lexer.longest_prefix care primeste un cuvant (string) si
gaseste cel mai lung prefix acceptat de 1 din Dfa-uri
- creati metoda Lexer.parse care tot apeleaza longest_prefix pana a consumat
tot cuvantul
"""

from lab1 import Dfa

A3_text = '0\n0 a 0\n0 b 1\n1 a 1\n1 b 1\n0\n'
A4_text = '0\n0 b 0\n0 a 1\n1 a 1\n1 b 1\n0\n'
A5_text = '0\n0 a 1\n0 b 3\n1 a 3\n1 b 2\n2 a 3\n2 b 0\n3 a 3\n3 b 3\n1\n'

class Lexer:
	_dfas = []

	#parse string and create each dfa
	def __init__(self,dfas):
		self._dfas = []
		l = dfas.split("\n\n")
		for x in l:
			self._dfas.append(Dfa(x))

	def longest_prefix(self,word):
		current_prefix = ""
		identifer = ""
		index = -1
		
		#reverse list in order to get first priority if prefix length is equal
		for i in range(1,len(word) + 1):
			for x in reversed(self._dfas):
				if x.accepted(word[:i]):
					#save accepted word
					current_prefix = word[:i]

					#save afd name
					identifer = x._token

					#save index to delete prefix from word
					index = i

		return (identifer,current_prefix,index)

	def parse(self,word):
		text = ""

		#consume word by finding longest prefix
		while word != "":
			tup = self.longest_prefix(word)

			#build string
			ide = str(tup[0])
			prefix = tup[1]
			index_for_delete = tup[2]
			text = text + ide + ' ' + prefix + '\n'

			#delete prefix
			if len(word) == 1:
				word = ""
			else:
				word = word[index_for_delete:]

		#delete last '\n'
		text = text[:-1]
		return text

def runlexer(dfa_name,input_name,output_name):
	dfa_file = open(dfa_name,"r")
	input_file = open(input_name,"r")
	output_file = open(output_name,"w")

	dfa_data = dfa_file.read()
	input_data = input_file.read()

	x = Lexer(dfa_data)

	output_data = x.parse(input_data)
	output_file.write(output_data)

	dfa_file.close()
	input_file.close()
	output_file.close()



if __name__ == "__main__":
	runlexer("T1.1.lex","T1.1.1.in","test.txt")
	
