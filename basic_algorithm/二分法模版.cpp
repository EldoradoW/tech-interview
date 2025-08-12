bool check(int x) {} // 检查x是否满足某种性质

// 区间[l, r]被划分成[l, mid]和[mid + 1, r]时使用：
// 寻找左边界：若找不到返回右边大于target的最小值
// 作用：可寻找一个数的左边界，或者寻找一个数右边大于它的最小值
// 为了防止不存在这个数，也不存在大于这个数的数，right应该是取不到的，右边是开区间
int bserach_l(int l, int r) {
    while(l < r) {
        int mid = l + r >> 1;
        if(check(mid)在区间内) r = mid; //check()判断mid是否满足性质
        else l = mid + 1;
    }
    return l;
}

// 区间[l, r]被划分成[l, mid - 1]和[mid, r]时使用：
// 寻找右边界：若找不到返回左边小于target的最大值
// 作用：可寻找一个数的右边界，或者寻找一个数左边小于它的最大值
// 为了防止不存在这个数，也不存在大于这个数的数，right应该是取不到的，右边是开区间
int bserach_l(int l, int r) {
    while(l < r) {
        int mid = l + r + 1 >> 1;
        if(check(mid)在区间内) l = mid; //check()判断mid是否满足性质
        else r = mid - 1;
    }
    return l;
}