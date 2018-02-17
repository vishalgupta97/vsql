#include<string>
#include<bitset>
#define SIZE 8192
class bloom_filter
{
public:std::bitset<SIZE> foo;
unsigned long hash_a(const char *s)
{
	unsigned long hash=5381;
	int c,i=0;
	while(c=s[i++])
		hash=hash*33+hash+c;
	return hash;
}
unsigned long hash_b(const char *s)
{
	unsigned long hash=5381;
	int c,i=0;
	while(c=s[i++])
		hash=(hash<<6)+(hash<<16)+c;
	return hash;
}
bool chk_hash(const char *s)
{
	unsigned long h1=hash_a(s);
	unsigned long h2=hash_b(s);
	unsigned long cnt=0;
	for(unsigned long n=0;n<7;n++)
	{
		unsigned long x=(h1+n*h2)%SIZE;
		if(foo[x])
			cnt++;
		else
			foo[x]=true;
	}
	if(cnt==7)
		return true;
	else
		return false;
}
};