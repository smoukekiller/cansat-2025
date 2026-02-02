import shutil

a = input("y?")
if (a != "y"): exit()
for i in range(100):
    shutil.rmtree(str(i))