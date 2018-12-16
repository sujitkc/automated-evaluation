from collections import defaultdict

t = input()
while (t > 0):
    l = defaultdict (list)
    weight = [0]
    n = input()
    for i in range(n):
        wt = input()
        weight.append(wt)
    for j in range(n-1):
        u,v = input()
        l[u].append(v)
    
    r = [0]*n+1
    for a in range(1, n+1):
        for b in l[a]:
            r[a] += (weight[a] + r[b])
    sum = 0
    for i in weight:
        sum += i
    
    expect = sum / 2
    min_diff = 1000
    ans = 0
    for i in r:
        diff = abs(expect - i)
        if (diff < min_diff):
            min_diff = diff
            ans = i

    if (ans < sum-ans):
        print ans
    else:
        print sum-ans
        
    t -= 1
