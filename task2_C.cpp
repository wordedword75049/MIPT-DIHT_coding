#include <iostream>
#include <stdio.h>
#include <string>
#include<string.h>
#include <vector>
#include <algorithm>

using namespace std;
const long maxlen = 1000000;
const int alphabet = 256;


vector <int> buildLCP(string str, int suf[maxlen]) {
	int n = str.length();
	vector<int> lcp(n);
	vector<int> pos(n);  // pos[] — массив, обратный массиву suf
	for (int i = 0; i < n; ++i) {
		pos[suf[i]] = i;
	};
	int k = 0;
	for (int i = 0; i < n; ++i) {
		if (k > 0)
		{
			k--;
		};
		if (pos[i] == n - 1) {
			lcp[n - 1] = -1;
			k = 0;
		}
		else {
			int j = suf[pos[i] + 1];
			while ((max(i + k, j + k) < n) and (str[i + k] == str[j + k])) {
				k++;
			}
			lcp[pos[i]] = k;
		}
	}
	return lcp;
}

int main()
{
	string s, t;
	int slen, tlen;
	cin >> s;
	slen=s.length();
	s += "$";
	cin >> t;
	tlen=t.length();
	s += t;
	s += "#";
	long n = s.length();
	long long k;
	cin >> k;
	const int maxlen = 100000;
	const int alphabet = 256;
//начало построение суфмассива
	int p[maxlen], cnt[maxlen], c[maxlen];
	memset(cnt, 0, alphabet * sizeof(int));
	for (int i = 0; i < n; ++i)
		++cnt[s[i]];
	for (int i = 1; i < alphabet; ++i)
		cnt[i] += cnt[i - 1];
	for (int i = 0; i < n; ++i)
		p[--cnt[s[i]]] = i;
	c[p[0]] = 0;
	int classes = 1;
	for (int i = 1; i < n; ++i) {
		if (s[p[i]] != s[p[i - 1]])  ++classes;
		c[p[i]] = classes - 1;
	}

	int pn[maxlen], cn[maxlen];
	for (int h = 0; (1 << h) < n; ++h) {
		for (int i = 0; i < n; ++i) {
			pn[i] = p[i] - (1 << h);
			if (pn[i] < 0)  pn[i] += n;
		}
		memset(cnt, 0, classes * sizeof(int));
		for (int i = 0; i < n; ++i)
			++cnt[c[pn[i]]];
		for (int i = 1; i < classes; ++i)
			cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; --i)
			p[--cnt[c[pn[i]]]] = pn[i];
		cn[p[0]] = 0;
		classes = 1;
		for (int i = 1; i < n; ++i) {
			int mid1 = (p[i] + (1 << h)) % n, mid2 = (p[i - 1] + (1 << h)) % n;
			if (c[p[i]] != c[p[i - 1]] || c[mid1] != c[mid2])
				++classes;
			cn[p[i]] = classes - 1;
		}
		memcpy(c, cn, n * sizeof(int));
	}//здесь заканчивается построение суфмассива
/*	cout << s << endl;
	for (int i = 0; i < n; i++) {
		cout << p[i] << " ";
	}
	cout << endl;
	cout << "suffmas" << endl;
	for (int i = 0; i < n; ++i) {
		 cout << "For  i =" <<i<< " value p[i]=" << p[i] << " string:" ;
		for (int j = p[i]; j < s.length(); ++j) {
			   cout << s[j] << " ";
		}
		  cout << endl;
	}
	
	cout << "LCP: ";*/
	vector<int>lcpmas = buildLCP(s, p);//вызов построения lcp
	/*for (int i=0; i<n; ++i){
	    cout << lcpmas[i] << " ";
	}
	 cout << endl;*/
	long long flag=0, prevlcp=0, curlcp=0, i=0, diff=0, result=0;
	while (flag == 0) {
	if (((p[i] < slen) && (p[i+1] >= slen))  || ((p[i] >= slen) && (p[i+1] < slen))) { //slen-длина первой строки,если брать как индекс, то указывает на разделитель
		curlcp = lcpmas[i]; //записываем новое lcp только если по условию мы смотрим суффиксы из разных строк, поэтому внутри if-a
	if (curlcp>prevlcp) {
		result += curlcp-prevlcp;
		}
	prevlcp = curlcp; 
		
	} else {
		if (lcpmas[i]<prevlcp) {
			prevlcp=lcpmas[i];
		}
	}
			if (result >= k) {
					long lenout = lcpmas[i];
					if (result > k) {
						lenout -= (result - k);
					}
					for (long j=p[i]; j<=p[i]+lenout-1; ++j) {
						cout << s[j];
					}
				flag = 1;
			} //вывод, тут все очевидно и просто
		++i;
		if (i>n-1) { //если вылетели за пределы суфмаса то флаг на 2 и прога уйдет на печать -1
			flag = 2;
		}
	}
	if (flag == 2) {
	cout << "-1";
	}	
}
