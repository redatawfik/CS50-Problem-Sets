import sys
import crypt

# All Capital and small letters to check
letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
# lenth of letters string
length = len(letters)
salt = "50"


def main():
    # check if user provide hashed passowrd
    if len(sys.argv) == 2:
        hash = sys.argv[1]
        if one(hash):
            return 0
        elif two(hash):
            return 0
        elif three(hash):
            return 0
        elif four(hash):
            return 0
        elif five(hash):
            return 0
        else:
            print("Not Found")
    else:
        print("Usage: ./crack hash")


def one(hash):
    # itrate throw one letter
    for c in letters:
        if crypt.crypt(c, salt) == hash:
            print(c)
            return True
    return False


def two(hash):
    # itrate throw two letters
    for c1 in letters:
        for c2 in letters:
            word = c1 + c2
            if crypt.crypt(word, salt) == hash:
                print(word)
                return True
    return False


def three(hash):
    # itrate throw three letters
    for c1 in letters:
        for c2 in letters:
            for c3 in letters:
                word = c1 + c2 + c3
                if crypt.crypt(word, salt) == hash:
                    print(word)
                    return True
    return False


def four(hash):
    # itrate throw four letters
    for c1 in letters:
        for c2 in letters:
            for c3 in letters:
                for c4 in letters:
                    word = c1 + c2 + c3 + c4
                    if crypt.crypt(word, salt) == hash:
                        print(word)
                        return True
    return False


def five(hash):
    # itrate throw five letters
    for c1 in letters:
        for c2 in letters:
            for c3 in letters:
                for c4 in letters:
                    for c5 in letters:
                        word = c1 + c2 + c3 + c4 + c5
                        if crypt.crypt(word, salt) == hash:
                            print(word)
                            return True
    return False


if __name__ == "__main__":
    main()
