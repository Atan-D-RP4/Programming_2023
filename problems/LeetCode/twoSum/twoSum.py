from typing import List

def twoSum(nums: List[int], target: int) -> List[int]:
    index_dict = {}  # Dictionary to store indices of elements

    for i, num in enumerate(nums):
        complement = target - num
        if complement in index_dict:
            return [index_dict[complement], i]

        # Store the current element's index in the dictionary
        index_dict[num] = i

    return []

def main():
    nums = [3, 2, 4]
    result = twoSum(nums, 6)
    print(result)

if __name__ == "__main__":
    main()
