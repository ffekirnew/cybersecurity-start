from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

def main():
    data = bytearray.fromhex('255044462d312e350a25d0d4c5d80a34')
    ciphertext = bytearray.fromhex('d06bf9d0dab8e8ef880660d2af65aa82')
    iv = bytearray.fromhex('09080706050403020100A2B2C2D2E2F2')

    with open('key_dict.txt') as f:
        keys = f.readlines()

    for k in keys:
        k = k.rstrip('\n')
        key = bytearray.fromhex(k)
        cipher = Cipher(algorithms.AES(bytes(key)), modes.CBC(iv))
        encryptor = cipher.encryptor()
        guess = encryptor.update(data)+ encryptor.finalize()
        if guess == ciphertext:
            print("Found the key:", k)
            exit(0)

    print("Cannot find the key!")

if __name__ == "__main__":
    main()
