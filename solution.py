class PizzaCombination():
	def __init__(self, people_in_team):
		self.people_in_team = people_in_team
		self.pizzas = []
		self.ingredients = set()
		self.score = 0

	def is_valid(self):
		return len(self.pizzas) == self.people_in_team

	def add_pizza(self, pizza):
		self.pizzas += [pizza]
		self.ingredients = self.ingredients.union(pizza[1])
		self.score = len(self.ingredients)**2

	def remove_pizza(self, pizza):
		self.pizzas.remove(pizza)
		self.ingredients = set()
		for p in self.pizzas:
			self.ingredients = self.ingredients.union(p[1])
		self.score = len(self.ingredients)**2

	def excange_pizzas(self, other_combination):
		while len(other_combination.pizzas) and not self.is_valid():
			best_score, best_pizza = -1, None
			for p in other_combination.pizzas:
				tmp_score = len(self.ingredients.union(p[1]))**2 - self.score
				if tmp_score > best_score:
					best_score = tmp_score
					best_pizza = p
			if best_score > -1:
				self.add_pizza(best_pizza)
				other_combination.remove_pizza(best_pizza)

	def __str__(self):
		return 'N people: %d; N pizzas: %d; Ingredients: %s; Score: %d' % (self.people_in_team, len(self.pizzas), str(self.ingredients), self.score)

	def res(self):
		return  ' '.join([str(self.people_in_team)] + [str(p[0]) for p in self.pizzas])


def input_data():
	teams = {}
	n_pizzas, teams[2], teams[3], teams[4] = [int(x) for x in input().split()]

	pizzas = []
	for _ in range(n_pizzas):
		pizzas += [set(input().split()[1:])]

	for x in teams:
		teams[x] = [[] for _ in range(teams[x])]

	return teams, pizzas


def solution(teams, pizzas):
	pizza_combinations = []
	for x in teams:
		pizza_combinations += [PizzaCombination(x) for _ in teams[x]]
	# print('\n'.join([str(x) for x in pizza_combinations]))

	for p in range(len(pizzas)):
		best_score, best_score_i = 0, -1
		for i in range(len(pizza_combinations)):
			if pizza_combinations[i].is_valid():
				continue

			tmp_score = len(pizza_combinations[i].ingredients.union(pizzas[p]))**2 - pizza_combinations[i].score
			if tmp_score > best_score:
				best_score = tmp_score
				best_score_i = i
		if best_score_i > -1:
			pizza_combinations[best_score_i].add_pizza((p, pizzas[p]))

	invalid_combinations = []
	i = 0
	while i < len(pizza_combinations):
		if not pizza_combinations[i].is_valid():
			tmp_combination = pizza_combinations.pop(i)
			if tmp_combination.score:
				invalid_combinations += [tmp_combination]
		else:
			i += 1

	while len(invalid_combinations) > 1 and invalid_combinations[1].score:
		invalid_combinations.sort(key=lambda x: -x.score)
		best_score, best_score_i = -1, -1
		for i in range(1, len(invalid_combinations)):
			tmp_score = len(invalid_combinations[0].ingredients.union(invalid_combinations[i].ingredients))**2 - invalid_combinations[0].score
			if tmp_score > best_score:
				best_score = tmp_score
				best_score_i = i
		if best_score_i > -1:
			invalid_combinations[0].excange_pizzas(invalid_combinations[best_score_i])
			if invalid_combinations[0].is_valid():
				pizza_combinations += [invalid_combinations.pop(0)]
		else:
			break

	print(len(pizza_combinations))
	for c in pizza_combinations:
		print(c.res())

	# print("Score:", sum([c.score for c in pizza_combinations]))


if __name__ == '__main__':
	teams, pizzas = input_data()
	solution(teams, pizzas)
