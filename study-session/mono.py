import random

alphabet = list('abcdefghijklmnopqrstuvwxyz')
print(alphabet)
random.shuffle(alphabet)
print(alphabet)
random.shuffle(alphabet)
print(alphabet)
random.shuffle(alphabet)
print(alphabet)
new_alphabet = random.sample(alphabet, 26)
