

findAddressOfMax(int* a, int n)
{

    int* amax;
    int i;
    amax = a;

    for(i = 1; i < n; i+=1)
    {
        a = a+i;
        if(*a > *amax){
            amax = a;
        }
    }

    return amax;

}
