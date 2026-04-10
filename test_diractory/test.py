from typing import List

def twoSum(nums: List[int], target: int) -> List[int]:
    for i in range(len(nums) - 1):
        for n in range(i + 1, len(nums)):
            if nums[i] + nums[n] == target:
                return [i, n]
    return []
                
nums = [2,7,11,15, 20, 0, 3]
target = 3

r = twoSum(nums, target)
print(r)