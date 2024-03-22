from typing import List

class Solution:
  def twoSum(self, nums: List[int], target: int) -> List[int]:
    lookup = {}
    for i, num in enumerate(nums):
      if target - num in lookup:
        return [lookup[target - num], i]
      lookup[num] = i

if __name__ == "__main__":
  solution = Solution()
  # nums = [2, 7, 11, 15]
  nums = list(map(int, input("Enter the array elements separated by space: ").strip().split()))
  print("\n")
  # target = 9
  target = int(input("Enter the target integer: "))
  print("\n")

  result = solution.twoSum(nums=nums, target=target)
  print(f"Input array: {nums}\n")
  print(f"target: {target}\n")
  print(f"Indices of the two numbers that add up to {target}: {result}")

  