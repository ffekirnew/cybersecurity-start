import random
import time

KEYSIZE = 16

def main():
    for t in range(1524020929 - 60 * 60 * 2, 1524020929): # within 2h window
        random.seed(t)
        key = [random.randint(0, 255) for _ in range(KEYSIZE)]
        for i in range(KEYSIZE):
            print('{:02x}'.format(key[i]), end='')
        print()

if __name__ == '__main__':
    main()

