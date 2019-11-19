from matplotlib.pylab import *
from matplotlib.pyplot import legend
from sys import argv

if len(argv) > 1:
    filnavn = argv[1]
else:
    filnavn = input("filnavn: ")

Tlist  = [[], [], [], []]
Elist  = [[], [], [], []]
Cvlist = [[], [], [], []]
Mlist  = [[], [], [], []]
Xlist  = [[], [], [], []]

counter = -1

with open(filnavn, "r") as infile:
    for line in infile:
        if line.split() == []:
            counter += 1
        else:
            T, E, Cv, M, X = line.split()
            Tlist[counter].append(eval(T))
            Elist[counter].append(eval(E))
            Cvlist[counter].append(eval(Cv))
            Mlist[counter].append(eval(M))
            Xlist[counter].append(eval(X))

Liste = [["<E(T)>", Elist], ["Cv", Cvlist], ["<|M|>", Mlist], ["X", Xlist]]
for i in range(len(Liste)):
    figure()
    xlabel("T")
    ylabel(Liste[i][0])
    for j in range(len(Tlist)):
        plot(Tlist[j], Liste[i][1][j], label = "L = %i"%(40 + j * 20))
    legend()
    savefig("Figur0%i.png"%i)
show()