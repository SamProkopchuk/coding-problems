class Solution(object):
    mod = (10**9) + 7
    n = 0
    def getState(self, t1_empty, t2_empty):
        # t1_empty and t2_empty are empty
        if t1_empty and t2_empty:
            return 0
        # t1_empty not empty, t2_empty empty
        if not t1_empty and t2_empty:
            return 1
        # t1_empty empty, t2_empty not empty
        if t1_empty and not t2_empty:
            return 2
        # both not empty
        return 3

    # ti -> ith quadrant
    def numTilingsDP(self, i, t1_empty, t2_empty, dp_arr):
        if i == self.n:
            return 1
        state = self.getState(t1_empty, t2_empty)
        if dp_arr[i][state] is not None:
            return dp_arr[i][state]

        # Verify out of bounds
        t3_empty, t4_empty = i+1 < self.n, i+1 < self.n

        count = 0

        # Place tromino (1 top, 2 bottom, L->R)
        if (t1_empty and t2_empty and t3_empty):
            # If placing 1 top, 2 bottom, t2_empty will not be empty, but t1_empty will
            count += self.numTilingsDP(i + 1, False, True, dp_arr)
        
        # Place tromino (2 top, 1 bottom, L->R):
        if (t1_empty and t2_empty and t4_empty):
            # Reflection of previous case
            count += self.numTilingsDP(i + 1, True, False, dp_arr)
        
        # Place tromino (1 top, 2 bottom, R->L)
        # Can only place if there is a gap, i.e. t2_empty is currently empty, but t1_empty is not
        # Otherwise there is a gap and it is not valid
        if (not t1_empty and t2_empty and t3_empty and t4_empty):
            # Once placed, t1_empty and t2_empty will be full
            count += self.numTilingsDP(i+1, False, False, dp_arr)
        
        # Place tromino (2 top, 1 bottom, R->L)
        if (t1_empty and not t2_empty and t3_empty and t4_empty):
            # Reflection of previous case
            count += self.numTilingsDP(i+1, False, False, dp_arr)
        
        # Place vertical domino
        if (t1_empty and t2_empty):
            # If only placing a vertical domino, t1_empty and t2_empty will be empty
            count += self.numTilingsDP(i+1, True, True, dp_arr)

        # Place 2 horizontal blocks
        if (t1_empty and t2_empty and t3_empty and t4_empty):
            # If only placing 2 horizontal blocks, t1_empty and t2_empty will be filled. 
            count += self.numTilingsDP(i+1, False, False, dp_arr)
        
        # Place 1 horizontal block, top
        # Can only place if one of the tiles are filled, otherwise there will be a gap
        if (t1_empty and not t2_empty and t3_empty):
            count += self.numTilingsDP(i+1, False, True, dp_arr)
        
        # Place 1 horizontal block, bottom
        if (not t1_empty and t2_empty and t4_empty):
            # Reflection of previous case
            count += self.numTilingsDP(i + 1, True, False, dp_arr)

        # t1_empty and t2_empty are already filled, nothing to place
        if (not t1_empty and not t2_empty):
            count += self.numTilingsDP(i+1, True, True, dp_arr)
        
        dp_arr[i][state] = count % self.mod

        return dp_arr[i][state]


    def numTilings(self, n):
        self.n = n
        dp_arr = [[None, None, None, None] for _ in range(n)]
        return self.numTilingsDP(0, True, True, dp_arr)
        
