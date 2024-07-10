import java.util.*;

class Solution {
    // use the fact that a xor a = 0
    // randomly pick a indice i, and find num[i]
    // split array into <= num[i] and > num[i] and find the xor of the 2 partition
    // case 1, the 2 numbers are in different partition, then
    // the 2 arrays result != 0 and the 2 numbers are the xor result
    // case 2, the 2 numbers are in the same partition, then
    // 1 of the array result is 0, other array is not 0
    // recurse on the partition with xor != 0
    // we neeed tail call recursion to ensure space is constant
    // expected time complexity is linear
    // to ensure no 'new' space is generated, we use quicksort in place array partition

    Random rand = new Random();
    
    void swap(int[] nums, int idx0, int idx1) {
        int temp = nums[idx0];
        nums[idx0] = nums[idx1];
        nums[idx1] = temp;
    }

    int[] findAns(int[] nums, int s, int e) {
        
        
        if (e - s + 1 == 2) {
            return new int[] {nums[s], nums[s + 1]};
        }
        
        int partitionIdx = s + rand.nextInt(e - s + 1);
        int split = nums[partitionIdx];
        
        swap(nums, s, partitionIdx);
        int low = s + 1;
        int high = e;
        int xor0 = split;
        int xor1 = 0;

        while (low < high) {
            while (low <= e && nums[low] <= split) {
                xor0 = xor0 ^ nums[low];
                low ++;
            }
            while (high >= s + 1 && nums[high] > split) {
                xor1 = xor1 ^ nums[high];
                high --;
            }
            if (low < high) {
                swap(nums, low, high);
            }
        }

        // cannot use xor to find the 2 numbers, as one of the 2 numbers can be 0
        // use size of partition, if both size is even is case 1, xor is the ans
        // if both even, 1 of the partiton must have xor != 0
        
        if ((low - s) % 2 == 1 && (e - high) % 2 == 1) {
            return new int[] {xor0, xor1};
        } else if (xor0 != 0) {
            return findAns(nums, s, low - 1);
        } else {
            return findAns(nums, high + 1, e);
        }
    } 

    public int[] singleNumber(int[] nums) {
        return findAns(nums, 0, nums.length - 1);
    }

   

    public static void main(String[] args) {
        int[] arr = {0,1,1,2};
        int[] ans = new Solution().findAns(arr, 0, 3);
        System.out.println(Arrays.toString(ans));
        
    }


}
