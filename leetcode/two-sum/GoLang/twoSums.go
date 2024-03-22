package main

import(
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func twoSum(nums []int, target int) []int {
	numMap := make(map[int]int)

	for i, num := range nums {
		complement := target - num

		if j, ok := numMap[complement]; ok {
			return []int{j, i}
		}
		numMap[num] = i
	}
	return nil
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	// Reading array of integers from the first line
	fmt.Println("Enter the array elements separated by space:")
	scanner.Scan()
	inputStr := scanner.Text()
	inputStrSlice := strings.Split(inputStr, " ")
	var nums []int
	for _, str := range inputStrSlice {
		num, err := strconv.Atoi(str)
		if err != nil {
			fmt.Printf("Error converting '%s' to integer: %s\n", str, err)
			return
		}
		nums = append(nums, num)
	}

	// Reading target integer from the second line
	fmt.Println("Enter the target integer:")
	scanner.Scan()
	targetStr := scanner.Text()
	target, err := strconv.Atoi(targetStr)
	if err != nil {
		fmt.Printf("Error converting target '%s' to integer: %s\n", targetStr, err)
		return
	}

	// Processing and output
	result := twoSum(nums, target)
	fmt.Printf("Indices of the two numbers that add up to %d: %v\n", target, result)
}