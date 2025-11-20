# 单序列双指针

## 双向双指针

两个指针 **left**=**0**, **right**=n−1，从数组的两端开始，向中间移动，这叫 **相向双指针** 。上面的滑动窗口相当于 **同向双指针** 。

经典例题：

* [15. 三数之和](https://leetcode.cn/problems/3sum/)
* [42. 接雨水](https://leetcode.cn/problems/trapping-rain-water/)
* [2422. 使用合并操作将数组转换为回文序列](https://leetcode.cn/problems/merge-operations-to-turn-array-into-a-palindrome/)

## 同向双指针

两个指针的移动方向相同（都向右，或者都向左）

经典例题：

* [3649. 完美对的数目](https://leetcode.cn/problems/number-of-perfect-pairs/)
* [1574. 删除最短的子数组使剩余数组有序](https://leetcode.cn/problems/shortest-subarray-to-be-removed-to-make-array-sorted/)

## 背向双指针

两个指针从数组中的同一个位置出发，一个向左，另一个向右，背向移动。

经典例题：

[1793. 好子数组的最大分数](https://leetcode.cn/problems/maximum-score-of-a-good-subarray/)
