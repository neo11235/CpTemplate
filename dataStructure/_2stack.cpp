/******first implementation*************/
struct stack{
    vector<ll> s,g={0ll};
    void push(ll x)
    {
        s.push_back(x);
        g.push_back(__gcd(x,g.back()));
    }
    ll pop()
    {
        ll res=s.back();
        s.pop_back();
        g.pop_back();
        return res;
    }
    ll gcd()
    {
        return g.back();
    }
    bool empty()
    {
        return s.empty();
    }

};
::stack s1,s2;
void add(ll x)
{
    s2.push(x);
}
void remove()
{
    if(s1.empty())
    {
        while(!s2.empty())
            s1.push(s2.pop());
    }
    s1.pop();
}
ll gcd()
{
    return __gcd(s1.gcd(),s2.gcd());
}
void clear()
{
    while(!s1.empty())
        s1.pop();
    while(!s2.empty())
        s2.pop();
}
/*************************************/

/***********oop implementation*************/
namespace _2stack
{
    template<class T,class ResT=T>
    struct stack{
        vector<T> data;
        vector<ResT> res;
        ResT zeroElement;
        ResT (*combine)(T,ResT);
        stack(){}
        stack(ResT zeroElement,ResT (*combine)(T,ResT))
        {
            this->zeroElement=zeroElement;
            this->combine=combine;
            res.push_back(zeroElement);
        }
        void set(ResT zeroElement,ResT (*combine)(T,ResT))
        {
            this->zeroElement=zeroElement;
            this->combine=combine;
            if(res.empty())
                res.push_back(zeroElement);
        }
        void push(T element)
        {
            data.push_back(element);
            res.push_back(combine(element,res.back()));
        }
        T  pop()
        {
            T retval=data.back();
            data.pop_back();
            res.pop_back();
            return retval;
        }
        void clear()
        {
            data.clear();
            res.clear();
            res.push_back(zeroElement);
        }
        ResT peek()
        {
            return res.back();
        }
        bool empty()
        {
            return data.empty();
        }
    };

    template<class T,class ResT=T>
    struct queue{
        stack<T,ResT> b,f;//back and front
        ResT (*combine)(T,ResT);
        queue(){}
        queue(ResT zeroElement,ResT (*combine)(T,ResT))
        {
            this->combine=combine;
            b.set(zeroElement,combine);
            f.set(zeroElement,combine);
        }
        void set(ResT zeroElement,ResT (*combine)(T,ResT))
        {
            b.set(zeroElement,combine);
            f.set(zeroElement,combine);
            this->combine=combine;
        }
        void clear()
        {
            b.clear();
            f.clear();
        }
        void push(T element)
        {
            f.push(element);
        }
        void pop()
        {
            if(b.empty())
            {
                while(!f.empty())
                {
                    b.push(f.pop());
                }
            }
            if(b.empty())
                return;
            b.pop();
        }
        ResT getResult()
        {
            return combine(f.peek(),b.peek());
        }

    };
}
/**************************************/
/*************** oop implementation 2****************/
namespace _2stack
{
    template<typename T,typename Combine,typename ResT=T>// combine function object must have 2 overloaded () operator
    struct stack{
        vector<T> data;
        vector<ResT> res;
        Combine combine;
        stack(){}
        void push(T element)
        {
            data.push_back(element);
            if(!res.empty())
                res.push_back(combine(element,res.back()));
            else
                res.push_back(combine(element));
        }
        T pop()
        {
            assert(!data.empty());
            T retval=data.back();
            data.pop_back();
            res.pop_back();
            return retval;
        }
        void clear()
        {
            data.clear();
            res.clear();
        }
        ResT peek()
        {
            assert(!res.empty());
            return res.back();
        }
        bool empty()
        {
            return data.empty();
        }
    };

    template<typename T,typename Combine,typename ResT=T>
    struct queue{
        stack<T,Combine,ResT> b,f;//back and front
        Combine combine;
        queue(){}
        void clear()
        {
            b.clear();
            f.clear();
        }
        void push(T element)
        {
            f.push(element);
        }
        void pop()
        {
            if(b.empty())
            {
                while(!f.empty())
                {
                    b.push(f.pop());
                }
            }
            if(b.empty())
                return;
            b.pop();
        }
        ResT getResult()
        {
            if(f.empty())
            {
                if(b.empty())
                {
                    return (ResT)0;///ResT must have converting constructor if its a user defined class
                }
                return b.peek();
            }
            else if(b.empty())
            {
                return f.peek();
            }
            return combine(f.peek(),b.peek());
        }

    };
}
///Example
struct func
{
    ll operator()(ll a,ll b)
    {
        return __gcd(a,b);
    }
    ll operator()(ll a)
    {
        return a;
    }
};
_2stack::queue<ll,func> Q;
/*****************************************/
