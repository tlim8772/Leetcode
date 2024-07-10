


import java.util.*;
//import java.util.function.Function;
 
public class lc3134 {
   // basically we use 2 pointer to find count of subarrays with #distinct elems >= limit
   // then binary seach on limit
   
   public long countSubArrays(int[] nums, int limit) {
      long sum = 0;
      HashMap<Integer, Integer> map = new HashMap<>();
      int distinct = 0;
      int p1 = 0;
      int p2 = 0;
      while (p1 < nums.length) {
         if (p2 == nums.length) {
            sum += (distinct >= limit) ? 1 : 0;
            
         } else {
            while (p2 < nums.length && distinct < limit) {
               Integer c = map.get(nums[p2]);
               if (c == null || c == 0) {
                  distinct ++;
                  map.put(nums[p2], 1);
               } else {
                  map.put(nums[p2], c + 1);
               }
               p2 ++;
            }
            sum += (distinct >= limit) ? nums.length - p2 + 1 : 0;
         }
         Integer back = map.get(nums[p1]);
         if (back == 1) {
            map.put(nums[p1], 0);
            distinct --;
         } else {
            map.put(nums[p1], back - 1);
         }
         p1 ++;
      }
      return sum;
   }

   public int medianOfUniquenessArray(int[] nums) {
      long len = (long) nums.length;
      long t = len * (len + 1) / 2;
      long target = (t / 2) + 1;
      int s = 1;
      int e = nums.length;
      while (s < e) {
         int m = (s + e) / 2 + (s + e) % 2;
         long count = countSubArrays(nums, m);
         if (count < target) {
            e = m - 1;
         } else {
            s = m;
         }
      }
      return s;     
   }


   public static void main(String[] args) {
      int[] arr = {4,3,5,4};
      lc3134 sol = new lc3134();
      long ans = sol.medianOfUniquenessArray(arr);
      System.out.println(ans);
   }
    
}