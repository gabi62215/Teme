from collections import defaultdict
from functools import reduce
import sys

class Dfa:
	_alphabet = []
	_initial_state = -1
	_delta = {}
	_current_state = -1
	_token = ""
	_states = 0

	def __init__(self):
		self._alphabet = []
		self._final_states = []
		self._delta = {}
		self._token = ""
		self._states = 0
		self._initial_state = -1
		self._current_state = -1

	def print_dfa(self):
		print("".join(self._alphabet))
		print(self._states)
		print(self._initial_state)
		s = ""
		for x in self._final_states:
			s = s + str(x) + " "
		s = s[:-1]
		print(s)
		s = ""
		for key in self._delta:
			s = s + str(key[0]) + "," + key[1] + "," + str(self._delta[key])
			print(s)
			s = ""

	def write_dfa(self):

		s = ""
		s = s + "".join(self._alphabet) + "\n"
		s = s + str(self._states) + "\n"
		s = s + str(self._initial_state) + "\n"
		t = ""
		for x in self._final_states:
			t = t + str(x) + " "
		t = t[:-1]
		s = s + t + "\n"
		t = ""
		for key in self._delta:
			t = t + str(key[0]) + "," + "'" + key[1] + "'" + "," + str(self._delta[key]) + "\n"
			s = s + t
			t = ""

		return s

class Nfa:
	_alphabet = []
	_initial_state = -1
	_final_states = []
	_delta = []
	_current_state = -1
	_token = ""

	def __init__(self):
		self._alphabet = []
		self._final_states = []
		self._delta = []
		self._token = ""

	def print_nfa(self):
		print(self._initial_state)
		print(self._final_states)
		print(self._delta)

class Expr:
	def __init__ (self):
		pass

	def __str__(self):
		pass

class Symbol(Expr):
	_char: str

	def __init__(self, c: str):
		self._char = c

	def __str__(self):
		return self._char


class Star(Expr): # (aab)* -> Star Expr(aab)
	_expr: Expr

	def __init__(self, expr: Expr):
		self._expr = expr

	def __str__(self):
		return "(" + self._expr.__str__() + ")*"

class Concat(Expr):
	_expr1: Expr
	_expr2: Expr

	def __init__(self, expr1: Expr, expr2: Expr):
		self._expr1 = expr1
		self._expr2 = expr2

	def __str__(self):
		return "(" + self._expr1.__str__() + ").(" + self._expr2.__str__() + ")"

class Plus(Expr):
	_expr: Expr

	def __init__(self, expr: Expr):
		self._expr = expr

	def __str__(self):
		return "(" + self._expr.__str__() + ")+"

class Union(Expr):
	_expr1: Expr
	_expr2: Expr

	def __init__(self, expr1: Expr, expr2: Expr):
		self._expr1 = expr1
		self._expr2 = expr2

	def __str__(self):
		return self._expr1.__str__() + " U " + self._expr2.__str__()

def parse_expr(s):
	words = s.split(" ")
	if len(words) == 1:
		return Symbol(words[0])
	while len(words) != 1:
		i = -1
		#add plus
		while words[i] != "STAR" and words[i] != "UNION" and words[i] != "CONCAT":
			if isinstance(words[i],Expr):
				i = i - 1
				continue
			words[i] = Symbol(words[i])
			i = i - 1
		
		if words[i] == "STAR":
			words[i] = Star(words[i+1])
			del words[i+1]

		# if words[i] == "PLUS":
		# 	words[i] = Star(words[i+1])
		# 	del words[i+1]

		elif words[i] == "UNION":
			words[i] = Union(words[i+1],words[i+2])
			if i+3 == 0:
				del words[i+1:]
			else:
				del words[i+1:i+3]

		elif words[i] == "CONCAT":
			words[i] = Concat(words[i+1],words[i+2])
			if i+3 == 0:
				del words[i+1:]
			else:
				del words[i+1:i+3]

	return words[0]	

def get_expr(input_name):
	input_file = open(input_name,"r")
	input_data = input_file.read()

	input_file.close()
	return parse_expr(input_data)
	
	#return parse_expr(input_data)

