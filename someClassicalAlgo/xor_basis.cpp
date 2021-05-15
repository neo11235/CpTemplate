/****first implementation****/
struct Basis{
    int basis[30];
    int sz=0;
    Basis()
    {
        clear();
    }
    void insertVector(int mask)
    {
        for(int i=0;i<30;i++)
        {
            if(!(mask&(1<<i)))
                continue;
            if(!basis[i])
            {
                basis[i]=mask;
                ++sz;
                return;
            }
            mask^=basis[i];
        }
    }
    bool check(int mask)
    {
        for(int i=0;i<30;i++)
        {
            if(!(mask&(1<<i)))
                continue;
            if(!basis[i])
            {
                return false;
            }
            mask^=basis[i];
        }
        return true;
    }
    void insertVector2(int mask)
    {
        for(int i=29;i>=0;i--)
        {
            if(!(mask&(1<<i)))
                continue;
            if(!basis[i])
            {
                basis[i]=mask;
                ++sz;
                return;
            }
            mask^=basis[i];
        }
    }
    bool check2(int mask)
    {
        for(int i=29;i>=0;i--)
        {
            if(!(mask&(1<<i)))
                continue;
            if(!basis[i])
            {
                return false;
            }
            mask^=basis[i];
        }
        return true;
    }
    void clear()
    {
        memset(basis,0,sizeof(basis));
        sz=0;
    }
};
/*******************************/
