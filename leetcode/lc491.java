import java.util.*;

class Solution {
    HashMap<String, Boolean> used = new HashMap<>();
    List<List<Integer>> store = new ArrayList<>();

    public String buildString(List<Integer> arr) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < arr.size(); i ++) {
            sb.append(arr.get(i).toString());
            if (i != arr.size() - 1) sb.append(' ');
        }
        return sb.toString();
    }

    public void addSolution(List<Integer> arr) {
        if (arr.size() < 2) return;
        
        String s = buildString(arr);
        if (used.get(s) != null) return;
        
        used.put(s, true);
        store.add(new ArrayList<>(arr));
    }

    public void helper(int prev, int index, List<Integer> arr, int[] nums) {
        if (index == nums.length) {
            addSolution(arr);
        } else if (nums[index] < prev) {
            helper(prev, index + 1, arr, nums);
        } else {
            // take
            arr.add(nums[index]);
            helper(nums[index], index + 1, arr, nums);
            arr.remove(arr.size() - 1);

            // dont take
            helper(prev, index + 1, arr, nums);
        }
    }

    public List<List<Integer>> findSubsequences(int[] nums) {
        helper(-9999, 0, new ArrayList<>(), nums);
        return store;
    }

    public void print() {
        for (List<Integer> arr : store) {
            System.out.println(Arrays.toString(arr.toArray()));
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        sol.helper(-9999, 0, new ArrayList<>(), new int[] {1,2,3,4,5,6,7,8,9,10,1,1,1,1,1});
        sol.print();
    }
}