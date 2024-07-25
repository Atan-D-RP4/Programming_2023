def main():
    rules = {
        3: "Fizz",
        5: "Buzz",
        7: "Jazz",
        11: "Bazz",
        "limit": 100
    }

    for i in range(1, rules["limit"]+1):
        output = ""
        for key in rules:
            if key == "limit":
                continue
            if i % key == 0:
                output += rules[key]
        if output == "":
            output = i
        print(output)

if __name__ == '__main__':
    main()

