from functools import reduce

class Solution:
    def fractionToDecimal(self, numerator: int, denominator: int) -> str:
        if numerator == 0:
            return '0'
        elif numerator * denominator < 0:
            return '-' + self.fractionToDecimal(abs(numerator), abs(denominator))
        
        numerator, denominator = abs(numerator), abs(denominator)
        
        left = numerator // denominator
        if numerator % denominator == 0:
            return str(left)
        
        next = (numerator % denominator) * 10
        repeat = -1
        lst = []
        seen = {}

        while next != 0:
            #print(next)
            if next in seen:
                repeat = seen[next]
                break
            elif next < denominator:
                lst.append(0)
                seen[next] = len(lst) - 1
                next *= 10
            else:
                lst.append(next // denominator)
                seen[next] = len(lst) - 1
                next %= denominator
                next *= 10
            
        #print(lst, seen, repeat)
        out = [str(left), '.']
        if repeat == -1:
            out += [str(elem) for elem in lst]
        else:
            out += [str(elem) for elem in lst[:repeat]]
            out.append('(')
            out += [str(elem) for elem in lst[repeat:]]
            out.append(')')
        
        return ''.join(out)
        
sol = Solution()
print(sol.fractionToDecimal(-1, -2147483648))