def symbol_to_nfa(symbol,i):
	nfa = Nfa()

	#build nfa for simple symbol
	nfa._alphabet.append(symbol._char)
	nfa._initial_state = i 
	nfa._final_states.append(i + 1)
	nfa._current_state = i 
	nfa._delta.append((i,symbol._char,i + 1))

	#increment i for each state assigned
	i = i + 2

	#nfa.print_nfa()

	return (nfa,i)

def expr_to_nfa(expr,i):
	if isinstance(expr,Symbol):
		return symbol_to_nfa(expr,i)
	elif isinstance(expr,Concat):
		return concat_to_nfa(expr,i)
	elif isinstance(expr,Union):
		return union_to_nfa(expr,i)
	elif isinstance(expr,Star):
		return star_to_nfa(expr,i)

def concat_to_nfa(concat,i):
	nfa = Nfa()

	#get nfas for each expr
	nfa_1 = expr_to_nfa(concat._expr1,i)
	i = nfa_1[1]
	nfa_2 = expr_to_nfa(concat._expr2,i)
	i = nfa_2[1]

	#connect final state of nfa_1 to initial state of nfa_2

	#set alphabet
	nfa._alphabet = nfa_1[0]._alphabet + nfa_2[0]._alphabet
	nfa._alphabet = list(dict.fromkeys(nfa._alphabet))

	#set states
	nfa._initial_state = nfa_1[0]._initial_state
	nfa._final_states = nfa_2[0]._final_states.copy()
	nfa._current_state = nfa_1[0]._initial_state

	#set delta
	nfa._delta = nfa_1[0]._delta + nfa_2[0]._delta
	nfa._delta.append((nfa_1[0]._final_states[-1],"",nfa_2[0]._initial_state))

	return (nfa,i)

def union_to_nfa(union,i):
	nfa = Nfa()

	#get nfas for each expr
	nfa_1 = expr_to_nfa(union._expr1,i)
	i = nfa_1[1]
	nfa_2 = expr_to_nfa(union._expr2,i)
	i = nfa_2[1]

	#add transition from initial state of nfa to each initial state of nfa_1 and nfa_2
	#add transition from finale states of nfa_2 and nfa_1 to final state of nfa

	#set alphabet
	nfa._alphabet = nfa_1[0]._alphabet + nfa_2[0]._alphabet
	nfa._alphabet = list(dict.fromkeys(nfa._alphabet))

	#set states
	nfa._initial_state = i
	nfa._final_states.append(i + 1)
	nfa._current_state = i

	#set delta
	nfa._delta = nfa_1[0]._delta + nfa_2[0]._delta
	nfa._delta.append((i,"",nfa_1[0]._initial_state))
	nfa._delta.append((i,"",nfa_2[0]._initial_state))
	nfa._delta.append((nfa_1[0]._final_states[-1],"",i + 1))
	nfa._delta.append((nfa_2[0]._final_states[-1],"",i + 1))

	#increment i for each state assigned
	i = i + 2

	return (nfa,i)

def star_to_nfa(star,i):
	nfa = Nfa()

	#get nfa for expr
	nfa_1 = expr_to_nfa(star._expr,i)
	i = nfa_1[1]

	#add transition from initial state of nfa to initial state of nfa_1
	#add transition from final state of nfa_1 to final state of nfa
	#add transition from final state of nfa_1 to initial state of nfa
	#add transition from initial state of nfa to final state of nfa

	#set alphabet
	nfa._alphabet = nfa_1[0]._alphabet.copy()
	nfa._alphabet = list(dict.fromkeys(nfa._alphabet))
	
	#set states
	nfa._initial_state = i
	nfa._final_states.append(i + 1)
	nfa._current_state = i

	#set delta
	nfa._delta = nfa_1[0]._delta.copy()
	nfa._delta.append((i,"",nfa_1[0]._initial_state))
	nfa._delta.append((nfa_1[0]._final_states[-1],"",i + 1))
	nfa._delta.append((nfa_1[0]._final_states[-1],"",i))
	nfa._delta.append((i,"",i + 1))

	#increment i for each state assigned
	i = i + 2

	return (nfa,i)

def plus_to_nfa(plus,i):
	nfa = Nfa()

	nfa_1 = expr_to_nfa(plus,_expr,i)
	i = nfa_1[1]

	


