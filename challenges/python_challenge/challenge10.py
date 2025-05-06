import re

def look_and_say_seq(n: int) -> list[int]:
    sequence = []
    a = '1'
    b = ''
    sequence.append(a)

    for i in range(n):
        j = 0
        k = 0
        while j < len(a):
            while k < len(a) and a[j] == a[k]:
                k += 1
            b += str(k-j) + a[j]
            j = k
        sequence.append(b)
        a = b
        b = ''
    return sequence

def look_and_say_seq_re(n: int) -> list[int]:
    sequence_re = []
    x = '1'
    sequence_re.append(x)

    for i in range(30):
        x = ''.join([str(len(i+j)) + i for i, j in re.findall(r'(\d)(\1*)', x)])
        sequence_re.append(x)

    return sequence_re


print(look_and_say_seq(5))

#  seq = look_and_say_seq(30)
#  print(len(seq[30]))
#
#  seq_re = look_and_say_seq_re(30)
#  print(len(seq_re[30]))
