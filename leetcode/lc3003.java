package leetcode;
import java.util.*;

public class lc3003 {
    
    public int[] suffixStore(String s, int k) {
        int[] out = new int[s.length() + 1];
        int[] bitMap = new int[26];
        int distinct = 0;
        int p1 = s.length() - 1;
        int p2 = s.length() - 1;
        while (p1 >= 0) {
            int c1 = s.charAt(p1) - 'a';
            distinct += (bitMap[c1] == 0) ? 1 : 0;
            bitMap[c1] += 1;
            while (p2 > p1 && distinct > k) {
                int c2 = s.charAt(p2) - 'a';
                distinct -= (bitMap[c2] == 1) ? 1 : 0;
                bitMap[c2] -= 1;
                p2 --;
            }
            out[p1] = 1 + out[p2 + 1];
            p1 --;
        }
        return out;
    }

    // important lemma, suppose we have a partition [s, e]
    // then we cannot have an partion [s', e'] where s' >= s and e' < e
    
    ArrayList<int[]> rangeCompress(String s, int k) {
        ArrayList<int[]> out = new ArrayList<>();
        //int[] res = new int[] {0, 0, -1, -1}
        int p1 = 0;
        int p2 = 0;
        int useless = -1;
        // however, we need to consider the index S, where changing char at index S, causes the range to end at S - 1.
        // this means from [start, S - 1] we have k distinct char already
        // we cannot use suffixStore, since the string has change
        // now we only have to consider the earliest char that has this property

        // why ?
        // consider [s1, e] and [s2, e], s1 < s2, char at s1, s2 have the property above, e is s.length() - 1
        // char at s1, s2 changed
        // suppose optimal is when we change s2 to some char, x
        // now suppose we change char at s1 to x instead, it can be proven new string [s1, e] #partitions >= new string [s2, e] #partitions
        // proof
        // suffixStore is an increasing array, if considering from right to left
        // let the 1st parition of [s2, e] be [s2, k2]
        // let 1st partiiton of [s1, e] be [s1, k1]
        // k1 > k2 not possible, clearly
        // case 1: k1 >= s2
        // suffixStore[k1 + 1] + 1>= suffixStore[k2 + 1] + 1, done
        // case2: k1 < s2
        // we prove that #partition [s2', e], where we change s2 <= #partition [s2, e] + 1,  we do not change char at s2
        // to increase #parition, let 1st partition of [s2', e] be [s2', k'], 1st partition of [s2, e] be [s2, k]
        // k' <= k, clealy
        // now 2nd partition of [s2' e], [k' + 1, k2'] 
        // now k2' cannot be < k clearly
        // case1: k2' = k, then subseqeunt partition for both strings are equal, at most +1 for [s2', e]
        // case2: k2' > k2, #partition [k2' + 1, e] <= #partition[k + 1, e]
        // so compare [s2', k'], [k' + 1, k2'] + (x, where x <= y) and [s2, k], + y


        int kFilled = -1;
        int[] bitMap = new int[26];
        Arrays.fill(bitMap, -1);
        int distinct = 0;
        while (p1 < s.length()) {
            if (p2 == s.length()) {
                int[] res = new int[] {p1, p2 - 1, useless, kFilled};
                out.add(res);
                break;
            }
            int c2 = s.charAt(p2) - 'a';
            distinct += (bitMap[c2] == -1) ? 1 : 0;
            if (distinct > k) {
                int[] res = new int[] {p1, p2 - 1, useless, kFilled};
                out.add(res);
                p1 = p2;
                p2 = p1;
                useless = -1;
                kFilled = -1;
                Arrays.fill(bitMap, -1);
                distinct = 0;
            } else if (bitMap[c2] != -1 && useless == -1) {
                //bitMap[c2] += 1;
                useless = bitMap[c2];
                kFilled = (kFilled == -1 && distinct == k) ? p2 : kFilled;
                p2 ++;
            } else if (distinct == k && bitMap[c2] != -1 && kFilled == -1) {
                //bitMap[c2] += 1;
                kFilled = p2;
                p2 ++;
            } else {
                bitMap[c2] = (bitMap[c2] == -1) ? p2 : bitMap[c2];
                p2 ++;
            }
        }
        return out;
    }

