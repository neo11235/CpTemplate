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
/**************************************/

/********64bit implementation**********/
struct Basis{
    typedef unsigned long long ULL;
    ULL basis[64];
    int size=0;
    Basis(){clear();}
    //maintain lower right triangle matrix(assuming matrix column numbered from 64 to 1)
    //should be used when max xor required
    //returns false when mask already present in vector space
    bool insertVectorLT(ULL mask)
    {
        for(int i=63;i>=0;--i)
        {
            if(!((mask>>i)&1))
                continue;
            if(!basis[i])
            {
                basis[i]=mask;
                ++size;
                return true;
            }
            mask^=basis[i];
        }
        return false;
    }
    bool checkLT(ULL mask)
    {
        for(int i=63;i>=0;--i)
        {
            if(!((mask>>i)&1))
                continue;
            if(!basis[i])
            {
                return false;
            }
            mask^=basis[i];
        }
        return true;
    }
    //returns a bitmask such that xor of basis[setbit]=mask
    //checkLT(mask) should be true before calling this function
    ULL linearCombiLT(ULL mask)
    {
        ULL res=0;
        for(int i=63;i>=0;--i)
        {
            if(!((mask>>i)&1))
                continue;
            mask^=basis[i];
            res|=(1ull<<i);
        }
        return res;
    }
    ULL max()
    {
        ULL res=0;
        for(int i=63;i>=0;--i)
        {
            if((res>>i)&1)
                continue;
            res^=basis[i];
        }
        return res;
    }
    ULL& operator[](int indx)
    {
        return basis[indx];
    }
    void clear()
    {
        memset(basis,0,sizeof(basis));
        size=0;
    }
};
/********************************************************/
///not tested but should be ok,runtime of each operation
///is O(SIZE),except clear() which is O(SIZE^2)
/******************General implementation***************/
template<int SIZE=64>
struct Basis{

    bitset<SIZE> basis[SIZE];
    int size=0;
    Basis(){}
    //maintain lower right triangle matrix
    //should be used when max xor required
    //returns false when mask already present in vector space
    bool insertVectorLT(bitset<SIZE> mask)
    {
        for(int i=SIZE-1;i>=0;--i)
        {
            if(!mask[i])
                continue;
            if(basis[i].none())
            {
                basis[i]=mask;
                ++size;
                return true;
            }
            mask^=basis[i];
        }
        return false;
    }
    bool checkLT(bitset<SIZE> mask)
    {
        for(int i=SIZE-1;i>=0;--i)
        {
            if(!mask[i])
                continue;
            if(basis[i].none())
                return false;
            mask^=basis[i];
        }
        return true;
    }
    //returns a bitmask such that xor of basis[setbit]=mask
    //checkLT(mask) should be true before calling this function
    bitset<SIZE> linearCombiLT(bitset<SIZE> mask)
    {
        bitset<SIZE> res;
        for(int i=SIZE-1;i>=0;--i)
        {
            if(!mask[i])
                continue;
            mask^=basis[i];
            res.set(i);
        }
        return res;
    }
    bitset<SIZE> max()
    {
        bitset<SIZE> res;
        for(int i=SIZE-1;i>=0;--i)
        {
            if(res[i])
                continue;
            res^=basis[i];
        }
        return res;
    }
    bitset<SIZE>& operator[](int indx)
    {
        return basis[indx];
    }
    void clear()
    {
        for(int i=0;i<SIZE;++i)
        {
            basis[i].reset();
        }
        size=0;
    }
};
/*******************************************************/
