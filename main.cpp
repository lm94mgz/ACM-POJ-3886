#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

typedef int factorial_order_type;
typedef unsigned long long factorial_value_type;

// 计算阶乘
factorial_value_type calc_factorial(factorial_order_type i)
{
	typedef map<factorial_order_type, factorial_value_type> cache_type;
	static cache_type cache;

	if (cache.find(i) != cache.end())
		return cache[i];

	factorial_order_type order = i;
	factorial_value_type value = i;
	while (--order > 0) value *= order;

	cache.insert(cache_type::value_type(i, value));
	return value;
}

typedef int block_count_type;
typedef vector<block_count_type> block_container;

// 每个迭代器表示一种积木的个数，函数用来计算这种排列的可能性：
// 排列的第一个元素必定是pos指向的那种积木的一个，必须要使用begin到end范围内的所有积木。
// 返回所有可能的排列数
factorial_value_type calc_permutation(block_container::const_iterator begin, block_container::const_iterator end, block_container::const_iterator pos)
{
	factorial_order_type sum_order = 0, temp;
	factorial_value_type divisor = 1;

	for (block_container::const_iterator it = begin; it != end; ++it)
	{
		temp = it == pos ? *it - 1 : *it;
		if (temp > 0)
		{
			sum_order += temp;
			divisor *= calc_factorial(temp);
		}
	}

	return calc_factorial(sum_order) / divisor;
}

int main()
{
	int count;
	cin >> count;

	while (count-- > 0)
	{
		block_container cache;
		cache.resize(26, 0);

		string input;
		cin >> input;

		for (string::iterator si = input.begin(); si != input.end(); ++si)
			cache[*si - 'A']++;

		factorial_value_type sum = 0;
		for (string::iterator si = input.begin(); si != input.end(); ++si)
		{
			block_container::iterator sbi = cache.begin() + (int)(*si - 'A');
			for (block_container::iterator bi = cache.begin(); bi != sbi; ++bi)
			{
				if (*bi > 0)
				{
					sum += calc_permutation(cache.begin(), cache.end(), bi);
				}
			}
			(*sbi)--;
		}

		cout << sum << endl;
	}

	return 0;
}
