input()
# Get items without duplicates, keeping order:
scores = [*dict.fromkeys(map(int, input().strip().split()))]
input()
alice_scores = list(map(int, input().strip().split()))
for alice_score in alice_scores:
    while scores and scores[-1] <= alice_score:
        del scores[-1]
    print(len(scores)+1)
