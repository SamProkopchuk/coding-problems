input()
# Get items without duplicates, keeping order:
scores = [*dict.fromkeys(map(int, input().split()))]
input()
alice_scores = [*map(int, input().split())]
for alice_score in alice_scores:
    while scores and scores[-1] <= alice_score:
        scores.pop()
    print(len(scores)+1)
