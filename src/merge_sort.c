void merge(int arr[], int i, int mid, int j) 
{
    int temp[len];
    int l = i;
    int r = j;
    int m = mid + 1;
    int k = l;

    while(l <= mid && m <= r) 
	{
        if(arr[l] <= arr[m]) 
		{
            temp[k++] = arr[l++];
        }
        else {
            temp[k++] = arr[m++];
        }
    }

    while(l <= mid)
	{
        temp[k++] = arr[l++];
	}
	
    while(m <= r) 
	{
        temp[k++] = arr[m++];
    }

    for(int i1 = i; i1 <= j; i1++) 
	{
        arr[i1] = temp[i1];
    }
}

void mergesort(int arr[], int i, int j) 
{
    int mid = 0;

    if(i < j) 
	{
        mid = (i + j) / 2;
        mergesort(arr, i, mid);
        mergesort(arr, mid + 1, j);
        merge(arr, i, mid, j);
    }
}