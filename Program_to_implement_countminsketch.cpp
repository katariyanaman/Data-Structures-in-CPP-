/* The following C++ program implements the Count-Min Sketch data structure,
   a probabilistic algorithm used for estimating the frequency of elements in a stream. */

# include <iostream>
# include <cmath>
# include <map>
# include <cstdlib>
# include <ctime>
# include <limits>
# include <cstring>
# define LONG_PRIME 32993
# define MIN(a,b) (a < b ? a : b)
# define ui unsigned int
using namespace std;
 
class CountMinSketch
{
    private:
        ui w,d;
        float eps;
        float gamma;
        ui aj, bj;
        ui total;
        int **C;
        int **hashes;
        void genajbj(int **hashes, int i);
    public:
       
        CountMinSketch(float ep, float gamm)
        {
            if (!(0.009 <= ep && ep < 1))
            {
                cout << "eps must be in this range: [0.01, 1)" << endl;
                exit(1);
            }
            else if (!(0 < gamm && gamm < 1))
            {
                cout << "gamma must be in this range: (0,1)" << endl;
                exit(1);
            }
            eps = ep;
            gamma = gamm;
            w = ceil(exp(1) / eps);
            d = ceil(log(1 / gamma));
            total = 0;
            C = new int *[d];
            ui i, j;
            for (i = 0; i < d; i++)
            {
                C[i] = new int[w];
                for (j = 0; j < w; j++)
                {
                    C[i][j] = 0;
                }
            }
            srand(time(NULL));
            hashes = new int* [d];
            for (i = 0; i < d; i++)
            {
                hashes[i] = new int[2];
                genajbj(hashes, i);
            }
        }
        
        ~CountMinSketch()
        {
            ui i;
            for (i = 0; i < d; i++)
            {
                delete[] C[i];
            }
            delete[] C;
            for (i = 0; i < d; i++)
            {
                delete[] hashes[i];
            }
            delete[] hashes;
        }
        
        void update(int item, int c)
        {
            total = total + c;
            ui hashval = NULL;
            for (ui j = 0; j < d; j++)
            {
                hashval = (hashes[j][0] * item + hashes[j][1]) % w;
                C[j][hashval] = C[j][hashval] + c;
            }
        }
 
        void update(const char *str, int c)
        {
            int hashval = hashstr(str);
            update(hashval, c);
        }
        
        ui estimate(int item)
        {
            int minval = numeric_limits<int>::max();
            unsigned int hashval = NULL;
            for (unsigned int j = 0; j < d; j++)
            {
                hashval = (hashes[j][0] * item + hashes[j][1]) % w;
                minval = MIN(minval, C[j][hashval]);
            }
            return minval;
        }
        
        ui estimate(const char *str)
        {
            int hashval = hashstr(str);
            return estimate(hashval);
        }
        
        ui totalcount()
        {
            return total;
        }
         
        ui hashstr(const char *str)
        {
            unsigned long hash = 5381;
            int c;
            while (c = *str++)
            {
                hash = ((hash << 5) + hash) + c;
            }
            return hash;
        }
};
 
void CountMinSketch::genajbj(int** hashes, int i)
{
    hashes[i][0] = int(float(rand())*float(LONG_PRIME)/float(RAND_MAX) + 1);
    hashes[i][1] = int(float(rand())*float(LONG_PRIME)/float(RAND_MAX) + 1);
}

int main()
{
    const char *ar_str[] = { "hello", "some", "one", "hello", "alice",
                             "one", "lady", "let", "us", "lady",
                             "alice", "in", "us", "wonderland", "lady",
                             "lady", "some", "hello", "none", "pie" };
    CountMinSketch c(0.01, 0.1);
    ui i, total = 0, count;
    map<const char *, int> mapitems;
    map<const char *, int>::const_iterator it;
    for (i = 0; i < 20; i++)
    {
        if ((it = mapitems.find(ar_str[i])) != mapitems.end())
        {
            mapitems[ar_str[i]] += i;
        }
        else
        {
            mapitems[ar_str[i]] = i;
        }
        c.update(ar_str[i], i);
        total = total + i;
 
    }
    for (it = mapitems.begin(); it != mapitems.end(); it++)
    {
        if (c.estimate(it->first) != mapitems[it->first])
        {
            cout << "Incorrect count for " << it->first << ":->error: ";
            count = abs(int(c.estimate(it->first)-mapitems[it->first]));
            cout << count << endl;
        }
        else
        {
            cout << "Correct count for '" << it->first;
            cout << "' :-->count: " << c.estimate(it->first) << endl;
        }
    }
    cout << "c.totalcount()==total ? ";
    cout << (c.totalcount() == total ? "True" : "False") << endl;
    cout << "Sketch Total: " << c.totalcount() << endl;
 
    cout << "Testing for strings not in ar_str..." << endl;
    const char *arn_str[] = {"sanfoundry", "hello", "linux", "us"};
    for (i = 0 ; i < 4; i++)
    {
        if (!c.estimate(arn_str[i]))
            cout<<arn_str[i] << " not found in string array"<<endl;
        else
            cout<<arn_str[i] << " found in string array"<<endl;
    }
    return 0;
}
