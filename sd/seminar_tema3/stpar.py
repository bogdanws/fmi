def can_reorder(n, trucks):
    stack = []
    next_needed = 1
    
    for truck in trucks:
        while stack and stack[-1] == next_needed:
            stack.pop()
            next_needed += 1
            
        if truck == next_needed:
            next_needed += 1
        else:
            stack.append(truck)
    
    while stack and stack[-1] == next_needed:
        stack.pop()
        next_needed += 1
    
    return next_needed > n

while True:
    n = int(input())
    if n == 0:
        break
    trucks = list(map(int, input().split()))
    if can_reorder(n, trucks):
        print("yes")
    else:
        print("no")

