from random import random


class Board:
    def __init__(self, slides):
        self.current = 1
        self.slides = {}
        for p in slides:
            start, end = [int(x) for x in p.split(",")]
            self.slides[start] = end

    def move(self, num):
        if self.current + num <= 100:
            self.current += num
        if self.current in self.slides:
            self.current = self.slides[self.current]
        return self.current


class Die:
    def __init__(self, probs):
        self.probs = [float(x) for x in probs]
        # if sum(self.probs) != 1.0:
        #   raise ValueError("Die: Probabilities don't add to one (%s)" % sum(self.probs))

    def roll(self):
        rand = random()
        for index, prob in enumerate(self.probs):
            if rand < prob:
                return index + 1
            rand -= prob
        return 6


def play(probs, ladders, snakes):
    board = Board(ladders + snakes)
    die = Die(probs)
    num_moves = 0
    while num_moves < 1000 and board.move(die.roll()) != 100:
        num_moves += 1
    return num_moves


t = int(input())

for _ in range(t):
    die_probs = list(map(float, input().split(",")))
    input()
    ladders = [x for x in input().split()]
    snakes = [x for x in input().split()]

    sum_ = 0
    trials = 0
    for i in range(5000):
        num_moves = play(die_probs, ladders, snakes)
        if num_moves < 1000:
            sum_ += num_moves
            num_trials += 1
        print(sum_ / num_trials)
