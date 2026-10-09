int maxPoints(int** points, int pointsSize, int* pointsColSize)
{
    if(pointsSize==1)
    {
        return(1);
    }
    if(pointsSize==2)
    {
        return(2);
    }
    int max1=1;
    int low;
    int high;
    float slope;
    float slope1;
    int* array = (int*)(calloc(pointsSize,sizeof(int)));
    for(low=0;low<pointsSize-1;low++)
    {

        for(high=low+1;high<pointsSize; high++)
        {
            int count = 0;
            array[low]++;
            array[high]++;

            if(points[high][0]-points[low][0]==0)
            {
               slope = 1000000; 
            }
            else
            {
                slope = (float)(points[high][1]-points[low][1])/(float)(points[high][0]-points[low][0]);
            }
            
            for(int i=0; i<pointsSize; i++)
            {
                if((i==low)||(i==high))
                {
                    continue;
                }
                else
                {
                    if(points[i][0]-points[low][0]==0)
                    {
                        slope1 = 1000000; 
                    }
                    else
                    {
                        slope1 = (float)(points[i][1]-points[low][1])/(float)(points[i][0]-points[low][0]);
            
                    }

                }
                if(slope==slope1)
                {
                    array[i]++;
                }
                
            }
            for(int i=0; i<pointsSize; i++)
                {
                    if(array[i]!=0)
                    {
                        count++;
                    }
                    
                    
                }
                if(max1<count)
                {
                    max1 = count;
                }
                
                for(int i=0; i<pointsSize; i++)
                {
                    array[i] = 0;
                }
        }
    

    }
    free(array);
    return(max1);
}