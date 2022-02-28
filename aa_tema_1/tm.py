import fileinput
import re


class Turing_Machine:
	number_of_states = 1
	final_states = []
	transitions = []
	configuration = []

def readTM():

	number_of_states = input()
	final_states_strings = raw_input().split()

	transition = []
	for line in fileinput.input():
		transition.append(line)

	turing_machine = Turing_Machine()
	
	turing_machine.number_of_states = number_of_states
	turing_machine.final_states = final_states_strings

	for x in transition:
		#position 0 current state
		#position 1 current symbol
		#position 2 next state
		#position 3 new symbol
		#position 4 cursor position
		aux = x.split()
		turing_machine.transitions.append(aux)
		
	return turing_machine

def stepReadAndPrint():

	configurations = raw_input().split();
	turing_machine = readTM()
	str = ""

	for x in configurations:
		
		#deletes '(' ')' and splits by ,
		#position 0 what's on the left side of the cursor
		#position 1 current state
		#position 2	what's on the right side of the cursor
		x = x.replace('(', '').replace(')', '')
		x = x.split(',')

		turing_machine.configuration = x
		result = step(turing_machine)

		if result == False:
			str += "False "
		else:
			str += "(" + result[0] + "," + result[1] + "," + result[2] + ") "
	#delete last space			
	str = str[:-1]	
	print(str)

def step(turing_machine):

	for x in turing_machine.transitions:
	#look for state and symbol
		if x[0] == turing_machine.configuration[1] and x[1] == turing_machine.configuration[2][0]:
			#modify current symbol and state
			string_list = list(turing_machine.configuration[2])
			string_list[0] = x[3]
			turing_machine.configuration[2] = "".join(string_list)
			turing_machine.configuration[1] = x[2]

			if x[4] == 'H':
				return turing_machine.configuration
			if x[4] == 'L':
			#add last letter from left word to the start of the word from the right
			#delete last letter from left word
				last_letter = len(turing_machine.configuration[0])-1
				turing_machine.configuration[2] = turing_machine.configuration[0][last_letter] + turing_machine.configuration[2]
				turing_machine.configuration[0] = turing_machine.configuration[0][:-1]
				if not turing_machine.configuration[0]:
					turing_machine.configuration[0] = "#"

			if x[4] == 'R':
			#add first letter from right to the end from left
			#delete first letter from right word
				turing_machine.configuration[0] = turing_machine.configuration[0] + turing_machine.configuration[2][0]
				turing_machine.configuration[2] = turing_machine.configuration[2][1:]
				if not turing_machine.configuration[2]:
					turing_machine.configuration[2] = "#"

			return turing_machine.configuration

	return False

def accept(turing_machine,word):
#write the word
	turing_machine.configuration = ["#","0","#"]
	turing_machine.configuration[2] = word
	
#loop until the machine reaches either a final state or step return false
	while step(turing_machine):

	#execute one step and check if it reached a final state
		for x in turing_machine.final_states:
			if x == turing_machine.configuration[1]:
				return True
			

	return False

def acceptReadAndPrint():

	words = raw_input().split();
	turing_machine = readTM()
	str = ""

	for x in words:
	#call function for each word
		if accept(turing_machine,x):
			str += "True "
		else:
			str +="False "
	#delete last space			
	str = str[:-1]	
	print(str)

def k_accept(turing_machine,k,word):
#write the word
	turing_machine.configuration = ["#","0","#"]
	turing_machine.configuration[2] = word
#count number of steps
	i = 0

	k = int(k)
	while step(turing_machine):
		
		i += 1

		if i > k:
			return False

		for x in turing_machine.final_states:
			if x == turing_machine.configuration[1] and i <= k:
				return True
	#if the steps are bigger then k return False
		
	
	return False

def k_acceptReadAndPrint():
	
	words_k = raw_input().split();
	turing_machine = readTM()
	str = ""

	for x in words_k:
	#call function for each word and k 
	#split string by , to get word and k
		x = x.split(",")
		if k_accept(turing_machine,x[1],x[0]):
			str += "True "
		else:
			str +="False "
	#delete last space		
	str = str[:-1]	
	print(str)


if __name__ == "__main__":

	name = raw_input()
	if name == "step":
		stepReadAndPrint()
	if name == "accept":
		acceptReadAndPrint()
	if name == "k_accept":
		k_acceptReadAndPrint()
	

	

		