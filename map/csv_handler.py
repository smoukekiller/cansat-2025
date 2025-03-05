import os

def write_to_csv(directory: str, init_byte: int, timestamp: int, value) -> None:
    filename = directory+str(init_byte) + ".csv"
    with open(filename, "a") as f:
        f.write(str(timestamp) + "," + str(value) + "\r\n")

def init_csv() -> int:
    counter = 0
    while True:
        directory = str(counter)
        flag = os.path.exists(directory)
        if (flag):
            counter += 1
            continue
        else:
            os.mkdir(str(counter))
            return counter
        
if __name__ == "__main__":
    init_csv()