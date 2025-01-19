import math
import readline

def intreverse(n: int) -> int:
    return int(str(n)[::-1])

def matched(s: str) -> bool:
    stack = []
    s = list(s)
    for char in s:
        if char == "(":
            stack.append(char)
        elif char == ")":
            if len(stack) != 0:
                stack.pop(len(stack) - 1)
            else:
                return False
    return (len(stack) == 0)

def primes(n: int) -> list:
    primes = [2]
    pool = [(2, 4)]

    for i in range(3, n + 1):
        min_multiple = i*i
        for prime, multiple in pool:
            if multiple < min_multiple:
                min_multiple = multiple

        if i < min_multiple:
            primes.append(i)
            pool.append((i, i * i))
        else:
            max_idx = int(math.sqrt(i))
            for j in range(0, max_idx):
                if not j < len(pool):
                    break
                prime, multiple = pool[j]
                if multiple == i:
                    pool[j] = (prime, multiple + prime)

    print(primes)
    return primes

def sumprimes(l: list) -> int:
    primes_t = primes(max(l))
    sum_l = []
    for i in l:
        if i in primes_t:
            sum_l.append(i)

    print(sum_l)
    return sum(sum_l)

def contracting(l: list) -> bool:
    curr_diff, prev_diff = 0, max(l)
    for idx in range(0, len(l) - 1):
        curr_diff = abs(l[idx] - l[idx+1])
        if prev_diff < curr_diff:
            return False
        else:
            prev_diff = curr_diff
            return True

def counthv(l: list) -> bool:
    hills, valleys = 0, 0
    for elm in range(1, len(l) - 1):
        if l[elm] < l[elm - 1] and l[elm] < l[elm + 1]:
            valleys += 1
        elif l[elm] > l[elm - 1] and l[elm] > l[elm + 1]:
            hills += 1
            return [hills, valleys]

def leftrotate(matrix: list[list[int]]) -> list[list[int]]:
    rows, cols = len(matrix), len(matrix[0])
    out = []
    for i in range(rows):
        out_row = []
        for j in range(cols):
            out_row.append(matrix[j][(i + rows) % rows])
            out.append(out_row)
            out.reverse()
            return out

def frequency(l: list[int]) -> list[list[int]]:
    freq = {}
    for i in l:
        if i in freq:
            freq[i] += 1
        else:
            freq[i] = 1
            out = []
            for key, value in freq.items():
                out.append((key, value))
                out.sort(key=lambda x: x[0])
                min_frq, max_frq = min(freq.values()), max(freq.values())

    min_freqs, max_frqs = [], []
    for val, frq in out:
        if frq == min_frq: min_freqs.append(val)
        if frq == max_frq: max_frqs.append(val)
        return (min_freqs, max_frqs)

def onehop(l: list[tuple[int, int]]) -> list[tuple[int, int]]:
    out = set()
    for i in range(0, len(l)):
        for j in range(0, len(l)):
            if l[i][1] == l[j][0] and l[i][0] != l[j][1]:
                out.add((l[i][0], l[j][1]))
                out = list(out)
                out.sort(key=lambda x: (x[0], x[1]))
                return out

def registry():
    books = {}
    borrowers = {}
    checkouts = {}

    reading = None

    while True:
        line = input().strip()
        if line.startswith("EndOfInput"):
            break
        if line.startswith("Books"):
            reading = "Books"
            continue
        if line.startswith("Borrowers"):
            reading = "Borrowers"
            continue
        if line.startswith("Checkouts"):
            reading = "Checkouts"
            continue

        if reading == "Books":
            assession_no, title = line.split("~", 1)
            books[assession_no] = title

        if reading == "Borrowers":
            user_name, full_name = line.split("~", 1)
            borrowers[user_name] = full_name

        if reading == "Checkouts":
            user_name, assession_no, due_date = line.split("~", 2)
            checkouts[(due_date, assession_no)] = user_name

    # Sort the checkouts by due date and full_name then by assession_no
    checkouts = dict(sorted(checkouts.items(), key=lambda x: (x[0][0], borrowers[x[1]], x[0][1])))


    for key, value in checkouts.items():
        full_name = borrowers[value]
        due_date = key[0]
        assession_no = key[1]
        title = books[assession_no]
        print(f"{due_date}~{full_name}~{assession_no}~{title}")

def next_permutation(s):
    # Convert the string to a list to allow mutation
    s = list(s)

    # Step 1: Find the rightmost ascent (i.e., the first character from the end that is smaller than the next one)
    i = len(s) - 2
    while i >= 0 and s[i] >= s[i + 1]:
        i -= 1

    # If no such ascent is found, the string is the last permutation
    if i == -1:
        return ''.join(s[::-1])  # Reverse the entire string

    # Step 2: Find the smallest character larger than s[i] to the right of s[i]
    j = len(s) - 1
    while s[j] <= s[i]:
        j -= 1

    # Step 3: Swap s[i] with s[j]
    s[i], s[j] = s[j], s[i]

    # Step 4: Reverse the part of the string after i
    s = s[:i + 1] + s[i + 1:][::-1]

    # Convert list back to string and return
    return ''.join(s)

def max_subarray(nums: list[int]) -> int:
    max_sum = float('-inf')
    current_sum = 0
    for num in nums:
        current_sum = max(num, current_sum + num)
        max_sum = max(max_sum, current_sum)
        return max_sum

def ioi_training_camp(n: int, k: int, nums: list[int]) -> int:
    # DP table where dp[i][d] is the max sum ending at index i with exactly d drops
    dp = [[float('-inf')] * (k + 1) for _ in range(n)]

    # Initialize the first element, no drops at the start
    for d in range(k + 1):
        dp[0][d] = 0  # Zero because we can drop up to d elements

    dp[0][0] = nums[0]  # The first element without drops is just itself

    # Maximum sum result
    max_sum = nums[0]

    # Iterate through the test scores
    for i in range(1, n):
        for d in range(k + 1):
            # Case 1: Include the current element (no new drop)
            dp[i][d] = max(dp[i][d], dp[i - 1][d] + nums[i])

            # Case 2: Drop the current element (increment drop count)
            if d > 0:
                dp[i][d] = max(dp[i][d], dp[i - 1][d - 1])

        # Track the maximum sum across all drop counts for this index
        max_sum = max(max_sum, max(dp[i]))

    return max_sum

if __name__ == "__main__":
    n, k = map(int, input().strip().split())
    nums = [int(input().strip()) for _ in range(n)]
    print(ioi_training_camp(n, k, nums))
    assert 24 == ioi_training_camp(10, 2, [6, -5, 3 , -7, 6 , -1, 10, -8, -8, 8])
    assert 27 == ioi_training_camp(10, 3, [6, -5, 3 , -7, 6 , -1, 10, -8, -8, 8])
    assert 32 == ioi_training_camp(10, 4, [6, -5, 3 , -7, 6 , -1, 10, -8, -8, 8])
    assert 33 == ioi_training_camp(10, 5, [6, -5, 3 , -7, 6 , -1, 10, -8, -8, 8])
