void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    int firstrowzero=0, firstcolzero=0;
    int r=matrixSize;
    int c=matrixColSize[0];
    int i,j;
    //CHECKING WHETHER THE FIRST COLUMN HAS ATLEAST ZERO
    for(i=0; i<r; i++)
        if(matrix[i][0]==0)
        {
            firstcolzero=1;
            break;
        }
    //CHECKING WHETHER FIRST ROW HAS ATLEAST ZERO
    for(j=0; j<c; j++)
        if(matrix[0][j]==0)
        {
             firstrowzero=1;
            break;
        }
    //MARKING THE POSITIONS OF ZEROES IN RESPECTIVE ROWS AND COLUMNS
    for(i=1; i<r; i++)
        for(j=1; j<c; j++)
            if(matrix[i][j]==0)
            {
               //MARKING IN FIRST ROW AND COLUMN
                matrix[i][0]=0;
                matrix[0][j]=0;
            }
    //SETTING ZEROES ACCORDING TO MARKERS
    for(i=1; i<r; i++)
        for(j=1; j<c; j++)
            if(matrix[i][0]==0 || matrix[0][j]==0)
               matrix[i][j]=0;
    //BY FLAG FINALLY, ZERO FIRST ROW(IF-NEEDED)
    if(firstrowzero)
        for(j=0; j<c; j++)
            matrix[0][j]=0;
    //ZERO FIRST COLUMN (IF-NEEDED)
    if(firstcolzero)
        for(i=0; i<r; i++)
            matrix[i][0]=0;
}