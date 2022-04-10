import random

def main(loops, percent):

    file = open("input.txt", "w")

    for l in range(loops):
        insertion = random.randint(1, 100)
        numUser   = random.randint(1, loops)

        if insertion < percent:
            add = "ACRESCENTA utilizador" + str(numUser) + " "

            creditCard = ""
            date       = ""

            for i in range(4):
                creditCard += str(random.randint(0, 9))
                date       += str(random.randint(0, 9))
            
            add += creditCard + " " + date + "\n"

            file.write(add)

        else:
            add = "CONSULTA utilizador"
            add += str(numUser) + "\n"

            file.write(add)
    
    file.write("FIM")


if __name__ == "__main__":
    # number of lines, percente of insertions
    main(3750000, 10)