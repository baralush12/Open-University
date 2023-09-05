/*
 * Represents Sudoku game logic and board state.
 */

public class Sudoku {
	
    final int SIZE = 3;
    private final int[][] board = new int[SIZE][SIZE];

    public int getCell(int row, int col) {
        return board[row][col];
    }

    public void setCell(int row, int col, int value) {
        board[row][col] = value;
    }

    public boolean isAllowed(int row, int col, int value) {
        return checkRow(row, col, value) && checkCol(row, col, value) && checkBlock(row, col, value);
    }

    private boolean checkRow(int row, int colToExclude, int value) {
        for (int col = 0; col < SIZE * SIZE; col++) {
            if (col != colToExclude && board[row][col] == value) {
                return false;
            }
        }
        return true;
    }

    private boolean checkCol(int rowToExclude, int col, int value) {
        for (int row = 0; row < SIZE * SIZE; row++) {
            if (row != rowToExclude && board[row][col] == value) {
                return false;
            }
        }
        return true;
    }

    private boolean checkBlock(int row, int col, int value) {
        int startRow = row / SIZE * SIZE;
        int startCol = col / SIZE * SIZE;

        for (int i = startRow; i < startRow + SIZE; i++) {
            for (int j = startCol; j < startCol + SIZE; j++) {
                if ((i != row || j != col) && board[i][j] == value) {
                    return false;
                }
            }
        }
        return true;
    }
    public void clearBoard() {
        for (int row = 0; row < SIZE * SIZE; row++) {
            for (int col = 0; col < SIZE * SIZE; col++) {
                board[row][col] = 0;
            }
        }
    }
}