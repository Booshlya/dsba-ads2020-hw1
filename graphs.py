import pandas as pd
from matplotlib import pyplot as plt

chart = pd.read_csv("cmake-build-release/project.results")


plt.plot(chart["size"],chart["grade school"], label = "Grade School")
plt.plot(chart["size"],chart["div_n_conq"], label = "divide and conq")
plt.plot(chart["size"],chart["Karatsuba"], label = "Karatsuba")
plt.legend()
plt.show()