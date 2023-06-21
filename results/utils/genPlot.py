import matplotlib.pyplot as plt

# Plot data from files
def plotData(files, title, labels, xLabel, yLabel):
    colors = ["b", "g", "r", "c", "m", "y", "k", "tab:brown"]

    for i in range(len(files)):
        with open(files[i], "r") as f:
            # Just plot column "expanded" (3) and "generated" (4) withouth the header
            data = f.readlines()[1:]

            # Distance to goal 34 - x
            x = [int(line.split(",")[0]) for line in data]
            x = [34 - x for x in x]
            
            y = [int(line.split(",")[3]) for line in data]
            yy = [int(line.split(",")[4]) for line in data]
            plt.plot(x, y, "--", label=labels[i] + " (expanded)", color=colors[i])
            plt.plot(x, yy, label=labels[i] + " (generated)", color=colors[i])

    # Y axis 10**1, 10**2, 10**3, 10**4, 10**5, 10**6...
    plt.yscale("log")
    plt.xlabel(xLabel)
    plt.ylabel(yLabel)
    plt.title(title)
    plt.legend()
    plt.show()

labelsNodes = [
    "Negamax",
    "Negamax α-β",
    "Scout",
    "Negascout",
]

files = [
    "../csv/negamax.csv",
    "../csv/negamax_ab.csv",
    "../csv/scout.csv",
    "../csv/negascout.csv",
]

files_tt = [
    "../csv/negamax_tt.csv",
    "../csv/negamax_ab_tt.csv",
    "../csv/scout_tt.csv",
    "../csv/negascout_tt.csv",
]

titleNodes = "Nodes generated and expanded (without transposition table)"
xLabelNodes = "Distance to goal PV" 
yLabelNodes = "# Nodes"
plotData(files, titleNodes, labelsNodes, xLabelNodes, yLabelNodes)

titleNodes = "Nodes generated and expanded (with transposition table)"
plotData(files_tt, titleNodes, labelsNodes, xLabelNodes, yLabelNodes)

labelsNodes = [
    "Negamax",
    "Negamax",
    "Negamax α-β",
    "Negamax α-β",
    "Scout",
    "Scout",
    "Negascout",
    "Negascout",
]
plotData(files + files_tt, titleNodes, labelsNodes, xLabelNodes, yLabelNodes)

labelsTime = [
    "Negamax",
    "Negamax α-β",
    "Scout",
    "Negascout",
]
yLabelTime = "Time (s)"

