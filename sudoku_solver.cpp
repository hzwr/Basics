#include <vector>

int backtrack = 0;


struct Pos
{
    int x, y;
};

Pos GetNextEmptyCell(const std::vector<std::vector<int>> &sudoku, int x, int y)
{
    
    x = x % 9;
    y = y % 9;

    for (; x < 9; ++x)
    {
        for (; y < 9; ++y)
        {
            if (sudoku[x][y] == 0)
            {
                return { x,y };
            }
        }
        y = 0;
    }

    return { -1,-1 };

}
bool Validate(const std::vector<std::vector<int>> &sudoku, int x, int y, int e)
{
    // Check row
    for (int i = 0; i < 9; ++i)
    {
        if (e == sudoku[x][i])
        {
            return false;
        }
    }

    // Check col
    for (int j = 0; j < 9; ++j)
    {
        if (e == sudoku[j][y])
        {
            return false;
        }
    }
   

    // Check section
    int secTopX = 3 * (x / 3);
    int secTopY = 3 * (y / 3);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (e == sudoku[secTopX + i][secTopY + j])
            {
                return false;
            }
        }
    }

    return true;
   
}


bool Solve(std::vector<std::vector<int>> &sudoku, int x = 0, int y = 0)
{
    // Next cell to fill
    int nextX = GetNextEmptyCell(sudoku, x, y).x;
    int nextY = GetNextEmptyCell(sudoku, x, y).y;
    if (nextX == -1)
    {
        return true;
    }


    for (int e = 1; e < 10; ++e)
    {
        if (Validate(sudoku, nextX, nextY, e))
        {
            sudoku[nextX][nextY] = e;

            if (Solve(sudoku, nextX, nextY))
            {
                return true;
            }

            sudoku[nextX][nextY] = 0;   // We need to reset the value, if 1-9 are all invalid
            backtrack++;
        }
    }
	return false;
}

int main()
{
    std::vector<std::vector<int>> sudoku = {
        {0, 0, 5, 3, 0, 0, 0, 0, 0},
        {8, 0, 0, 0, 0, 0, 0, 2, 0},
        {0, 7, 0, 0, 1, 0, 5, 0, 0},
        {4, 0, 0, 0, 0, 5, 3, 0, 0},
        {0, 1, 0, 0, 7, 0, 0, 0, 6},
        {0, 0, 3, 2, 0, 0, 0, 8, 0},
        {0, 6, 0, 5, 0, 0, 0, 0, 9},
        {0, 0, 4, 0, 0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 9, 7, 0, 0}
    };

    if (Solve(sudoku))
    {
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                printf("%d ", sudoku[i][j]);
            }
            printf("\n");
        }
    }

    printf("Backtracks: %d", backtrack);



}