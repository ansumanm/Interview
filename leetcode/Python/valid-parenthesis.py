class Solution:
    def isValid(self, s: str) -> bool:
        pair = {")": "(", "}": "{", "]": "["}

        stack = []

        for char in list(s):
            if char in ["(", "{", "["]:
                stack.append(char)
            elif char in [")", "}", "]"]:
                try:
                    ele = stack.pop()
                    if ele != pair[char]:
                        return False
                except:
                    return False

        # stack should be empty
        if len(stack) > 0:
            return False

        return True


def main():
    cases = ["()", "()[]{}", "(]", "]"]

    s = Solution()
    for case in cases:
        print("%s %s" % (case, str(s.isValid(case))))


main()
