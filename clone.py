import os


def main():
    file_name = os.path.basename(__file__)
    with open(file_name, "r") as f:
        file = f.read()
        os.system(f"echo '{file}' | lolcat")
    # delete file clone.py
    os.remove(file_name)
    # create a new file clone.py
    os.system(f"touch copy_{file_name}")
    # write content to the new file
    with open(f"copy_{file_name}", "w") as f:
        f.write(file)


if __name__ == "__main__":
    main()
