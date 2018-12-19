#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <windows.h>
unsigned il = 0;

using namespace std;

void ShellSort(int tab[], int ilosc);
int increment(long inc[], long ilosc);
void ShellSedgewickSort(int tab[], int ilosc);
void ShellKnuthSort(int tab[], int ilosc);
void BubbleSort(int tab[], int ilosc);
void InsertionSort(int tab[], int ilosc);

int main()
{
	srand( time(0) );
	int N;
	for (int i = 0; i < 5; i++) {
		N = 1000;
		switch (i) {
		case 0: cout << "Shell`s sorting!\n"; break;
		case 1: cout << "\nKnuth`s sorting!\n"; break;
		case 2: cout << "\nSedgewick`s sorting!\n"; break;
		case 3: cout << "\nBubble sorting!\n"; break;
		case 4: cout << "\nInsertion sorting!\n"; break;
		}
		while (N <= 10000) {
			int tab[N];
			for (int i = 0; i < N; i++) tab[i] = rand() % 10000 + 1;
			LARGE_INTEGER time_s, time_n, freq;
			QueryPerformanceCounter(&time_s);

			switch (i) {
			case 0: ShellSort(tab, N); break;
			case 1: ShellKnuthSort(tab, N); break;
			case 2: ShellSedgewickSort(tab, N); break;
			case 3: BubbleSort(tab, N); break;
			case 4: InsertionSort(tab, N); break;
			}

			QueryPerformanceFrequency(&freq);
			QueryPerformanceCounter(&time_n);

			cout << N << " " << (double)(time_n.QuadPart - time_s.QuadPart) / (double)freq.QuadPart << " " << il << endl;
			N += 1000;
		}
		il = 0;
	}
	return 0;
}

void ShellSort(int tab[], int ilosc)
{
	int t, j;
	for(int k = ilosc/2; k > 0; k /=2){
        for(int i = k; i < ilosc; i++)
        {
            t = tab[i];
            for(j = i; j>=k; j-=k)
            {
                if(t < tab[j-k])
                {
                    tab[j] = tab[j-k];
                    il++;
                }
                else
                    break;
            }
            tab[j] = t;
            il++;
        }
    }
}

void ShellKnuthSort(int tab[], int ilosc)
{
	int j, h, i;
	for(h = 1; h < ilosc; h = 3 * h + 1);
    h /= 9;
    if(!h) h++;
    while(h)
    {
    	for(j = ilosc - h - 1; j >= 0; j--)
    	{
        	int x = tab[j];
        	i = j + h;
        	while((i < ilosc) && (x > tab[i]))
      		{
        		tab[i - h] = tab[i];
        		il++;
        		i += h;
      		}
      		tab[i - h] = x;
      		il++;
    	}
    	h /= 3;
    }
}

int increment(long inc[], long ilosc) 
{
  int p1, p2, p3, s;

  p1 = p2 = p3 = 1;
  s = -1;
  do 
  {
      if (++s % 2) 
	  {
          inc[s] = 8*p1 - 6*p2 + 1;
	  } 
	  else 
	  {
      	  inc[s] = 9*p1 - 9*p3 + 1;
      	  p2 *= 2;
          p3 *= 2;
      }
	  p1 *= 2;
  }
  while(3*inc[s] < ilosc);  

  return s > 0 ? --s : 0;
}

void ShellSedgewickSort(int tab[], int ilosc)
{
	long inc, i, j, seq[40];
    int s;
    s = increment(seq, ilosc);
    while (s >= 0) 
	{
		inc = seq[s--];
        for (i = inc; i < ilosc; i++) 
		{
        	int temp = tab[i];
      		for (j = i-inc; (j >= 0) && (tab[j] > temp); j -= inc)
      		{
        		tab[j+inc] = tab[j];
        		il++;
        	}
      		tab[j+inc] = temp;
      		il++;
    	}
  	}
}

void BubbleSort(int tab[], int ilosc)
{
	for(int i=0; i<ilosc; i++)
	{
		for(int j=i+1; j<ilosc; j++)
		{
			if(tab[i] > tab[j])
			{
				int temp = tab[i];
				tab[i] = tab[j];
				il++;
				tab[j] = temp;
				il++;
			}
		}
	}
}

void InsertionSort(int tab[], int ilosc)
{
	int x;
	for(int i=1; i<ilosc; i++)
	{
		x = tab[i];
		int j = i - 1;
		while(j != 0 && x < tab[j])
		{
			tab[j+1] = tab[j];
			il++;
			j--;
		}
		tab[j+1] = x;
		il++;
	}
}
