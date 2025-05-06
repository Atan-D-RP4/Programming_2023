def quad_sum(nums: list[int], index: int) -> int:
    if index == len(nums):
        return 0

    if nums[index] > 0:
        return quad_sum(nums, index + 1)
    return nums[index] ** 4 + quad_sum(nums, index + 1)


def solution(max_depth: int, ans: list[int]) -> None:
    if max_depth == 0:
        return

    count = int(input())
    nums = list(map(int, input().strip().split()))

    if count != len(nums):
        ans.append(-1)
        return
    ans.append(quad_sum(nums, 0))
    solution(max_depth - 1, ans)


def print_list(nums: list[int], index: int) -> None:
    if index == len(nums):
        return

    print(nums[index], end="\n")
    print_list(nums, index + 1)


def main() -> None:
    tests: int = int(input())

    ans: list[int] = []
    solution(tests, ans)
    print_list(ans, 0)


if __name__ == "__main__":
    main()

"""
{
  "github_url": "https://gist.github.com/Atan-D-RP4/a0f49be4a4890f4b42fc0e8dc60d6cb8",
  "contact_email": "chaitanyarp4@gmail.com",
  "solution_language": "python"
}
"""

"""
curl -X POST https://api.challenge.hennge.com/challenges/backend-recursion/004 \
     -H "Authorization: Basic bmluamFAZXhhbXBsZS5jb206MTU5NTk0MjU2MA==" \
     -H "Accept: */*" \
     -H "Content-Type: application/json" \
     -H "Content-Length: 159" \
     -d '{ "github_url": "https://gist.github.com/Atan-D-RP4/a0f49be4a4890f4b42fc0e8dc60d6cbb8", "contact_email": "chaitanyarp4@gmail.com", "solution_language": "python" }'
"""