    int maxPartitionsAfterOperations(String s, int k) {
        int[] suffixStore = suffixStore(s, k);
        ArrayList<int[]> ranges = rangeCompress(s, k);
        int max = ranges.size();
    
        for (int i = 0; i < ranges.size(); i ++) {
            int[] range = ranges.get(i);
            for (int z = 2; z <= 3; z ++) {
                if (range[z] == -1) {
                    continue;
                } else if (z == 3 && range[z] == range[z -1]) {
                    continue;
                }
                for (int m = 0; m < 26; m ++) {
                    if (m == s.charAt(range[z]) - 'a') {
                        continue;
                    }
                    int[] bitMap = new int[26];
                    int distinct = 0;
                    // add everything up before the 1st repeated char, and we only need to consider changing the 1st repeated char
                    // and at the earliest possible index, i.e repeated char at index 2,5,8, change index 2
                    // now suppose we have another repeated index, suppose at index 1, 7
                    // why we still change at 2
                    // if we change at 1, can only end at 6 or more, why? because the number of distinct char [start, 6] is the same
                    // when we dont change 1
                    // but since 7 is the next repeated char, there exist a repeated char < 7, with the 1st of its kind at index < 7
                    // so changing at index 2, will still cause the new range to end at worst the same as when we change char at index 1

                    
                    // however, we need to consider the index S, where changing char at index S, causes the range to end at S - 1.
                    // we cannot use suffixStore, since the string has change
                    for (int j = range[0]; j < range[z]; j ++) {
                        int cJ = s.charAt(j) - 'a';
                        distinct += (bitMap[cJ] == 0) ? 1 : 0;
                        bitMap[cJ] += 1;
                    }
                    for (int j = range[z]; j <= range[1]; j ++) {
                        // we do not need to consider if the new range is ends further right than prev range, as then result will be at best equal to
                        // original result.
                        // new range can stop before the changed char, but only 1 index before changed char
                        int cJ = (j == range[z]) ? m : s.charAt(j) - 'a';
                        distinct += (bitMap[cJ] == 0) ? 1 : 0;
                        if (distinct > k && j != range[z]) {
                            max = Math.max(max, i + 1 + suffixStore[j]);
                            break;
                        } else if (distinct > k && j == range[z]) {
                            // problem is if new range stops exactly 1 index before change index, cannot use suffixStore, because the string has changed
                            // but we are sure that we will never go beyond the the next range
                            int p1 = j;
                            //System.out.println(p1);
                            int[] bitMap2 = new int[26];
                            int distinct2 = 0;
                            while (p1 < s.length()) {
                                int c1 = (p1 == j) ? m : s.charAt(p1) - 'a';
                                distinct2 += (bitMap2[c1] == 0) ? 1 : 0;
                                //System.out.println(distinct2);
                                if (distinct2 > k) {
                                    max = Math.max(max, i + 1 + 1 + suffixStore[p1]);
                                    //System.out.println(max);
                                    break;
                                } else {
                                    bitMap2[c1] += 1;
                                    p1 ++;
                                }
                            }
                            max = (distinct2 <= k) ? Math.max(max, i + 1 + 1) : max;
                            break;
                        } else {
                            bitMap[cJ] += 1;
                        }
                    }
                }
            }
        }
        return max;
    }










    public static void main(String[] args) {
        lc3003 sol = new lc3003();
        String s = "accca";
        //System.out.println(Arrays.toString(sol.suffixStore(s, 25)));
        ArrayList<int[]> aa = sol.rangeCompress(s, 2);
        for (int[] xx : aa) {
            System.out.println(Arrays.toString(xx));
        }
        int ans = sol.maxPartitionsAfterOperations(s, 2);
        System.out.println(ans);
    }
}