def regex_to_nfa(file_name):
	expr = get_expr(file_name)
	nfa = expr_to_nfa(expr,0)

	return nfa[0]

def get_epsilon_closures(nfa):
	#queue for adding each transition that you reach by epsilon
	queue = []
	epsilon_closures = defaultdict(list)

	#check every transition in delta to get epsilon closure
	for transition in nfa._delta:

		#check if state was reached before
		if not transition[0] in epsilon_closures[transition[0]]:
			epsilon_closures[transition[0]].append(transition[0])
		if not transition[2] in epsilon_closures[transition[2]]:
			epsilon_closures[transition[2]].append(transition[2])

		#found epsilon transition,add to_state to the queue for futher inspecting
		if transition[1] == "":
			epsilon_closures[transition[0]].append(transition[2])
			queue.append(transition[2])

		#see how far you can get by epsilon
		while queue != []:
			state = queue.pop(0)

			for x in nfa._delta:
				if x[0] == state and x[1] == "" and (not x[2] in epsilon_closures[transition[0]]):
					epsilon_closures[transition[0]].append(x[2])
					queue.append(x[2])

	#delete any duplicates
	for key in epsilon_closures:
		epsilon_closures[key] = list(dict.fromkeys(epsilon_closures[key]))

	return epsilon_closures

def get_state(states,delta,symbol,epsilon_closures):
	#list to add reachable states
	l = []

	#iterate through each state and check delta
	for x in states:
		for transition in delta:
			if transition[0] == x and transition[1] == symbol:
				l = l + epsilon_closures[transition[2]]

	return l

def check_finale_state(l_1,l_2):
	#checks if element in l_1 is prezent in l_2
	for x in l_1:
		if x in l_2:
			return True

	return False


def nfa_to_dfa(nfa):
	epsilon_closures = get_epsilon_closures(nfa)
	dfa = Dfa()
	i = 0
	#dictionary to map int states to set states
	states = {}
	sink_state = -1

	#get initial state and add it to states
	initial_state = frozenset(epsilon_closures[nfa._initial_state])
	states[initial_state] = i
	i = i + 1

	#set initial and current state
	dfa._initial_state = states[initial_state]
	dfa._current_state = states[initial_state]

	#queue for processing each state
	queue = []
	queue.append(initial_state)
	processed = []
	
	#as long as queue is not empty process states
	while queue != []:
		#dequeue and get list from set
		from_state = queue.pop()
		l = list(from_state)
		
		#check if any state from initial nfa is final in order to make dfa state final
		if(check_finale_state(l,nfa._final_states)) and (not states[from_state] in dfa._final_states):
			dfa._final_states.append(states[from_state])

		#iterate through alphabet to complete delta
		for x in nfa._alphabet:
			#add each character to the dfa alphabet
			if x != "" and (not x in dfa._alphabet):
				dfa._alphabet.append(x)

			#get state and add it to dictionary
			to_state = frozenset(get_state(l,nfa._delta,x,epsilon_closures))
			if not to_state in states:
				states[to_state] = i
				i = i + 1

			#add transition and check if the discovered state is final
			if to_state != frozenset():
				dfa._delta[(states[from_state],x)] = states[to_state]

				if check_finale_state(to_state,nfa._final_states) and (not states[to_state] in dfa._final_states):
					dfa._final_states.append(states[to_state])

				#add new discovered state to be queue,if it wasn't already processed
				if not to_state in processed:
					queue.append(to_state)

			#if it is an empty set,then the state is a sink state
			else:
				dfa._delta[(states[from_state],x)] = states[to_state]
				sink_state = states[to_state]

		#mark state as processed
		processed.append(from_state)

	#if a sink state exists,add transition to it
	if sink_state != -1:
		for x in dfa._alphabet:
			dfa._delta[(sink_state,x)] = sink_state

	#set number of states
	dfa._states = len(states)
	return dfa

if __name__ == "__main__":
	
	#regex to nfa to dfa
	nfa = regex_to_nfa(sys.argv[1])
	dfa = nfa_to_dfa(nfa)

	#write to file
	output_file = open(sys.argv[2],"w")
	output_data = dfa.write_dfa()
	output_file.write(output_data)
	output_file.close()
