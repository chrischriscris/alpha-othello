import matplotlib.pyplot as plt

# Plot data from files
def plotData(files, title, labels, xLabel, yLabel, x_idx, y_idx, exp=False):
    colors = ["b", "g", "r", "c", "m", "y", "k", "tab:brown"]

    for i in range(len(files)):
        with open(files[i], "r") as f:
            # Just plot column "expanded" (3) and "generated" (4) withouth the header
            data = f.readlines()[1:]

            # Distance to goal 34 - x
            x = [int(line.split(",")[x_idx]) for line in data]
            x = [34 - x for x in x]
            
            # If y is exponential (time), plot log(y)
            if (exp):
                y = [float(line.split(",")[y_idx[0]]) for line in data]
                plt.plot(x, y, label=labels[i], color=colors[i])
            else:
                y = [int(line.split(",")[y_idx[0]]) for line in data]
                plt.plot(x, y, "--", label=labels[i] + " (expanded)", color=colors[i])

            if (len(y_idx) > 1):
                yy = [int(line.split(",")[y_idx[1]]) for line in data]
                plt.plot(x, yy, label=labels[i] + " (generated)", color=colors[i])

    # Y axis 10**1, 10**2, 10**3, 10**4, 10**5, 10**6...
    plt.yscale("log")
    plt.xlabel(xLabel)
    plt.ylabel(yLabel)
    plt.title(title)
    plt.legend()
    plt.show()

labels = [
    "Negamax",
    "Negamax TT",
    "Negamax α-β",
    "Negamax α-β TT",
    "Scout",
    "Scout TT",
    "Negascout",
    "Negascout TT",
]

files = [
    "../tests/csv/negamax.csv",
    "../tests/csv/negamax_tt.csv",
    "../tests/csv/negamax_ab.csv",
    "../tests/csv/negamax_ab_tt.csv",
    "../tests/csv/scout.csv",
    "../tests/csv/scout_tt.csv",
    "../tests/csv/negascout.csv",
    "../tests/csv/negascout_tt.csv",
]
xLabel = "Distance to goal PV" 

# ----------------------- NODES -------------------------
titleNodes = "Nodes generated and expanded"
yLabelNodes = "# Nodes"

# No TT
labelsNodes = ["Negamax", "Negamax α-β", "Scout", "Negascout"]
filesNoTT = [files[0], files[2], files[4], files[6]]
titleNoTT = "Nodes generated and expanded (without transposition table)"
plotData(filesNoTT, titleNoTT, labelsNodes, xLabel, yLabelNodes, 0, [3, 4])

# With TT
filesTT = [files[1], files[3], files[5], files[7]]
titleTT = "Nodes generated and expanded (with transposition table)"
plotData(filesTT, titleTT, labelsNodes, xLabel, yLabelNodes, 0, [3, 4])

# Both
plotData(files, titleNodes, labels, xLabel, yLabelNodes, 0, [3, 4])

# ----------------------- TIME -------------------------
titleTime = "Time (s) to find the solution"
yLabelTime = "Time (s)"
plotData(files, titleTime, labels, xLabel, yLabelTime, 0, [5], True)