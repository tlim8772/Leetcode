

function b_search(arr: number[], key: number): number {
    let s = 0;
    let e = arr.length - 1;
    while (s < e) {
        const m = (s + e) >> 1;
        if (arr[m] < key) s = m + 1;
        else e = m;
    }
    return (arr[s] == key) ? s : -1;
}

function solveQueries(nums: number[], queries: number[]): number[] {
    const store = new Map<number, number[]>();
    for (let i = 0; i < nums.length; i++) {
        if (!store.has(nums[i])) store.set(nums[i], []);
        store.get(nums[i])?.push(i);
    }

    const out = []
    for (const q of queries) {
        const n = nums[q];
        const idxs = store.get(n) || [];

        if (idxs.length <= 1) {
            out.push(-1);
            continue;
        }
        
        const pos = b_search(idxs, q);

        const r = idxs[(pos + 1) % idxs.length];
        const l = idxs[(pos - 1 + idxs.length) % idxs.length];
        
        const ldist = (l <= q) ? q - l : (q + nums.length - l);
        const rdist = (q <= r) ? r - q : (r + nums.length - q);
        out.push(Math.min(ldist, rdist));
    }

    return out;
};


const nums = [1,3,1,4,1,3,2];
const queries = [0,3,5];

const ans = solveQueries(nums, queries);
console.log(ans);